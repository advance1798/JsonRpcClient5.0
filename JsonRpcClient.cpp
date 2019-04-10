#include <iostream>
#include <string>
#include <string.h>
#include <curl/curl.h>
#include "JsonRpcClient.h"

using namespace std;

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
	struct curl_slist *header;
	//curl_socket_t sockfd;
	//long sockextr;
	//size_t iolen;	

	CURLcode p1;

	curl = curl_easy_init();
	if(curl != NULL)
	{
		//设置http发送的内容类型为JSON
		header  = curl_slist_append(header, "Content_Type:json");
		//构建HTTP报文头,请求消息头用于告诉服务器如何处理请求
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

		curl_easy_setopt(curl, CURLOPT_URL, url);//url
		curl_easy_setopt(curl, CURLOPT_PORT, 6666);

		//设置为非0表示本次操作为POST
		curl_easy_setopt(curl,CURLOPT_POST,1);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
		//设置要POST的JSON数据
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsondata);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, receive_data);//接收
   		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &(this->recvdata));

   		//curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_data);//发送
   		//curl_easy_setopt(curl, CURLOPT_READDATA, jsondata);

		res = curl_easy_perform(curl);

		if(res != CURLE_OK)
		{
				cout << "curl_easy_perform failed" << endl;
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
			//JsonRpcResponse(temp.recvdata);
			
			JsonRpcResponse *p = new JsonRpcResponse(temp.recvdata);
			cout << p->GetId() << endl;
						cout << "----------" << endl;

			cout << p->GetResult() << endl;
						cout << "----------" << endl;


			delete p;
}
