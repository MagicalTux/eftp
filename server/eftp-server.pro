######################################################################
# Automatically generated by qmake (2.01a) Sun Jan 13 12:56:32 2013
######################################################################

TEMPLATE = app
TARGET = ../eftp-server
DEPENDPATH += .
INCLUDEPATH += .

!contains(QT_VERSION, ^4\\..*) {
	QT -= gui
} else {
	DEFINES += EFTP_COMPAT_STDPATH
}
QT += network sql

INCLUDEPATH += ../common/

# Input
HEADERS += EFtpServer.hpp ../common/EFtpDatabase.hpp
SOURCES += cli.cpp EFtpServer.cpp ../common/EFtpDatabase.cpp