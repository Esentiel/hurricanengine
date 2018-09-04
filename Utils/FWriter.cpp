#include "FWriter.h"
#include "stdafx.h"

FWriter::FWriter(const std::string& filepath)
{	
	mFlushTime = std::chrono::system_clock::now();
	mFile.open(filepath.c_str(), std::fstream::out);
	if (!mFile.is_open())
	{
		std::cout << "file is not open" << std::endl;
	}
}

void FWriter::PushToBuffer(const std::string& str)
{
	mBuffer << str << '\n';
}

void FWriter::Flush()
{
	if (!mFile.is_open())
	{
		std::cout << "file is not open" << std::endl;
	}
	mTimeNow = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = mTimeNow - mFlushTime;
	if (elapsed_seconds.count() >= 5.0)
	{
		mFile << mBuffer.str() << std::endl;
		mBuffer.str("");
		mFlushTime = std::chrono::system_clock::now();
	}
}

FWriter::~FWriter()
{
	mFile.close();
}
