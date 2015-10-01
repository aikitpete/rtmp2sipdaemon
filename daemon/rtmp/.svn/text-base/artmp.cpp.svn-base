/* A simple server in the internet domain using TCP
   The port number is passed as an argument */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cstdio>

using namespace std;

#include "../Socket/Socket.h"
#include "crtmpsession.h"


void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     CTcpServerSocket _serverSocket;

     _serverSocket.StartServer(1935,1);
     int _iSocket = _serverSocket.AcceptConnection();

     CRtmpSession _rtmpSession(&_serverSocket, _iSocket);

     _rtmpSession.Run();

     _serverSocket.StopServer();

     return 0; 
}
