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

	m_isRun = true;
	char receivedMsg[MAX_MESSAGE_SIZE];
	int receivedBytes = 0;
	while (m_isRun)
	{
		receivedBytes = m_udpSocket->recv(receivedMsg, sizeof(receivedMsg));

		if (receivedBytes > 0)
		{
			cout << receivedMsg << endl;
		}

	}
	cout<<"closing receiver thread"<<endl;
}

UDPMessenger::UDPMessenger(int port)
{
	// init the messenger
	m_udpSocket = new UDPSocket(port);
	m_isRun = false;
	this->start();
}

UDPMessenger::~UDPMessenger()
{
	close();
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
	if (m_isRun == true)
	{
		m_isRun = false;
		waitForThread();
	}
	if (m_udpSocket != NULL)
	{
		m_udpSocket->close();
		delete m_udpSocket;
		m_udpSocket = NULL;
	}
}

