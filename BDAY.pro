#-------------------------------------------------
#
# Project created by QtCreator 2019-05-27T19:29:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BDAY
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        database.cpp \
        dialog.cpp \
        forstr.cpp \
        main.cpp \
        mainwindow.cpp \
        removedialog.cpp \
        settings.cpp \
        showdialog.cpp

HEADERS += \
        database.h \
        dialog.h \
        forstr.h \
        mainwindow.h \
        removedialog.h \
        settheader.h \
        settings.h \
        showdialog.h \
        version.h

FORMS += \
        dialog.ui \
        mainwindow.ui \
        removedialog.ui \
        settings.ui \
        showdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
