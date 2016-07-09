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
const char* CLIENT_CLI_createAChatRoom = "cr";
const char* CLIENT_CLI_sendAMessage= "s";
const char* CLIENT_CLI_printCurrStatus = "l";
const char* CLIENT_CLI_disconnectTheOpenSession = "cs";
const char* CLIENT_CLI_disconnectFromServer = "d";
const char* CLIENT_CLI_help = "h";
const char* CLIENT_CLI_closeTheApp = "x";

void printMenu()
{
	cout << "options:" << endl;
	printf("%s - connect to the server\n", CLIENT_CLI_connectToServer);
	printf("%s - prints user names on server\n", CLIENT_CLI_listAllUsers);
	printf("%s - prints user names available on server\n", CLIENT_CLI_listAllConnectedUsers);
	printf("%s - print all rooms on server\n", CLIENT_CLI_listAllRooms);
	printf("%s - print all users in room\n", CLIENT_CLI_listAllUsersInRoom);
	printf("%s - login to the server\n", CLIENT_CLI_loginToServer);
	printf("%s - create a new user\n", CLIENT_CLI_registerToServer);
	printf("%s - open session with a user\n", CLIENT_CLI_openSessionWithUser);
	printf("%s - enter a chat room\n", CLIENT_CLI_enterAChatRoom);
	printf("%s - create a chat room\n", CLIENT_CLI_createAChatRoom);
	printf("%s - send message to a user\n", CLIENT_CLI_sendAMessage);
	printf("%s	- prints the current status of the client\n", CLIENT_CLI_printCurrStatus);
	printf("%s - close current session/exit a chat room\n", CLIENT_CLI_disconnectTheOpenSession);
	printf("%s - disconnect from server\n", CLIENT_CLI_disconnectFromServer);
	printf("%s	- print this menu\n", CLIENT_CLI_help);
	printf("%s	- shutdown\n", CLIENT_CLI_closeTheApp);
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
		else if (command == CLIENT_CLI_createAChatRoom)
		{
			string chatRoom;
			cin >> chatRoom;
			messenger->createAChatRoom(chatRoom);
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
			printf("invalid command! type %s for help\n", CLIENT_CLI_help);
		}
	}

	return 0;
}




