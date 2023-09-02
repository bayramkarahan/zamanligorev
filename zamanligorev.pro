#-------------------------------------------------
#
# Project created by QtCreator 2023
#-------------------------------------------------

QT += widgets network core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zamanligorev
TEMPLATE = app


CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    singleinstance.cpp

HEADERS += \
        mainwindow.h \
    filecrud.h \
    singleinstance.h \
    hakkinda.h \
    giris.h \
    ayar.h


RESOURCES += \
    resources.qrc


DEFINES += QT_DEPRECATED_WARNINGS

target.path = /usr/bin

zamanligorevtray.files = zamanligorevtray
zamanligorevtray.path = /usr/bin

desktop_file.files = zamanligorev.desktop
desktop_file.path = /usr/share/applications/

icon.files = icons/zamanligorev.svg
icon.path = /usr/share/zamanligorev/

conf.files = zamanligorev.conf
conf.path = /usr/share/zamanligorev/

auto_start.files = autostartzamanligorevtray.desktop
auto_start.path = /etc/xdg/autostart/

servicescript.files = zamanligorevservicescript
servicescript.path = /usr/bin


service.files = zamanligorev.service
service.path = /etc/systemd/system/



INSTALLS += target desktop_file icon conf auto_start zamanligorevtray servicescript service

DISTFILES += \
   zamanligorev.conf\
    zamanligorev.desktop \
    autostartzamanligorevtray.desktop \
    zamanligorevtray \
    zamanligorevservicescript
