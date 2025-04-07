#ifndef IJZTJPLAYER_H
#define IJZTJPLAYER_H

#include <string>

#if defined(JZTJPLAYER_LIBRARY)
#  define JZTJPLAYER_API __declspec(dllexport)
#else
#  define JZTJPLAYER_API __declspec(dllimport)
#endif

class IJZTJPlayer
{
public:
    virtual ~IJZTJPlayer(){};

    virtual int openMediaFile(const std::string &fileName) = 0;
};

extern "C" JZTJPLAYER_API IJZTJPlayer *createIJZTJPlayer();

#endif // IJZTJPLAYER_H
