#ifndef AUDIOSTREAMHANDLE_H
#define AUDIOSTREAMHANDLE_H

#include "istreamhandle.h"

class AudioStreamHandle : public IStreamHandle
{
public:
    AudioStreamHandle(MediaPlayerContext *context);
    ~AudioStreamHandle();

    void openStream(int streamIndex);
    void pushAVPacket(AVPacket *pkt);

private:
    void decodeThread();

public:
    std::thread m_decodeThread;
};

#endif // AUDIOSTREAMHANDLE_H
