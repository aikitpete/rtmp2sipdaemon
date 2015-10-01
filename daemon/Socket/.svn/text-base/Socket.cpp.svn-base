#include "Socket.h"

CSocketBase::CSocketBase() throw(SocketException *)
{
#ifdef WIN32
	WSADATA m_wsaData;
	WORD wVersionRequested = MAKEWORD(1,1);
	if(WSAStartup(wVersionRequested, &m_wsaData) != 0)
		throw(new SocketException(SocketError::ERR_INIT_SOCKET));
#endif	// WIN32
}

CSocketBase::~CSocketBase()
{
#ifdef WIN32
	WSACleanup();
#endif	// WIN32
}

int
CSocketBase::SendData(int iSendTo, const CPacket *pData) const throw(SocketException *)
{
	int retval;
	if((retval = send(iSendTo, (const char *)pData->GetBuffer(), pData->GetLength(), 0)) == -1)
		throw(new SocketException(SocketError::ERR_SEND_DATA));
	//
	return retval;
}

int
CSocketBase::RecieveData(int iRecvFrom, CPacket *pData) throw(SocketException *)
{
	const int maxlen = 0xFFFF;	// 64kB
	char buf[maxlen];
	memset(buf, 0, maxlen);
	int recv_ret;
	if((recv_ret = recv(iRecvFrom, buf, maxlen, 0)) == -1)
		throw(new SocketException(SocketError::ERR_RECV_DATA));
	//
	if(recv_ret > 0)
		pData->AppendToBuffer(buf, recv_ret);
	//
	return recv_ret;
}

SOCKET
CSocketBase::WaitForIncomingData(long lSec, long lUsec) throw(SocketException *)
{
	fd_set rfds;
	timeval tv;
	tv.tv_sec = lSec;
	tv.tv_usec = lUsec;
	//
	FD_ZERO(&rfds);
	FD_SET(m_sock, &rfds);
	if(select(m_sock + 1, &rfds, NULL, NULL, (lSec == -1 ? NULL : &tv)) < 0)
		throw(new SocketException(SocketError::ERR_SELECT_SOCKET_INTERRUPTED));
	//
	if(FD_ISSET(m_sock, &rfds))
		return m_sock;
	//
	return -1;
}

CClientSocketBase::~CClientSocketBase()
{
	//
}

CServerSocketBase::~CServerSocketBase()
{
	//
}
