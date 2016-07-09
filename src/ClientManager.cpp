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
	this->isConnected = false;
	this->isLoginToServer = false;
	this->isInSession = false;
	this->isConnectedToClient = false;
	this->isInRoom = false;
	srand(time(NULL));

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
	if (m_tcpSocket == NULL)
	{
		cout << "Fail to create TCP Socket" << endl;
		return;
	}

	isConnected = true;

	m_dispatcher = new CommandDispatcher(this);
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
	if (isLoginToServer)
	{
		cout << "you are already login to server" << endl;
		return;
	}

	sendCommand(LOGIN);
	ostringstream converter;
	converter << m_port;
	sendData(userName + ":" + password + ":" + converter.str());
//	DEBUG_PRINT("login to server with (%s:%s:%d), port after converter (%s)\n", userName.data(), password.data(), m_port, converter.str().data());

	m_username = userName;
}

void ClientManager::registerToServer(string userName, string password)
{
	if (!isConnected)
	{
		cout << "you aren't connected to server" << endl;
		return;
	}
	if (isLoginToServer)
	{
		cout << "you are already login to server" << endl;
		return;
	}

	sendCommand(SIGNUP);
	ostringstream converter;
	converter << m_port;
	sendData(userName + ":" + password + ":" + converter.str());
//	DEBUG_PRINT("register to server with (%s:%s:%d), port after converter (%s)\n", userName.data(), password.data(), m_port, converter.str().data());

	m_username = userName;
}

void ClientManager::openASessionWithUserName(string userName)
{
	if (!isLoginToServer)
	{
		cout << "you aren't login to server" << endl;
		return;
	}

	sendCommand(OPEN_SESSION_WITH_PEER);
	sendData(userName);
	m_peerName = userName;
}

void ClientManager::enterAChatRoom(string chatRoom)
{
	if (!isLoginToServer)
	{
		cout << "you aren't login to server" << endl;
		return;
	}

	sendCommand(ENTER_ROOM);
	sendData(chatRoom);

	m_chatRoomName = chatRoom;

}

void ClientManager::createAChatRoom(string chatRoom)
{
	if (!isLoginToServer)
	{
		cout << "you aren't login to server" << endl;
		return;
	}

	sendCommand(OPEN_ROOM);
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
//		DEBUG_PRINT("sending (%s) to (%s):(%s:%s)\n", message.data(), user->second->getUserName().data(), user->second->getIP().data(), user->second->GetPort().data());
		this->sendUDPMessage("> [" + m_username + "] " + message, user->second->GetPort(), user->second->getIP());
	}
}

