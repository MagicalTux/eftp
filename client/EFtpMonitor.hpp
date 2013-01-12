#include <QObject>

class EFtpClient;

class EFtpMonitor: public QObject {
	Q_OBJECT;
public:
	EFtpMonitor(EFtpClient *client, const QString &path);
	virtual void rescan() = 0; // needs to be called at least once

signals:
	void directoryCreated(const QString &path);
	void directoryDeleted(const QString &path);
	void fileCreated(const QString &path);
	void fileChanged(const QString &path);
	void fileAttrChanged(const QString &path);
	void fileDeleted(const QString &path);
	void fileRename(const QString &oldpath, const QString &newpath);

protected:
	EFtpClient *client;
	QString path;
};

