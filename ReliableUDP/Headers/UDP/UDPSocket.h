#pragma once

#include "stdafx.h"
#include "SocketAddress.h"

#ifdef NETWORKLIBRARY_EXPORTS
#define NETWORKLIBRARY_API __declspec(dllexport)
#else
#define NETWORKLIBRARY_API __declspec(dllimport)
#endif

class UDPSocket;
typedef std::unique_ptr<UDPSocket> UDPSocketPtr;

class UDPSocket
{
public:
	UDPSocket(SOCKET& socket);
	NETWORKLIBRARY_API int Bind(const SocketAddressPtr& toAddress);
	NETWORKLIBRARY_API int SendTo(const char * data, int len, const SocketAddress& to);
	NETWORKLIBRARY_API int ReceiveFrom(char * buffer, int len, SocketAddress& from);
	NETWORKLIBRARY_API int SetNonBlockingMode(bool shouldBeNonBlocking);
	~UDPSocket();
private:
	SOCKET mSocket;
	bool isBlocking;
	void Close();
	
};

