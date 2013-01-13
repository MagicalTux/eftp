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

	if (!tables.contains("inode")) {
		db.exec("CREATE TABLE `inode` (`inode_id` INT PRIMARY KEY NOT NULL, `parent_inode_id` INT NOT NULL, `name` VARCHAR(255) NOT NULL, `type` CHAR(1) NOT NULL, `chmod` INT NOT NULL, `size` BIGINT NOT NULL, `created` BIGINT NOT NULL, `modified` BIGINT NOT NULL, `deleted` BIGINT, `impl` BIGINT)");
		db.exec("CREATE UNIQUE INDEX `inode_name` ON `inode`(`parent_inode_id`,`name`)");
	}
	if (!tables.contains("block")) {
		db.exec("CREATE TABLE `block` (`block_id` INT PRIMARY KEY NOT NULL, `inode_id` INT NOT NULL, `offset` INT NOT NULL, `block_hash` CHAR(40) NOT NULL, `modified` BIGINT NOT NULL)");
		db.exec("CREATE UNIQUE INDEX `block_offset` ON `block`(`inode_id`,`offset`)");
	}
}


