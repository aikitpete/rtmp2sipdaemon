#ifndef _TESTERTCPSOCKET_H_
#define _TESTERTCPSOCKET_H_

#ifdef WIN32
//	#include <windows.h>
	#define SLEEP(msec) Sleep(msec)
#else	// WIN32
	#include <unistd.h>
	#define SLEEP(msec) usleep(msec * 1000)
#endif	// WIN32

#include "Tester.h"
#include "../Socket.h"

class CTesterTcpSocket : public CTester
{
	private:
		CTcpServerSocket *m_server;
		CTcpClientSocket *m_client1;
		CTcpClientSocket *m_client2;

	public:
		bool Init ();
		bool Run  ();
		bool Clean();
};

#endif	// _TESTERTCPSOCKET_H_
