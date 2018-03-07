#pragma once

#include "stdafx.h"

#ifdef NETWORKLIBRARY_EXPORTS
#define NETWORKLIBRARY_API __declspec(dllexport)
#else
#define NETWORKLIBRARY_API __declspec(dllimport)
#endif

class SocketUtil
{
public:
	NETWORKLIBRARY_API static void ReportError(const std::wstring &msg) { std::wcout << msg << std::endl; }
	NETWORKLIBRARY_API static int GetLastError() { return WSAGetLastError(); }
};

