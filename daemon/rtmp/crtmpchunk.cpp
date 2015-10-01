#include "crtmpchunk.h"
#include <iostream>
using namespace std;

CRtmpChunk::CRtmpChunk()
{
    m_iCsId = -1;
}

CRtmpChunk::~CRtmpChunk()
{

}

std::string CRtmpChunk::GetEncodeChunk() const
{
    string _out;

    // build new content


    // One byte version
    _out.push_back(char(m_type << 6));
    if (m_iCsId < 63)
        _out[0] +=char( m_iCsId) & 0x3F;

    // Two byte version
    if (m_iCsId > 63 && m_iCsId <= 319)
        _out.push_back(char(_out[0] += - 64));


    // Three byte version
    if (m_iCsId > 319)    /* @TODO up limit isnt checked */
    {
        _out[0] += 1;
        _out.push_back(char((m_iCsId-64)%256));
        _out.push_back(char((m_iCsId-64)/256));
    }

    if (m_type < 3)
    {
        for (int i=2 ; i >= 0 ; --i)
            _out.push_back(char((m_iTimestamp >> i) & 0xFF));
    }

    if (m_type < 2)
    {
        for (int i=2 ; i >= 0 ; --i)
        {
             _out.push_back(char((m_iMsgLen >> 8*i) & 0xFF));
        }
        _out.push_back(char(m_iMsgTypeId));
    }

    if (m_type == 0)
    {
        for (int i=3 ; i >= 0 ; --i)
             _out.push_back(char((m_iStreamId >> i) & 0xFF));
    }

    return _out;
}


bool CRtmpChunk::SetType(ChunkType type)
{
    if ((int)type > 3 || (int)type < 0)     // invalid type
        return false;

    m_type = type;
    return true;
}

CRtmpChunk::ChunkType CRtmpChunk::GetType() const
{
    return m_type;
}

bool CRtmpChunk::SetCsId(int iCsId)
{
    if (iCsId < 3 || iCsId > 65599)     // invalid chunk stream ID
        return false;

    m_iCsId = iCsId;
    return true;
}

int CRtmpChunk::GetCsId() const
{
    return m_iCsId;
}

bool CRtmpChunk::SetTimestamp(int iTimestamp)
{
    if (iTimestamp > 0x00FFFFFF) // 0x00FFFFFF == 16777215
    {
        m_iTimestamp = 0x00FFFFFF;
        return false;
    }
    m_iTimestamp = iTimestamp;
    return true;
}

bool CRtmpChunk::SetMsgLen(int iMsgLen)
{
    m_iMsgLen = iMsgLen;
    return true;
}

bool CRtmpChunk::SetMsgTypeId(int iMsgTypeId)
{
    m_iMsgTypeId = iMsgTypeId;
    return true;
}

bool CRtmpChunk::SetStreamId(int iStreamId)
{
    m_iStreamId = iStreamId;
    return true;
}

int CRtmpChunk::GetTimestamp() const
{
    if (m_type == RTMP_CHNK_T3)
        return -1;
    return m_iTimestamp;
}

int CRtmpChunk::GetMsgLen() const
{
    if (m_type == RTMP_CHNK_T2 || m_type == RTMP_CHNK_T3)
        return -1;
    return m_iMsgLen;
}

int CRtmpChunk::GetMsgTypeId() const
{
    if (m_type == RTMP_CHNK_T2 || m_type == RTMP_CHNK_T3)
        return -1;
    return m_iMsgTypeId;
}

int CRtmpChunk::GetStreamId() const
{
    if (m_type == RTMP_CHNK_T1 || m_type == RTMP_CHNK_T2 || m_type == RTMP_CHNK_T3)
        return -1;
    return m_iStreamId;
}

