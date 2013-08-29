#include "jsoncpp_rpc.h"

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
		_itoa_s(id, buf, 10);
		req += " , \"id\": " + string(buf);
	}
	req += "}";

	return req;
}

std::string jsoncpp_rpc::Request::serialize() const
{
	Json::Value root;
	root["jsonrpc"] = "2.0";
	root["method"] = m_method;
	root["params"] = m_params;
	Json::StyledWriter w;
	return w.write(root);
}

bool jsoncpp_rpc::Request::serialize(const std::string &json)
{
	Json::Reader rd;
	Json::Value root;
	if (false == rd.parse(json, root))
	{
		string s =rd.getFormatedErrorMessages();
		return false;
	}

	string version = root.get("jsonrpc", "null").asString();
	if (0 == strcmp(version.c_str(), "null") || 0 != strcmp(version.c_str(), "2.0"))
		return false;

	m_method = root.get("method", "null").asString();
	if (0 == strcmp(version.c_str(), "null"))
		return false;

	m_params = root["params"];
	return true;
}

jsoncpp_rpc::Response::Response()
	: m_id(NULL), m_errorCode(0)
{
}

string jsoncpp_rpc::Response::serialize() const
{
	string output;
	output = "{\"jsonrpc\": \"2.0\"";

	if (m_errorCode > 0)
	{
		char buf[32];
		_itoa_s(m_errorCode, buf, 10);
		output += ", \"error\": {\"error\": " + string(buf) + ", \"message\": \"" + m_errorMessage + "\"}, \"id\": ";
		_itoa_s(m_id, buf, 10);
		output += m_id == NULL ? "null}" : string(buf) + "}";
	}
	else
	{
		char buf[32];
		_itoa_s(m_errorCode, buf, 10);
		output += ", \"result\": " + m_result + "\"id\": ";
		_itoa_s(m_id, buf, 10);
		output += m_id == NULL ? "null}" : string(buf) + "}";
	}

	return "";
}
