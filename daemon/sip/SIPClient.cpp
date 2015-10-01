#include "SIPClient.h"

#include <algorithm>
#include <cctype>
#include <sstream>
using std::ostringstream;

inline string & __strtolower(string &str)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}

CSipClient::CSipClient( const string &strSipServerAddress, int iSipServerPort,
						const string &strSipClientAddress, int iSipClientPort,
						const string &strCalleeId, const string &strAuthUser,
						const string &strAuthPasswd, const string &strUserNamePrefix)
{
	m_bSipServerAddressChanged = false;
	//
	m_strSipServerAddress = strSipServerAddress;
	m_strSipClientAddress = strSipClientAddress;
	m_iSipServerPort = iSipServerPort;
	m_iSipClientPort = iSipClientPort;
	m_strCalleeId = strCalleeId;
	m_strAuthUser = strAuthUser;
	m_strAuthPasswd = strAuthPasswd;
	m_strUserNamePrefix = strUserNamePrefix;
	//
	m_iStatus = SipStatus::SS_INITIAL;
	//
	static ostringstream user;
	user.str("");
	user.clear();
	user << strAuthUser;	// TESTING ONLY!!!
	//user << m_strUserNamePrefix << iSipClientPort;
	//
	m_sipLastSentRequest = new CSipRequest(user.str(), strCalleeId, strSipClientAddress, iSipClientPort, strSipServerAddress);
	m_sipLastRecievedResponse = new CSipResponse(user.str(), strCalleeId, strSipClientAddress, iSipClientPort, strSipServerAddress);
	//
	m_sipLastSentRequest->GetAuthorization().SetUser(m_strAuthUser);
	m_sipLastSentRequest->GetAuthorization().SetPasswd(m_strAuthPasswd);
	//
	m_sipLastSentRequest->GetProxyAuthorization().SetUser(m_strAuthUser);
	m_sipLastSentRequest->GetProxyAuthorization().SetPasswd(m_strAuthPasswd);
	//
	m_bInitialized = false;
}

CSipClient::~CSipClient()
{
	m_client.DisconnectFromHost();
	m_server.StopServer();
	//
	while(!m_qPacketQueue.empty())
	{
		delete (m_qPacketQueue.front());
		m_qPacketQueue.pop();
	}
	//
	if(m_sipLastSentRequest != NULL)
		delete m_sipLastSentRequest;
	//
	if(m_sipLastRecievedResponse != NULL)
		delete m_sipLastRecievedResponse;
}

bool
CSipClient::RecieveResponse(SOCKET socket) throw(SocketException *)
{
	sockaddr ci;
	m_sipLastRecievedResponse->ClearBuffer();
	m_server.RecieveData(socket, &ci, m_sipLastRecievedResponse);
	m_sipLastRecievedResponse->Update(m_sipLastRecievedResponse->GetBuffer());
	//
	// check if it's response to the last sent request...others don't interest me at all
	if(m_sipLastSentRequest->GetCSeq() > m_sipLastRecievedResponse->GetCSeq())	// delayed response
		return false;															// - no need to be processed
	//
	// check call-id, tags and branch; if there is some difference, then some foreign transaction arrived
	if(m_sipLastSentRequest->GetCallId() != m_sipLastRecievedResponse->GetCallId())
		return false;
	//
	if(m_sipLastSentRequest->GetBranch() != m_sipLastRecievedResponse->GetBranch())
		return false;
	//
	if(m_sipLastSentRequest->GetCallerTag() != m_sipLastRecievedResponse->GetCallerTag())
		return false;
	//
/* check from anf to tags
   ----------------------
	if(m_sipLastSentRequest->GetCalleeTag().length() == 0)	// callee's tag wasn't set yet?
		m_sipLastSentRequest->SetCalleeTag(m_sipLastRecievedResponse->GetCalleeTag());
	else if(m_sipLastSentRequest->GetCalleeTag() != m_sipLastRecievedResponse->GetCalleeTag())
		return false;
*/
	//
	return true;
}

