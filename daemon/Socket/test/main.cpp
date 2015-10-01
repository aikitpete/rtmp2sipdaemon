#ifdef WIN32
	#include <vld.h>	// Memory leak detection
#endif

#include "TestSuitcase.h"

#include "TesterPacket.h"
#include "TesterTCPSocket.h"
#include "TesterUDPSocket.h"

int main()
{
	CTestSuitcase tests;
	tests.AddTester(new CTesterPacket, "CPacket");
	tests.AddTester(new CTesterTcpSocket, "CTcpSocket: Client --x-- Server");
	tests.AddTester(new CTesterUdpSocket, "CUdpSocket: Client --x-- Server\n[UDP doesn't check if some packet is lost]");
	tests.RunAll();
	return 0;
}
