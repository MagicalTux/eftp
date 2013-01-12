#include <QObject>
#include <QSqlDatabase>

class EFtpDatabase: public QObject {
	Q_OBJECT;
public:
	EFtpDatabase(const QString &path, QObject *parent = 0); // path to db file

private:
	QSqlDatabase db;
};