void
CSipClient::SendRequestQueue() throw(SocketException *)
{
	CSipPacket *tmp;
	while(!m_qPacketQueue.empty())
	{
		tmp = m_qPacketQueue.front();
		m_client.SendData(tmp);
		// no exception was thrown...ok
		m_qPacketQueue.pop();
		if(m_sipLastSentRequest)
			delete m_sipLastSentRequest;
		//
		m_sipLastSentRequest = (CSipRequest *)tmp;	// TODO: muze delat neplechu
	}
}

void
CSipClient::PushSipPacket(CSipPacket *p)
{
	m_qPacketQueue.push(p);
}

void
CSipClient::PushRegister(int iCSeq, bool bAuthRequired)
{
	CSipRequest *req = new CSipRequest(*m_sipLastSentRequest);
	req->SetCommand("REGISTER");
	req->SetCalleeTag("");	// don't use callee tag, because this is 1st request of the dialog
	req->SetContent("");
	req->SetCSeq(iCSeq);
	if(bAuthRequired)
	{
		req->SetAuthorizationRequired(true);
		req->GetAuthorization().SetDomain(m_sipLastRecievedResponse->GetAuthorization().GetDomain());
		req->GetAuthorization().SetNonce(m_sipLastRecievedResponse->GetAuthorization().GetNonce());
		req->GetAuthorization().SetOpaque(m_sipLastRecievedResponse->GetAuthorization().GetOpaque());
		req->GetAuthorization().SetQop(m_sipLastRecievedResponse->GetAuthorization().GetQop());
		req->GetAuthorization().SetRealm(m_sipLastRecievedResponse->GetAuthorization().GetRealm());
		req->GetAuthorization().SetStale(m_sipLastRecievedResponse->GetAuthorization().GetStale());
		req->GetAuthorization().SetType(m_sipLastRecievedResponse->GetAuthorization().GetType());
	}
	else
		req->SetAuthorizationRequired(false);
	//
	req->BuildPacket();
	//
	PushSipPacket(req);
}

void
CSipClient::PushInvite(int iCSeq, bool bProxyAuthRequired)
{
	CSipRequest *req = new CSipRequest(*m_sipLastSentRequest);
	req->SetCommand("INVITE");
	req->SetCalleeTag("");	// don't use callee tag, because this is 1st request of the dialog
	//req->SetContent("SDP -- TODO");
	req->SetCSeq(iCSeq);
	if(bProxyAuthRequired)
	{
		req->SetProxyAuthorizationRequired(true);
		req->GetProxyAuthorization().SetDomain(m_sipLastRecievedResponse->GetProxyAuthorization().GetDomain());
		req->GetProxyAuthorization().SetNonce(m_sipLastRecievedResponse->GetProxyAuthorization().GetNonce());
		req->GetProxyAuthorization().SetOpaque(m_sipLastRecievedResponse->GetProxyAuthorization().GetOpaque());
		req->GetProxyAuthorization().SetQop(m_sipLastRecievedResponse->GetProxyAuthorization().GetQop());
		req->GetProxyAuthorization().SetRealm(m_sipLastRecievedResponse->GetProxyAuthorization().GetRealm());
		req->GetProxyAuthorization().SetStale(m_sipLastRecievedResponse->GetProxyAuthorization().GetStale());
		req->GetProxyAuthorization().SetType(m_sipLastRecievedResponse->GetProxyAuthorization().GetType());
	}
	else
		req->SetProxyAuthorizationRequired(false);
	//
	req->BuildPacket();
	//
	PushSipPacket(req);
}

void
CSipClient::PushCancel(int iCSeq)
{
	CSipRequest *req = new CSipRequest(*m_sipLastSentRequest);
	req->SetCommand("CANCEL");
	req->SetContent("");
	req->SetCSeq(iCSeq);
	req->BuildPacket();
	//
	PushSipPacket(req);
}

