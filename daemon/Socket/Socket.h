/*************************************************************************
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ************************************************************************/

/**
 * @file
 * Socket.h
 * 
 * @author
 * Martin Ovesny (<a href="mailto:ovesnmar@fel.cvut.cz">ovesnmar@fel.cvut.cz</a>)
 *
 * @brief
 * Multiplatform (Windows and Unix tested) library for TCP and UDP socket manipulation.
 */

#ifndef _SOCKET_H_
#define _SOCKET_H_

#ifdef WIN32
	#ifdef MSVCpp
		#pragma warning(disable: 4290)
	#endif	// MSVCpp
	#include <Winsock2.h>
	#define socklen_t int
#else	// WIN32
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <netdb.h>
	#define closesocket close
	#define SOCKET int
#endif	// WIN32

#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
using std::string;
using std::vector;

namespace SocketError
{

	/**
	 * @brief
	 * Error flags thrown by SocketException.
	 */
	enum
	{
		ERR_UNKNOWN,
		ERR_INIT_SOCKET,
		ERR_PORT_OUT_OF_RANGE,
		ERR_CREATE_SOCKET,
		ERR_BIND_SOCKET,
		ERR_LISTEN_SOCKET,
		ERR_SELECT_SOCKET_INTERRUPTED,
		ERR_RESOLVE_ADDRESS,
		ERR_CONNECT_SOCKET,
		ERR_SEND_DATA,
		ERR_RECV_DATA,
		ERR_ACCEPT_CONNECTION
	};
}

/**
 * @brief
 * Socket exception. Only purpose of this class is that
 * it's not recommended to throw primitive data types.
 */
class SocketException
{
	private:
		int m_iExCode;
		
	public:
		/**
		 * @brief
		 * Constructor.
		 *
		 * @param iExCode
		 * Code of exception - from SocketError enumeration.
		 */
		SocketException(int iExCode) : m_iExCode(iExCode) { }
};

/**
 * @brief
 * Class encapsulating basic informations about packet (data and length).
 */
class CPacket
{
	private:
		char *m_pData;
		int m_iLen;
		
	public:
		/**
		 * @brief
		 * Default constructor (buffer is empty).
		 */
		CPacket();
		
		/**
		 * @brief
		 * Constructor. Data is copied into the buffer and lenfth is saved.
		 *
		 * @param pData
		 * Pointer to data buffer. It's char pointer only because of that char is 1 byte long.
		 *
		 * @param iLen
		 * Length of data in bytes.
		 */
		CPacket(const char *pData, int iLen);
		
		/**
		 * @brief
		 * Copy constructor.
		 */
		CPacket(const CPacket &packet);
		
		/**
		 * @brief
		 * Destructor.
		 */
		virtual ~CPacket();
		
		/**
		 * @brief
		 * Assign operator.
		 */
		CPacket & operator=(const CPacket &packet);
		
		/**
		 * @brief
		 * [getter] Length property
		 *
		 * @return
		 * Length of stored buffer in bytes.
		 */
		inline int GetLength() const { return m_iLen; }
		
		/**
		 * @brief
		 * [getter] Buffer property
		 *
		 * @return
		 * Constant pointer to data buffer.
		 */
		inline const char * GetBuffer() const { return m_pData; }
		
		/**
		 * @brief
		 * [getter] Buffer property contverted to unsigned char
		 *
		 * @return
		 * Constant pointer to data buffer.
		 */
		inline const unsigned char * GetBufferU() const { return (const unsigned char *)m_pData; }
		
		/**
		 * @brief
		 * Copy data to buffer and save length of data.
		 * If there is already some data in buffer, it's deleted!
		 *
		 * @param pData
		 * Pointer to data buffer. Buffer is coppied into internal buffer of class instance.
		 *
		 * @param iLen
		 * Length of data in bytes.
		 *
		 * @return
		 * Length of data in the internal buffer (same as iLen).
		 */
		int SetBuffer(const char *pData, int iLen);
		
