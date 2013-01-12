#include "EFtpDatabase.hpp"

EFtpDatabase::EFtpDatabase(const QString &path, QObject *parent): QObject(parent) {
	db = QSqlDatabase::addDatabase("QSQLITE");
	qDebug("here");
}


