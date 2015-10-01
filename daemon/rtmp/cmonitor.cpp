#include "cmonitor.h"

#include <iostream>

using namespace std;

CMonitor::CMonitor()
{
}

CMonitor::~CMonitor()
{

}

void CMonitor::Draw(const CRtmpChunk & inptChunk)
{
    cout << "Chunk = Type: " << (int)inptChunk.GetType()
         << " CsId: " << inptChunk.GetCsId();
    if (inptChunk.GetType()!= CRtmpChunk::RTMP_CHNK_T3)
        cout << " Timestamp: " << inptChunk.GetTimestamp();

    if (inptChunk.GetType() == CRtmpChunk::RTMP_CHNK_T0 || inptChunk.GetType() == CRtmpChunk::RTMP_CHNK_T1)
        cout << " Message length: " << inptChunk.GetMsgLen()
             << " Message type ID: " << inptChunk.GetMsgTypeId();

    if (inptChunk.GetType() == CRtmpChunk::RTMP_CHNK_T0)
        cout << " Message stream ID: " << inptChunk.GetStreamId();

    cout << endl;

}

void CMonitor::Draw(const CRtmpMessage & inptHeader)
{
   cout << "Message Header = Type: " << int(inptHeader.GetMsgType())
        << " Payload length: " << inptHeader.GetPayloadLen()
        << " Timestamp: " << inptHeader.GetTimestamp()
        << " Stream ID: " << inptHeader.GetStreamId()
        << endl;
}