void
CSipClient::PushAck(int iCSeq)
{
	CSipRequest *req = new CSipRequest(*m_sipLastSentRequest);
	req->SetCommand("ACK");
	req->SetContent("");
	req->SetCSeq(iCSeq);
	req->BuildPacket();
	//
	PushSipPacket(req);
}

void
CSipClient::PushBye(int iCSeq)
{
	CSipRequest *req = new CSipRequest(*m_sipLastSentRequest);
	req->SetCommand("BYE");
	req->SetCalleeTag("");	// don't use callee tag, because this is 1st request of the dialog
	req->SetContent("");
	req->SetCSeq(iCSeq);
	req->BuildPacket();
	//
	PushSipPacket(req);
}

void
CSipClient::PushOk(int iCSeq)
{
	CSipResponse *req = new CSipResponse(*m_sipLastRecievedResponse);
	req->SetStatusCode(200);
	req->SetStatus("OK");
	req->SetContent("");
	req->SetCSeq(iCSeq);
	req->SetCSeqCommand(m_sipLastSentRequest->GetCommand());
	req->BuildPacket();
	//
	PushSipPacket(req);
}

bool
CSipClient::Init(fd_set *fdsRead, fd_set *fdsWrite)
{
	if(((m_fdsRead = fdsRead) == NULL) || ((m_fdsWrite = fdsWrite) == NULL))
		return false;
	//
	m_server.StartServer(m_iSipClientPort);
	m_client.ConnectToHost(m_strSipServerAddress, m_iSipServerPort);
	//
	PushRegister(1);
	m_iStatus = SipStatus::SS_REGISTERING;
	//
	return (m_bInitialized = true);
}

void
CSipClient::SetFd() throw(CSipException *)
{
	if(!m_bInitialized)
		throw(new CSipException(SipError::NOT_INITIALIZED));
	//
	FD_SET(m_server.GetSocket(), m_fdsRead);
	FD_SET(m_client.GetSocket(), m_fdsRead);
	//
	if(m_qPacketQueue.size() > 0)	// no I need something to write?
		FD_SET(m_client.GetSocket(), m_fdsWrite);
}

