#ifndef _SESSION_H
#define _SESSION_H

#include <pthread.h>
#include "Rtmp.h"

enum SessionState {
  SS_STARTED,
  SS_STOPED,
  SS_CONNECTED,
  SS_DIALING,
  SS_TALKING
};

class CSession {
  SessionState m_state;
  pthread_t m_thread;
  CRtmp m_rtmp;

 public:
  CSession(int iSocket);
  ~CSession();

  /**
   * creates and runs thread
   * @return true if thread has been created successfully
   */
  bool Start();

  /**
   * implements session main logic
   */
  void Run();

  /**
   * thread's entry point, calls Run() method
   * @param _pSession pointer to session object
   * @return pthread exit status
   */
//  friend void *SessionProc(void *pSession);

  void Handshake();
};

#endif

