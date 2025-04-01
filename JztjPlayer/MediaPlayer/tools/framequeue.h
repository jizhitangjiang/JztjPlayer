#ifndef FRAMEQUEUE_H
#define FRAMEQUEUE_H

#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

struct MyFrame;
struct AVFrame;

class FrameQueue
{
public:
    FrameQueue();
    ~FrameQueue();

    void init(int maxSize);

    AVFrame* getWritableFrame();
    int pushWritableFrame();

    AVFrame* getReadableFrame();
    int pushReadableFrame();

    void clean();

private:
    std::mutex m_mutex;
    std::condition_variable m_cond;

    int m_maxSize{0};
    int m_size{0};
    int m_rIndex{0};
    int m_wIndex{0};
    std::vector<MyFrame *> m_frames;
};

#endif // FRAMEQUEUE_H
