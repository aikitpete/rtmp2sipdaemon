#include "Rtmp.h"

#include <unistd.h>
#include "Debug.h"

CRtmp::CRtmp(int iSocket)
{
  m_iSocket = iSocket;
  m_pRead = NULL;
  m_pWrite = NULL;
}

CRtmp::~CRtmp()
{
  DBGMSG("rtmp destructor called")
  if(m_iSocket) {
    close(m_iSocket);
    m_iSocket = 0;
  }
}

void CRtmp::Init(fd_set *pRead, fd_set *pWrite)
{
  m_pRead = pRead;
  m_pWrite = pWrite;
}

void CRtmp::SetFd()
{
  FD_SET(m_iSocket, m_pRead);
  if(/* something to send */ 0) {
    FD_SET(m_iSocket, m_pWrite);
  }
}

