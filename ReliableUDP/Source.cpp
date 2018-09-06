#include "stdafx.h"

#include "CommunicationManager.h"
#include <thread>

int main(int argc, char *argv[])
{
	GameUtils::InitLoger();

	//  For optimization.

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);



	bool isServer = false;
	if (argc > 1)
	{
		isServer = true;
	}
	CommunicationManager commMgr;
	if (isServer)
	{
		
		commMgr.InitSocket("127.0.0.1:50000");

		while (true)
		{
			auto it = commMgr.mClients.begin();
			if (it != commMgr.mClients.end())
			{
				uint16_t iid = 128;
				char * data = new char[8];
				data[0] = 8;
				data[1] = iid & 0xff;
				data[2] = (iid >> 8) & 0xff;
				data[3] = 'E';
				data[4] = 'L';
				data[5] = 'l';
				data[6] = '0';
				data[7] = 'H';

				MemoryStream m(data, 8);



				Message msg;
				msg.mReliability = Message::MessageReliability::eReliable;
				msg.mOrdering = Message::MessageOrdering::eOrdered;
				msg.mData = &m;

				it->second->mMsgQueue->Enqueue(msg);

			}
			commMgr.ReceiveData();
			commMgr.SendUpdates();


			using namespace std::chrono_literals;
			std::this_thread::sleep_for(5s);
		}
	}
	else
	{
		commMgr.InitSocket("127.0.0.1:55000");
		commMgr.CreateClientEndpoint("127.0.0.1:50000");


		while (true)
		{
			auto it = commMgr.mClients.begin();
			if (it != commMgr.mClients.end())
			{
				uint16_t iid = 128;
				char * data = new char[8];
				data[0] = 8;
				data[1] = iid & 0xff;
				data[2] = (iid >> 8) & 0xff;
				data[3] = 'H';
				data[4] = 'e';
				data[5] = 'l';
				data[6] = 'l';
				data[7] = 'o';

				MemoryStream m(data, 8);
				


				Message msg;
				msg.mReliability = Message::MessageReliability::eReliable;
				msg.mOrdering = Message::MessageOrdering::eOrdered;
				msg.mData = &m;

				it->second->mMsgQueue->Enqueue(msg);

				commMgr.ReceiveData();
				commMgr.SendUpdates();

			}


			

			using namespace std::chrono_literals;
			std::this_thread::sleep_for(5s);
		}


		
	}
	
	

}