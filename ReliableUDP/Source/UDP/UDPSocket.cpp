#include "stdafx.h"
#include "UDP/UDPSocket.h"
#include "UDP/SocketUtil.h"



int UDPSocket::Bind(const SocketAddressPtr& bindAddress)
{
	int err = bind(mSocket, (sockaddr *)&bindAddress->mSockAddr, bindAddress->GetSize());
	if (err != 0)
	{
		SocketUtil::ReportError(L"UDPSocket::Bind");
		return SocketUtil::GetLastError();
	}
	return NO_ERROR;
}

int UDPSocket::SendTo(const void* data, int len, const SocketAddress& to)
{
	int byteSentCount = sendto(mSocket,
		static_cast<const char*>(data),
		len,
		0, (sockaddr *)&to.mSockAddr, to.GetSize());
	if (byteSentCount >= 0)
	{
		return byteSentCount;
	}
	else
	{
		//return error as negative number
		SocketUtil::ReportError(L"UDPSocket::SendTo");
		return -SocketUtil::GetLastError();
	}
}

int UDPSocket::ReceiveFrom(void* buffer, int len, SocketAddress& from)
{
	int fromLength = from.GetSize();
	int readByteCount = recvfrom(mSocket,
		static_cast<char*>(buffer),
		len,
		0, (sockaddr *)&from.mSockAddr,
		&fromLength);
	if (readByteCount >= 0)
	{
		return readByteCount;
	}
	else
	{
		auto error = SocketUtil::GetLastError();
		if (!(error == WSAEWOULDBLOCK && !isBlocking))
			SocketUtil::ReportError(L"UDPSocket::ReceiveFrom");
		return -error;
	}
}


int UDPSocket::SetNonBlockingMode(bool shouldBeNonBlocking)
{
	u_long arg = shouldBeNonBlocking ? 1 : 0;
	isBlocking = !shouldBeNonBlocking;
	int result = ioctlsocket(mSocket, FIONBIO, &arg);

	if (result == SOCKET_ERROR)
	{
		SocketUtil::ReportError(L"UDPSocket::SetNonBlockingMode");
		return SocketUtil::GetLastError();
	}
	else
	{
		return NO_ERROR;
	}
}

void UDPSocket::Close()
{
	closesocket(mSocket);
}