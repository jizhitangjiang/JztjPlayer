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

using VideoYUVDataCallback = void(*)(int w, int h, int yStride, int uStride, int vStride,
                                     uint8_t *yData, uint8_t *uData, uint8_t *vData, void *obj);

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

    void                 *videoDataObj{nullptr};
    VideoYUVDataCallback videoDataCallback{nullptr};
};

#endif // MEDIAPLAYERDEF_H
