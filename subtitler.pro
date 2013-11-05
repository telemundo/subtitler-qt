#-------------------------------------------------
#
# Project created by QtCreator 2013-11-05T14:48:29
#
#-------------------------------------------------

QT      += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = Subtitler

TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp

HEADERS += mainwindow.h

FORMS   += mainwindow.ui

app_bundle {
    ICON = subtitler.icns
}

win32 {
    RC_FILE = subtitler.rc
}

debug {
    message( $$CONFIG )
}
