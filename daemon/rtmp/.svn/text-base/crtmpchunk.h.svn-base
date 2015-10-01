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
 * crtmpchunk.h
 *
 * @author
 * Ales Podskalsky (<a href="mailto:podskale@fel.cvut.cz">podskale@fel.cvut.cz</a>)
 *
 * @brief
 * Contain CRtmpChunk class that represent chunk packet.
 */

#ifndef CRTMPCHUNK_H
#define CRTMPCHUNK_H

#include <string>

/**
 * @brief
 * Class represents chunk packet.
 */
class CRtmpChunk
{
    public:
        /**
         * @brief
         * Default constructor.
        */
        CRtmpChunk();

        /**
         * @brief
         * Destructor.
         */
        virtual ~CRtmpChunk();

    public:
        enum ChunkType{ RTMP_CHNK_T0 = 0 , RTMP_CHNK_T1 = 1 , RTMP_CHNK_T2 = 2 , RTMP_CHNK_T3 = 3 };

        /**
         * @brief
         * [getter] Getter function for get constant pointer to the chunk array.
         *
         * @return
         * Returns constant pointer to the chunk array.
         */
        std::string GetEncodeChunk() const;

        /**
         * @brief
         * [setter] Setter function for set chunk type.
         *
         * @param type
         * Chunk type from CRtmpChunk::ChunkType enum.
         *
         * @return
         * Returns boolean value indicate result of opreation.
         *
         * @see
         * CRtmpChunk::ChunkType
         */
        bool SetType(ChunkType type);

        /**
         * @brief
         * [setter] Setter function for set chunk stream ID.
         *
         * @param type
         * Integer value represents chunk stream ID.
         *
         * @return
         * Returns boolean value indicate result of opreation.
         */
        bool SetCsId(int iCsId);

        /**
         * @brief
         * [setter] Setter function for set timestamp.
         *
         * @param iTimestamp
         * Chunk type from CRtmpChunk::ChunkType enum.
         *
         * @return
         * Returns boolean value indicate result of opreation.
         */
        bool SetTimestamp(int iTimestamp);

        /**
         * @brief
         * [setter] Setter function for set message length.
         *
         * @param iMsgLen
         * Integer value represents message length.
         *
         * @return
         * Returns boolean value indicate result of opreation.
         */
        bool SetMsgLen(int iMsgLen);

        /**
         * @brief
         * [setter] Setter function for set message type ID.
         *
         * @param iMsgTypeId
         * Integer value represents message type ID.
         *
         * @return
         * Returns boolean value indicate result of opreation.
         */
        bool SetMsgTypeId(int iMsgTypeId);

        /**
         * @brief
         * [setter] Setter function for set setream ID.
         *
         * @param iStreamId
         * Integer value represents stream ID.
         *
         * @return
         * Returns boolean value indicate result of opreation.
         */
        bool SetStreamId(int iStreamId);


        /**
         * @brief
         * [getter] Getter function for get chunk type.
         *
         * @return
         * Returns CRtmpChunk::ChunkType value represents chunk type.
         *
         * @see
         * CRtmpChunk::ChunkType
         *
         */
        ChunkType GetType() const;

        /**
         * @brief
         * [getter] Getter function for get chunk stream ID.
         *
         * @return
         * Returns integer value represents chunk stream ID.
         */
        int GetCsId() const;

        /**
         * @brief
         * [getter] Getter function for get timestamp.
         *
         * @return
         * Returns integer value represents timestamp.
         */
        int GetTimestamp() const;

        /**
         * @brief
         * [getter] Getter function for get message length.
         *
         * @return
         * Returns integer value represents message length.
         */
        int GetMsgLen() const;

        /**
         * @brief
         * [getter] Getter function for get message type ID.
         *
         * @return
         * Returns integer value represents message type ID.
         */
        int GetMsgTypeId() const;

        /**
         * @brief
         * [getter] Getter function for get setream ID.
         *
         * @return
         * Returns integer value represents stream ID.
         */
        int GetStreamId() const;

    private:
        ChunkType m_type;

        int m_iFmt;
        int m_iCsId;
        int m_iTimestamp;
        int m_iMsgLen;
        int m_iMsgTypeId;
        int m_iStreamId;

};

#endif // CRTMPCHUNK_H
