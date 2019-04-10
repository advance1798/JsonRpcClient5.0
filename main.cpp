#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <curl/curl.h>

#include "JsonRpc.h"
#include "JsonRpcClient.h"
 
using namespace std;

	
//	JsonRpcRequest A;
//	A.SetJsonRpc("2.0");
//	A.SetMethod("subtract");
//	A.SetParams("{\"subtrahend\": 23, \"minuend\": 42}");
//	A.SetId(1);
//
//	cout << A.Validate() << endl;//测试报文是否合法
//	
//	cout << A.ToString() << endl;
//
//	JsonRpcRequest B("{\"jsonrpc\":\"2.0\",\"method\":\"subtract\", \"params\": {\"subtrahend\": 100, \"minuend\": 100}}");//测试缺少id
//	JsonRpcRequest B(A.ToString());
//	cout << B.GetParams() << endl;
//	cout << B.GetId() << endl;
//	cout << B.GetMethod() << endl;
//	cout << B.Validate() << endl;

//	cout << "-----------------------" << endl;

//	JsonRpcResponse C;

//	C.SetResult(21);
//	C.SetResult("{\"state\":\"success\"}");
//	C.SetId(3);
//	C.SetError("{\"code\": -32600, \"message\": \"nvalid Request\"}");
//	cout << C.Validate() << endl;//测试result 和 error不能同时存在
//
//	cout << C.ToString() << endl;
//
//	JsonRpcResponse D(C.ToString());
//
//	cout << D.GetResult() << endl;
//	cout << D.GetError() << endl;
//	cout << D.GetId() << endl;

//	cout << D.Validate() << endl;

//Json (*f)(Json &params);

int main()
{
	char jsondata[1024];
	memset(jsondata,0,sizeof(jsondata));

	JsonRpcRequest A;

	A.SetJsonRpc("2.0");
    A.SetMethod("Print_Sth");
    A.SetParams("{\"message\": \"hello, world!\"}");
    A.SetId(1);

    A.Validate();

	//strcpy(jsondata, A.ToString().c_str());

	JsonRpcClient one;

	
	one.doRequest("127.0.0.1",A.ToString().c_str());
	//one.SendData(jsondata,"http://172.18.6.62/demo");
	return 0;
}
