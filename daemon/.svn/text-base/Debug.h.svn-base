#ifndef _DEBUG_H
#define _DEBUG_H

#include <syslog.h>

#ifdef _DEBUG
#define DBGOPEN(n)\
openlog(n, LOG_PID|LOG_CONS, LOG_USER);

#define DBGMSG(m)\
syslog(LOG_DEBUG, m);

#elif
#define DBGOPEN(f) 
#define DBGMSG(m) 
#endif

#endif

