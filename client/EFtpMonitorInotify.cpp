#include "EFtpMonitorInotify.hpp"
#include <QSocketNotifier>
#include <QDir>
#include <sys/inotify.h>

// Yep, Qt has a QFileSystemWatcher that uses inotify too, but it's too vague
// when returning events, making it not suitable for us (maybe later)

EFtpMonitorInotify::EFtpMonitorInotify(EFtpClient *_client, const QString &_path): EFtpMonitor(_client, _path) {
	rename_cookie = 0;
	fd = inotify_init1(IN_NONBLOCK | IN_CLOEXEC);
	fdn = new QSocketNotifier(fd, QSocketNotifier::Read, this);
	connect(fdn, SIGNAL(activated(int)), this, SLOT(activity(int)));
	init_watch(path);
}

void EFtpMonitorInotify::handle_event(struct inotify_event *ev) {
	if (ev->mask & IN_Q_OVERFLOW) init_watch(path);
	if (ev->wd == -1) return; // case of IN_Q_OVERFLOW

	if (!wd.contains(ev->wd)) {
		qDebug("even with unknown wd %d", ev->wd);
		inotify_rm_watch(fd, ev->wd); // remove it, just in case
		return;
	}

	QString name;
	if (ev->len > 0) name = QString::fromUtf8(ev->name);

	if ((ev->mask & IN_CREATE) && (ev->mask & IN_ISDIR)) {
		// new dir, we need to listen to it!
		init_watch(path+wd.value(ev->wd)+"/"+name);
		directoryCreated(wd.value(ev->wd)+"/"+name);
	} else if (ev->mask & IN_CREATE) {
		// created something else than a dir
		fileCreated(wd.value(ev->wd)+"/"+name);
	}

	if (ev->mask & IN_CLOSE_WRITE) {
		fileChanged(wd.value(ev->wd)+"/"+name);
	}

	if ((ev->mask & IN_DELETE) && (ev->mask & IN_ISDIR)) {
		directoryDeleted(wd.value(ev->wd)+"/"+name);
	} else if (ev->mask & IN_DELETE) {
		fileDeleted(wd.value(ev->wd)+"/"+name);
	}

	if (ev->mask & IN_DELETE_SELF) {
		directoryDeleted(wd.value(ev->wd));
	}

	if (ev->mask & IN_MODIFY) {
		fileChanged(wd.value(ev->wd)+"/"+name);
	}

	if (ev->mask & IN_ATTRIB) {
		fileAttrChanged(wd.value(ev->wd)+"/"+name);
	}

	if (ev->mask & IN_MOVED_TO) {
		if (rename_cookie == ev->cookie) {
			fileRename(rename_oldname, wd.value(ev->wd)+"/"+name);

			if (ev->mask & IN_ISDIR) {
				QString p = wd.value(ev->wd)+"/"+name;
				int res = inotify_add_watch(fd, p.toUtf8().constData(), EFTP_INOTIFY_MASK);
				// should return the same id as before
				if (!wd.contains(res)) qDebug("hm, weird");
				wd.insert(res, p.mid(path.size())); // insert will replace value
			}

			rename_cookie = 0;
		} else if (ev->mask & IN_ISDIR) {
			init_watch(path+wd.value(ev->wd)+"/"+name); // force rescan of this dir
		}
	} else if (rename_cookie != 0) {
		qDebug("rename from without rename to, probably a rename to outside (ie. a delete for us)");
		if (rename_mask & IN_ISDIR) {
			directoryDeleted(rename_oldname);
		} else {
			fileDeleted(rename_oldname);
		}
		rename_cookie = 0;
	}

	if (ev->mask & IN_MOVED_FROM) { // *IMPORTANT* must be set after IN_MOVED_TO
		rename_cookie = ev->cookie;
		rename_mask = ev->mask;
		rename_oldname = wd.value(ev->wd)+"/"+name;
	}

	if (ev->mask & IN_MOVE_SELF) {
		QDir dir(wd.value(ev->wd));
		if (!dir.exists()) {
			// lost track of this, remove!
			inotify_rm_watch(fd, ev->wd);
			ev->mask |= IN_IGNORED; // ensures removal of wd
		}
	}

//	qDebug("Got a inotify event, name %s/%s (cookie %d)!", qPrintable(wd.value(ev->wd)), qPrintable(name), ev->cookie);

	if (ev->mask & IN_IGNORED) { // *IMPORTANT* Keep me last in line, or face consequences!
		// that wd is being removed
		wd.remove(ev->wd);
	}
}

void EFtpMonitorInotify::activity(int _fd) {
	if (_fd != fd) return; // should be equal, always
	// we'll be called again if we didn't read enough, but maybe loop on this?
	struct inotify_event *e;
	char buf[sizeof(*e)*EFTP_INOTIFY_MAXREAD];

	int res = read(fd, &buf, sizeof(buf)); // kernel guarantees that no event is truncated
	if (res == -1) {
		qDebug("event read failed");
		return;
	}
	int pos = 0;
	while(pos < res) {
		e = (struct inotify_event*)&buf[pos];
		handle_event(e);
		pos += sizeof(*e)+e->len;
	}
}

void EFtpMonitorInotify::init_watch(const QString &p) {
	qDebug("scanning: %s", qPrintable(p));
	int res = inotify_add_watch(fd, p.toUtf8().constData(), EFTP_INOTIFY_MASK);
	if (res == -1) {
		qDebug("inotify_add_watch failed");
		return;
	}
	wd.insert(res, p.mid(path.size()));

	// scan directory for directories
	QDir dp(p);
	QStringList l = dp.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden);

	for(int i = 0; i < l.size(); i++) init_watch(dp.filePath(l.at(i)));
}

