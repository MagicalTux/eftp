#include "EFtpDatabase.hpp"
#include <QCoreApplication>

EFtpDatabase::EFtpDatabase(const QString &path, QObject *parent): QObject(parent) {
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(path);
	if (!db.open()) {
		qDebug("Failed to open database %s, can't work", qPrintable(path));
		QCoreApplication::exit(1);
		return;
	}
	qDebug("EFtpDatabase: located at %s", qPrintable(path));
}


