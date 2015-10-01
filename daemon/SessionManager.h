#ifndef _SESSION_MANAGER_H
#define _SESSION_MANAGER_H

#include <list>
//#include <string>

class CSession;

class CSessionManager {
  int m_iSocket;
  //bool m_state;
  std::list<CSession *> m_lsSession;

  bool BindAndListen(unsigned short usPort);
  bool CreateSession(int iSocket);
 public:
  /**
   * initialize instance
   * @param _usPort TCP port number the instance listen to
   * @return true if instance has been initialized successfully
   */
  bool Init(unsigned short usPort);
  CSessionManager();
  ~CSessionManager();
  void Run();
};

#endif

