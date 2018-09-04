#include "stdafx.h"

#include "UDP/SocketAddressFactory.h"
#include "UDP/SocketUtil.h"


SocketAddressPtr SocketAddressFactory::CreateIPv4FromString(const std::string& stringAddr)
{
	auto pos = stringAddr.find_last_of(':');
	std::string host, port;
	if (pos != std::string::npos)
	{
		host = stringAddr.substr(0, pos);
		port = stringAddr.substr(pos + 1);
	}
	else
	{
		host = stringAddr;
		//use default port...
		port = "0";
	}

	auto portInt = std::atoi(port.c_str());
	u_short portShort(0);
	if (portInt <= USHRT_MAX)
		portShort = static_cast<u_short>(portInt);
	else
		std::cout << "ASSERT";

	ULONG srcAddr;
	sockaddr_in sockAddr;

	sockAddr.sin_family = AF_INET;
	inet_pton(AF_INET, host.c_str(), &srcAddr);
	sockAddr.sin_addr.s_addr = srcAddr;
	sockAddr.sin_port = htons(portShort);


	auto toRet = std::make_shared<SocketAddress>(std::move(sockAddr));

	return toRet;
}