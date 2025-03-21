HEADERS += \
    $$PWD/audiostreamhandle.h \
    $$PWD/istreamhandle.h \
    $$PWD/mediaplayer.h \
    $$PWD/mediaplayerdef.h \
    $$PWD/videostreamhandle.h

SOURCES += \
    $$PWD/audiostreamhandle.cpp \
    $$PWD/istreamhandle.cpp \
    $$PWD/mediaplayer.cpp \
    $$PWD/videostreamhandle.cpp

DISTFILES +=

INCLUDEPATH += $$PWD/tools/

include(tools/tools.pri)