int
CSipClient::Iterate() throw(CSipException *, SocketException *)
{
	if(!m_bInitialized)
		throw(new CSipException(SipError::NOT_INITIALIZED));
	//
	SOCKET socket = 0;
	if(FD_ISSET(m_server.GetSocket(), m_fdsRead))
	{
		socket = m_server.GetSocket();
	}
	else if(FD_ISSET(m_client.GetSocket(), m_fdsRead))
	{
		socket = m_client.GetSocket();
	}
	//
	if(socket != 0)
	{
		if(RecieveResponse(socket))
		{
			// call termination requested?
			if(m_sipLastRecievedResponse->GetCommand() == "BYE")
			{
				PushOk(m_sipLastRecievedResponse->GetCSeq());
				m_iStatus = SipStatus::SS_HANGING_UP;
			}
			//
			switch(m_sipLastRecievedResponse->GetStatusCode())
			{
				case SipResponse::RINGING:
					m_iStatus = SipStatus::SS_RINGING;
					break;
				
				case SipResponse::MULTIPLE_CHOICES:
					// TODO:
					//   send to rtmp client
					//   pick one
					//   alter callee
					//   resend request
					m_iStatus = SipStatus::SS_ERROR;
					throw(new CSipException(SipError::COMMUNICATION_TERMINATION));
					break;
				
				case SipResponse::MOVED_PERMANENTLY:
					m_bSipServerAddressChanged = true;
					m_strSipServerAddress = m_sipLastRecievedResponse->GetContactAddress();
				//
				case SipResponse::MOVED_TEMPORARILY:
					m_sipLastSentRequest->SetSipServerAddress(m_sipLastRecievedResponse->GetContactAddress());
					PushSipPacket(new CSipRequest(*m_sipLastSentRequest));
					break;
				
				case SipResponse::USE_PROXY:
					// TODO:
					//   add proxy to request
					//   resend request
					m_iStatus = SipStatus::SS_ERROR;
					throw(new CSipException(SipError::COMMUNICATION_TERMINATION));
					break;
				
				case SipResponse::UNAUTHORIZED:
					if(!m_sipLastSentRequest->IsAuthorizationRequired())	// need to be authorized
					{
						PushRegister(m_sipLastRecievedResponse->GetCSeq() + 1, true);
					}
					else	// authorization wasn't successful - bad login or bad format of request,
					{		// because there is implemented only Digest auth MD5 request type
						m_iStatus = SipStatus::SS_ERROR;
						throw(new CSipException(SipError::COMMUNICATION_TERMINATION));
					}
					break;

				case SipResponse::PROXY_AUTHENTICATION_REQUIRED:
					if(!m_sipLastSentRequest->IsProxyAuthorizationRequired())	// need to be authorized
					{
						PushInvite(m_sipLastRecievedResponse->GetCSeq() + 1, true);
					}
					else	// authorization wasn't successful - bad login or bad format of request,
					{		// because there is implemented only Digest auth MD5 request type
						m_iStatus = SipStatus::SS_ERROR;
						throw(new CSipException(SipError::COMMUNICATION_TERMINATION));
					}
					break;
				
				case SipResponse::REQUEST_TIMEOUT:
					PushSipPacket(new CSipRequest(*m_sipLastSentRequest));
					break;
				
				case SipResponse::REQUEST_ENTITY_TOO_LARGE:
					// if rety-after field
					//   wait && resend request
					// else
					//   error
					break;
				
				case SipResponse::TEPORARILY_UNAVAILABLE:	// far sip client hanged up
					m_iStatus = SipStatus::SS_HANGED_UP;
					break;
				
				case SipResponse::REQUEST_TERMINATED:		// far rtmp client hanged up and then this sip client sent CANCEL request
					m_iStatus = SipStatus::SS_HANGED_UP;
					break;
				
				default:
					if( (m_sipLastRecievedResponse->GetStatusCode() >= 100) &&
						(m_sipLastRecievedResponse->GetStatusCode() <= 199))	// 1xx
					{
						// keep waiting for some other response
					}
					else if((m_sipLastRecievedResponse->GetStatusCode() >= 200) &&
							(m_sipLastRecievedResponse->GetStatusCode() <= 299))	// 2xx
					{
						switch(m_iStatus)
						{
							case SipStatus::SS_REGISTERING:
								PushInvite(1);
								m_iStatus = SipStatus::SS_INVITING;
								break;
							
							case SipStatus::SS_INVITING:	// SDP
							case SipStatus::SS_RINGING:
								m_iStatus = SipStatus::SS_CALL_ACCEPTED;
								break;
							
							case SipStatus::SS_HANGING_UP:
								m_iStatus = SipStatus::SS_HANGED_UP;
								break;
							
							// Following responses are multiple responses, which mean, that some of following requests
							// were lost somewhere between client and server (caused by UDP transport) => resend
							case SipStatus::SS_CALL_ACCEPTED:
							case SipStatus::SS_CALLING:
								PushAck(m_sipLastRecievedResponse->GetCSeq() + 1);
								break;
							
							case SipStatus::SS_HANGED_UP:
								PushOk(m_sipLastRecievedResponse->GetCSeq());
								break;
							
							default:
								// nothing to do
								//   - a redundant or delayed packet (caused by UDP transport)
								//     or the client is already in final state
								break;
						}
					}
					else
					{
						m_iStatus = SipStatus::SS_ERROR;
						throw(new CSipException(SipError::COMMUNICATION_TERMINATION));
					}
					break;
			}
		}
	}
	//
	if(FD_ISSET(m_client.GetSocket(), m_fdsWrite))
	{
		SendRequestQueue();
	}
	//
	return m_iStatus;
}
