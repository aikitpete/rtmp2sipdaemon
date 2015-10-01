#include "Socket.h"
#include <algorithm>

CTcpServerSocket::~CTcpServerSocket()
{
	//
}

void
CTcpServerSocket::StartServer(int iPort, int iQueueSize) throw(SocketException *)
{
	if((m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	    throw(new SocketException(SocketError::ERR_CREATE_SOCKET));
	//
	sockaddr_in sockName;
	sockName.sin_family = AF_INET;
	sockName.sin_port = htons(iPort);
	sockName.sin_addr.s_addr = INADDR_ANY;
	//
	if(bind(m_sock, (sockaddr *)&sockName, sizeof(sockName)) == -1)
	    throw(new SocketException(SocketError::ERR_BIND_SOCKET));
	//
	if(listen(m_sock, iQueueSize) == -1)
		throw(new SocketException(SocketError::ERR_LISTEN_SOCKET));
	//
}

void CTcpServerSocket::StopServer()
{
	for(size_t i = 0, i_max = m_vClients.size(); i < i_max; ++i)
	{
		shutdown(m_vClients[i], 2);
		closesocket(m_vClients[i]);
	}
	m_vClients.clear();
	//
	shutdown(m_sock, 2);
	closesocket(m_sock);
}

int
CTcpServerSocket::AcceptConnection(in_addr *ip) throw(SocketException *)
{
	SOCKET retval;
	sockaddr_in clientInfo;
	socklen_t addrlen = sizeof(clientInfo);
	retval = accept(m_sock, (sockaddr*)&clientInfo, &addrlen);
	if(retval == -1)
		throw(new SocketException(SocketError::ERR_ACCEPT_CONNECTION));
	//
	m_vClients.push_back(retval);
	//
	if(ip)
		memcpy(ip, &clientInfo.sin_addr, sizeof(clientInfo.sin_addr));
	//
	return retval;
}

void
CTcpServerSocket::CloseConnection(int iClient)
{
	shutdown(iClient, 2);
	closesocket(iClient);
	//
	vector<SOCKET>::iterator itErase = find(m_vClients.begin(), m_vClients.end(), iClient);
	if(itErase != m_vClients.end())
		m_vClients.erase(itErase);
}

SOCKET
CTcpServerSocket::WaitForIncomingData(long lSec, long lUsec) throw(SocketException *)
{
	fd_set rfds;
	timeval tv;
	tv.tv_sec = lSec;
	tv.tv_usec = lUsec;
	//
	SOCKET max = m_sock;
	FD_ZERO(&rfds);
	FD_SET(max, &rfds);
	for(size_t i = 0, i_max = m_vClients.size(); i < i_max; ++i)
    {
        FD_SET(m_vClients[i], &rfds);
        if(m_vClients[i] > max)
			max = m_vClients[i];
    }
	if(select(max + 1, &rfds, NULL, NULL, (lSec == -1 ? NULL : &tv)) < 0)
		throw(new SocketException(SocketError::ERR_SELECT_SOCKET_INTERRUPTED));
	//
	if(FD_ISSET(m_sock, &rfds))
		return m_sock;
	//
	for(size_t i = 0, i_max = m_vClients.size(); i < i_max; ++i)
    {
		if(FD_ISSET(m_vClients[i], &rfds))
			return m_vClients[i];
    }
	//
	return -1;
}
