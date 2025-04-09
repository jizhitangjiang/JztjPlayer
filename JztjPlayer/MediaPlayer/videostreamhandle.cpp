#include "videostreamhandle.h"

static const int s_maxFrameQueueSize = 3;

VideoStreamHandle::VideoStreamHandle(MediaPlayerContext *context)
    : IStreamHandle(context)
{

}

VideoStreamHandle::~VideoStreamHandle()
{

}

void VideoStreamHandle::openStream(int streamIndex)
{
    m_context->videoDecoder = IStreamHandle::createDecoder(s_maxFrameQueueSize);
    IStreamHandle::openDecoder(m_context->videoDecoder, streamIndex);

    m_decodeThread = std::thread(std::bind(&VideoStreamHandle::decodeThread, this));
    m_renderThread = std::thread(std::bind(&VideoStreamHandle::renderThread, this));
}

void VideoStreamHandle::pushAVPacket(AVPacket *pkt)
{
    m_context->videoDecoder->pkts->pushPacket(pkt);
    return;
}

void VideoStreamHandle::decodeThread()
{
    Decoder *decoder = m_context->videoDecoder;
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

void VideoStreamHandle::renderThread()
{
    Decoder *decoder = m_context->videoDecoder;
    while (true) {
        AVFrame *rFrame = decoder->frames->getReadableFrame();
        m_context->videoDataCallback(rFrame->width, rFrame->height,
                                     rFrame->linesize[0], rFrame->linesize[1], rFrame->linesize[2],
                                     rFrame->data[0], rFrame->data[1], rFrame->data[2],
                                      m_context->videoDataObj);
        decoder->frames->pushReadableFrame();
        av_frame_unref(rFrame);
    }

}
