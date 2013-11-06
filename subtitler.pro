QT      += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = Subtitler
VERSION  = 2.0
TEMPLATE = app

# Application icons
mac:ICON = subtitler.icns
win32:RC_FILE = subtitler.rc

SOURCES += main.cpp \
           mainwindow.cpp

HEADERS += mainwindow.h

FORMS   += mainwindow.ui

# Define the preprocessor macro to get the application version in our application.
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# Include the Fervor library (autoupdater)
!include("lib/fervor/Fervor.pri") {
    error("Unable to include Fervor. Try running `git submodule update --init --recursive`")
}

# Debugging information
debug {
    message($$CONFIG)
}
