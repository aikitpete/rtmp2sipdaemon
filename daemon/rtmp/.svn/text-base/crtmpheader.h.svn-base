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
 * crtmpheader.h
 *
 * @author
 * Ales Podskalsky (<a href="mailto:podskale@fel.cvut.cz">podskale@fel.cvut.cz</a>)
 *
 * @brief
 * Contain CRtmpHeader class for store information about message header.
 */

#ifndef CRTMPHEADER_H
#define CRTMPHEADER_H

/**
 * @brief
 * Class represents header of RTMP packet.
 */
class CRtmpHeader
{
    public:
         /**
         * @brief
         * Default constructor.
         */
        CRtmpHeader();

        /**
         * @brief
         * Destructor.
         */
        virtual ~CRtmpHeader();

    public:
        enum MsgType { UNKNOWN = -1 , SET_CHUNK_SIZE = 1 , ABORT_MESSAGE = 2 , ACKNOWLEDGEMENT = 3 , USER_CONTROL_MESSAGE = 4 ,
               WINDOW_ACKONWLEDGEMENT = 5 , SET_PEER_BANDWIDTH = 6 , AMF0_COMMAND_MESSAGE = 20 ,
               AMF3_COMMAND_MESSAGE = 17 , AMF0_DATA_MESSAGE = 18 , AMF3_DATA_MESSAGE = 15 ,
               AMF0_SHARED_OBJECT_MESSAGE = 19 , AMF3_SHARED_OBJECT_MESSAGE = 16 ,
               AUDIO_MESSAGE = 8 , VIDEO_MESSAGE = 9 , AGGREGATE_MESSAGE = 22};

        /**
         * @brief
         * [setter] Setter function for set message type.
         *
         * @param msgType
         * Message type from CRtmpHeader::MsgType enum.
         *
         * @return
         * Returns boolean value indicate result of opreation.
         *
         * @see
         * CRtmpHeader::MsgType
         */
        bool SetMsgType(MsgType msgType);

        /**
         * @brief
         * [setter] Setter function for set payload length section.
         *
         * @param iPayloadLen
         * Integer vaule represent length of the payload.
         *
         * @return
         * Returns boolean value indicate result of opreation.
         *
         */
        bool SetPayloadLen(int iPayloadLen);

        /**
         * @brief
         * [setter] Setter function for set timestamp section.
         *
         * @param iPayloadLen
         * Integer vaule represent length of the payload.
         *
         * @return
         * Returns boolean value indicate result of opreation.
         *
         */
        bool SetTimestamp(int iTimestamp);

        /**
         * @brief
         * [setter] Setter function for set stream ID section.
         *
         * @param iStreamId
         * Integer vaule represent ID of the current stream.
         *
         * @return
         * Returns boolean value indicate result of opreation.
         *
         */
        bool SetSreamId(int iStreamId);

        /**
         * @brief
         * [getter] Getter function for get message type.
         *
         * @return
         * Returns CRtmpHeader::MsgType value represents type of the message.
         *
         * @see
         * CRtmpHeader::MsgType
         *
         */
        MsgType GetMsgType() const;

        /**
         * @brief
         * [getter] Getter function for get payload length.
         *
         * @return
         * Returns integer value represents length of the payload.
         */
        int GetPayloadLen() const;

        /**
         * @brief
         * [getter] Getter function for get timestamp.
         *
         * @return
         * Returns integer value represents timestamp of the message.
         */
        int GetTimestamp() const;

        /**
         * @brief
         * [getter] Getter function for get stream ID.
         *
         * @return
         * Returns integer value represents ID of the stream.
         */
        int GetStreamId() const;


    private:
        MsgType m_msgType;
        int m_iPayloadLen;
        int m_iTimestamp;
        int m_iStreamId;
};

#endif // CRTMPHEADER_H
