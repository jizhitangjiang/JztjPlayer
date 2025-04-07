QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DESTDIR = $$PWD/../bin

INCLUDEPATH += $$PWD/../JztjPlayer

LIBS += -L$$PWD/../bin -lJztjPlayer

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui


