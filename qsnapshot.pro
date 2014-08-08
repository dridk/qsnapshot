#-------------------------------------------------
#
# Project created by QtCreator 2014-08-04T20:13:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cutesnapshot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    previewwidget.cpp \
    abstractsnapshotwidget.cpp \
    areasnapshotwidget.cpp \
    fullsnapshotwidget.cpp

HEADERS  += mainwindow.h \
    previewwidget.h \
    abstractsnapshotwidget.h \
    areasnapshotwidget.h \
    fullsnapshotwidget.h

RESOURCES += \
    icons.qrc

