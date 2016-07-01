/*
 * ClientManager.h
 *
 *  Created on: May 14, 2016
 *      Author: Or Gafni
 */

#ifndef CLIENTMANAGER_H_
#define CLIENTMANAGER_H_

#include <map>
#include "Client.h"
#include "CommandDispatcher.h"
#include "UDPMessenger.h"
#include "TCPSocket.h"
#include "iostream"

using namespace std;

class ClientManager
{
	friend class CommandDispatcher;
public:
	ClientManager();

	void connectToServer(string serverIp);
	void listAllUsers();
	void listAllConnectedUsers();
	void listAllRooms();
	void listAllUsersInRoom(string roomName);
	void loginToServer(string userName, string password);
	void registerToServer(string userName, string password);
	void openASessionWithUserName(string userName);
	void enterAChatRoom(string chatRoom);
	void sendAMessage(string message);
	void printCurrStatus();
	void closeSession();
	void close();

private:

	/**
	 * Read incoming command from server
	 */
	int readCommand();

	/**
	 * send the given command to the server
	 */
	void sendCommand(int command);

	/**
	 * Send the given data to the server
	 */
	void sendData(string data);

	/**
	 * Send a UDP message to a peer
	 */
	void sendUDPMessage(string message, string port, string ip);

private:
	bool isConnected;
	bool isInSession;
	bool isInRoom;
	bool isConnectedToClient;
	int  m_port;
	int m_peerPort;
	string m_username;
	string m_password;
	string m_peerName;
	string m_peerIP;
	string m_chatRoomName;
	UDPMessenger* m_udpMessenger;
	TCPSocket* m_tcpSocket;
	CommandDispatcher* m_dispatcher;

	map<string, Client*> m_peers;
};

#endif /* CLIENTMANAGER_H_ */
