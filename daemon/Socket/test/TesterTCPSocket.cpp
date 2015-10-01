#include "TesterTCPSocket.h"
#include <iostream>
using std::cout;
using std::endl;

/* 
   Testing TCP server and TCP client
   ---------------------------------
   1) Start server -> tested by connecting to the server -> it's also test for client, that connecting works
   2) Multiple of clients send messages to server -> testing of client's send and server's recv
   3) Server respondes to client -> testing of server's send and client's recv
          + During 2 previous tests, there will be some delay to test waiting for message
   4) Server disconnects client -> client can't communicate
   5) Client disconnects itself from server -> client can't communicate
   6) Shutdown server -> tested by starting new server on the port used by server, that is shutted down (port can't be blocked)
*/

bool
CTesterTcpSocket::Init()
{
	m_server  = new CTcpServerSocket;
	m_client1 = new CTcpClientSocket;
	m_client2 = new CTcpClientSocket;
	return true;
}

bool
CTesterTcpSocket::Run()
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
		sock = m_server->WaitForIncomingData(1, 0);
		if(sock == m_server->GetSocket())
			client1 = m_server->AcceptConnection();
		else
			throw(new SocketException(SocketError::ERR_UNKNOWN));
		//
		m_client2->ConnectToHost("127.0.0.1", port);
		sock = m_server->WaitForIncomingData(1, 0);
		if(sock == m_server->GetSocket())
			client2 = m_server->AcceptConnection();
		else
			throw(new SocketException(SocketError::ERR_UNKNOWN));
		//
		cout << "OK" << endl;
		//
		// step 2 & 3
		cout << "Send/Recieve...";
		CPacket packet;
		CPacket p1("c1", 3);
		CPacket p2("c2", 3);
		m_client1->SendData(&p1);
		m_client2->SendData(&p2);
		for(int i = 0; i < 2; ++i)
		{
			packet.ClearBuffer();
			//
			sock = m_server->WaitForIncomingData(1, 0);
			m_server->RecieveData(sock, &packet);
			if(packet.GetLength() != 3)
				throw(new SocketException(SocketError::ERR_UNKNOWN));
			//
			if(string(packet.GetBuffer()) == "c1")
			{
				CPacket p("resp1", 6);
				m_server->SendData(sock, &p);
			}
			else if(string(packet.GetBuffer()) == "c2")
			{
				CPacket p("resp2", 6);
				m_server->SendData(sock, &p);
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
		cout << "Close connection...";
		bool ok = false;
		m_server->CloseConnection(client1);
		try
		{
			CPacket p("", 1);
			m_server->SendData(client1, &p);
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
		cout << "Disconnect from host...";
		ok = false;
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
		// step 6
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
CTesterTcpSocket::Clean()
{
	delete m_server;
	delete m_client1;
	delete m_client2;
	//
	return true;
}