		/**
		 * @brief
		 * Inserts data to the end of internal buffer.
		 *
		 * @param pData
		 * Pointer to data buffer, which you want to append.
		 * Buffer is coppied into internal buffer of class instance.
		 *
		 * @param iLen
		 * Length of appended data (pData) in bytes.
		 *
		 * @return
		 * Length of data in the internal buffer.
		 */
		int AppendToBuffer(const char *pData, int iLen);
		
		/**
		 * @brief
		 * Deletes buffer content and sets length = 0.
		 */
		void ClearBuffer();
};

/**
 * @brief
 * Abstract base class for socket communication.
 */
class CSocketBase
{
	protected:
		/**
		 * @brief
		 * Socket of client if class is implemented by client of server if it's server class.
		 */
		SOCKET m_sock;
		
	public:
		/**
		 * @brief
		 * Constructor. Initializes socket library (Windows platform only).
		 *
		 * @throw SocketException
		 * SocketError::ERR_INIT_SOCKET - socket engine can't be initialized (Windows platform only)
		 */
		CSocketBase() throw(SocketException *);
		
		/**
		 * @brief
		 * Destructor.
		 */
		virtual ~CSocketBase() = 0;
		
		/**
		 * @brief
		 * [getter] Socket property (m_sock).
		 *
		 * @return
		 * Internal socket handle.
		 */
		virtual inline SOCKET GetSocket() const { return m_sock; }
		
		/**
		 * @brief
		 * Waits until some of sockets isn't readable or time runs out.
		 * Uses select() inside.
		 * Time to wait = lSec + lUsec.
		 *
		 * @throw SocketException
		 * SocketError::ERR_SELECT_SOCKET_INTERRUPTED - error occured during the select() call
		 * it can happen in case of system signal, etc.
		 *
		 * @param lSec
		 * Time in seconds to wait. If lSec == -1 then wait interval is infinite.
		 *
		 * @param lUsec
		 * Time in microseconds to wait.
		 *
		 * @return
		 * Socket, which is now readable. It's a return value of the select() call.
		 */
		virtual SOCKET WaitForIncomingData(long lSec = -1, long lUsec = 0) throw(SocketException *);
		
		/**
		 * @brief
		 * Reads data from socket (iRecvFrom) to CPacket object.
		 *
		 * @throw SocketException
		 * SocketError::ERR_RECV_DATA - error occured during the reading
		 *
		 * @param iRecvFrom
		 * Socket which data is read from.
		 *
		 * @param pData
		 * [out] Pointer to CPacket object, which is filled by incoming data in the method.
		 *
		 * @return
		 * Length of data read by method.
		 */
		virtual int RecieveData(int iRecvFrom, CPacket *pData) throw(SocketException *);
		
		/**
		 * @brief
		 * Writes data to socket (iSendTo) from CPacket object.
		 *
		 * @throw SocketException
		 * SocketError::ERR_SEND_DATA - error occured during the writing
		 *
		 * @param iSendTo
		 * Socket which data is send to.
		 *
		 * @param pData
		 * Pointer to CPacket object, which is read and written to socket (iSendTo) in the method.
		 *
		 * @return
		 * Length of data written by method.
		 */
		virtual int SendData(int iSendTo, const CPacket *pData) const throw(SocketException *);
};

/**
 * @brief
 * Abstract base class for server socket.
 */
class CServerSocketBase : public CSocketBase
{
	public:
		/**
		 * @brief
		 * Default constructor.
		 */
		CServerSocketBase() : CSocketBase() { }
		
		/**
		 * @brief
		 * Destructor.
		 */
		virtual ~CServerSocketBase() = 0;
		
		/**
		 * @brief
		 * Starts up the server listening on iPort.
		 *
		 * @throw SocketException
		 * SocketError::ERR_CREATE_SOCKET - Can't create socket.
		 * SocketError::ERR_BIND_SOCKET   - Can't bind socket. Port is probably block by another application.
		 * SocketError::ERR_LISTEN_SOCKET - Can't set request queue size (TCP only).
		 *
		 * @param iPort
		 * Port which server will listen on.
		 *
		 * @param iQueueSize
		 * Size of client's request queue.
		 */
		virtual void StartServer(int iPort, int iQueueSize = 100) throw(SocketException *) = 0;
		
