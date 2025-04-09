#include "mediaplayer.h"

int interruptCallback(void* opaque)
{
    return 0;
}

MediaPlayer::MediaPlayer()
{
    m_mediaPlayer = new MediaPlayerContext;
}

MediaPlayer::~MediaPlayer()
{

}

void MediaPlayer::setVideoYUVDataCallback(VideoYUVDataCallback callback, void *obj)
{
    m_mediaPlayer->videoDataCallback = callback;
    m_mediaPlayer->videoDataObj = obj;
}

int MediaPlayer::openFile(const std::string &fileName)
{
    if (fileName.empty()) {
        return -1;
    }

    m_mediaPlayer->fileName = fileName;
    m_readThread = std::thread(std::bind(&MediaPlayer::readThread, this));
    return 0;
}

void MediaPlayer::readThread()
{
    m_mediaPlayer->avfromat = avformat_alloc_context();

    AVFormatContext *ic = m_mediaPlayer->avfromat;
    ic->interrupt_callback.callback = interruptCallback;
    ic->interrupt_callback.opaque = m_mediaPlayer;

    int ret = avformat_open_input(&ic, m_mediaPlayer->fileName.c_str(), nullptr, nullptr);
    if (ret < 0) {
        //todo
    }

    avformat_find_stream_info(ic, nullptr);
    av_dump_format(ic, 0, NULL, 0);

    int audioStreamIndex = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
    int videoStreamIndex = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);

    if (audioStreamIndex >= 0) {
//        m_audioStream = new AudioStreamHandle(m_mediaPlayer);
//        m_audioStream->openStream(audioStreamIndex);
    }

    if (videoStreamIndex >= 0) {
        m_videoStream = new VideoStreamHandle(m_mediaPlayer);
        m_videoStream->openStream(videoStreamIndex);
    }

    AVPacket pkt;
    while (true) {
        ret = av_read_frame(ic, &pkt);
        if (ret < 0) {
            //todo
        }

        if (pkt.stream_index == audioStreamIndex) {
           // m_audioStream->pushAVPacket(&pkt);
        } else if (pkt.stream_index == videoStreamIndex) {
            m_videoStream->pushAVPacket(&pkt);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
