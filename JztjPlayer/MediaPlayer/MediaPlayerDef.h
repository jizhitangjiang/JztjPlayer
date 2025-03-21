#ifndef MEDIAPLAYERDEF_H
#define MEDIAPLAYERDEF_H

#include <string>
#include "framequeue.h"
#include "packetqueue.h"

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

struct Decoder
{
    AVCodecContext *context{nullptr};

    PacketQueue *pkts{nullptr};

    FrameQueue  *frames{nullptr};
};

struct MediaPlayerContext
{
    std::string fileName;   //视频地址

    AVFormatContext *avfromat{nullptr};

    Decoder *audioDecoder{nullptr};
    Decoder *videoDecoder{nullptr};
};

#endif // MEDIAPLAYERDEF_H
