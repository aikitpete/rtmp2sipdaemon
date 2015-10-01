#ifndef _RTMP_H
#define _RTMP_H

#include <sys/types.h>
//#include <sys/socket.h>
//#include <unistd.h>
//#include <netinet/in.h>

class CRtmp {
  int m_iSocket;
  fd_set *m_pRead, *m_pWrite;
public:
  CRtmp(int iSocket);
  ~CRtmp();

  void Init(fd_set *pRead, fd_set *pWrite);
  void SetFd();
};

#endif

