#-------------------------------------------------
#
# Project created by QtCreator 2023
#-------------------------------------------------

QT += widgets core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zamanligorevgui
TEMPLATE = app


CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
    hakkinda.h \
    giris.h


RESOURCES += \
    resources.qrc


DEFINES += QT_DEPRECATED_WARNINGS

target.path = /usr/bin

desktop_file.files = zamanligorevgui.desktop
desktop_file.path = /usr/share/applications/

icon.files = icons/zamanligorev.svg
icon.path = /usr/share/icons/

conf.files = zamanligorev.conf
conf.path = /usr/share/zamanligorev/


INSTALLS += target desktop_file icon conf

DISTFILES += \
   zamanligorev.conf\
    zamanligorevgui.desktop
