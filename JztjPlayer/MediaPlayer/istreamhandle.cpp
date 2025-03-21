#include "istreamhandle.h"

IStreamHandle::IStreamHandle(MediaPlayerContext *context)
{
    m_context = context;
}

IStreamHandle::~IStreamHandle()
{

}

int IStreamHandle::openDecoder(int streamIdex)
{
    if (streamIdex >= m_context->avfromat->nb_streams) {
        return -1;
    }

    AVStream *st = m_context->avfromat->streams[streamIdex];
    if (!st) {
        return 0;
    }

    AVCodecParameters *codecpar = st->codecpar
    return 0;
}

AVFrame *IStreamHandle::decodePacket(Decoder *decoder)
{

    return nullptr;
}
