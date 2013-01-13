#include "EFtpDatabase.hpp"
#include <QCoreApplication>
#include <QStringList>
#include <QSqlQuery>

EFtpDatabase::EFtpDatabase(const QString &path, QObject *parent): QObject(parent) {
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(path);
	if (!db.open()) {
		qDebug("Failed to open database %s, can't work", qPrintable(path));
		QCoreApplication::exit(1);
		return;
	}
	qDebug("EFtpDatabase: located at %s", qPrintable(path));

	QStringList tables = db.tables();

	if (!tables.contains("dir")) {
		db.exec("CREATE TABLE `dir` (`dir` INT PRIMARY KEY NOT NULL, `parent_dir_id` INT NOT NULL, `name` VARCHAR(128) NOT NULL, `chmod` INT NOT NULL, `created` INT NOT NULL, `modified` INT NOT NULL, `deleted` INT, `impl` INT)");
		db.exec("CREATE UNIQUE INDEX `dir_name` ON `dir`(`parent_dir_id`,`name`)");
	}
}


