#include "framequeue.h"
#include "MediaPlayerDef.h"

static const int s_maxFrameQueueSize = 16;

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
        m_frames.push_back(frame);
    }
}

int FrameQueue::pushFrame(AVFrame *frame)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_size >= m_maxSize) {
        m_cond.wait(lock);
    }

    MyFrame *myFrame = m_frames[m_wIndex];
    av_frame_move_ref(myFrame->frame, frame);

    if (++m_wIndex >= m_maxSize) {
        m_wIndex = 0;
    }
    return 0;
}

int FrameQueue::getPacket(AVFrame* frame)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_size <= 0) {
        m_cond.wait(lock);
    }

    MyFrame *myFrame = m_frames[m_rIndex];
    av_frame_move_ref(frame, myFrame->frame);

    if (++m_rIndex >= m_maxSize) {
        m_rIndex = 0;
    }
    return 0;
}

void FrameQueue::clean()
{

}

