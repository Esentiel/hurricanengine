#pragma once

#include "stdafx.h"
#include "MessageQueue.h"
#include "UDP/SocketAddress.h"
#include "AckRange.h"

using PacketSequenceNumber = uint16_t;

class UDPSocket;
class SocketAddress;
class Message;

class EndpointManager
{
public:
	EndpointManager(UDPSocket* socket, SocketAddress addr);
	~EndpointManager();

	void SendAll();
	void ReadHeader(const std::array<char, MAX_PACKET_SIZE> *buffer);
private:
	MessageQueue::WritingResult WriteMsg();
	void WriteHeader();
	void ResetBuffer();
	void ProcessAcks(PacketSequenceNumber ack, uint8_t ackCount);

	UDPSocket* mSocket;
	std::unique_ptr<SocketAddress> mRecipient;

	PacketSequenceNumber mLastSentSeq;
	PacketSequenceNumber mNextToSend;
	PacketSequenceNumber mLastAckedSeq;

	std::map<PacketSequenceNumber, std::vector<Message*>> mSentPackets;
	std::unique_ptr<MessageQueue> mMsgQueue;
	std::unique_ptr<std::array<char, MAX_PACKET_SIZE>> mBuffer;
	uint8_t mBufferSize;
	uint8_t mHeaderSize;
	std::deque<AckRange> mPendingAcks;
	std::deque<AckRange> mConfirmAcks;

	uint8_t mSendCounter;
};

