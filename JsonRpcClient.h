#ifndef CLIENT_H_
#define CLIENT_H_ 

#include "JsonRpc.h"

class JsonRpcClient
{
	
	private:
		std::string recvdata;
		
		int SendData(const char *url, const char *jsondata);

	public:
		JsonRpcClient();
		void doRequest(const char *url, const char * jsondata);
};

#endif
