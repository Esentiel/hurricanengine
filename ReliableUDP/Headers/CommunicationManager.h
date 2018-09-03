#pragma once

#include "stdafx.h"
#include "UDP/UDPSocket.h"
#include "EndpointManager.h"
#include "WorkQueue.h"

using MsgQueue = threadsafe_queue_lb_impr<Message>;
using MsgQueuePtr = std::unique_ptr<MsgQueue>;
using MemStreamQueue = threadsafe_queue_lb_impr<InputMemoryBitStream>;
using MemStreamQueuePtr = std::unique_ptr<MemStreamQueue>;

class CommunicationManager
{
public:
	CommunicationManager();
	~CommunicationManager();

	int InitSocket(const std::string &addrStr);

	void CreateClientEndpoint(const std::string &addrStr);

	void ProcessUpdatesFromGame();
	void ProcessUpdatesFromNetwork();

	void SendUpdates();
	void ReceiveData();

private:
	void ResetRecvBuffer();
public:
	std::map<std::string, std::unique_ptr<EndpointManager>> mClients;
private:
	std::unique_ptr<UDPSocket> mSocket;
	std::unique_ptr<std::array<char, MAX_PACKET_SIZE>> mReceiveBuff;
	uint8_t mReceiveBuffSize;

	MsgQueuePtr mInputQueue;
	MemStreamQueuePtr mOutputQueue;
};

