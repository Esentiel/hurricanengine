#pragma once

#include "stdafx.h"
#include "SocketAddress.h"

#ifdef NETWORKLIBRARY_EXPORTS
#define NETWORKLIBRARY_API __declspec(dllexport)
#else
#define NETWORKLIBRARY_API __declspec(dllimport)
#endif


class SocketAddressFactory
{
public:
	NETWORKLIBRARY_API static SocketAddressPtr CreateIPv4FromString(const std::string& stringAddr);
};
