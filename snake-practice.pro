QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++2a console

TEMPLATE = subdirs

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SUBDIRS += \
    backend \
    frontend

INCLUDEPATH += \
    /usr/include/openssl

LIBS += \
    -L/usr/lib/openssl \
    -lcrypto

backend.subdir = src/backend
frontend.subdir = src/frontend

frontend.depends = backend

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/src/backend/release/ -lbackend
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/src/backend/debug/ -lbackend
else:unix: LIBS += -L$$OUT_PWD/src/backend/ -lbackend

INCLUDEPATH += $$PWD/src/backend
DEPENDPATH += $$PWD/src/backend
