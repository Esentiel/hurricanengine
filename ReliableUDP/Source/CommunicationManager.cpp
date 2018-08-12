#include "stdafx.h"
#include "CommunicationManager.h"

#include "UDP/SocketUtil.h"


CommunicationManager::CommunicationManager() :
	mReceiveBuff(std::make_unique<std::array<char, MAX_PACKET_SIZE>>()),
	mReceiveBuffSize(0)
{
}


CommunicationManager::~CommunicationManager()
{
}

void CommunicationManager::CreateClientEndpoint(SocketAddress &addr)
{
	std::string id = addr.GetIP();
	auto mgr = std::make_unique<EndpointManager>(mSocket.get(), addr);

	mClients.emplace(id, std::move(mgr));
}

void CommunicationManager::SendUpdates()
{
	auto it = mClients.begin();
	for (auto clientIt = mClients.begin(); clientIt != mClients.end(); ++clientIt)
	{
		clientIt->second->SendAll();
	}
}

void CommunicationManager::ReceiveData()
{
	int result(0);
	SocketAddress addr;
	ResetRecvBuffer();

	result = mSocket->ReceiveFrom(mReceiveBuff->data(), MAX_PACKET_SIZE, addr);
	if (result > 0)
	{
		std::string key = SocketAddress(addr).GetIP();
		auto clientEP = mClients.find(key);
		if (clientEP != mClients.end())
		{
			clientEP->second->ReadHeader(mReceiveBuff.get());

			// TODO: send data to the game
		}
		else
		{
			// TODO: first time connected
		}
	}
	else
	{
		SocketUtil::ReportError(L"SendAll() failed to send packet!");
		SocketUtil::GetLastError();
	}
}

void CommunicationManager::ResetRecvBuffer()
{
	if (mReceiveBuffSize)
	{
		std::fill(std::begin(*mReceiveBuff), std::end(*mReceiveBuff), 0);
		mReceiveBuffSize = 0;
	}
}



//void ProcessTimedOutPackets()
//{
//	uint64_t timeoutTime = std::chrono::system_clock::now().time_since_epoch().count() - kAckTimeout;
//	while (!mInFlightPackets.empty())
//	{
//		//packets are sorted, so all timed out packets must be at front
//		const auto& nextInFlightPacket = mInFlightPackets.front();
//		if (nextInFlightPacket.GetTimeDispatched() < timeoutTime)
//		{
//			HandlePacketDeliveryFailure(nextInFlightPacket);
//			mInFlightPackets.pop_front();
//		}
//		else
//		{
//			//no packets beyond could be timed out
//			break;
//		}
//	}
//} 