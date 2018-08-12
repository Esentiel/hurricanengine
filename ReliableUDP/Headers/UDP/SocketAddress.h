#pragma once

#include "stdafx.h"

#ifdef NETWORKLIBRARY_EXPORTS
#define NETWORKLIBRARY_API __declspec(dllexport)
#else
#define NETWORKLIBRARY_API __declspec(dllimport)
#endif

class SocketAddress;
typedef std::shared_ptr<SocketAddress> SocketAddressPtr;


class SocketAddress
{
public:
	NETWORKLIBRARY_API SocketAddress();
	NETWORKLIBRARY_API SocketAddress(const sockaddr_in&& sockAddr);
	NETWORKLIBRARY_API int GetSize() const { return sizeof(mSockAddr); }
	NETWORKLIBRARY_API std::string GetIP() const;

	NETWORKLIBRARY_API SocketAddress& operator=(SocketAddress sockAddr) = delete;
	sockaddr_in  mSockAddr;
private:
	friend class UDPSocket;
	
};
