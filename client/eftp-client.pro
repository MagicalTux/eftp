######################################################################
# Automatically generated by qmake (2.01a) Fri Jan 11 21:37:52 2013
######################################################################

TEMPLATE = app
TARGET = ../eftp-client
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
HEADERS += EFtpClient.hpp EFtpMonitor.hpp EFtpMonitorInotify.hpp ../common/EFtpDatabase.hpp
SOURCES += cli.cpp EFtpClient.cpp EFtpMonitor.cpp EFtpMonitorInotify.cpp ../common/EFtpDatabase.cpp
