#include "crtmpsession.h"
#include "handshakepackets.h"
#include "camf0stream.h"
#include "crtmpmessage.h"
#include "cmonitor.h"

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <sstream>
using namespace std;

CRtmpSession::CRtmpSession(CTcpServerSocket * _pServerSocket, int iSocket)
{
    m_pServerSocket = _pServerSocket;
    m_iSocket = iSocket;

    //default chunk  size
    m_iChunkSize = 128;
}

CRtmpSession::~CRtmpSession()
{

}

std::string CRtmpSession::CreatePacket(CRtmpMessage message)
{
    string _out;
    string _payload = message.PopPayload();

    CRtmpChunk _chunk;
    _chunk.SetCsId(3);
    _chunk.SetType(CRtmpChunk::RTMP_CHNK_T0);
    _chunk.SetMsgLen(message.GetPayloadLen());
    _chunk.SetMsgTypeId(message.GetMsgType());
    _chunk.SetStreamId(message.GetStreamId());
    _chunk.SetTimestamp(message.GetTimestamp());

    _out = _chunk.GetEncodeChunk();

    _chunk.SetType(CRtmpChunk::RTMP_CHNK_T3);
    while (_payload.size() > (unsigned int)m_iChunkSize)
    {
        _out.append(_payload.substr(0,m_iChunkSize));
        _payload.erase(0,m_iChunkSize);

        _out.append(_chunk.GetEncodeChunk());

    }
    _out.append(_payload);


    return _out;
}


CPacket CRtmpSession::OnConnect()
{
    // create answer
    cout << "Creating answer.." << endl;

    cout << "Creating payload." << endl;
    CAmf0StreamOut _amf0sout;
    std::vector<std::pair<std::string,CAmf0Variant> > _object;
    _object.push_back(pair<std::string,CAmf0Variant>("description",CAmf0Variant(string("Connection succeeded."))));
    _object.push_back(pair<std::string,CAmf0Variant>("code",CAmf0Variant(string("NetConnection.Connect.Success"))));
    _object.push_back(pair<std::string,CAmf0Variant>("objectEncoding",CAmf0Variant(double(0))));
    _object.push_back(pair<std::string,CAmf0Variant>("details",CAmf0Variant(0,CAmf0Variant::AMF0_NULL)));
    _object.push_back(pair<std::string,CAmf0Variant>("level",CAmf0Variant(string("status"))));

    _amf0sout << CAmf0Variant(string("_result")) << CAmf0Variant(double(1)) <<  CAmf0Variant(0,CAmf0Variant::AMF0_NULL)
              << CAmf0Variant(_object,CAmf0Variant::AMF0_MIXED_ARRAY);
    cout << "Payload created" << endl;


    cout << "Creating message." << endl;
    CRtmpMessage _message;
    _message.SetPayloadLen(_amf0sout.EncodeAmf().size());
    _message.SetTimestamp(0);
    _message.SetSreamId(0);
    _message.SetMsgType(CRtmpMessage::AMF0_COMMAND_MESSAGE);
    CMonitor::Draw(_message);
    cout << "Chunk header created." << endl;
    _message.PushToPayload(_amf0sout.EncodeAmf());

    cout << "DecodeAmf: " << _amf0sout.DecodeAmf(_amf0sout.EncodeAmf().data(),_amf0sout.EncodeAmf().size()) << endl;
    cout << "Message complete." << endl;

    string _strOutMessage = CreatePacket(_message);
    CPacket _packet;
    _packet.SetBuffer(_strOutMessage.data(),_strOutMessage.size());

    return _packet;
}

CPacket CRtmpSession::OnCreateStream(int iTransID)
{
    CPacket _packet;
    // create answer
    cout << "Creating answer.." << endl;

    cout << "Creating payload." << endl;
    CAmf0StreamOut _amf0sout;
    _amf0sout << CAmf0Variant(string("_result")) << CAmf0Variant(double(iTransID)) <<  CAmf0Variant(0,CAmf0Variant::AMF0_NULL)
              << CAmf0Variant(double(1));
    cout << "Payload created" << endl;


    cout << "Creating message." << endl;
    CRtmpMessage _message;
    _message.SetPayloadLen(_amf0sout.EncodeAmf().size());
    _message.SetTimestamp(0);
    _message.SetSreamId(0);
    _message.SetMsgType(CRtmpMessage::AMF0_COMMAND_MESSAGE);
    CMonitor::Draw(_message);
    cout << "Chunk header created." << endl;
    _message.PushToPayload(_amf0sout.EncodeAmf());

    cout << "DecodeAmf: " << _amf0sout.DecodeAmf(_amf0sout.EncodeAmf().data(),_amf0sout.EncodeAmf().size()) << endl;
    cout << "Message complete." << endl;

    string _strOutMessage = CreatePacket(_message);
    _packet.SetBuffer(_strOutMessage.data(),_strOutMessage.size());


    return _packet;
}

