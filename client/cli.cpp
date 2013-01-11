#include <QCoreApplication>
#include "EFtpClient.hpp"

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);

	EFtpClient e;
	e.setPath("/tmp/eftp");

	return app.exec();
}

