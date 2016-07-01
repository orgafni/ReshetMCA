/*
 * ClientManager.cpp
 *
 *  Created on: May 14, 2016
 *      Author: Or Gafni
 */

#include <sstream>
#include <stdlib.h>
#include "ClientManager.h"
#include "TCPMessengerProtocol.h"

ClientManager::ClientManager()
{
	this->m_dispatcher = NULL;
	this->m_tcpSocket = NULL;
	this->m_udpMessenger = NULL;
	this->m_port = 0;
	this->m_peerPort = 0;
	this->isConnected = false;
	this->isInSession = false;
}

void ClientManager::connectToServer(string serverIp)
{
	if (isConnected)
	{
		cout << "You are all ready connected..." << endl;
		return;
	}

	m_port = rand() % 10500 + 10000;
	m_udpMessenger = new UDPMessenger(m_port);
	if (m_udpMessenger == NULL)
	{
		cout << "Fail to create UDP messenger" << endl;
		return;
	}
	m_tcpSocket = new TCPSocket(serverIp, MSNGR_PORT);
	if (m_udpMessenger == NULL)
	{
		cout << "Fail to create TCP Socket" << endl;
		return;
	}

	isConnected = true;

	m_dispatcher->start();

}

void ClientManager::listAllUsers()
{
	if (!isConnected)
	{
		cout << "you aren't connected to server" << endl;
		return;
	}
	sendCommand(ALL_USERS);
}

void ClientManager::listAllConnectedUsers()
{
	if (!isConnected)
	{
		cout << "you aren't connected to server" << endl;
		return;
	}
	sendCommand(CONNECTED_USERS);
}

void ClientManager::listAllRooms()
{
	if (!isConnected)
	{
		cout << "you aren't connected to server" << endl;
		return;
	}
	sendCommand(ALL_ROOMS);
}

void ClientManager::listAllUsersInRoom(string roomName)
{
	if (!isConnected)
	{
		cout << "you aren't connected to server" << endl;
		return;
	}
	sendCommand(ROOM_USERS);
	sendData(roomName);
}

void ClientManager::loginToServer(string userName, string password)
{
	if (!isConnected)
	{
		cout << "you aren't connected to server" << endl;
		return;
	}

	sendCommand(LOGIN);
	ostringstream converter;
	converter << m_port;
	sendData(userName + ":" + password + ":" + converter.str());
}

void ClientManager::registerToServer(string userName, string password)
{
	if (!isConnected)
	{
		cout << "you aren't connected to server" << endl;
		return;
	}

	sendCommand(SIGNUP);
	ostringstream converter;
	converter << m_port;
	sendData(userName + ":" + password + ":" + converter.str());
}

void ClientManager::openASessionWithUserName(string userName)
{
	if (!isConnected)
	{
		cout << "you aren't connected to server" << endl;
		return;
	}

	sendCommand(OPEN_SESSION_WITH_PEER);
	sendData(userName);
	m_peerName = userName;
}

void ClientManager::enterAChatRoom(string chatRoom)
{
	if (!isConnected)
	{
		cout << "you aren't connected to server" << endl;
		return;
	}

	sendCommand(ENTER_ROOM);
	sendData(chatRoom);

	m_chatRoomName = chatRoom;

}

void ClientManager::sendAMessage(string message)
{
	if (!isInSession)
	{
		cout << "you aren't connected to any user or room" << endl;
		return;
	}

	if(message.size()>0 && message[0] == ' ') message.erase(0,1);

	for (std::map<string, Client*>::iterator user = this->m_peers.begin(); user != this->m_peers.end(); ++user)
	{
		this->sendUDPMessage("> [" + m_username + "] " + message, user->second->GetPort(), user->second->getIP());
	}
}

void ClientManager::printCurrStatus()
{
	if (!isConnected)
	{
		cout << "The client is not connected to a server" << endl;
	}
	else if (!isInSession)
	{
		cout << "The client has not active session" << endl;
	}
	else if (isInRoom)
	{
		cout << "The client connected to a room" << endl;
	}
	else if (isConnectedToClient)
	{
		cout << "The client connected to a another client" << endl;
	}
	else
	{
		cout << "unknown state of client!!!" << endl;
	}
}

void ClientManager::closeSession()
{
	if (!isInSession)
	{
		cout << "you aren't connected to any user or room" << endl;
		return;
	}

	sendCommand(CLOSE_SESSION_WITH_PEER);
}

void ClientManager::close()
{
	if (!isConnected)
	{
		cout << "you aren't connected to a server" << endl;
		return;
	}

	sendCommand(DISCONNECT);
}

int ClientManager::readCommand()
{
	int command;
	m_tcpSocket->recv((char*)&command, sizeof(command));
	command = ntohl(command);

	return command;
}

void ClientManager::sendCommand(int command)
{
	command = htonl(command);
	m_tcpSocket->send((char*)&command, sizeof(command));
}

void ClientManager::sendData(string data)
{
	int dataLen = data.length();
	dataLen = htonl(dataLen);
	m_tcpSocket->send((char*)&dataLen, sizeof(dataLen));
	m_tcpSocket->send(data.data(), data.length());
}

void ClientManager::sendUDPMessage(string message, string port, string ip)
{
	int portInt = atoi(port.c_str());
	this->m_udpMessenger->sendTo(message, ip, portInt);
}

