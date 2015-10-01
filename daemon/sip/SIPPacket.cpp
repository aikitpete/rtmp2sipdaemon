#include "SIPPacket.h"

#include <ctime>
#include <cstdlib>

CAuthorization::CAuthorization()
{
	//
}

CAuthorization::CAuthorization(const CAuthorization &auth)
{
	*this = auth;
}

CAuthorization::~CAuthorization()
{
	//
}

CAuthorization &
CAuthorization::operator=(const CAuthorization &auth)
{
	m_strDomain = auth.m_strDomain;
	m_strNonce  = auth.m_strNonce;
	m_strOpaque = auth.m_strOpaque;
	m_strQop    = auth.m_strQop;
	m_strRealm  = auth.m_strRealm;
	m_strStale  = auth.m_strStale;
	m_strType   = auth.m_strType;
	m_strUser   = auth.m_strUser;
	m_strPasswd = auth.m_strPasswd;
	//
	return *this;
}

CSipPacket::CSipPacket( const string &strCallerId, const string &strCalleeId, const string &strCallerAddress,
						int iCallerPort, const string &strSipServerAddress)
{
	osip_init(&m_osip);
	//
	m_strCallId           = GetRandomId(32);
	m_strBranch           = "z9hG4bk-" + GetRandomId(16);
	m_strCallerTag        = GetRandomId(8);
	m_strCallerId         = strCallerId;
	m_strCalleeId         = strCalleeId;
	m_strCallerAddress    = strCallerAddress;
	m_strSipServerAddress = strSipServerAddress;
	m_strContentType      = "application/sdp";
	m_iStatusCode         = 0;
	m_iCallerPort         = iCallerPort;
	m_iCSeq               = 1;
	m_iExpires            = 3600;
	m_iMaxForwards        = 70;
}

CSipPacket::CSipPacket(const CSipPacket &packet)
{
	osip_init(&m_osip);
	//
	*this = packet;
}

CSipPacket &
CSipPacket::operator=(const CSipPacket &packet)
{
	m_strCallId           = packet.m_strCallId;
	m_strBranch           = packet.m_strBranch;
	m_strCallerTag        = packet.m_strCallerTag;
	m_strCalleeTag        = packet.m_strCalleeTag;
	m_strCallerId         = packet.m_strCallerId;
	m_strCalleeId         = packet.m_strCalleeId;
	m_strCallerScreenName = packet.m_strCallerScreenName;
	m_strCalleeScreenName = packet.m_strCalleeScreenName;
	m_strCallerAddress    = packet.m_strCallerAddress;
	m_strSipServerAddress = packet.m_strSipServerAddress;
	m_strContactAddress   = packet.m_strContactAddress;
	m_strUserAgent        = packet.m_strUserAgent;
	m_strServer           = packet.m_strServer;
	m_strContentType      = packet.m_strContentType;
	m_strContent          = packet.m_strContent;
	m_strCommand          = packet.m_strCommand;
	m_strStatus           = packet.m_strStatus;
	m_iStatusCode         = packet.m_iStatusCode;
	m_iCallerPort         = packet.m_iCallerPort;
	m_iCSeq               = packet.m_iCSeq;
	m_iExpires            = packet.m_iExpires;
	m_iMaxForwards        = packet.m_iMaxForwards;
	m_auth                = packet.m_auth;
	m_authProxy           = packet.m_authProxy;
	//
	return *this;
}

CSipPacket::~CSipPacket()
{
	osip_free(m_osip);
}

string
CSipPacket::GetRandomId(int iLen) const
{
	srand((unsigned int)time(NULL));
	//
	const int iSymbLen = 16;
	static char szSymbols[iSymbLen] =
	{
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
	};
	//
	string retval;
	for(int i = 0; i < iLen; ++i)
		retval += szSymbols[rand() % iSymbLen];
	//
	return retval;
}

