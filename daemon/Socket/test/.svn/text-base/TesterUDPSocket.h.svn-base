#ifndef _TESTERUDPSOCKET_H_
#define _TESTERUDPSOCKET_H_

#ifdef WIN32
//	#include <windows.h>
	#define SLEEP(msec) Sleep(msec)
#else	// WIN32
	#include <unistd.h>
	#define SLEEP(msec) usleep(msec * 1000)
#endif	// WIN32

#include "Tester.h"
#include "../Socket.h"

class CTesterUdpSocket : public CTester
{
	private:
		CUdpServerSocket *m_server;
		CUdpClientSocket *m_client1;
		CUdpClientSocket *m_client2;

	public:
		bool Init ();
		bool Run  ();
		bool Clean();
};

#endif	// _TESTERUDPSOCKET_H_
