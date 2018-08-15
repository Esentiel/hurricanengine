// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdint.h>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <array>
#include <queue>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <assert.h>

#define MAX_PACKET_SIZE 128 //size in bytes w/o headers
#define MAX_SEND_ATTEMPTS 100
#define HEADER_SIZE 7 // bytes

using PacketSequenceNumber = uint16_t;
