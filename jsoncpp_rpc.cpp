#include "jsoncpp_rpc.h"
//#include "../jsoncpp/json.h"

using namespace std;

string jsoncpp_rpc::writeRequest(const string &method, const string &params, int id)
{
	string req;	
	req = "{\"jsonrpc\": \"2.0\"";

	if (method.length() > 0)
		req += " , \"method\": \"" + method + "\"";
	if (params.length() > 0)
		req += " , \"params\": " + params;
	if (id >= 0)
	{
		char buf[32];
		_itoa(id, buf, 10);
		req += " , \"id\": " + string(buf);
	}
	req += "}";

	return req;
}

string jsoncpp_rpc::Response::serialize() const
{
	// TODO
	return "";
}