		/**
		 * @brief
		 * Stops server listening.
		 */
		virtual inline void StopServer() { shutdown(m_sock, 2); closesocket(m_sock); }
};

/**
 * @brief
 * Abstract base class for client socket.
 */
class CClientSocketBase : public CSocketBase
{
	public:
		/**
		 * @brief
		 * Default constructor.
		 */
		CClientSocketBase() : CSocketBase() { }
		
		/**
		 * @brief
		 * Destructor.
		 */
		virtual ~CClientSocketBase() = 0;
		
		/**
		 * @brief
		 * Calls CSocketBase::SendData(m_sock, pData), because client socket doesn't
		 * send requests to more than one server.
		 *
		 * @see
		 * CSocketBase::SendData
		 */
		virtual inline int SendData(const CPacket *pData) const throw(SocketException *) { return CSocketBase::SendData(m_sock, pData); }
		
		/**
		 * @brief
		 * Calls CSocketBase::RecieveData(m_sock, pData), because client socket doesn't
		 * recieve responds from more than one server.
		 *
		 * @see
		 * CSocketBase::RecieveData
		 */
		virtual inline int RecieveData(CPacket *pData)  throw(SocketException *) { return CSocketBase::RecieveData(m_sock, pData); }
		
		/**
		 * @brief
		 * Connects to server.
		 *
		 * @throw SocketException
		 * SocketError::ERR_RESOLVE_ADDRESS   - Can't translate address from DNS name.
		 * SocketError::ERR_CREATE_SOCKET     - Can't create socket.
		 * SocketError::ERR_CONNECT_SOCKET    - Can't connect to server.
		 * SocketError::ERR_PORT_OUT_OF_RANGE - port is out of range. It has to be between 0 and 65535
		 *
		 * @param strAddress
		 * Address of server. May be both IP addres and DNS stranslated address.
		 *
		 * @param iPort
		 * Port which server is litening on.
		 */
		virtual void ConnectToHost(const string &strAddress, int iPort) throw(SocketException *) = 0;
		
		/**
		 * @brief
		 * Disconnects from server.
		 */
		virtual inline void DisconnectFromHost() { shutdown(m_sock, 2); closesocket(m_sock); }
};

/**
 * @brief
 * Client socket implementation for UDP.
 */
class CUdpClientSocket : public CClientSocketBase
{
	public:
		/**
		 * @brief
		 * Default constructor.
		 */
		CUdpClientSocket() : CClientSocketBase() { }
		
		/**
		 * @brief
		 * Default destructor.
		 */
		virtual ~CUdpClientSocket();
		
		/**
		 * @brief
		 * UDP sockets don't connect to server. This function is user, because
		 * when it "connects", you don't need to fill information about socket, what you send.
		 * You can simply use CClientSocketBase::RecieveData and CClientSocketBase::SendData
		 * which both have only one parameter - data.
		 *
		 * @see
		 * CClientSocketBase::ConnectToHost
		 */
		virtual void ConnectToHost(const string &address, int port) throw(SocketException *);
};

/**
 * @brief
 * Server socket implementation for UDP.
 */
class CUdpServerSocket : public CServerSocketBase
{
	public:
		/**
		 * @brief
		 * Default constructor.
		 */
		CUdpServerSocket() : CServerSocketBase() { }
		
		/**
		 * @brief
		 * Destructor.
		 */
		virtual ~CUdpServerSocket();
		
		/**
		 * @brief
		 * Starts server.
		 *
		 * @see
		 * CServerSocketBase::StartServer
		 */
		virtual void StartServer(int iPort, int iQueueSize = 100) throw(SocketException *);
		
