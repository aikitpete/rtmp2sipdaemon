#ifndef _SIP_REQUEST_H_
#define _SIP_REQUEST_H_

#include "SIPPacket.h"
#include "../md5/md5.h"

#include <string>
using std::string;

class CSipRequest : public CSipPacket
{
	private:
		bool m_bAuthRequired;
		bool m_bProxyAuthRequired;
		
		inline string md5(const string &strValue) const { return MD5(strValue).hexdigest(); }
		string unq(const string &strValue) const;
	
	public:
		CSipRequest(const string &strCallerId, const string &strCalleeId, const string &strCallerAddress,
					int iCallerPort, const string &strSipServerAddress)
					: CSipPacket(strCallerId, strCalleeId, strCallerAddress, iCallerPort, strSipServerAddress)
					{ m_bAuthRequired = false; m_bProxyAuthRequired = false; }
		CSipRequest(const CSipPacket &p) : CSipPacket(p) { m_bAuthRequired = false; m_bProxyAuthRequired = false; }
		CSipRequest(const CSipRequest &req);
		virtual ~CSipRequest();
		//
		CSipRequest & operator=(const CSipRequest &req);
		//
		inline void SetAuthorizationRequired(bool bAuthRequired) { m_bAuthRequired = bAuthRequired; }
		inline void SetProxyAuthorizationRequired(bool bProxyAuthRequired) { m_bProxyAuthRequired = bProxyAuthRequired; }
		//
		inline bool IsAuthorizationRequired() const { return m_bAuthRequired; }
		inline bool IsProxyAuthorizationRequired() const { return m_bProxyAuthRequired; }
		//
		virtual void BuildPacket() throw(CSipException *);
};

#endif	// _SIP_REQUEST_H_
