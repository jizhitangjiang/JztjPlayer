#ifndef ISTREAMHANDLE_H
#define ISTREAMHANDLE_H

#include "mediaplayerdef.h"
#include <functional>

class IStreamHandle
{
public:
    IStreamHandle(MediaPlayerContext *context);
    ~IStreamHandle();

protected:
    Decoder* createDecoder(int frameMaxSize);
    int openDecoder(Decoder *decoder, uint32_t streamIdex);
    int decodePacket(Decoder *decoder, AVFrame *frame);

protected:
    MediaPlayerContext *m_context{nullptr};
};

#endif // ISTREAMHANDLE_H
