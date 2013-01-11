#include "EFtpClient.hpp"
#include "EFtpMonitorInotify.hpp"
#include <QDir>

EFtpClient::EFtpClient() {
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
	new EFtpMonitorInotify(this, path);
	return true;
}

