#pragma once

#include "stdafx.h"
#include "SocketAddress.h"

#ifdef NETWORKLIBRARY_EXPORTS
#define NETWORKLIBRARY_API __declspec(dllexport)
#else
#define NETWORKLIBRARY_API __declspec(dllimport)
#endif

class UDPSocketFactory;
class UDPSocket;
typedef std::shared_ptr<UDPSocket> UDPSocketPtr;

class UDPSocket
{
public:
	NETWORKLIBRARY_API int Bind(const SocketAddressPtr& toAddress);
	NETWORKLIBRARY_API int SendTo(const void* data, int len, const SocketAddress& to);
	NETWORKLIBRARY_API int ReceiveFrom(void* buffer, int len, SocketAddress& from);
	NETWORKLIBRARY_API int SetNonBlockingMode(bool shouldBeNonBlocking);
private:
	friend class UDPSocketFactory;
	friend void CloseSocket(UDPSocket* s);
	UDPSocket(SOCKET& socket) : mSocket(socket), isBlocking(false) {}
	SOCKET mSocket;
	bool isBlocking;
	void Close();
};

