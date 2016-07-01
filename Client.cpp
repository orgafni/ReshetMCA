/*
 * Client.cpp
 *
 *  Created on: May 14, 2016
 *      Author: user
 */

#include "Client.h"


Client::Client(string userName, string ip, string port)
{
	this->m_userName = userName;
	this->m_ip = ip;
	this->m_port = port;
}

Client::Client(string clientDetails)
{
	vector<string> tokens;

	tokens = splitDetails(clientDetails);
	this->m_userName = tokens[0];
	this->m_ip = tokens[1];
	this->m_port = tokens[2];
}

vector<string> Client::splitDetails(string userDetails)
{
	char* token;
	char detailsForSplit[100];
	vector<string> tokens;

	if (userDetails != "")
	{
		strncpy(detailsForSplit, userDetails.data(), userDetails.length() + 1);

		// split the details by ':' char
		token = strtok(detailsForSplit, ":");
		while (token != NULL)
		{
			tokens.push_back(token);
			token = strtok(NULL, ":");
		}
	}

	return tokens;
}

Client::~Client() {}

