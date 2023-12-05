QT       += core gui sql printsupport serialport charts xml opengl network
QT += core serialport
QT       += core gui sql
QT       += sql
QT       += printsupport
QT += widgets svg
QT += opengl
QT += xml
QT       += core gui sql printsupport multimedia multimediawidgets charts svg network axcontainer widgets serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    connection.cpp \
    rapport.cpp \
    arduino.cpp \
    qrcode.cpp \
qrcodegen.cpp \
formateur.cpp \
popup.cpp \
rechercher.cpp \
employe.cpp \
smtp.cpp \
trier.cpp
HEADERS += \
    mainwindow.h \
    connection.h \
    rapport.h \
    arduino.h \
    qrcode.h \
qrcodegen.h \
formateur.h \
popup.h \
employe.h \
smtp.h \


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
