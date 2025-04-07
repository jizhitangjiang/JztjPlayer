#ifndef JZTJPLAYER_H
#define JZTJPLAYER_H

#include "IJZTJPlayer.h"
#include "mediaplayer/mediaplayer.h"

class JztjPlayer : public IJZTJPlayer
{
public:
    JztjPlayer();
    ~JztjPlayer();

public:
    int openMediaFile(const std::string &fileName) override;

private:
    MediaPlayer *m_mediaPlayer{nullptr};
};

#endif // JZTJPLAYER_H
