#include "EFtpServer.hpp"
#include <EFtpDatabase.hpp>
#include <QDir>
#ifdef EFTP_COMPAT_STDPATH
# include <QDesktopServices>
#else
# include <QStandardPaths>
#endif

EFtpServer::EFtpServer(quint16) {
#ifdef EFTP_COMPAT_STDPATH
	QDir db_path(QDesktopServices::storageLocation(QDesktopServices::CacheLocation));
#else
	QDir db_path(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
#endif
	db_path.mkpath("."); // ensure path exists
	db = new EFtpDatabase(db_path.filePath("master.db"), this);
}

