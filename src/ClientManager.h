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

	/** ====== function called from CommandDispatcher **/

	/**
	 * The session with the client closed
	 */
	void sessionWithPeerClosed();

	/**
	 * A user left the room that the client is connected to
	 */
	void userLeftRoom();

	/**
	 * A new user enter the room you connected to
	 */
	void userEnterRoom();

	/**
	 * Session with another peer is established
	 */
	void sessionWithPeerOpened();

	/**
	 * the client is disconnected from server
	 */
	void disconnectedFromServer();

	/**
	 * sign up to server success
	 */
	void signUpSuccess();

	/**
	 * All users received from server
	 */
	void receivedAllUsers();

	/**
	 * All  connected users received from server
	 */
	void receivedAllConnectedUsers();

	/**
	 * All rooms received from server
	 */
	void receivedAllRooms();

	/**
	 * All users in room received from server
	 */
	void receivedAllUsersInRoom();

	void connectedToRoomSuccessfully();

private:

	/**
	 * Read incoming command from server
	 */
	int readCommand();

	/**
	 * Read incoming data from server
	 */
	string readData();

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

	/**
	 * Remove a peer from the peers list
	 */
	void removePeer(string closingUserDetails);

	/**
	 * Remove all peers from the peers list
	 */
	void deleteAllPeers();

private:
	bool isConnected;
	bool isInSession;
	bool isInRoom;
	bool isConnectedToClient;
	int  m_port;
	string m_username;
	string m_password;
	string m_peerName;
	string m_chatRoomName;
	UDPMessenger* m_udpMessenger;
	TCPSocket* m_tcpSocket;
	CommandDispatcher* m_dispatcher;

	map<string, Client*> m_peers;
};

#endif /* CLIENTMANAGER_H_ */
