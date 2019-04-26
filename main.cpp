#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <curl/curl.h>

#include "JsonRpc.h"
#include "JsonRpcClient.h"
 
using namespace std;

int main()
{
     MJsonRpcRequest M;
	JsonRpcRequest A,B,C;
	/*const char *message = "{\"message\": \"hello, world! lt was dreadfully cold, \
it was snowing fast, and almost dark； the evening----the last evening of the old \
year was drawing in. But, cold and dark as it was, a poor little girl, with bare head and feet, \
was still wandering about the streets. When she left her home she had slippers on, \
but they were much too large for her； indeed, properly, they belonged to her mother,\
and had dropped off her feet while she was running very fast across the road, \
to get out of the way of two carriages. One of the slippers was not to be found, \
the other had been snatched up by a little boy, who ran off with it thinking it might serve him as a doll's cradle.\
 So the little girl now walked on, her bare feet quite red and blue with the cold.\\"}";*/

    A.SetMethod("Print_Sth");
    A.SetParams("{\"one\":1, \"two\":2}");
   // A.SetId(1);

    M.InsertJsonObj(A);
    
    
    B.SetMethod("Print_Sth");
    B.SetParams("{\"three\":3, \"four\":4}");
    //B.SetId(2);
    M.InsertJsonObj(B);

   /* C.SetMethod("Print_Sth");
    C.SetParams("{\"five\":5, \"six\":6}");
    C.SetId(003);
    M.InsertJsonObj(C);*/

	//strcpy(jsondata, A.ToString().c_str());

	JsonRpcClient one;
    cout << M.ToString().c_str() << endl;
	
	one.doRequest("127.0.0.1",M.ToString().c_str());
	//one.SendData(jsondata,"http://172.18.6.62/demo");
	return 0;
}
