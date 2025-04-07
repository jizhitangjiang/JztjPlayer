#include "jztjplayer.h"


JztjPlayer::JztjPlayer()
{
    m_mediaPlayer = new MediaPlayer;
}

JztjPlayer::~JztjPlayer()
{

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
