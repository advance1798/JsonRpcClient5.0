#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <sstream>
#include "JsonRpcClient.h"

using namespace std;

void OutputInfo(JsonRpcResponse &response);

JsonRpcClient::JsonRpcClient()
{
	recvdata = "";
}

static size_t receive_data(void *ptr,size_t size,size_t nmemb,void *stream)
{		
		
    	size_t nsize = size * nmemb;

    	std::string *s = (std::string *)stream;
    	s->append((const char *)ptr,nsize);    
    	 //c->recvdata += string((const char *)ptr,nsize);
    	return nsize; 
 
}

//static size_t read_data(void *ptr,size_t size,size_t nmemb,void *stream)
//{
//	size_t nsize = size * nmemb;

//	const char *s = (const char *)stream;
//	std::string *ptr1 = (std::string *)ptr;
//	ptr1->append(s, nsize);
//
//	return nsize;
//}

int JsonRpcClient::SendData(const char *url, const char *jsondata)
{
	CURL *curl = NULL;
	CURLcode res;
	struct curl_slist *header = NULL;	

	int len = strlen(jsondata);
	//cout << len << endl;	
	stringstream ss;
	ss << len;
	string str = ss.str();
	str = "Content-Length: " + str;
	//cout << str.c_str() << endl;
	
	curl = curl_easy_init();
	if(curl != NULL)
	{
	
		header  = curl_slist_append(header, str.c_str());
		if (header == NULL) {
			curl_slist_free_all(header);
  			return -1;
		}

		res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
		if(res != CURLE_OK)
			return -1;

		res = curl_easy_setopt(curl, CURLOPT_URL, url);
		//Returns CURLE_OK on success or CURLE_OUT_OF_MEMORY if there was insufficient heap space. 
		if(res != CURLE_OK)
			return -1;

		res = curl_easy_setopt(curl, CURLOPT_PORT, 6666);
		if(res != CURLE_OK)
			return -1;

		//curl_easy_setopt(curl,CURLOPT_POST,1);
		//Returns CURLE_OK if HTTP is supported, and CURLE_UNKNOWN_OPTION if not. 
		
		res = curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
		if(res != CURLE_OK)
			return -1;
		//设置要POST的JSON数据
		res = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsondata);
		if(res != CURLE_OK)
			return -1;

		res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, receive_data);
		if(res != CURLE_OK)
			return -1;

   		res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &(this->recvdata));
   		if(res != CURLE_OK)
			return -1;

   		//curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_data);//发送
   		//curl_easy_setopt(curl, CURLOPT_READDATA, jsondata);

		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
		{
				cout << "curl_easy_perform failed" << endl;
				return -1;
		}

		curl_easy_cleanup(curl);	
	}
	

	return 0;
}


void JsonRpcClient::doRequest(const char *url, const char *jsondata) 
{
	JsonRpcClient temp;

	temp.SendData(url, jsondata);

	cout << temp.recvdata << endl;
	cout << "----------" << endl;

	//MJsonRpcResponse multiresponses(temp.recvdata);
	
	//在这之前得判断一下是否收到的是空数据，或者这一情况归结为解析失败里。
		MJsonRpcResponse multiResponses(temp.recvdata);

		for(int i = 0; i < multiResponses.GetSize(); ++i)
		{
			OutputInfo(multiResponses[i]);
		}

}

void OutputInfo(JsonRpcResponse &response)
{
	switch(response.Validate())
			{
				case PARSE_FAILED:
				cout << "id:" << response.GetId() << "parse failed" << endl;
				break;

				case GET_ERROR:
				cout << "id:" << response.GetId() << response.GetError() << endl;
				break;

				case GET_RESULT:
				cout << "id:" << response.GetId() << response.GetResult() << endl;
				break;

				case INVALID_INCLUDE:
				cout << "id:" << response.GetId() << "invalid include" << endl;
				break;

				case NO_JSONRPC:
				cout << "id:" << response.GetId() << "no jsonrpc" << endl;
				break;

				case NO_RESULT_OR_ERROR:
				cout << "id:" << response.GetId() << "no result or error" << endl;
				break;

				case INVALID_ERROR:
				cout << "id:" << response.GetId() << "invalid error" << endl;
				break;

				case 0 :
				cout << "validating finished, but no result returned" << endl;
				break;
				
				default:
				break;
			}
}