void ClientManager::printCurrStatus()
{
	if (!isConnected)
	{
		cout << "The client is not connected to a server" << endl;
	}
	else if (!isLoginToServer)
	{
		cout << "The client is not login to server" << endl;
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
	if (!isLoginToServer)
	{
		cout << "you aren't login to a server" << endl;
		return;
	}

	isConnected = false;
	sendCommand(DISCONNECT);
}

int ClientManager::readCommand()
{
	int command;
	m_tcpSocket->recv((char*)&command, sizeof(command));
	command = ntohl(command);

	return command;
}

string ClientManager::readData()
{
	string msg;
	char buff[1500];
	int msgLen;
	m_tcpSocket->recv((char*)&msgLen, sizeof(msgLen));
	msgLen = ntohl(msgLen);
	int totalrc = 0;
	int rc;
	while (totalrc < msgLen)
	{
		rc = m_tcpSocket->recv((char*)&buff[totalrc], msgLen - totalrc);
		if (rc > 0)
		{
			totalrc += rc;
		}
		else
		{
			break;
		}
	}
	if (rc > 0 && totalrc == msgLen)
	{
		buff[msgLen] = 0;
		msg = buff;
	}
	else
	{
		m_tcpSocket->close();
	}

	return msg;

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

void ClientManager::removePeer(string closingUserDetails)
{
	Client* tempPeer = new Client(closingUserDetails);

	map<string, Client*>::iterator clientIter = m_peers.find(tempPeer->getUserName());

	m_peers.erase(clientIter);
	delete clientIter->second;
	delete tempPeer;
}

void ClientManager::deleteAllPeers()
{
	map<string, Client*>::iterator iter = m_peers.begin();
	map<string, Client*>::iterator iterEnd = m_peers.end();

	for (; iter != iterEnd; iter++)
	{
		m_peers.erase(iter);
		delete iter->second;
	}
}

void ClientManager::sessionWithPeerClosed()
{
	string closingUserDetails = readData();
	if (isConnectedToClient == false)
	{
		cout << "session closed, but the client is not connected to another client..." << endl;
		return;
	}

	// In case I closed the session
	if (closingUserDetails == "me")
	{
		cout << "you closed the session with <" << m_peerName << ">"  << endl;
	}
	else
	{
		cout << "<" << m_peerName << "> closed the session with you" << endl;
	}

	isConnectedToClient = false;
	isInSession = false;
	m_peerName = "";

	deleteAllPeers();
}

void ClientManager::userLeftRoom()
{
	string closingUserDetails = readData();
	if (isInRoom == false)
	{
		cout << "user left room, but the client is not in any room..." << endl;
		return;
	}


	// In case I closed the session
	if (closingUserDetails == "me")
	{
		cout << "you left room <" << m_chatRoomName << ">" << endl;
		isInRoom = false;
		isInSession = false;
		m_chatRoomName = "";

		deleteAllPeers();
	}
	else
	{
		int delimeterIndex = closingUserDetails.find(":");
		string leftUserName = closingUserDetails.substr(0, delimeterIndex);

		cout << "<" << leftUserName << "> left the room" << endl;

		removePeer(closingUserDetails);
	}

}

void ClientManager::userEnterRoom()
{
	string enterUserDetails = readData();
	if (isInRoom == false)
	{
		cout << "user enter room , but the client is not connected to any room..." << endl;
		return;
	}

	// Ad the client to the peers
	Client* clientEntered = new Client(enterUserDetails);
	m_peers[clientEntered->getUserName()] = clientEntered;

	cout << "<" << clientEntered->getUserName() << "> entered the room." << endl;
}

void ClientManager::sessionWithPeerOpened()
{
	string otherUserDetails = readData();

	isConnectedToClient = true;
	isInSession = true;
	isInRoom = false;

	// Create client based on the received userDetails
	Client* otherClient = new Client(otherUserDetails);

	// Delete all other peers and insert the new one
	m_peerName = otherClient->getUserName();
	deleteAllPeers();
	m_peers[m_peerName] = otherClient;
	cout << "session with <" << m_peerName << "> established" << endl;
//	DEBUG_PRINT("%s details = %s\n", m_peerName.data(), otherUserDetails.data());
}

void ClientManager::disconnectedFromServer()
{
	// Close and delete all the sockets the client connected to

	if (m_tcpSocket != NULL)
	{
		m_tcpSocket->close();
		delete m_tcpSocket;
		m_tcpSocket = NULL;
	}

	if (m_udpMessenger != NULL)
	{
		m_udpMessenger->close();
		delete m_udpMessenger;
		m_udpMessenger = NULL;
	}

	deleteAllPeers();
	isInSession = false;
	isConnected = false;
	isLoginToServer = false;
	isConnectedToClient = false;
	isInRoom = false;
	m_peerName = "";
	m_chatRoomName = "";

	cout << "You successfully disconnected from server" << endl;
}

void ClientManager::signUpSuccess()
{
	cout << "You registered to server successfully" << endl;
	isLoginToServer = true;
}

void ClientManager::receivedAllUsers()
{
	string allUsers = readData();
	if (allUsers == "")
	{
		cout << "There are no users in the server" << endl;
	}
	else
	{
		cout << "The users in the server:" << endl;
		cout << allUsers << endl;
	}
}

void ClientManager::receivedAllConnectedUsers()
{
	string allConnectedUsers = readData();
	if (allConnectedUsers == "")
	{
		cout << "There are no connected users in the server" << endl;
	}
	else
	{
		cout << "The connected users in the server:" << endl;
		cout << allConnectedUsers << endl;
	}
}

void ClientManager::receivedAllRooms()
{
	string allRooms= readData();
	if (allRooms == "")
	{
		cout << "There are no rooms in the server" << endl;
	}
	else
	{
		cout << "The rooms in the server:" << endl;
		cout << allRooms << endl;
	}
}

void ClientManager::receivedAllUsersInRoom()
{
	string allUsersInRoom= readData();
	if (allUsersInRoom == "")
	{
		cout << "There are no users in the requested room" << endl;
	}
	else
	{
		cout << "The users in the room requested:" << endl;
		cout << allUsersInRoom << endl;
	}
}

void ClientManager::connectedToRoomSuccessfully()
{
	string clientsInRoomDetails = readData();

	// Split the received details to the chatRoomName and then <userName, ip, port>
	vector<string> tokens = Client::splitDetails(clientsInRoomDetails);
	m_chatRoomName = tokens[0];

	if (tokens.size() == 1)
	{
		cout << "You are the first user in the room <" << m_chatRoomName << ">" << endl;
	}

	// Add all the users to the peers list
	for (int i = 1; i < tokens.size(); i+=3)
	{
		Client* newClient = new Client(tokens[i],tokens[i+1], tokens[i+2]);

		m_peers[newClient->getUserName()] = newClient;
	}

	cout << "You successfully connected to the room: <" << m_chatRoomName << ">" << endl;

	isInRoom = true;
	isInSession = true;
}

void ClientManager::roomOpened()
{
	m_chatRoomName = readData();

	cout << "You successfully created the room <" << m_chatRoomName << ">" << endl;
	isInRoom = true;
	isInSession = true;
}
