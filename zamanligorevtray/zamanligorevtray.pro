#-------------------------------------------------
#
# Project created by QtCreator 2023
#-------------------------------------------------

QT += widgets network core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zamanligorevtray
TEMPLATE = app


CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
    filecrud.h \
        mainwindow.h


RESOURCES += \
    resources.qrc


DEFINES += QT_DEPRECATED_WARNINGS

target.path = /usr/bin

icon.files = icons/zamanligorev.svg
icon.path = /usr/share/icons

auto_start.files = autostartzamanligorevtray.desktop
auto_start.path = /etc/xdg/autostart/

INSTALLS += target icon  auto_start

DISTFILES += \
   zamanligorev.conf\
    autostartzamanligorevtray.desktop
