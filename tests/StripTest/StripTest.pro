#-------------------------------------------------
#
# Project created by QtCreator 2013-07-29T09:40:38
#
#-------------------------------------------------

QT       += core

QT       += gui
QT       += xml

CONFIG   += console
CONFIG   -= app_bundle

TARGET = StripTest

DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += APP_NAME=\\\"$$TARGET\\\"
DEFINES += ORG_NAME=\\\"Phonations\\\"

TEMPLATE = app

include(../../libs/PhTools/PhTools.pri)
include(../../libs/PhStrip/PhStrip.pri)

INCLUDEPATH += ../../libs

#Main app
SOURCES += main.cpp \
