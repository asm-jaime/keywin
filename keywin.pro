#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T21:09:55
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = keywin
TEMPLATE = app


SOURCES += main.cpp \
    keywidget.cpp \
    keywindow.cpp \
    wigglywidget.cpp

HEADERS  += \
    keywidget.h \
    keywindow.h \
    wigglywidget.h \
    buffer.h

FORMS    += \
    keywindow.ui

TRANSLATIONS = spreadsheet_en.ts \
               spreadsheet_ru.ts

DISTFILES +=

RESOURCES += \
    keyresource.qrc
