#include <string>
using namespace std;

#include "crtmpmessage.h"

CRtmpMessage::CRtmpMessage()
{
    m_msgType = CRtmpMessage::UNKNOWN;
    m_iPayloadLen = -1;
    m_iTimestamp = -1;
    m_iStreamId = -1;
}

CRtmpMessage::~CRtmpMessage()
{

}

bool CRtmpMessage::SetMsgType(MsgType msgType)
{
    m_msgType = msgType;
    return true;
}

bool CRtmpMessage::SetPayloadLen(int iPayloadLen)
{
    m_iPayloadLen = iPayloadLen;
    return true;
}

bool CRtmpMessage::SetTimestamp(int iTimestamp)
{
    m_iTimestamp = iTimestamp;
    return true;
}

bool CRtmpMessage::SetSreamId(int iStreamId)
{
    m_iStreamId = iStreamId;
    return true;
}

CRtmpMessage::MsgType CRtmpMessage::GetMsgType() const
{
    return m_msgType;
}

int CRtmpMessage::GetPayloadLen() const
{
    return m_iPayloadLen;
}

int CRtmpMessage::GetTimestamp() const
{
    return m_iTimestamp;
}

int CRtmpMessage::GetStreamId() const
{
    return m_iStreamId;
}

bool CRtmpMessage::ReadChunk(CRtmpChunk chunk)
{
    if (chunk.GetType() <= CRtmpChunk::RTMP_CHNK_T2)
    {
        SetTimestamp(chunk.GetTimestamp());
    }

    if (chunk.GetType() <= CRtmpChunk::RTMP_CHNK_T1)
    {
        SetPayloadLen(chunk.GetMsgLen());
        SetMsgType(MsgType(chunk.GetMsgTypeId()));
    }

    if (chunk.GetType() == CRtmpChunk::RTMP_CHNK_T0)
    {
        SetSreamId(chunk.GetStreamId());
    }

    return true;
}

bool CRtmpMessage::PushToPayload(std::string strPayload)
{
    m_strPayload.append(strPayload);
    return true;
}

std::string CRtmpMessage::PopPayload()
{
    string _out;
    _out.swap(m_strPayload);
    return _out;
}

int CRtmpMessage::GetLoadedPayloadLen() const
{
    return m_strPayload.size();
}
