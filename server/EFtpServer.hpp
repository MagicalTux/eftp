#include <QTcpServer>

class EFtpDatabase;

class EFtpServer: public QTcpServer {
	Q_OBJECT;
public:
	EFtpServer(quint16 port);

private:
	EFtpDatabase *db;
};

