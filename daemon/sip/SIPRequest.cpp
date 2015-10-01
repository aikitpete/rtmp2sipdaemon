#include "SIPConstants.h"
#include "SIPRequest.h"

#include <sstream>
#include <algorithm>
#include <vector>
using std::ostringstream;
using std::vector;
using std::find;

string
CSipRequest::unq(const string &strValue) const
{
	size_t pos1 = 1 + strValue.find('\"');
	size_t pos2 = strValue.rfind('\"');
	if(pos1 == pos2)	// none or only 1 quote found
		return strValue;
	//
	return strValue.substr(pos1, pos2 - pos1);
}

CSipRequest::CSipRequest(const CSipRequest &req) : CSipPacket(req)
{
	m_bAuthRequired = req.m_bAuthRequired;
	m_bProxyAuthRequired = req.m_bProxyAuthRequired;
}

CSipRequest::~CSipRequest()
{
	//
}

CSipRequest &
CSipRequest::operator=(const CSipRequest &req)
{
	*((CSipPacket *)this) = CSipPacket::operator=(req);
	m_bAuthRequired = req.m_bAuthRequired;
	m_bProxyAuthRequired = req.m_bProxyAuthRequired;
	//
	return *this;
}

void
CSipRequest::BuildPacket() throw(CSipException *)
{
	static vector<string> vSupportedCmds;
	if(vSupportedCmds.size() == 0)	// not initialized yet?
	{
		vSupportedCmds.push_back("REGISTER");
		vSupportedCmds.push_back("INVITE");
		vSupportedCmds.push_back("CANCEL");
		vSupportedCmds.push_back("ACK");
		vSupportedCmds.push_back("BYE");
	}
	//
	if(find(vSupportedCmds.begin(), vSupportedCmds.end(), GetCommand()) == vSupportedCmds.end())
		throw(new CSipException(SipError::UNSUPPORTED_COMMAND));
	//
	static ostringstream request;
	request.clear();
	request.str("");
	//
	if(GetCSeqCommand().length() == 0)
		SetCSeqCommand(GetCommand());
	//
	request << GetCommand() << " sip:";
	if(GetCommand() != "REGISTER")
	{
		request << GetCalleeId() << "@";
	}
	request << GetSipServerAddress() << " SIP/2.0\r\n"
			<< "Via: SIP/2.0/UDP " << GetCallerAddress() << ":" << GetCallerPort()
			<< ";branch=" << GetBranch() << "\r\n"
			<< "Contact: <sip:" << GetCallerId() << "@" << GetCallerAddress()
			<< ":" << GetCallerPort() << ">\r\n"
			<< "Call-ID: " << GetCallId() << "\r\n"
			<< "Cseq: " << GetCSeq() << " " << GetCSeqCommand() << "\r\n"
			<< "Expires: " << GetExpires() << "\r\n";
	//
	if(GetMaxForwards() > 0)
		request << "Max-Forwards: " << GetMaxForwards() << "\r\n";
	//
	if(GetUserAgent().length() > 0)
		request << "User-Agent: " << GetUserAgent() << "\r\n";
	//
	// To field:
	if(GetCommand() != "REGISTER")
	{
		request << "To: ";
		if(GetCalleeScreenName().length() > 0)
			request << "\"" << GetCalleeScreenName() << "\"";
		//
		request << "<sip:" << GetCalleeId() << "@" << GetSipServerAddress() << ">";
		if(GetCalleeTag().length() > 0)
			request << ";tag=" << GetCalleeTag();
		request << "\r\n";
	}
	else
	{
		request << "To: ";
		if(GetCallerScreenName().length() > 0)
			request << "\"" << GetCallerScreenName() << "\"";
		//
		request << "<sip:" << GetCallerId() << "@" << GetSipServerAddress() << ">\r\n";
	}
	//
	// From field:
	request << "From: ";
	if(GetCallerScreenName().length() > 0)
		request << "\"" << GetCallerScreenName() << "\"";
	//
	request << "<sip:" << GetCallerId() << "@" << GetSipServerAddress() << ">"
			<< ";tag=" << GetCallerTag() << "\r\n";
	//
	if((GetCommand() != "ACK") && (GetCommand() != "CANCEL"))
		request << "Allow: REGISTER, INVITE, ACK, CANCEL, BYE\r\n";
	//
	if(m_bAuthRequired)	// Authorization
	{	// TODO: this auth presume, that Type = Digest and Qop = auth
		//
		string A1 = GetAuthorization().GetUser() + ":" + unq(GetAuthorization().GetRealm())
					+ ":" + GetAuthorization().GetPasswd();
		string A2 = GetCommand() + ":sip:" + GetSipServerAddress();
		string KD_secret = md5(A1);
		string KD_data = unq(GetAuthorization().GetNonce()) + ":" + md5(A2);
		string response = md5(KD_secret + ":" + KD_data);
		//
		request << "Authorization: Digest username=\"" << GetAuthorization().GetUser() << "\","
				<< "realm=\"" << unq(GetAuthorization().GetRealm())
				<< "\",nonce=\"" << unq(GetAuthorization().GetNonce()) << "\","
				<< "uri=\"sip:" << GetSipServerAddress() << "\",response=\"" << response << "\",";
		//
		if(GetAuthorization().GetOpaque().length() > 0)
			request << "opaque=\"" << unq(GetAuthorization().GetOpaque()) << "\",";
		//
		request	<< "algorithm=MD5\r\n";
	}
	//
	if(m_bProxyAuthRequired)	// Proxy authorization
	{	// TODO: this auth presume, that Type = Digest and Qop = auth
		//
		string A1 = GetAuthorization().GetUser() + ":" + unq(GetAuthorization().GetRealm())
					+ ":" + GetAuthorization().GetPasswd();
		string A2 = GetCommand() + ":sip:" + GetSipServerAddress();
		string KD_secret = md5(A1);
		string KD_data = unq(GetAuthorization().GetNonce()) + ":" + md5(A2);
		string response = md5(KD_secret + ":" + KD_data);
		//
		request << "Proxy-Authorization: Digest username=\"" << GetProxyAuthorization().GetUser() << "\","
				<< "realm=\"" << unq(GetAuthorization().GetRealm())
				<< "\",nonce=\"" << unq(GetAuthorization().GetNonce()) << "\","
				<< "uri=\"sip:" << GetSipServerAddress() << "\",response=\"" << response << "\",";
		//
		if(GetAuthorization().GetOpaque().length() > 0)
			request << "opaque=\"" << unq(GetAuthorization().GetOpaque()) << "\",";
		//
		request	<< "algorithm=MD5\r\n";
	}
	//
	request << "Content-Type: " << GetContentType() << "\r\n"
			<< "Content-Length: " << GetContent().length() << "\r\n"
			<< "\r\n" << GetContent();
	//
	SetBuffer(request.str().c_str(), request.str().length());
}
