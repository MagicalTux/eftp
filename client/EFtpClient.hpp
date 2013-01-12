#include <QObject>

class EFtpDatabase;

class EFtpClient: public QObject {
	Q_OBJECT;
public:
	EFtpClient();
	bool setPath(const QString &path);

public slots:
	void directoryCreated(const QString &path);
	void directoryDeleted(const QString &path);
	void fileCreated(const QString &path);
	void fileChanged(const QString &path);
	void fileAttrChanged(const QString &path);
	void fileDeleted(const QString &path);
	void fileRename(const QString &oldpath, const QString &newpath);

signals:
	void monitorStop(); // this signal will cause all monitors to die

private:
	QString path;
	EFtpDatabase *db;
};

