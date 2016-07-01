//============================================================================
// Name        : UDPMessenger
// Author      : Eliav Menachi
// Version     :
// Copyright   : Your copyright notice
// Description : UDP Messenger application
//============================================================================

#include "UDPMessenger.h"

using namespace std;

#define MAX_MESSAGE_SIZE (100)

void UDPMessenger::run()
{
	// receiver thread...

	char receivedMsg[MAX_MESSAGE_SIZE];
	while (m_udpSocket != NULL)
	{
		m_udpSocket->recv(receivedMsg, sizeof(receivedMsg));
		cout << "incoming msg: " << receivedMsg << endl;
	}
	cout<<"closing receiver thread"<<endl;
}

UDPMessenger::UDPMessenger(int port)
{
	// init the messenger
	m_udpSocket = new UDPSocket(port);

	this->start();
}

void UDPMessenger::sendTo(string msg,string ip, int port)
{
	m_udpSocket->sendTo(msg, ip, port);
}

void UDPMessenger::reply(string msg)
{
	m_udpSocket->reply(msg);
}

void UDPMessenger::close()
{
	m_udpSocket->close();
	delete m_udpSocket;
	m_udpSocket = NULL;
}

