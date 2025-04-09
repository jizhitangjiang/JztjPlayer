#ifndef VIDEOSTREAMHANDLE_H
#define VIDEOSTREAMHANDLE_H

#include "istreamhandle.h"

class VideoStreamHandle : public IStreamHandle
{
public:
    VideoStreamHandle(MediaPlayerContext *context);
    ~VideoStreamHandle();

    void openStream(int streamIndex);
    void pushAVPacket(AVPacket *pkt);

private:
    void decodeThread();
    void renderThread();

public:
    std::thread m_renderThread;
    std::thread m_decodeThread;
};

#endif // VIDEOSTREAMHANDLE_H
