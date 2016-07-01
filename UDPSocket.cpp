/*
 * UDPSocket.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Eliav Menachi
 */

#include "UDPSocket.h"
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>


UDPSocket::UDPSocket(int port)
{
	// Create an UDP socket
	m_socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

	// Check that the socket created successfully
	if (m_socket_fd < 0)
	{
		error(1, errno, "Fail to create socket");
	}
	int enable = 1;
	if (setsockopt(m_socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	{
		error(1, errno, "setsockopt(SO_REUSEADDR) failed");
	}

	// Clear and fill the s_in struct
	struct sockaddr_in s_in;
	bzero((char*)&m_from, sizeof(s_in));
	s_in.sin_family = (short)AF_INET;
	s_in.sin_addr.s_addr = htonl(INADDR_ANY);
	s_in.sin_port = htons(port);

	// Bind the socket the to an address
	if (bind(m_socket_fd, (struct sockaddr*)&s_in,sizeof(s_in)) < 0)
	{
		error(1, errno, "Error naming channel");
	}

}

int UDPSocket::recv(char* buffer, int length)
{
	printf("UDP server receive ...\n");
	socklen_t fromSize = sizeof(m_from);
	int bytesReceived = recvfrom(m_socket_fd, buffer, length, 0,(struct sockaddr*)&m_from, &fromSize);

	if (bytesReceived < 0)
	{
		error(1, errno, "Fail to recvfrom");
	}

	return bytesReceived;
}

int UDPSocket::sendTo(const string& msg,const string& ip, int port)
{
	struct sockaddr_in destAddr;
	bzero((char*)&destAddr, sizeof(destAddr));
	destAddr.sin_family = (short)AF_INET;
	if (inet_pton(AF_INET, ip.data(), &destAddr.sin_addr) != 1)
	{
		error(1, errno, "fail to convert string ip to int ip");
	}
	destAddr.sin_port = htons(port);

	int bytesSent = sendto(m_socket_fd,
						   msg.data(),
						   msg.length(),
						   0,
						   (struct sockaddr*)&destAddr,
						   sizeof(destAddr));

	if (bytesSent < 0)
	{
		error(1, errno, "Failed to sendto");
	}

	return bytesSent;
}

int UDPSocket::reply(const string& msg){

	string destIp;
	return sendTo(msg, fromAddr(), ntohs(m_from.sin_port));
}

void UDPSocket::close(){
	cout<<"closing socket"<<endl;
	shutdown(m_socket_fd,SHUT_RDWR);
	::close(m_socket_fd);
}

string UDPSocket::fromAddr(){
	char fromAddr[INET_ADDRSTRLEN];
	if (inet_ntop(AF_INET, &(m_from.sin_addr), fromAddr, INET_ADDRSTRLEN) == NULL)
	{
		error(1, errno, "fail to convert addr to string");
	}
	return fromAddr;
}



