//============================================================================
// Name        : UDPMessenger.h
// Author      : Eliav Menachi
// Version     :
// Copyright   : Your copyright notice
// Description : UDP Messenger application
//============================================================================

#include <pthread.h>
#include "UDPSocket.h"
#include "MThread.h"

using namespace std;


class UDPMessenger: public MThread{
	static const int MSNGR_PORT = 3344;
	UDPSocket* m_udpSocket;


public:
	UDPMessenger(int port);

	/**
	 * sends the given message to the given peer specified by IP and port
	 */
	void sendTo(string msg,string ip, int port);

	/**
	 * reply to an incoming message, this method will send the given message
	 * the peer from which the last message was received.
	 */
	void reply(string msg);

	/**
	 * close the messenger and all related objects (socket)
	 */
	void close();

	/**
	 * This method runs in a separate thread, it reads the incoming messages
	 * from the socket and prints the content on the terminal.
	 * The thread should exist when the socket is closed
	 */
	void run();
};

