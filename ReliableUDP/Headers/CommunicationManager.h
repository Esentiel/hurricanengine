#pragma once

#include "stdafx.h"
#include "UDP/UDPSocket.h"
#include "EndpointManager.h"
#include "WorkQueue.h"

using MsgQueuePtr = std::unique_ptr<threadsafe_queue_lb_impr<Message>>;
using MemStreamQueuePtr = std::unique_ptr<threadsafe_queue_lb_impr<InputMemoryBitStream>>;

class CommunicationManager
{
public:
	CommunicationManager();
	~CommunicationManager();

	void CreateClientEndpoint(SocketAddress &addr);

	void ProcessUpdatesFromGame();
	void ProcessUpdatesFromNetwork();

	void SendUpdates();
	void ReceiveData();

private:
	void ResetRecvBuffer();

	std::map<std::string, std::unique_ptr<EndpointManager>> mClients;
	std::unique_ptr<UDPSocket> mSocket;
	std::unique_ptr<std::array<char, MAX_PACKET_SIZE>> mReceiveBuff;
	uint8_t mReceiveBuffSize;

	MsgQueuePtr mInputQueue;
	MemStreamQueuePtr mOutputQueue;
};

