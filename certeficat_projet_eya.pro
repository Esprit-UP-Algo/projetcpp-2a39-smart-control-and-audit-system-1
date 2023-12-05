QT       += core gui serialport
QT       += sql
QT += printsupport
QT       += charts
QT += core gui widgets

# Include QZXing
QT       += core gui multimedia multimediawidgets
include(C:\Users\riahi\OneDrive\Desktop\new/src/qzxing.pri)
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
    arduino.cpp \
    certeficat.cpp \
    conection.cpp \
    main.cpp \
    interface_certeficat.cpp

HEADERS += \
    arduino.h \
    certeficat.h \
    conection.h \
    interface_certeficat.h

FORMS += \
    interface_certeficat.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
