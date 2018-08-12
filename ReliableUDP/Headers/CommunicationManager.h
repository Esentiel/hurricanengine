#pragma once

#include "stdafx.h"
#include "UDP/UDPSocket.h"
#include "EndpointManager.h"

class CommunicationManager
{
public:
	CommunicationManager();
	~CommunicationManager();

	void CreateClientEndpoint(SocketAddress &addr);

	void SendUpdates();
	void ReceiveData();

private:
	void ResetRecvBuffer();

	std::map<std::string, std::unique_ptr<EndpointManager>> mClients;
	std::unique_ptr<UDPSocket> mSocket;
	std::unique_ptr<std::array<char, MAX_PACKET_SIZE>> mReceiveBuff;
	uint8_t mReceiveBuffSize;
};

