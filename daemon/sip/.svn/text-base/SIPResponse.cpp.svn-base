#include "SIPConstants.h"
#include "SIPResponse.h"

#include <sstream>
#include <algorithm>
#include <vector>
using std::ostringstream;
using std::vector;
using std::find;

CSipResponse::~CSipResponse()
{
	//
}

void
CSipResponse::BuildPacket() throw(CSipException *)
{
	if(GetCommand().length() == 0)
		throw(new CSipException(SipError::UNSUPPORTED_COMMAND));
	//
	static ostringstream response;
	response.clear();
	response.str("");
	//
	if(GetCSeqCommand().length() == 0)
		SetCSeqCommand(GetCommand());
	//
	response << "SIP/2.0" << GetStatusCode() << GetStatus() << " SIP/2.0\r\n"
			 << "Via: SIP/2.0/UDP " << GetCallerAddress() << ":" << GetCallerPort()
			 << ";branch=" << GetBranch() << "\r\n"
			 << "Contact: <sip:" << GetCallerId() << "@" << GetCallerAddress()
			 << ":" << GetCallerPort() << ">;expires=" << GetExpires() << "\r\n"
			 << "Call-ID: " << GetCallId() << "\r\n"
			 << "Cseq: " << GetCSeq() << " " << GetCSeqCommand() << "\r\n";
	//
	if(GetServer().length() > 0)
		response << "Server: " << GetServer() << "\r\n";
	//
	// To field:
	response << "To: ";
	if(GetCalleeScreenName().length() > 0)
		response << "\"" << GetCalleeScreenName() << "\"";
	//
	response << "<sip:" << GetCalleeId() << "@" << GetSipServerAddress() << ">";
	response << ";tag=" << GetCalleeTag() << "\r\n";
	//
	// From field:
	response << "From: ";
	if(GetCallerScreenName().length() > 0)
		response << "\"" << GetCallerScreenName() << "\"";
	//
	response << "<sip:" << GetCallerId() << "@" << GetCallerAddress() << ">"
			 << ";tag=" << GetCallerTag() << "\r\n";
	//
	response << "Allow: REGISTER, INVITE, ACK, CANCEL, BYE\r\n";
	//
	if(GetContent().length() > 0)
	{
		response << "Content-Length: " << GetContent().length() << "\r\n"
				 << "Content-Type: " << GetContentType() << "\r\n"
				 << "\r\n" << GetContent();
	}
	else
		response << "\r\n";
	//
	SetBuffer(response.str().c_str(), response.str().length());
}
