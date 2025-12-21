QT -= gui
TARGET = zamanligorevservice

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        servis.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Database.h \
    servis.h

target.path = /usr/bin

service.files = zamanligorev.service
service.path = /etc/systemd/system/

serviceconf.files = zamanligorev.json
serviceconf.path = /usr/share/zamanligorev/

sessionlock.files = sessionlockzg
sessionlock.path = /usr/bin/

INSTALLS += target service serviceconf sessionlock

DISTFILES += zamanligorev.service
