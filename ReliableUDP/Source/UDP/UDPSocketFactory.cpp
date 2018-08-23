#include "stdafx.h"
#include "UDP/UDPSocketFactory.h"
#include "UDP/SocketUtil.h"

UDPSocketPtr UDPSocketFactory::CreateUDPSocket(SocketAddressFamily family)
{
	SOCKET s = socket(static_cast<int>(family), SOCK_DGRAM, IPPROTO_UDP);
	if (s != INVALID_SOCKET)
	{
		return std::move(std::make_unique<UDPSocket>(s));
	}
	else
	{
		SocketUtil::ReportError(L"SocketUtil::CreateUDPSocket");
		return nullptr;
	}
}