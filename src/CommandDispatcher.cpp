/*
 * CommandDispatcher.cpp
 *
 *  Created on: May 14, 2016
 *      Author: Or Gafni
 */

#include "CommandDispatcher.h"
#include "ClientManager.h"
#include "iostream"

using namespace std;

CommandDispatcher::CommandDispatcher(ClientManager* manager)
{
	this->m_manager = manager;
}

// Getting requests from server and processing them
void CommandDispatcher::run()
{
	int command;
	string name;
	string ip;
	string data;
	string port;

	while (m_manager->isConnected)
	{
		command = m_manager->readCommand();

		switch(command)
		{
			case(CLOSE_SESSION_WITH_PEER):
			{
				m_manager->sessionWithPeerClosed();
				break;
			}
			case(CLOSE_SESSION_WITH_ROOM):
			{
				m_manager->userLeftRoom();
				break;
			}
			case(ENTER_ROOM):
			{
				m_manager->userEnterRoom();
				break;
			}
			case(SESSION_ESTABLISHED):
			{
				m_manager->sessionWithPeerOpened();
				break;
			}
			case(DISCONNECT):
			{
				m_manager->disconnectedFromServer();
				break;
			}
			case(SIGNUP_OK):
			{
				m_manager->signUpSuccess();
				break;
			}
			case(USER_EXISTS):
			{
				cout << "failed to sign up to server, the user name you choose already exist (" << m_manager->m_username << ")" << endl;
				break;
			}
			case(USER_NO_EXIST):
			{
				cout << "failed to login as <" << m_manager->m_username << ">, not exist on server" << endl;
				break;
			}
			case(CONNECTION_REFUSED):
			{
				cout << "failed to login as <" << m_manager->m_username << ">, password not match" << endl;
				break;
			}
			case(ALL_USERS):
			{
				m_manager->receivedAllUsers();
				break;
			}
			case(CONNECTED_USERS):
			{
				m_manager->receivedAllConnectedUsers();
				break;
			}
			case(ALL_ROOMS):
			{
				m_manager->receivedAllRooms();
				break;
			}
			case(ROOM_USERS):
			{
				m_manager->receivedAllUsersInRoom();
				break;
			}
			case(ROOM_NOT_EXIST):
			{
				cout << "room requested not exist" << endl;
				break;
			}
			case(ROOM_EXIST):
			{
				cout << "cannot create room, room name already exist on server" << endl;
				break;
			}
			case(USER_NO_EXIST):
			{
				cout << "cannot connect to requested user name <" << m_manager->m_peerName << ">. user not exist" << endl;
				break;
			}
			case(CONNECTED_TO_ROOM):
			{
				m_manager->connectedToRoomSuccessfully();
				break;
			}
			default:
			{
				cout << "server sent unknown command (" << command << ")" << endl;
				break;
			}
		}
//		// Session to another user is ready
//		case (SESSION_ESTABLISHED):
//
//			// Reading the peer's ip and port
//			data = m_manager->readData();
//			port = data.substr(0,5);
//			ip = data.substr(6);
//
//			// Start the session
//			m_manager->sessionCreated(ip, port);
//
//			break;
//
//		// Got request to open a session
//		case(OPEN_SESSION):
//
//			// Getting the peer's name
//			name = m_manager->readData();
//
//			// If in session, informing
//			if (m_manager->getIsInSession())
//			{
//				cout << "someone is trying to talk to you" << endl;
//			}
//			else
//			{
//				// Saving the peer's name and informing server
//				m_manager->setPeerName(name);
//				m_manager->sendMessage(SESSION_CREATED, name);
//			}
//		break;
//
//		// Got user list from server
//		case (USERS_LIST):
//			// Displaying
//			cout << m_manager->readData() << endl;
//			break;
//
//		// Got user details from server
//		case (USER_DETAILS):
//				// Displaying
//				cout << m_manager->readData() << endl;
//		break;
//
//		// A session was closed
//		case (CLOSE_SESSION):
//
//			// Displaying and closing session
//			cout << m_manager->readData() << endl;
//			m_manager->sessionClosed();
//		break;
//
//		// Server is shutting down
//		case (EXIT):
//			cout << m_manager->readData() << endl;
//			m_manager->serverClosed();
//		break;
//		case(ERROR):
//				cout << m_manager->readData() << endl;
//
//		break;
//		}
	}

}

