#include "jztjplayer.h"


JztjPlayer::JztjPlayer()
{
    m_mediaPlayer = new MediaPlayer;
}

JztjPlayer::~JztjPlayer()
{

}

void JztjPlayer::setVideoYUVDataCallback(VideoYUVDataCallback callback, void *obj)
{
    m_mediaPlayer->setVideoYUVDataCallback(callback, obj);
}

int JztjPlayer::openMediaFile(const std::string &fileName)
{
    int ret = m_mediaPlayer->openFile(fileName);
    return ret;
}

IJZTJPlayer *createIJZTJPlayer()
{
    return new JztjPlayer();
}
