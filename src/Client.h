/*
 * Client.h
 *
 *  Created on: May 14, 2016
 *      Author: user
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>

using namespace std;

class Client
{
private:
	string m_userName;
	string m_ip;
	string m_port;

public:
	Client(string userName, string ip, string port);
	Client(string clientDetails);
	virtual ~Client();

	static vector<string> splitDetails(string userDetails);

	void setIP(string ip)
	{
		m_ip = ip;
	}

	string getIP()
	{
		return m_ip;
	}

	void setPort(string port)
	{
		m_port = port;
	}

	string GetPort()
	{
		return m_port;
	}

	const string getAddress()
	{
		char address[50];
		strncpy(address, this->m_ip.data(), this->m_ip.length() + 1);
		strncat(address, ":", 2);
		strncat(address, this->m_port.data(), this->m_port.length() + 1);
		return address;
	}

	const string getUserName()
	{
		return m_userName;
	}

	void setUserName(string userName)
	{
		this->m_userName = userName;
	}

};

#endif /* CLIENT_H_ */