CPacket CRtmpSession::OnPublish(int iTransID)
{
    CPacket _packet;
    // create answer
    cout << "Creating answer.." << endl;

    cout << "Creating payload." << endl;
    CAmf0StreamOut _amf0sout;
    std::vector<std::pair<std::string,CAmf0Variant> > _object;
    _object.push_back(pair<std::string,CAmf0Variant>("description",CAmf0Variant(string(""))));
    _object.push_back(pair<std::string,CAmf0Variant>("code",CAmf0Variant(string("NetStream.Publish.Start"))));
    _object.push_back(pair<std::string,CAmf0Variant>("details",CAmf0Variant(0,CAmf0Variant::AMF0_NULL)));
    _object.push_back(pair<std::string,CAmf0Variant>("level",CAmf0Variant(string("status"))));


    _amf0sout << CAmf0Variant(string("onStatus")) << CAmf0Variant(double(iTransID)) <<  CAmf0Variant(0,CAmf0Variant::AMF0_NULL)
              << CAmf0Variant(_object,CAmf0Variant::AMF0_MIXED_ARRAY);
    cout << "Payload created" << endl;


    cout << "Creating message." << endl;
    CRtmpMessage _message;
    _message.SetPayloadLen(_amf0sout.EncodeAmf().size());
    _message.SetTimestamp(0);
    _message.SetSreamId(0);
    _message.SetMsgType(CRtmpMessage::AMF0_COMMAND_MESSAGE);
    CMonitor::Draw(_message);
    cout << "Chunk header created." << endl;
    _message.PushToPayload(_amf0sout.EncodeAmf());

    cout << "DecodeAmf: " << _amf0sout.DecodeAmf(_amf0sout.EncodeAmf().data(),_amf0sout.EncodeAmf().size()) << endl;
    cout << "Message complete." << endl;

    string _strOutMessage = CreatePacket(_message);
    _packet.SetBuffer(_strOutMessage.data(),_strOutMessage.size());


    return _packet;
}

bool CRtmpSession::ProcessMessage(int iChunkStreamID)
{
    string _strInMessage = m_mapChunkStreams[iChunkStreamID].PopPayload();


    if (m_mapChunkStreams[iChunkStreamID].GetMsgType() == CRtmpMessage::AMF0_COMMAND_MESSAGE)
    {
        // draw incoming..
        CAmf0StreamIn _amf0sin;
        cout << "DecodeAmf: " << _amf0sin.DecodeAmf(_strInMessage.data(),_strInMessage.size()) << endl << endl;


        if (_amf0sin.At(0).toString() == "connect")
        {
            Write(OnConnect());
        }
        if (_amf0sin.At(0).toString() == "createStream")
        {
            Write(OnCreateStream(_amf0sin.At(1).toDouble()));
        }
            if (_amf0sin.At(0).toString() == "publish")
        {
            Write(OnPublish(_amf0sin.At(1).toDouble()));
        }

    }

    if (m_mapChunkStreams[iChunkStreamID].GetMsgType() == CRtmpMessage::VIDEO_MESSAGE)
    {
        cout << "New video message" << endl;
        for (int i = 0 ; i< _strInMessage.size() ; ++i)
        {
            cout << _strInMessage[i];
        }
        cout << endl;
    }



    return true;
}

void CRtmpSession::Run()
{



    Handshake();

    CRtmpChunk _chunk;
    CPacket _packet;
    int _iPayloadSize; // for count payload size to read
    int _iChunkStreamID = 0;
    while (1)
    {
        m_pServerSocket->WaitForIncomingData(10,0);
        cout << "Hmm new message" << endl;
        // read chunk
        _chunk = ReadChunk();
        CMonitor::Draw(_chunk);

        // get Chunk stream ID
        _iChunkStreamID = _chunk.GetCsId();
        // read chunk to the  right stream
        m_mapChunkStreams[_iChunkStreamID].ReadChunk(_chunk);

        //count payload size
        _iPayloadSize = m_mapChunkStreams[_iChunkStreamID].GetPayloadLen() -
                        m_mapChunkStreams[_iChunkStreamID].GetLoadedPayloadLen();
        // if remaining payload > max chunk size than we can load only max chunk size
        if (_iPayloadSize > m_iChunkSize)
            _iPayloadSize = m_iChunkSize;

        //read payload
        _packet = Read(_iPayloadSize);
        m_mapChunkStreams[_iChunkStreamID].PushToPayload(string(_packet.GetBuffer(),_iPayloadSize));

        // if message is fully loaded than we can proceed message and send answer
        if (m_mapChunkStreams[_iChunkStreamID].GetPayloadLen() ==
                        m_mapChunkStreams[_iChunkStreamID].GetLoadedPayloadLen())
            ProcessMessage(_iChunkStreamID);
        else
            cout << "Loaded chunk isnt all" << endl;
    }


}


