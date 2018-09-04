#pragma once
#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <chrono>

class FWriter
{
public:
	FWriter(const std::string& filepath);
	void PushToBuffer(const std::string& str);
	void Flush();
	~FWriter();
private:
	std::fstream mFile;
	std::ostringstream mBuffer;
	std::chrono::time_point<std::chrono::system_clock> mTimeNow, mFlushTime;
};
