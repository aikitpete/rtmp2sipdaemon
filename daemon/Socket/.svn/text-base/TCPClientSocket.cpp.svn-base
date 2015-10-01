#include "Socket.h"

CTcpClientSocket::~CTcpClientSocket()
{
	//
}

void
CTcpClientSocket::ConnectToHost(const string &strAddress, int iPort) throw(SocketException *)
{
	if((iPort <= 0) && (iPort >= 65536))
		throw(new SocketException(SocketError::ERR_PORT_OUT_OF_RANGE));
	//
	hostent *host = gethostbyname(strAddress.c_str());
	if(host == NULL)
		throw(new SocketException(SocketError::ERR_RESOLVE_ADDRESS));
	//
	if((m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		throw(new SocketException(SocketError::ERR_CREATE_SOCKET));
	//
	sockaddr_in serverSock;
	serverSock.sin_family = AF_INET;
	serverSock.sin_port = htons(iPort);
	memcpy(&(serverSock.sin_addr), host->h_addr, host->h_length);
	//
	if(connect(m_sock, (sockaddr *)&serverSock, sizeof(serverSock)) == -1)
		throw(new SocketException(SocketError::ERR_CONNECT_SOCKET));
	//
}
