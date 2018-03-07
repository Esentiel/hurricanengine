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