#ifndef _SIPCLIENT_H_
#define _SIPCLIENT_H_

#include "SIPConstants.h"
#include "SIPRequest.h"
#include "SIPResponse.h"
#include "../Socket/Socket.h"

#include <queue>
#include <string>
using std::string;
using std::queue;

class CSipClient
{
	private:
		int m_iStatus;
		CSipRequest *m_sipLastSentRequest;
		CSipResponse *m_sipLastRecievedResponse;
		//
		bool m_bSipServerAddressChanged;
		//
		string m_strSipServerAddress;
		string m_strSipClientAddress;
		int m_iSipServerPort;
		int m_iSipClientPort;
		string m_strCalleeId;
		string m_strUserNamePrefix;
		string m_strAuthUser;
		string m_strAuthPasswd;
		//
		bool m_bInitialized;
		fd_set *m_fdsRead;
		fd_set *m_fdsWrite;
		CUdpServerSocket m_server;
		CUdpClientSocket m_client;
		//
		queue<CSipPacket *> m_qPacketQueue;
		
	protected:
		bool RecieveResponse(SOCKET socket) throw(SocketException *);
		void SendRequestQueue() throw(SocketException *);
		//
		void PushSipPacket(CSipPacket *p);
		void PushRegister(int iCSeq, bool bAuthRequired = false);
		void PushInvite(int iCSeq, bool bProxyAuthRequired = false);
		void PushCancel(int iCSeq);
		void PushAck(int iCSeq);
		void PushBye(int iCSeq);
		void PushOk(int iCSeq);
		
	public:
		CSipClient( const string &strSipServerAddress, int iSipServerPort,
					const string &strSipClientAddress, int iSipClientPort,
					const string &strCalleeId, const string &strAuthUser = "anonymous",
					const string &strAuthPasswd = "", const string &strUserNamePrefix = "nehet");
		~CSipClient();
		//
		inline int GetStatus() const { return m_iStatus; }
		inline CSipPacket * GetLastSentRequest() const { return m_sipLastSentRequest; }
		inline CSipPacket * GetLastRecievedResponse() const { return m_sipLastRecievedResponse; }
		inline string GetSipServerAddress() const { return m_strSipServerAddress; }
		inline bool SipServerAdressChanged() const { return m_bSipServerAddressChanged; }
		//
		bool Init(fd_set *fdsRead, fd_set *fdsWrite);
		void SetFd() throw(CSipException *);
		int Iterate() throw(CSipException *, SocketException *);
};

#endif	// _SIPCLIENT_H_
