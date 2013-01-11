#include "EFtpMonitor.hpp"
#include "EFtpClient.hpp"

EFtpMonitor::EFtpMonitor(EFtpClient *_client, const QString &_path): QObject(_client) {
	client = _client;
	path = _path;
	connect(client, SIGNAL(monitorStop()), this, SLOT(deleteLater()));
}

