
#include "packetqueue.h"
#include "mediaplayerdef.h"

PacketQueue::PacketQueue()
{

}

PacketQueue::~PacketQueue()
{

}

int PacketQueue::pushPacket(AVPacket *pkt)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    MyPacket *packet = nullptr;
    if (!m_freePackets.empty()) {
        packet = m_freePackets.front();
        m_freePackets.pop();
    }

    if (!packet) {
        packet = new MyPacket();
    }

    av_packet_move_ref(&packet->pkt, pkt);
    m_packets.push(packet);

    m_cond.notify_one();
    return 0;
}

int PacketQueue::getPacket(AVPacket *pkt)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    if (m_packets.empty()) {
        m_cond.wait(lock);
    }

    MyPacket *packet = m_packets.front();
    m_packets.pop();

    av_packet_move_ref(pkt, &packet->pkt);
    m_freePackets.push(packet);
    return 0;
}

void PacketQueue::clean()
{
    while (!m_packets.empty()) {
        MyPacket *packet = m_packets.front();
        av_packet_unref(&packet->pkt);
        m_packets.pop();
    }

    while (!m_freePackets.empty()) {
        MyPacket *packet = m_freePackets.front();
        av_packet_unref(&packet->pkt);
        m_freePackets.pop();
    }
}

void PacketQueue::init()
{

}

