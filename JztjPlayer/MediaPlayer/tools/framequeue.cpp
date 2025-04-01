#include "framequeue.h"
#include "mediaplayerdef.h"

FrameQueue::FrameQueue()
{

}

FrameQueue::~FrameQueue()
{

}

void FrameQueue::init(int maxSize)
{
    m_frames.reserve(maxSize);
    for (int i = 0; i < maxSize; i++) {
        MyFrame *frame = new MyFrame();
        frame->frame = av_frame_alloc();
        m_frames.push_back(frame);
    }
}

AVFrame *FrameQueue::getWritableFrame()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_size >= m_maxSize) {
        m_cond.wait(lock);
    }

    MyFrame *myFrame = m_frames[m_wIndex];
    return myFrame->frame;
}

int FrameQueue::pushWritableFrame()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if (++m_wIndex >= m_maxSize) {
        m_wIndex = 0;
    }

    m_size++;
    m_cond.notify_one();
    return 0;
}

AVFrame* FrameQueue::getReadableFrame()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_size <= 0) {
        m_cond.wait(lock);
    }

    MyFrame *myFrame = m_frames[m_rIndex];
    return myFrame->frame;
}

int FrameQueue::pushReadableFrame()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if (++m_rIndex >= m_maxSize) {
        m_rIndex = 0;
    }

    m_size--;
    m_cond.notify_one();
    return 0;
}

void FrameQueue::clean()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    for (int i = 0; i < m_frames.size(); i++) {
        MyFrame *frame = m_frames[i];
        av_frame_free(&frame->frame);
        delete  m_frames[i];
        m_frames[i] = nullptr;
    }
    m_frames.clear();
}

