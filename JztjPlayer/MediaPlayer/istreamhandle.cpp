#include "istreamhandle.h"

IStreamHandle::IStreamHandle(MediaPlayerContext *context)
{
    m_context = context;
}

IStreamHandle::~IStreamHandle()
{

}

int IStreamHandle::openDecoder(Decoder *decoder, int streamIdex)
{
    if (streamIdex >= m_context->avfromat->nb_streams) {
        return -1;
    }

    AVStream *st = m_context->avfromat->streams[streamIdex];
    if (!st) {
        return -1;
    }

    AVCodecParameters *codecpar = st->codecpar;
    if (!codecpar) {
        return -2;
    }

    const AVCodec *codec = avcodec_find_decoder(codecpar->codec_id);
    if (!codec) {
        return -3;
    }

    AVCodecContext *codecContext = avcodec_alloc_context3(codec);
    if (!codec) {
        return -4;
    }

    int ret = avcodec_open2(codecContext, codec, nullptr);
    if (ret) {
        return -5;
    }

    decoder->context = codecContext;
    return 0;
}

AVFrame *IStreamHandle::decodePacket(Decoder *decoder)
{

    return nullptr;
}
