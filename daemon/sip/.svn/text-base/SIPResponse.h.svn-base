#ifndef _SIP_RESPONSE_H_
#define _SIP_RESPONSE_H_

#include "SIPPacket.h"

class CSipResponse : public CSipPacket
{
	public:
		CSipResponse(const string &strCallerId, const string &strCalleeId, const string &strCallerAddress,
					 int iCallerPort, const string &strSipServerAddress)
					: CSipPacket(strCallerId, strCalleeId, strCallerAddress, iCallerPort, strSipServerAddress)
					{ }
		CSipResponse(const CSipPacket &p) : CSipPacket(p) { }
		CSipResponse(const CSipResponse &resp) : CSipPacket(resp) { }
		virtual ~CSipResponse();
		//
		CSipResponse & operator=(const CSipResponse &resp);
		//
		virtual void BuildPacket() throw(CSipException *);
};

#endif	// _SIP_RESPONSE_H_
