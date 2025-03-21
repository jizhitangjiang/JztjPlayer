#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include "mediaplayerdef.h"

class MediaPlayer
{
public:
    MediaPlayer();
    ~MediaPlayer();

private:
    MediaPlayerContext *m_mediaPlayer{nullptr};
};

#endif // MEDIAPLAYER_H