CRtmpMessage CRtmpSession::ReadMessage()
{
    CRtmpMessage _out;

    CPacket _packet;
    _packet = Read(11);

    _out.SetMsgType(CRtmpMessage::MsgType((int)_packet.GetBufferU()[0]));
    _out.SetPayloadLen((int(_packet.GetBufferU()[1]) << 2) + (int(_packet.GetBufferU()[2]) << 1) + int(_packet.GetBufferU()[3]));
    _out.SetTimestamp((int(_packet.GetBufferU()[4]) << 3) + (int(_packet.GetBufferU()[5]) << 2) +
                         (int(_packet.GetBufferU()[6]) << 1) + (int(_packet.GetBufferU()[7])));
    _out.SetSreamId((int(_packet.GetBufferU()[8]) << 2) + (int(_packet.GetBufferU()[9]) << 1) + int(_packet.GetBufferU()[10]));

    return _out;
}

CRtmpChunk  CRtmpSession::ReadChunk()
{
    CRtmpChunk _out;

    CPacket _packet;
    _packet = Read(1);

    // Format type is represented by first two bits in first byte of Chunk Basic header. 0x60 is for anding first two bits.
    _out.SetType(CRtmpChunk::ChunkType(((int)_packet.GetBufferU()[0] & 0xC0) >> 6));

    // Chunk stream ID is stored in 0 - 5 bits. If this nuber 0 or 1 it signs chunk basic header type 2 or 3.
    _out.SetCsId((int)_packet.GetBufferU()[0] & 0x1F);
    if (_out.GetCsId() == 0)
    {
        _packet = Read(1);
        // Chunk basic header 2 has chunk stream ID in second byte + 64
         _out.SetCsId((int)_packet.GetBufferU()[0] + 64);

    }
    if (_out.GetCsId() == 1)
    {
        _packet = Read(2);
        // Chunk basic header 3 has chunk stream ID in third byte * 256 + second byte + 64
        _out.SetCsId((int)_packet.GetBufferU()[1]*256 + (int)_packet.GetBufferU()[0] + 64);
    }

    // Chunk type 0, 1 and 2 has timestamp section
    if (_out.GetType() == CRtmpChunk::RTMP_CHNK_T0 || _out.GetType() == CRtmpChunk::RTMP_CHNK_T1 ||
        _out.GetType() == CRtmpChunk::RTMP_CHNK_T2)
    {
        _packet = Read(3);
        _out.SetTimestamp((int(_packet.GetBufferU()[0]) << 2) + (int(_packet.GetBufferU()[1]) << 1) + int(_packet.GetBufferU()[2]));

    }

    // Chunk type 0 and 1 has message length and message type section too
    if (_out.GetType() == CRtmpChunk::RTMP_CHNK_T0 || _out.GetType() == CRtmpChunk::RTMP_CHNK_T1)
    {
        _packet = Read(4);
        _out.SetMsgLen((int(_packet.GetBufferU()[0]) << 2) + (int(_packet.GetBufferU()[1]) << 1) + int(_packet.GetBufferU()[2]));
        _out.SetMsgTypeId(int(_packet.GetBufferU()[3]));

    }

    // In addition chunk type 0 contains stream id
    if (_out.GetType() == CRtmpChunk::RTMP_CHNK_T0)
    {
        _packet = Read(4);
        _out.SetStreamId((int(_packet.GetBufferU()[0]) << 3) + (int(_packet.GetBufferU()[1]) << 2) +
                         (int(_packet.GetBufferU()[2]) << 1) + (int(_packet.GetBufferU()[3])));
    }

    if (_out.GetTimestamp() == 0x00FFFFFF)
    {
        _packet = Read(4);
        _out.SetTimestamp((int(_packet.GetBufferU()[0]) << 3) + (int(_packet.GetBufferU()[1]) << 2) +
                         (int(_packet.GetBufferU()[2]) << 1) + (int(_packet.GetBufferU()[3])));
    }
    return _out;
}

bool CRtmpSession::Handshake()
{
    CPacket _packet;

    _packet = Read(1537);
    Write(_packet);

    _packet = Read(1536);
    Write(_packet);

    return true;
}

int  CRtmpSession::Write(CPacket packet)
{
    return write(m_iSocket,packet.GetBuffer(),packet.GetLength());

    //return m_pServerSocket->SendData(m_iSocket,&packet);
}

CPacket  CRtmpSession::Read(int iSize)
{
    char _pucBuffer[iSize];
    bzero(_pucBuffer,iSize);
    int n = read(m_iSocket,_pucBuffer,iSize);
    return CPacket(_pucBuffer, n);

/*    CPacket _packet;
    m_pServerSocket->RecieveData(m_iSocket,&_packet);
    return _packet;*/
}
