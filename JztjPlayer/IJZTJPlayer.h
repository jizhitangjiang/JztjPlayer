#ifndef IJZTJPLAYER_H
#define IJZTJPLAYER_H

#include <string>

#if defined(JZTJPLAYER_LIBRARY)
#  define JZTJPLAYER_API __declspec(dllexport)
#else
#  define JZTJPLAYER_API __declspec(dllimport)
#endif

using VideoYUVDataCallback = void(*)(int w, int h, int yStride, int uStride, int vStride,
                                     uint8_t *yData, uint8_t *uData, uint8_t *vData, void *obj);

class IJZTJPlayer
{
public:
    virtual ~IJZTJPlayer(){};

    virtual void setVideoYUVDataCallback(VideoYUVDataCallback callback, void *obj) = 0;
    virtual int openMediaFile(const std::string &fileName) = 0;
};

extern "C" JZTJPLAYER_API IJZTJPlayer *createIJZTJPlayer();

#endif // IJZTJPLAYER_H
