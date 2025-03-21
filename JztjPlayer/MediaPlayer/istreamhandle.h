#ifndef ISTREAMHANDLE_H
#define ISTREAMHANDLE_H

#include "mediaplayerdef.h"

class IStreamHandle
{
public:
    IStreamHandle(MediaPlayerContext *context);
    ~IStreamHandle();

    int openDecoder(int streamIdex);
    AVFrame* decodePacket(Decoder *decoder);

private:
    MediaPlayerContext *m_context{nullptr};
};

#endif // ISTREAMHANDLE_H
