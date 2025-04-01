#include "istreamhandle.h"

IStreamHandle::IStreamHandle(MediaPlayerContext *context)
{
    m_context = context;
}

IStreamHandle::~IStreamHandle()
{

}

Decoder* IStreamHandle::createDecoder(int frameMaxSize)
{
    Decoder *decoder = new Decoder;
    decoder->frames = new FrameQueue;
    decoder->pkts = new PacketQueue;

    decoder->frames->init(frameMaxSize);
    return decoder;
}

int IStreamHandle::openDecoder(Decoder *decoder, int streamIdex)
{
    if (streamIdex >= m_context->avfromat->nb_streams) {
        return -1;
    }

    AVStream *st = m_context->avfromat->streams[streamIdex];
    if (!st) {
        return -2;
    }

    AVCodecParameters *codecpar = st->codecpar;
    if (!codecpar) {
        return -3;
    }

    const AVCodec *codec = avcodec_find_decoder(codecpar->codec_id);
    if (!codec) {
        return -4;
    }

    AVCodecContext *codecContext = avcodec_alloc_context3(codec);
    if (!codec) {
        return -5;
    }

    int ret = avcodec_open2(codecContext, codec, nullptr);
    if (ret) {
        return -6;
    }

    decoder->context = codecContext;
    return 0;
}

int IStreamHandle::decodePacket(Decoder *decoder, AVFrame *frame)
{
    if (!decoder) {
        return -1;
    }

    AVPacket pkt;
    int ret = AVERROR(EAGAIN);

    while (1) {
        do {
            ret = avcodec_receive_frame(decoder->context, frame);
            if (ret >= 0) {
                return 0;
            }

            if (ret == AVERROR_EOF) {
                return 1;
            }

        }while(ret != AVERROR(EAGAIN));

        decoder->pkts->getPacket(&pkt);
        avcodec_send_packet(decoder->context, &pkt);
        av_packet_unref(&pkt);
    }

    return 0;
}
