#include <QCoreApplication>
#include "EFtpClient.hpp"

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);

	QCoreApplication::setApplicationName("eftp-client");
	QCoreApplication::setOrganizationName("eftp");
	QCoreApplication::setOrganizationDomain("eftp.net");

	EFtpClient e;
	e.setPath("/tmp/eftp");

	return app.exec();
}

