#include <QObject>

class EFtpClient: public QObject {
	Q_OBJECT;
public:
	EFtpClient();
	bool setPath(const QString &path);

signals:
	void monitorStop(); // this signal will cause all monitors to die

private:
	QString path;
};

