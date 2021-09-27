QT += core gui multimedia opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = timeline
TEMPLATE = app

SOURCES += main.cpp \
            video_sample.cpp \
            timeline.cpp

HEADERS += video_sample.h \
            timeline.h

