#include "Socket.h"

CUdpServerSocket::~CUdpServerSocket()
{
	//
}

void
CUdpServerSocket::StartServer(int iPort, int iQueueSize) throw(SocketException *)
{
	if((m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
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
}

int
CUdpServerSocket::SendData(int iSendTo, const sockaddr *clientInfo, const CPacket *pData) const throw(SocketException *)
{
	int addrlen = sizeof(*clientInfo);
	//
	int retval;
	if((retval = sendto(iSendTo, (const char *)pData->GetBuffer(), pData->GetLength(), 0, clientInfo, addrlen)) == -1)
		throw(new SocketException(SocketError::ERR_SEND_DATA));
	//
	return retval;
}

int
CUdpServerSocket::RecieveData(int iRecvFrom, sockaddr *clientInfo, CPacket *pData) throw(SocketException *)
{
	const int maxlen = 0xFFFF;	// 64kB
	char buf[maxlen];
	memset(buf, 0, maxlen);
	socklen_t addrlen = sizeof(*clientInfo);
	//
	int recv_ret;
	if((recv_ret = recvfrom(iRecvFrom, buf, maxlen, 0, clientInfo, &addrlen)) == -1)
		throw(new SocketException(SocketError::ERR_RECV_DATA));
	//
	if(recv_ret > 0)
		pData->AppendToBuffer(buf, recv_ret);
	//
	return recv_ret;
}
