#include "SessionManager.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <memory.h>
#include "Session.h"
#include "Debug.h"

const int MAX_CONNECTIONS = 10;

CSessionManager::CSessionManager()
{
  m_iSocket = 0;
}

CSessionManager::~CSessionManager()
{
  DBGMSG("manager destructor called")
  if(m_iSocket) {
    close(m_iSocket);
    m_iSocket = 0;
  }
}

bool CSessionManager::Init(unsigned short usPort)
{
  return BindAndListen(usPort);
}

void CSessionManager::Run()
{
  int _iResult;
  fd_set _read;
  timeval _timeout = {0, 0};
  _timeout.tv_sec = 1;

  FD_ZERO(&_read);
  FD_SET(m_iSocket, &_read);
  _iResult = select(FD_SETSIZE, &_read, NULL, NULL, &_timeout);
  if(_iResult == 1) {
    sockaddr_in _addr;
    socklen_t _addrlen = sizeof(_addr);
    _iResult = accept(m_iSocket, (sockaddr*)&_addr, &_addrlen);
    if(_iResult < 0) {
      return;
    }
    CreateSession(_iResult);
  }
}

bool CSessionManager::BindAndListen(unsigned short usPort)
{
  m_iSocket = socket(AF_INET, SOCK_STREAM, 0);
  if(m_iSocket < 0) {
    m_iSocket = 0;
    return false;
  }

  while(1) {
    if(fcntl(m_iSocket, F_SETFL, O_NONBLOCK))
      break;

    sockaddr_in _saddr;
    memset(&_saddr, 0, sizeof(_saddr));
    _saddr.sin_family = AF_INET;
    _saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    _saddr.sin_port = htons((u_short)usPort);
    if(bind(m_iSocket, (sockaddr *)&_saddr, sizeof(_saddr)))
      break;

    if(listen(m_iSocket, MAX_CONNECTIONS))
      break;

    return true;
  }
  close(m_iSocket);
  m_iSocket = 0;
  return false;
}

bool CSessionManager::CreateSession(int iSocket)
{
//  if(fcntl(_iSocket, F_SETFL, O_NONBLOCK))
//    return false;

  CSession *_sess = new CSession(iSocket);

  m_lsSession.push_back(_sess);

  _sess->Start();
  return true;
}

