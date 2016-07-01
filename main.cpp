/*
 * main.cpp
 *
 *  Created on: May 13, 2016
 *      Author: Or Gafni
 */

#include <iostream>
#include "ClientManager.h"

using namespace std;

const char* CLIENT_CLI_connectToServer = "c";
const char* CLIENT_CLI_listAllUsers = "lu";
const char* CLIENT_CLI_listAllConnectedUsers = "lcu";
const char* CLIENT_CLI_listAllRooms = "lr";
const char* CLIENT_CLI_listAllUsersInRoom = "lru";
const char* CLIENT_CLI_loginToServer = "login";
const char* CLIENT_CLI_registerToServer = "register";
const char* CLIENT_CLI_openSessionWithUser = "o";
const char* CLIENT_CLI_enterAChatRoom = "or";
const char* CLIENT_CLI_sendAMessage= "s";
const char* CLIENT_CLI_printCurrStatus = "l";
const char* CLIENT_CLI_disconnectTheOpenSession = "cs";
const char* CLIENT_CLI_disconnectFromServer = "d";
const char* CLIENT_CLI_help = "h";
const char* CLIENT_CLI_closeTheApp = "x";

void printMenu()
{
	cout << "options:" << endl;
	cout << "%s - connect to the server" << CLIENT_CLI_connectToServer <<endl;
	cout << "%s - prints user names on server" << CLIENT_CLI_listAllUsers <<endl;
	cout << "%s - prints user names available on server" << CLIENT_CLI_listAllConnectedUsers <<endl;
	cout << "%s - print all rooms on server" << CLIENT_CLI_listAllRooms <<endl;
	cout << "%s - print all users in room" << CLIENT_CLI_listAllUsersInRoom <<endl;
	cout << "%s - login to the server" << CLIENT_CLI_loginToServer <<endl;
	cout << "%s - create a new user" << CLIENT_CLI_registerToServer <<endl;
	cout << "%s - open session with a user" << CLIENT_CLI_openSessionWithUser <<endl;
	cout << "%s - enter a chat room" << CLIENT_CLI_enterAChatRoom <<endl;
	cout << "%s - send message to a user" << CLIENT_CLI_sendAMessage <<endl;
	cout << "%s	- prints the current status of the client" << CLIENT_CLI_printCurrStatus <<endl;
	cout << "%s - close current session/exit a chat room" << CLIENT_CLI_disconnectTheOpenSession <<endl;
	cout << "%s - disconnect from server" << CLIENT_CLI_disconnectFromServer <<endl;
	cout << "%s	- print this menu" << CLIENT_CLI_help <<endl;
	cout << "%s	- shutdown" << CLIENT_CLI_closeTheApp <<endl;
}

int main()
{
	cout << "welcome to messenger!" << endl;

	bool isRun = true;
	ClientManager* messenger = new ClientManager();
	printMenu();
	string command;
	string name;
	string message;

	while (isRun)
	{
		cin >> command;

		if (command == CLIENT_CLI_connectToServer)
		{
			string ip;
			cin >> ip;
			messenger->connectToServer(ip);
		}
		else if (command == CLIENT_CLI_listAllUsers)
		{
			messenger->listAllUsers();
		}
		else if (command == CLIENT_CLI_listAllConnectedUsers)
		{
			messenger->listAllConnectedUsers();
		}
		else if (command == CLIENT_CLI_listAllRooms)
		{
			messenger->listAllRooms();
		}
		else if (command == CLIENT_CLI_listAllUsersInRoom)
		{
			string room;
			cin >> room;
			messenger->listAllUsersInRoom(room);
		}
		else if (command == CLIENT_CLI_loginToServer)
		{
			string userName;
			string password;
			cin >> userName;
			cin >> password;
			messenger->loginToServer(userName, password);
		}
		else if (command == CLIENT_CLI_registerToServer)
		{
			string userName;
			string password;
			cin >> userName;
			cin >> password;
			messenger->registerToServer(userName, password);
		}
		else if (command == CLIENT_CLI_openSessionWithUser)
		{
			string userName;
			cin >> userName;
			messenger->openASessionWithUserName(userName);
		}
		else if (command == CLIENT_CLI_enterAChatRoom)
		{
			string chatRoom;
			cin >> chatRoom;
			messenger->enterAChatRoom(chatRoom);
		}
		else if (command == CLIENT_CLI_sendAMessage)
		{
			string message;
			getline(std::cin, message);

			messenger->sendAMessage(message);
		}
		else if (command == CLIENT_CLI_printCurrStatus)
		{
			messenger->printCurrStatus();
		}
		else if (command == CLIENT_CLI_disconnectTheOpenSession)
		{
			messenger->closeSession();
		}
		else if (command == CLIENT_CLI_disconnectFromServer)
		{
			messenger->close();
		}
		else if (command == CLIENT_CLI_help)
		{
			printMenu();
		}
		else if (command == CLIENT_CLI_closeTheApp)
		{
			messenger->close();
			isRun = false;
		}
		else
		{
			cout << "invalid command! type %s for help" << CLIENT_CLI_help << endl;
		}
	}

	return 0;
}