		/**
		 * @brief
		 * Reads data from socket (iRecvFrom) to CPacket object.
		 *
		 * @throw SocketException
		 * SocketError::ERR_RECV_DATA - error occured during the reading
		 *
		 * @param iRecvFrom
		 * Socket which data is read from.
		 *
		 * @param clientInfo
		 * [out] Information about client (address info - IPv4/IPv6, etc.).
		 *
		 * @param pData
		 * [out] Pointer to CPacket object, which is filled by incoming data in the method.
		 *
		 * @return
		 * Length of data read by method.
		 *
		 * @see
		 * CSocketBase::RecieveData
		 */
		virtual int RecieveData(int iRecvFrom, sockaddr *clientInfo, CPacket *pData) throw(SocketException *);
		
		/**
		 * @brief
		 * Writes data to socket (iSendTo) from CPacket object.
		 *
		 * @throw SocketException
		 * SocketError::ERR_SEND_DATA - error occured during the writing
		 *
		 * @param iSendTo
		 * Socket which data is send to.
		 *
		 * @param clientInfo
		 * Information about client (address info - IPv4/IPv6, etc.).
		 *
		 * @param pData
		 * Pointer to CPacket object, which is read and written to socket (iSendTo) in the method.
		 *
		 * @return
		 * Length of data written by method.
		 *
		 * @see
		 * CSocketBase::SendData
		 */
		virtual int SendData(int iSendTo, const sockaddr *clientInfo, const CPacket *pData) const throw(SocketException *);
};

/**
 * @brief
 * Client socket implementation for TCP.
 */
class CTcpClientSocket : public CClientSocketBase
{
	public:
		/**
		 * @brief
		 * Default constructor.
		 */
		CTcpClientSocket() : CClientSocketBase() { }
		
		/**
		 * @brief
		 * Destructor.
		 */
		virtual ~CTcpClientSocket();
		
		/**
		 * @brief
		 * Connects to server.
		 *
		 * @see
		 * CClientSocketBase::ConnectToHost
		 */
		virtual void ConnectToHost(const string &address, int port) throw(SocketException *);
};

/**
 * @brief
 * Server socket implementation fot TCP.
 */
class CTcpServerSocket : public CServerSocketBase
{
	protected:
		/**
		 * @brief
		 * List of clients, that are connected to server.
		 */
		vector<SOCKET> m_vClients;
		
	public:
		/**
		 * @brief
		 * Default constructor.
		 */
		CTcpServerSocket() : CServerSocketBase() { }
		
		/**
		 * @brief
		 * Destructor.
		 */
		virtual ~CTcpServerSocket();
		
		/**
		 * @brief
		 * Starts server.
		 *
		 * @see
		 * CServerSocketBase::StartServer
		 */
		virtual void StartServer(int iPort, int iQueueSize = 100) throw(SocketException *);
		
		/**
		 * @brief
		 * Stops server.
		 *
		 * @see
		 * CServerSocketBase::StopServer
		 */
		virtual void StopServer();
		
		/**
		 * @brief
		 * Accepts connection = adds client's socket to the list of connected clients.
		 *
		 * @throw SocketException
		 * SocketError::ERR_ACCEPT_CONNECTION - error during accepting client
		 *
		 * @param ip
		 * [out] Information about client which is accepted (IP address, etc.).
		 *
		 * @return
		 * Socket of client, whose connection is accepted.
		 */
		virtual int AcceptConnection(in_addr *ip = NULL) throw(SocketException *);
		
		/**
		 * @brief
		 * Closes connection with client.
		 *
		 * @param iClient
		 * Client's socket, whitch you can close connection with.
		 */
		virtual void CloseConnection(int iClient);
		
		/**
		 * @brief
		 * Waits until some of sockets (client's for recieving data or
		 * server's for accepting new client's connections) isn't readable or time runs out.
		 *
		 * @see
		 * CSocketBase::WaitForIncomingData
		 */
		virtual SOCKET WaitForIncomingData(long lSec = -1, long lUsec = 0) throw(SocketException *);
};
	
#endif	// _SOCKET_H_
