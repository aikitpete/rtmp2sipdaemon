#include "TesterUDPSocket.h"
#include <iostream>
using std::cout;
using std::endl;

/* 
   Testing UDP server and UDP client
   ---------------------------------
   1) Start server -> tested by connecting to the server -> it's also test for client, that connecting works
   2) Multiple of clients send messages to server -> testing of client's send and server's recv
   3) Server respondes to client -> testing of server's send and client's recv
          + During 2 previous tests, there will be some delay to test waiting for message
   4) Client disconnects itself from server -> client can't communicate
   5) Shutdown server -> tested by starting new server on the port used by server, that is shutted down (port can't be blocked)
*/

bool
CTesterUdpSocket::Init()
{
	m_server  = new CUdpServerSocket;
	m_client1 = new CUdpClientSocket;
	m_client2 = new CUdpClientSocket;
	return true;
}

bool
CTesterUdpSocket::Run()
{
	try
	{
		SOCKET sock, client1, client2;
		// step 1
		cout << "Start server...";
		int port = 9999;
		for(int i = 0; i < 100; ++i, ++port)   // tries to listen on some port of range from 9999 to 10099
		{
			try
			{
				m_server->StartServer(port);
			}
			catch(SocketException *ex)
			{
				delete ex;
				continue;
			}
			break;
		}
		m_client1->ConnectToHost("127.0.0.1", port);
		m_client2->ConnectToHost("127.0.0.1", port);
		// UDP has no Accept; Just recieve some data, process and send back or somewhere else...
		cout << "OK" << endl;
		//
		// step 2 & 3
		cout << "Send/Recieve...";
		CPacket packet;
		CPacket p1("c1", 3);
		CPacket p2("c2", 3);
		m_client1->SendData(&p1);
		m_client2->SendData(&p2);
		sockaddr clientInfo;
		for(int i = 0; i < 2; ++i)
		{
			packet.ClearBuffer();
			memset(&clientInfo, 0, sizeof(clientInfo));
			//
			sock = m_server->WaitForIncomingData(1, 0);
			m_server->RecieveData(sock, &clientInfo, &packet);
			if(packet.GetLength() != 3)
				throw(new SocketException(SocketError::ERR_UNKNOWN));
			//
			if(string(packet.GetBuffer()) == "c1")
			{
				CPacket p("resp1", 6);
				m_server->SendData(sock, &clientInfo, &p);
				client1 = sock;
			}
			else if(string(packet.GetBuffer()) == "c2")
			{
				CPacket p("resp2", 6);
				m_server->SendData(sock, &clientInfo, &p);
				client2 = sock;
			}
			else
				throw(new SocketException(SocketError::ERR_UNKNOWN));
		}
		//   ... check ...
		packet.ClearBuffer();
		m_client1->RecieveData(&packet);
		if((string(packet.GetBuffer()) != "resp1") || (packet.GetLength() != 6))
			throw(new SocketException(SocketError::ERR_UNKNOWN));
		//
		packet.ClearBuffer();
		m_client2->RecieveData(&packet);
		if((string(packet.GetBuffer()) != "resp2") || (packet.GetLength() != 6))
			throw(new SocketException(SocketError::ERR_UNKNOWN));
		//
		cout << "OK" << endl;
		//
		// step 4
		cout << "Disconnect from host...";
		bool ok = false;
		m_client2->DisconnectFromHost();
		try
		{
			CPacket p("", 1);
			m_client2->SendData(&p);
		}
		catch(SocketException *ex)
		{
			delete ex;
			ok = true;
		}
		if(!ok)
			throw(new SocketException(SocketError::ERR_UNKNOWN));
		//
		cout << "OK" << endl;
		//
		// step 5
		cout << "Stop server...";
		m_server->StopServer();
		SLEEP(100);
		m_server->StartServer(port);
		SLEEP(100);
		m_server->StopServer();
		cout << "OK" << endl;
	}
	catch(SocketException *ex)
	{
		delete ex;
		cout << "FAILED" << endl;
		return false;
	}
	return true;
}

bool
CTesterUdpSocket::Clean()
{
	delete m_server;
	delete m_client1;
	delete m_client2;
	//
	return true;
}