void
CSipPacket::Update(const osip_message_t *sip)
{
	if(!sip) return;
	//
	if(sip->call_id)
		m_strCallId = ToString(sip->call_id->number);
	//
	if(sip->to)
	{
		if(sip->to->url)
		{
			m_strSipServerAddress = ToString(sip->to->url->host);
			m_strCallerId         = ToString(sip->to->url->username);
		}
		//
		m_strCallerScreenName = ToString(sip->to->displayname);
		//
		osip_uri_param_t *tag;
		osip_uri_param_get_byname(&(sip->to->gen_params), "tag", &tag);
		if(tag)
			m_strCalleeTag = ToString(tag->gvalue);
		//
	}
	//
	if(sip->from)
	{
		if(sip->from->url)
		{
			m_strCallerAddress = ToString(sip->from->url->host);
			if(sip->from->url->port)
				m_iCallerPort = atoi(sip->from->url->port);
			//
			m_strCalleeId      = ToString(sip->from->url->username);
		}
		//
		m_strCalleeScreenName = ToString(sip->from->displayname);
		//
		osip_uri_param_t *tag;
		osip_uri_param_get_byname(&(sip->from->gen_params), "tag", &tag);
		if(tag)
			m_strCallerTag = ToString(tag->gvalue);
		//
	}
	//
	osip_header_t *head;
	for(int i = 0; i < sip->headers.nb_elt; ++i)
	{
		head = (osip_header_t *)(osip_list_get(&(sip->headers), i));
		if(!head)
			continue;
		//
		if(strcmp(head->hname, "expires") == 0)
		{
			if(head->hvalue)
				m_iExpires = atoi(head->hvalue);
		}
		else if(strcmp(head->hname, "max-forwards") == 0)
		{
			if(head->hvalue)
				m_iMaxForwards = atoi(head->hvalue);
		}
		else if(strcmp(head->hname, "user-agent") == 0)
			m_strUserAgent = ToString(head->hvalue);
		else if(strcmp(head->hname, "server") == 0)
			m_strServer = ToString(head->hvalue);
	}
	//
	if(sip->contacts.nb_elt > 0)
	{
		osip_contact_t *contact = (osip_contact_t *)osip_list_get(&(sip->contacts), 0);
		if(contact)
		{
			if(contact->url)
				m_strContactAddress  = ToString(contact->url->host);
			//
			if(m_iExpires == 0)	// if not found in headers it could be in Contant field as parameter
			{
				osip_uri_param_t *expires;
				osip_uri_param_get_byname(&(contact->gen_params), "expires", &expires);
				if(expires->gvalue)
					m_iExpires = atoi(expires->gvalue);
			}
		}
	}
	//
	if(sip->content_type)
		m_strContentType = ToString(sip->content_type->type) + '/' + ToString(sip->content_type->subtype);
	//
	if(sip->cseq)
	{
		if(sip->cseq->number)
			m_iCSeq = atoi(sip->cseq->number);
		//
		m_strCSeqCommand = ToString(sip->cseq->method);
	}
	//
	m_strCommand  = ToString(sip->sip_method);
	m_strStatus   = ToString(sip->reason_phrase);
	m_iStatusCode = sip->status_code;
	//
	if(sip->vias.nb_elt > 0)
	{
		osip_uri_param_t *branch;
		osip_via_param_get_byname((osip_via_t *)(osip_list_get(&(sip->vias), 0)), "branch", &branch);
		if(branch)
			m_strBranch = ToString(branch->gvalue);
		//
	}
	//
	if(sip->bodies.nb_elt > 0)
	{
		char *body;
		size_t bodylen;
		osip_body_to_str((osip_body_t *)(osip_list_get(&(sip->bodies), 0)), &body, &bodylen);
		m_strContent = ToString(body);
	}
	//
	osip_www_authenticate_t *www_auth = (osip_www_authenticate_t *)osip_list_get(&(sip->www_authenticates), 0);
	if(www_auth)
	{
		if(www_auth->auth_type  ) GetAuthorization().SetType   ( osip_www_authenticate_get_auth_type   (www_auth) );
		if(www_auth->domain     ) GetAuthorization().SetDomain ( osip_www_authenticate_get_domain      (www_auth) );
		if(www_auth->nonce      ) GetAuthorization().SetNonce  ( osip_www_authenticate_get_nonce       (www_auth) );
		if(www_auth->opaque     ) GetAuthorization().SetOpaque ( osip_www_authenticate_get_opaque      (www_auth) );
		if(www_auth->qop_options) GetAuthorization().SetQop    ( osip_www_authenticate_get_qop_options (www_auth) );
		if(www_auth->realm      ) GetAuthorization().SetRealm  ( osip_www_authenticate_get_realm       (www_auth) );
		if(www_auth->stale      ) GetAuthorization().SetStale  ( osip_www_authenticate_get_stale       (www_auth) );
	}
	else
	{
		osip_proxy_authenticate_t *proxy_auth = (osip_proxy_authenticate_t *)osip_list_get(&(sip->proxy_authenticates), 0);
		if(proxy_auth)
		{
			if(proxy_auth->auth_type  ) GetProxyAuthorization().SetType   ( osip_proxy_authenticate_get_auth_type   (proxy_auth) );
			if(proxy_auth->domain     ) GetProxyAuthorization().SetDomain ( osip_proxy_authenticate_get_domain      (proxy_auth) );
			if(proxy_auth->nonce      ) GetProxyAuthorization().SetNonce  ( osip_proxy_authenticate_get_nonce       (proxy_auth) );
			if(proxy_auth->opaque     ) GetProxyAuthorization().SetOpaque ( osip_proxy_authenticate_get_opaque      (proxy_auth) );
			if(proxy_auth->qop_options) GetProxyAuthorization().SetQop    ( osip_proxy_authenticate_get_qop_options (proxy_auth) );
			if(proxy_auth->realm      ) GetProxyAuthorization().SetRealm  ( osip_proxy_authenticate_get_realm       (proxy_auth) );
			if(proxy_auth->stale      ) GetProxyAuthorization().SetStale  ( osip_proxy_authenticate_get_stale       (proxy_auth) );
		}
	}
}

void
CSipPacket::Update(const string &data)
{
	osip_message_t *sip;
	osip_message_init(&sip);
	osip_message_parse(sip, data.c_str(), data.length());
	//
	Update(sip);
	//
	osip_message_free(sip);
}
