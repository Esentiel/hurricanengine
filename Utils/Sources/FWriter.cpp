#include "stdafx.h"
#include "Constants.h"
#include "FWriter.h"

FWriter::FWriter(const std::string& filepath)
	: mPeriod(FLUSHINTERVAL), mFlushTime{ std::chrono::system_clock::now() }
{
	mBuffer = std::make_unique<std::ostringstream>();
	mFile.open(filepath.c_str(), std::fstream::out);
	if (!mFile.is_open())
	{
		std::cout << "file is not open" << std::endl;
	}
}

void FWriter::PushToBuffer(const std::string& str)
{
	*mBuffer << str << '\n';
	Flush();
}

void FWriter::Flush()
{
	if (mFile.is_open())
	{
		std::chrono::time_point<std::chrono::system_clock> timeNow = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = timeNow - mFlushTime;
		if (elapsed_seconds.count() >= mPeriod)
		{
			mFile << mBuffer->str();
			mBuffer->str("");
			mFlushTime = timeNow;
		}
	}
	else std::cout << "file is not open" << std::endl;
}

FWriter::~FWriter()
{
	mFile.close();
}
