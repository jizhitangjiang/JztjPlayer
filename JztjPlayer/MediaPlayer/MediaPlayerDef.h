#ifndef MEDIAPLAYERDEF_H
#define MEDIAPLAYERDEF_H

extern "C" {
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libswresample/swresample.h"
#include "libswscale/swscale.h"
}

struct MyPacket
{
    AVPacket pkt;
};

struct MyFrame
{
    AVFrame *frame;
};
#endif // MEDIAPLAYERDEF_H
