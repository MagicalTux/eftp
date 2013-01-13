#include <QCoreApplication>
#include "EFtpServer.hpp"

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);

	QCoreApplication::setApplicationName("eftp-server");
	QCoreApplication::setOrganizationName("eftp");
	QCoreApplication::setOrganizationDomain("eftp.net");

	EFtpServer s(16543);

	return app.exec();
}

