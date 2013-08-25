#-------------------------------------------------
#
# Project created by QtCreator 2013-08-01T12:25:30
#
#-------------------------------------------------

QT	+= core gui
QT	+= xml
QT	+=multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4):

TARGET = GraphicTest
TEMPLATE = app

JOKER_ROOT = $${_PRO_FILE_PWD_}/../..

INCLUDEPATH += $${JOKER_ROOT}/libs

include($${JOKER_ROOT}/libs/PhTools/PhTools.pri)
include($${JOKER_ROOT}/libs/PhGraphic/PhGraphic.pri)

HEADERS  += MainWindow.h \
	GraphicTestView.h \
    ../../libs/PhTools/PhColor.h \

SOURCES += main.cpp\
        MainWindow.cpp \
	GraphicTestView.cpp \
    ../../libs/PhTools/PhColor.cpp \

# Windows specific
win32 {
	RESOURCES_PATH = .
}

# Ubuntu specific
linux {
	RESOURCES_PATH = .
}


# MacOS specific
mac {
	RESOURCES_PATH = $${TARGET}.app/Contents/MacOS
}

QMAKE_POST_LINK += echo $${RESOURCES_PATH}
QMAKE_POST_LINK += && cp $${JOKER_ROOT}/data/img/look.png $${RESOURCES_PATH}
QMAKE_POST_LINK += && cp $${JOKER_ROOT}/data/fonts/Bedizen.ttf $${RESOURCES_PATH}



