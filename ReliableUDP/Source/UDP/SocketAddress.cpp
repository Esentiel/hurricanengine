#include "stdafx.h"

#include "UDP/SocketAddress.h"

SocketAddress::SocketAddress(const sockaddr_in&& sockAddr) :
	mSockAddr(sockAddr)
{
}

SocketAddress::SocketAddress()
{
	mSockAddr.sin_family = AF_INET;
	mSockAddr.sin_addr.s_addr = INADDR_ANY;
	mSockAddr.sin_port = 0;
}

std::string SocketAddress::GetIP() const
{
	std::string ip("");
	char buff[256];

	if (!mSockAddr.sin_addr.s_addr == INADDR_ANY)
	{
		if (!inet_ntop(mSockAddr.sin_family, &mSockAddr.sin_addr, buff, 256))
			ip = std::string(buff);
			
	}

	return ip;
}
