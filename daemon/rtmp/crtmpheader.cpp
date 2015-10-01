#include "crtmpheader.h"

CRtmpHeader::CRtmpHeader()
{
    m_msgType = CRtmpHeader::UNKNOWN;
    m_iPayloadLen = -1;
    m_iTimestamp = -1;
    m_iStreamId = -1;
}

CRtmpHeader::~CRtmpHeader()
{

}

bool CRtmpHeader::SetMsgType(MsgType msgType)
{
    m_msgType = msgType;
    return true;
}

bool CRtmpHeader::SetPayloadLen(int iPayloadLen)
{
    m_iPayloadLen = iPayloadLen;
    return true;
}

bool CRtmpHeader::SetTimestamp(int iTimestamp)
{
    m_iTimestamp = iTimestamp;
    return true;
}

bool CRtmpHeader::SetSreamId(int iStreamId)
{
    m_iStreamId = iStreamId;
    return true;
}

CRtmpHeader::MsgType CRtmpHeader::GetMsgType() const
{
    return m_msgType;
}

int CRtmpHeader::GetPayloadLen() const
{
    return m_iPayloadLen;
}

int CRtmpHeader::GetTimestamp() const
{
    return m_iTimestamp;
}

int CRtmpHeader::GetStreamId() const
{
    return m_iStreamId;
}

