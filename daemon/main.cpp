#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include "SessionManager.h"
#include "Debug.h"

const char *RUNNING_DIR = "/";

void signal_handler(int sig)
{
  switch(sig) {
  case SIGHUP:
    DBGMSG("sighup")
    break;
  case SIGTERM:
    DBGMSG("sigterm")
    exit(0);
    break;
  default:
    DBGMSG("unhandled signal")
  }
}

void daemonize()
{
  pid_t _pid, _sid;

  if(getppid() == 1)
    return; /* already a daemon */

  _pid = fork();
  if(_pid < 0)
    exit(1); /* fork error */
  if(_pid > 0)
    exit(0); /* parent exits */

  /* child (daemon) continues */
  _sid = setsid(); /* obtain a new process group */
  umask(0); /* set newly created file permissions */
  chdir(RUNNING_DIR); /* change running directory */

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  signal(SIGCHLD,SIG_IGN); /* ignore child */
  signal(SIGTSTP,SIG_IGN); /* ignore tty signals */
  signal(SIGTTOU,SIG_IGN);
  signal(SIGTTIN,SIG_IGN);
  signal(SIGHUP,signal_handler); /* catch hangup signal */
  signal(SIGTERM,signal_handler); /* catch kill signal */
}

int main()
{
  daemonize();
  DBGOPEN("OurDaemon")

  CSessionManager _manager;
  if(_manager.Init(5000)) {
    DBGMSG("manager init succeeded on port 5000")
  } else {
    DBGMSG("manager init failed")
    exit(-1);
  }

  while(1) {
    _manager.Run();
    sleep(1);
  }
  DBGMSG("main loop ended")
  exit(0);
}

