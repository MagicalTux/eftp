#include "EFtpMonitor.hpp"
#include <QMap>

// maximum inotify events to read in one go
#define EFTP_INOTIFY_MAXREAD 64
#define EFTP_INOTIFY_MASK IN_ATTRIB | IN_CLOSE_WRITE | IN_CREATE | IN_DELETE | IN_DELETE_SELF | IN_MODIFY | IN_MOVE_SELF | IN_MOVED_FROM | IN_MOVED_TO | IN_DONT_FOLLOW | IN_EXCL_UNLINK

class QSocketNotifier;
struct inotify_event;

class EFtpMonitorInotify: public EFtpMonitor {
	Q_OBJECT;
public:
	EFtpMonitorInotify(EFtpClient *client, const QString &path);

public slots:
	void activity(int fd);

private:
	void init_watch(const QString &p);
	void handle_event(struct inotify_event*);

	int fd;
	QSocketNotifier *fdn;
	QMap<int,QString> wd; // watch descriptors
	
	quint32 rename_cookie;
	int rename_mask;
	QString rename_oldname;
//	QMap<int,QString> cookie; // for rename
};

