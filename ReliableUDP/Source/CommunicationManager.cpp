#include "stdafx.h"
#include "CommunicationManager.h"

#include "UDP/SocketUtil.h"
#include "UDP/SocketAddressFactory.h"
#include "UDP/UDPSocketFactory.h"

CommunicationManager::CommunicationManager() :
	mReceiveBuff(std::make_unique<std::array<char, MAX_PACKET_SIZE>>()),
	mReceiveBuffSize(0),
	mInputQueue(std::make_unique<MsgQueue>()),
	mOutputQueue(std::make_unique<MemStreamQueue>())
{
}


CommunicationManager::~CommunicationManager()
{
}

int CommunicationManager::InitSocket(const std::string &addrStr)
{
	UDPSocketPtr socket = UDPSocketFactory::CreateUDPSocket(SocketAddressFamily::INET);
	SocketAddressPtr sockAddr = SocketAddressFactory::CreateIPv4FromString(addrStr);
	auto err = SocketUtil::GetLastError();
	int result = socket->Bind(sockAddr);
	
	if (result >= 0)
	{
		socket->SetNonBlockingMode(true);

		mSocket.swap(socket);
	}


	return result;
}

void CommunicationManager::CreateClientEndpoint(const std::string &addrStr)
{
	SocketAddressPtr sockAddr = SocketAddressFactory::CreateIPv4FromString(addrStr);
	std::string id = sockAddr->GetIP();
	auto mgr = std::make_unique<EndpointManager>(mSocket.get(), *sockAddr);

	mClients.emplace(id, std::move(mgr));
}

void CommunicationManager::ProcessUpdatesFromGame()
{
	while (!mInputQueue->empty())
	{
		Message msg;
		if (mInputQueue->try_pop(msg))
		{
			for (auto it = mClients.begin(); it != mClients.end(); ++it)
			{
				it->second->PushToQueue(std::move(msg));
			}
		}
	}

}

void CommunicationManager::ProcessUpdatesFromNetwork()
{

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

	while (mSocket->ReceiveFrom(mReceiveBuff->data(), MAX_PACKET_SIZE, addr) > 0)
	{
		std::cout << "Received" << std::endl;
		std::string key = SocketAddress(addr).GetIP();
		auto clientEP = mClients.find(key);
		if (clientEP == mClients.end())
		{
			// TODO: first time connected
			//std::cout << "New client added: " << key << std::endl;
			mClients.insert({ key , std::make_unique<EndpointManager>(mSocket.get(), addr) });
		}
		
		clientEP = mClients.find(key);
		if (clientEP != mClients.end())
		{
			//std::cout << "Received bytes from client: " << key << std::endl;
			clientEP->second->ReadHeader(mReceiveBuff.get());

			std::vector<InputMemoryBitStream> memStreams = clientEP->second->ReadData(mReceiveBuff.get());
			for (auto & memStream : memStreams)
			{
				mOutputQueue->push(std::move(memStream));
			}
		}
	}

	if (!result)
	{
		//SocketUtil::ReportError(L"ReceiveData() failed to send packet!");
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