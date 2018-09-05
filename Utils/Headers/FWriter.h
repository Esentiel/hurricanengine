#pragma once

#include "stdafx.h"

class FWriter
{
public:
	FWriter(const std::string& filepath);
	void PushToBuffer(const std::string& str);
	~FWriter();
private:
	void Flush();
	std::fstream mFile;
	std::unique_ptr<std::ostringstream> mBuffer;
	std::chrono::time_point<std::chrono::system_clock> mFlushTime;
	const double mPeriod;
};
