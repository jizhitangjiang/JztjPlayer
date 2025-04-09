#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include "mediaplayerdef.h"

#include "audiostreamhandle.h"
#include "videostreamhandle.h"

class MediaPlayer
{
public:
    MediaPlayer();
    ~MediaPlayer();

    void setVideoYUVDataCallback(VideoYUVDataCallback callback, void *obj);
    int openFile(const std::string &fileName);

private:
    void readThread();

private:
    MediaPlayerContext *m_mediaPlayer{nullptr};
    AudioStreamHandle *m_audioStream{nullptr};
    VideoStreamHandle *m_videoStream{nullptr};

    std::thread m_readThread;
};

#endif // MEDIAPLAYER_H
