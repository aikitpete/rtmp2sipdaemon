/*************************************************************************
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ************************************************************************/


/**
 * @file
 * crtmpsession.h
 *
 * @author
 * Ales Podskalsky (<a href="mailto:podskale@fel.cvut.cz">podskale@fel.cvut.cz</a>)
 *
 * @brief
 * This class should be only for testing RTMP connection.
 */

#ifndef CRTMPSESSION_H
#define CRTMPSESSION_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>

#include <map>

#include "../Socket/Socket.h"
#include "crtmpprotocol.h"
#include "crtmpchunk.h"
#include "crtmpmessage.h"

/**
 * @brief
 * Class providing easy interface for using RTMP.
 */
class CRtmpSession
{
    public:
        /**
         * @brief
         * Constructor for initialize session with socket reference.
        */
        CRtmpSession(CTcpServerSocket * _pServerSocket, int iSocket);

        /**
         * @brief
         * Destructor.
        */
        virtual ~CRtmpSession();

    public:
        /**
         * @brief
         * Run function for testing RTMP library functions.
        */
        void Run();

    private:
        /**
         * @brief
         * Function for do handshake over RTMP protocol.
         *
         * @return
         * Boolean value shows result of the handshake.
        */
        bool Handshake();

        /**
         * @brief
         * Function for read and parse Chunk from input buffer.
         *
         * @return
         * CRtmpChunk object represents RTMP chunk.
        */
        CRtmpChunk ReadChunk();

        /**
         * @deprecated
         * Deprecated because message headers are't sent over RTMP stream. That information we can read from chunk.
         *
         * @brief
         * Function for read and parse message header from input buffer.
         *
         * @return
         * Boolean value shows result of the handshake.
        */
        CRtmpMessage ReadMessage();


        std::string CreatePacket(CRtmpMessage message);
        bool ProcessMessage(int iChunkStreamID);

        /**
         * @brief
         * Ancillary function for writing CPacket to the output buffer.
         *
         * @param packet
         * Packet which we want to write to the buffer.
         *
         * @return
         * Integer value shows how many bytes was realy written.
        */
        int Write(CPacket packet);

        /**
         * @brief
         * Ancillary function for reading CPacket from the intput buffer.
         *
         * @param iSize
         * Number of bytes we want to read from the input buffer.
         *
         * @return
         * CPacket object read from the input buffer.
        */
        CPacket Read(int iSize);
    private:
        CTcpServerSocket *m_pServerSocket;
        int m_iSocket;

        int m_iChunkSize;
        std::map<int, CRtmpMessage> m_mapChunkStreams;

    private:
        CPacket OnConnect();
        CPacket OnCreateStream(int iTransID);
        CPacket OnPublish(int iTransID);
};

#endif // CRTMPSESSION_H
