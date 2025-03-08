
#ifndef PACKETQUEUE_H
#define PACKETQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

struct MyPacket;
struct AVPacket;

class PacketQueue
{
public:
    PacketQueue();
    ~PacketQueue();

    int pushPacket(AVPacket *pkt);
    int getPacket(AVPacket *pkt);

    void clean();

private:
    void init();

private:
    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::queue<MyPacket *> m_packets;
    std::queue<MyPacket *> m_freePackets;
};

#endif // PACKETQUEUE_H
