TEMPLATE = lib
DEFINES += JZTJPLAYER_LIBRARY

CONFIG += c++11

ROOT_PATH = $$PWD/../

HEADERS += \
    IJZTJPlayer.h \
    jztjplayer.h

SOURCES += \
    jztjplayer.cpp


INCLUDEPATH += $$ROOT_PATH/3rdparty/win64/ffmpeg-5.1.2/include

LIBS += -L$$ROOT_PATH/3rdparty/win64/ffmpeg-5.1.2/lib\
    -lavcodec -lavdevice -lavfilter -lavformat -lavutil -swresample -lswscale


include(mediaplayer/mediaplayer.pri)
