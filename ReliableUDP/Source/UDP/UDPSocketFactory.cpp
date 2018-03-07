#include "stdafx.h"
#include "UDP/UDPSocketFactory.h"
#include "UDP/SocketUtil.h"

void CloseSocket(UDPSocket* mSocket)
{
	mSocket->Close();
}

UDPSocketPtr UDPSocketFactory::CreateUDPSocket(SocketAddressFamily family)
{
	SOCKET s = socket(static_cast<int>(family), SOCK_DGRAM, IPPROTO_UDP);
	if (s != INVALID_SOCKET)
	{
		return std::shared_ptr<UDPSocket>(new UDPSocket(s), CloseSocket);
	}
	else
	{
		SocketUtil::ReportError(L"SocketUtil::CreateUDPSocket");
		return nullptr;
	}
}