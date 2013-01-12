#include "EFtpClient.hpp"
#include "EFtpMonitorInotify.hpp"
#include <EFtpDatabase.hpp>
#include <QDir>
#ifdef EFTP_COMPAT_STDPATH
# include <QDesktopServices>
#else
# include <QStandardPaths>
#endif

EFtpClient::EFtpClient() {
#ifdef EFTP_COMPAT_STDPATH
	db = new EFtpDatabase(QDesktopServices::storageLocation(QDesktopServices::CacheLocation)+"/eftp.db", this);
#else
	db = new EFtpDatabase(QStandardPaths::writableLocation(QStandardPaths::CacheLocation)+"/eftp.db", this);
#endif
	qDebug("EFtpClient: hi");
}

bool EFtpClient::setPath(const QString &_path) {
	QDir d(_path);
	if (!d.exists()) {
		d.mkpath(".");
		if (!d.exists()) return false;
	}
	monitorStop();
	path = _path;
	EFtpMonitor *mon = new EFtpMonitorInotify(this, path);
	connect(mon, SIGNAL(directoryCreated(const QString&)), this, SLOT(directoryCreated(const QString&)));
	connect(mon, SIGNAL(directoryDeleted(const QString&)), this, SLOT(directoryDeleted(const QString&)));
	connect(mon, SIGNAL(fileCreated(const QString&)), this, SLOT(fileCreated(const QString&)));
	connect(mon, SIGNAL(fileChanged(const QString&)), this, SLOT(fileChanged(const QString&)));
	connect(mon, SIGNAL(fileAttrChanged(const QString&)), this, SLOT(fileAttrChanged(const QString&)));
	connect(mon, SIGNAL(fileDeleted(const QString&)), this, SLOT(fileDeleted(const QString&)));
	connect(mon, SIGNAL(fileRename(const QString&,const QString&)), this, SLOT(fileRename(const QString&,const QString&)));
	mon->rescan();
	return true;
}

void EFtpClient::directoryCreated(const QString &path) {
	qDebug("directoryCreated(%s)", qPrintable(path));
}

void EFtpClient::directoryDeleted(const QString &path) {
	qDebug("directoryDeleted(%s)", qPrintable(path));
}

void EFtpClient::fileCreated(const QString &path) {
	qDebug("fileCreated(%s)", qPrintable(path));
}

void EFtpClient::fileChanged(const QString &path) {
	qDebug("fileChanged(%s)", qPrintable(path));
}

void EFtpClient::fileAttrChanged(const QString &path) {
	qDebug("fileAttrChanged(%s)", qPrintable(path));
}

void EFtpClient::fileDeleted(const QString &path) {
	qDebug("fileDeleted(%s)", qPrintable(path));
}

void EFtpClient::fileRename(const QString &oldpath, const QString &newpath) {
	qDebug("fileRename(%s,%s)", qPrintable(oldpath), qPrintable(newpath));
}

