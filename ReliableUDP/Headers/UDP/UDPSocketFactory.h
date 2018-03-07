#pragma once

#include "stdafx.h"
#include "UDPSocket.h"


#ifdef NETWORKLIBRARY_EXPORTS
#define NETWORKLIBRARY_API __declspec(dllexport)
#else
#define NETWORKLIBRARY_API __declspec(dllimport)
#endif


enum class SocketAddressFamily
{
	INET = AF_INET,
	INET6 = AF_INET6
};

class UDPSocketFactory
{
public:
	NETWORKLIBRARY_API static UDPSocketPtr CreateUDPSocket(SocketAddressFamily family);
private:
};

