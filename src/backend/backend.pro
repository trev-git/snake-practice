QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++2a console

TEMPLATE = lib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Database/database.cpp

HEADERS += \
    Database/database.h

win32 {
    LIBS += \
        -IC:/msys64/mingw64/include \
        -LC:/msys64/mingw64/lib \
        -llibcrypto
} else {
    LIBS += \
        -L/usr/include -lcrypto
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
