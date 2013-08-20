/**
 *	jsoncpp-rpc
 *
 *	CPP impl of json-rpc based on jsoncpp.
 *
 *	supports JSON-RPC version 2.0
 *
 *	@author : taekwonv@gmail.com
 */

#ifndef JSONCPPRPC_H
#define JSONCPPRPC_H

#include <string>

//
// NOTE:
//	This is not a functional version yet. I am working on building and will revise them soon.

class jsoncpp_rpc
{
public:	
	static std::string writeRequest(const std::string &method, const std::string &params, int id);

	class Response
	{
	public:
		Response();
		bool set(const std::string &json);

		void result(const std::string &res) { m_result = res; }
		std::string result() const { return m_result; }
		void id(int id) { m_id = id; }
		int id() const { return m_id; }
		void error(int code, std::string &message);
		int errorCode() const { return m_errorCode; }
		std::string errorMessage() const { return m_errorMessage; }

		std::string serialize() const;

	private:
		std::string m_result;
		int m_id;
		int m_errorCode;
		std::string m_errorMessage;
	};
};

#endif
