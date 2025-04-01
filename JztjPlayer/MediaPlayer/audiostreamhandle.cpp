#include "audiostreamhandle.h"

static const int s_maxFrameQueueSize = 16;

void AudioStreamHandle::decodeThread()
{
    Decoder *decoder = m_context->audioDecoder;
    AVFrame *frame = av_frame_alloc();
    while (true) {
        int ret = decodePacket(decoder, frame);
        if (ret) {
            //todo
        }

        AVFrame *wFrame = decoder->frames->getWritableFrame();
        av_frame_move_ref(wFrame, frame);
        decoder->frames->pushWritableFrame();
        av_frame_unref(frame);
    }

    av_frame_free(&frame);
    return;
}

AudioStreamHandle::AudioStreamHandle(MediaPlayerContext *context)
    : IStreamHandle(context)

{

}

AudioStreamHandle::~AudioStreamHandle()
{

}

void AudioStreamHandle::openStream(int streamIndex)
{
    m_context->audioDecoder = IStreamHandle::createDecoder(s_maxFrameQueueSize);
    IStreamHandle::openDecoder(m_context->audioDecoder, streamIndex);

    m_decodeThread = std::thread(std::bind(&AudioStreamHandle::decodeThread, this));
    return;
}

void AudioStreamHandle::pushAVPacket(AVPacket *pkt)
{
    m_context->audioDecoder->pkts->pushPacket(pkt);
    return;
}
