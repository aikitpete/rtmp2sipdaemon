#include "Session.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include "Rtmp.h"
#include "Debug.h"

CSession::CSession(int iSocket) :
m_rtmp(iSocket)
{
  m_state = SS_STOPED;
}

CSession::~CSession()
{
  DBGMSG("session destructor called")
}

void *SessionProc(void *pSession)
{
  CSession &_sess = *(CSession *)pSession;
  DBGMSG("session started")
  _sess.Run();
  DBGMSG("session ended")
  pthread_exit(NULL);
}

bool CSession::Start()
{
  return (pthread_create(&m_thread, NULL, SessionProc, (void *)this) == 0);
}

void CSession::Run()
{
  int _iResult;
  fd_set _read, _write;
  timeval _timeout = {0, 0};

  m_state = SS_STARTED;
  m_rtmp.Init(&_read, &_write);

  while(m_state != SS_STOPED) {

    _timeout.tv_sec = 1;
    FD_ZERO(&_read);
    FD_ZERO(&_write);

// setting fd_sets for read and write
    m_rtmp.SetFd();
//  m_sip.SetFd(&_read, &_write);
//  m_rtp.SetFd(&_read, &_write);
    _iResult = select(FD_SETSIZE, &_read, &_write, NULL, &_timeout);
    if(_iResult > 0) {
      DBGMSG("select session")
      switch(m_state) {
      case SS_STOPED:
        break;
      case SS_STARTED:
        DBGMSG("rtmp handshake")
        Handshake();
        break;
      case SS_CONNECTED:
        break;
      case SS_DIALING:
        break;
      case SS_TALKING:
        break;
      }
    } else if(_iResult == 0) {
      DBGMSG("select timeout")
    } else {
      DBGMSG("select error")
    }
  }
}

void CSession::Handshake()
{

}

