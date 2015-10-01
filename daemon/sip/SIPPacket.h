#ifndef _SIP_PACKET_H_
#define _SIP_PACKET_H_

#include "../Socket/Socket.h"
#include <osip2/osip.h>

#include <string>
using std::string;

class CSipException
{
	private:
		int m_iExCode;
		
	public:
		CSipException(int iExCode) : m_iExCode(iExCode) { }
		//
		inline int GetExceptionCode() const { return m_iExCode; }
};

class CAuthorization
{
	private:
		string m_strType;
		string m_strDomain;
		string m_strNonce;
		string m_strOpaque;
		string m_strQop;
		string m_strRealm;
		string m_strStale;
		//
		string m_strUser;
		string m_strPasswd;
	
	public:
		CAuthorization();
		CAuthorization(const CAuthorization &auth);
		~CAuthorization();
		//
		CAuthorization & operator=(const CAuthorization &auth);
		//
		inline void SetDomain(const string &strDomain) { m_strDomain = strDomain; }
		inline void SetNonce(const string &strNonce) { m_strNonce = strNonce; }
		inline void SetOpaque(const string &strOpaque) { m_strOpaque = strOpaque; }
		inline void SetQop(const string &strQop) { m_strQop = strQop; }
		inline void SetRealm(const string &strRealm) { m_strRealm = strRealm; }
		inline void SetStale(const string &strStale) { m_strStale = strStale; }
		inline void SetType(const string &strType) { m_strType = strType; }
		inline void SetUser(const string &strUser) { m_strUser = strUser; }
		inline void SetPasswd(const string &strPasswd) { m_strPasswd = strPasswd; }
		//
		inline string GetDomain() const { return m_strDomain; }
		inline string GetNonce() const { return m_strNonce; }
		inline string GetOpaque() const { return m_strOpaque; }
		inline string GetQop() const { return m_strQop; }
		inline string GetRealm() const { return m_strRealm; }
		inline string GetStale() const { return m_strStale; }
		inline string GetType() const { return m_strType; }
		inline string GetUser() const { return m_strUser; }
		inline string GetPasswd() const { return m_strPasswd; }
};

class CSipPacket : public CPacket
{
	private:
		osip_t *m_osip;
		string m_strCallId;
		string m_strBranch;
		string m_strCallerTag;
		string m_strCalleeTag;
		string m_strCallerId;
		string m_strCalleeId;
		string m_strCallerScreenName;
		string m_strCalleeScreenName;
		string m_strCallerAddress;
		string m_strSipServerAddress;
		string m_strContactAddress;
		string m_strUserAgent;
		string m_strServer;
		string m_strContentType;
		string m_strContent;
		string m_strCommand;
		string m_strCSeqCommand;
		string m_strStatus;
		int m_iStatusCode;
		int m_iCallerPort;
		int m_iCSeq;
		int m_iExpires;
		int m_iMaxForwards;
		CAuthorization m_auth;
		CAuthorization m_authProxy;
	
	protected:
		inline string ToString(char *szString) const { return ((szString != NULL) ? szString : ""); }
		string GetRandomId(int iLen) const;
	
	public:
		CSipPacket( const string &strCallerId, const string &strCalleeId, const string &strCallerAddress,
					int iCallerPort, const string &strSipServerAddress);
		CSipPacket(const CSipPacket &packet);
		CSipPacket & operator=(const CSipPacket &packet);
		virtual ~CSipPacket() = 0;
		//
		inline void SetCallId(const string &strCallId) { m_strCallId = strCallId; }
		inline void SetBranch(const string &strBranch) { m_strBranch = strBranch; }
		inline void SetCallerTag(const string &strCallerTag) { m_strCallerTag = strCallerTag; }
		inline void SetCalleeTag(const string &strCalleeTag) { m_strCalleeTag = strCalleeTag; }
		inline void SetCallerId(const string &strCallerId) { m_strCallerId = strCallerId; }
		inline void SetCalleeId(const string &strCalleeId) { m_strCalleeId = strCalleeId; }
		inline void SetCallerScreenName(const string &strCallerScreenName) { m_strCallerScreenName = strCallerScreenName; }
		inline void SetCalleeScreenName(const string &strCalleeScreenName) { m_strCalleeScreenName = strCalleeScreenName; }
		inline void SetCallerAddress(const string &strCallerAddress) { m_strCallerAddress = strCallerAddress; }
		inline void SetCallerPort(int iCallerPort) { m_iCallerPort = iCallerPort; }
		inline void SetSipServerAddress(const string &strSipServerAddress) { m_strSipServerAddress = strSipServerAddress; }
		inline void SetContactAddress(const string &strContactAddress) { m_strContactAddress = strContactAddress; }
		inline void SetUserAgent(const string &strUserAgent) { m_strUserAgent = strUserAgent; }
		inline void SetServer(const string &strServer) { m_strServer = strServer; }
		inline void SetCSeq(int iCSeq) { m_iCSeq = iCSeq; }
		inline void SetExpires(int iExpires) { m_iExpires = iExpires; }
		inline void SetMaxForwards(int iMaxForwards) { m_iMaxForwards = iMaxForwards; }
		inline void SetContentType(const string &strContentType) { m_strContentType = strContentType; }
		inline void SetContent(const string &strContent) { m_strContent = strContent; }
		inline void SetCommand(const string &strCommand) { m_strCommand = strCommand; }
		inline void SetCSeqCommand(const string &strCSeqCommand) { m_strCSeqCommand = strCSeqCommand; }
		inline void SetStatus(const string &strStatus) { m_strStatus = strStatus; }
		inline void SetStatusCode(int iStatusCode) { m_iStatusCode = iStatusCode; }
		//
		inline string GetCallId()           const { return m_strCallId; }
		inline string GetBranch()           const { return m_strBranch; }
		inline string GetCallerTag()        const { return m_strCallerTag; }
		inline string GetCalleeTag()        const { return m_strCalleeTag; }
		inline string GetCallerId()         const { return m_strCallerId; }
		inline string GetCalleeId()         const { return m_strCalleeId; }
		inline string GetCallerScreenName() const { return m_strCallerScreenName; }
		inline string GetCalleeScreenName() const { return m_strCalleeScreenName; }
		inline string GetCallerAddress()    const { return m_strCallerAddress; }
		inline int    GetCallerPort()       const { return m_iCallerPort; }
		inline string GetSipServerAddress() const { return m_strSipServerAddress; }
		inline string GetContactAddress()   const { return m_strContactAddress; }
		inline string GetUserAgent()        const { return m_strUserAgent; }
		inline string GetServer()           const { return m_strServer; }
		inline int    GetCSeq()             const { return m_iCSeq; }
		inline int    GetExpires()          const { return m_iExpires; }
		inline int    GetMaxForwards()      const { return m_iMaxForwards; }
		inline string GetContentType()      const { return m_strContentType; }
		inline string GetContent()          const { return m_strContent; }
		inline string GetCommand()          const { return m_strCommand; }
		inline string GetCSeqCommand()      const { return m_strCSeqCommand; }
		inline string GetStatus()           const { return m_strStatus; }
		inline int    GetStatusCode()       const { return m_iStatusCode; }
		inline CAuthorization & GetAuthorization() { return m_auth; }
		inline CAuthorization & GetProxyAuthorization() { return m_authProxy; }
		//
		virtual void BuildPacket() throw(CSipException *) = 0;
		void Update(const osip_message_t *sip);
		void Update(const string &data);
};

#endif	// _SIP_PACKET_H_
