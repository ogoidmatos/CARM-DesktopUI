QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    benchmarkmodal.cpp \
    interfacegpu.cpp \
    main.cpp \
    mainwindow.cpp \
    progressmodal.cpp \
    waitingspinnerwidget.cpp

HEADERS += \
    benchmarkdata.h \
    benchmarkmodal.h \
    dbmanager.h \
    interfacegpu.h \
    mainwindow.h \
    progressmodal.h \
    waitingspinnerwidget.h

FORMS += \
    mainwindow.ui

OTHER_FILES += carm-roofline/*

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
