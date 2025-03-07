QT -= gui

TEMPLATE = lib
DEFINES += JZTJPLAYER_LIBRARY

CONFIG += c++11

ROOT_PATH = $$PWD/../

SOURCES += \
    jztjplayer.cpp

HEADERS += \
    JztjPlayer_global.h \
    jztjplayer.h

LIBS += -L$$ROOT_PATH/3rdparty/win64/ffmpeg-5.1.2/lib\
    -lavcodec -lavdevice -lavfilter -lavformat -lavutil -swresample -lswscale
