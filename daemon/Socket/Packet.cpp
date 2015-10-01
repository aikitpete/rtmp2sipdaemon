#include "Socket.h"

CPacket::CPacket()
{
	m_pData = NULL;
	m_iLen = 0;
}

CPacket::CPacket(const char *pData, int iLen)
{
	m_iLen = iLen;
	m_pData = (char *)malloc(m_iLen);
	memcpy(m_pData, pData, m_iLen);
}

CPacket::CPacket(const CPacket &packet)
{
	m_pData = NULL;
	m_iLen = 0;
	//
	*this = packet;
}

CPacket::~CPacket()
{
	ClearBuffer();
}

CPacket &
CPacket::operator=(const CPacket &packet)
{
	ClearBuffer();
	//
	m_iLen = packet.GetLength();
	m_pData = (char *)malloc(m_iLen);
	memcpy(m_pData, packet.GetBuffer(), m_iLen);
	//
	return *this;
}

int
CPacket::SetBuffer(const char *pData, int iLen)
{
	ClearBuffer();
	//
	m_iLen = iLen;
	m_pData = (char *)malloc(m_iLen);
	memcpy(m_pData, pData, m_iLen);
	//
	return m_iLen;
}

int
CPacket::AppendToBuffer(const char *pData, int iLen)
{
	if(m_pData == NULL)
		SetBuffer(pData, iLen);
	else
	{
		char *buf = (char *)malloc(m_iLen + iLen);
		memcpy(buf, m_pData, m_iLen);
		memcpy(buf + m_iLen, pData, iLen);
		iLen += m_iLen;
		//
		ClearBuffer();
		m_iLen = iLen;
		m_pData = buf;
	}
	return m_iLen;
}

void
CPacket::ClearBuffer()
{
	if(m_pData != NULL)
		free(m_pData);
	//
	m_pData = NULL;
	m_iLen = 0;
}
