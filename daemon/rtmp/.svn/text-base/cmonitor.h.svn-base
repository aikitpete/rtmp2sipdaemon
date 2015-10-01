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
 * cpacket.h
 *
 * @author
 * Ales Podskalsky (<a href="mailto:podskale@fel.cvut.cz">podskale@fel.cvut.cz</a>)
 *
 * @brief
 * Classes and functions for monitoring packet traffic and content. Also useful for loging.
 */

#ifndef CMONITOR_H
#define CMONITOR_H

#include "crtmpchunk.h"
#include "crtmpmessage.h"

/**
 * @brief
 * Class for monitoring contents of data structures.
 */
class CMonitor
{
    public:
        /**
         * @brief
         * Default constructor.
        */
        CMonitor();

        /**
         * @brief
         * Destructor.
        */
        virtual ~CMonitor();

    public:
        /**
         * @brief
         * Function to write out content of CRtmpChunk header.
         *
         * @param inptChunk
         * Refenrence to CRtmpChunk object.
         */
        static void Draw(const CRtmpChunk & inptChunk);

        /**
         * @brief
         * Function to write out content of CRtmpHeader header.
         *
         * @param inptHeader
         * Refenrence to CRtmpHeader object.
         */
        static void Draw(const CRtmpMessage& inptHeader);

};

#endif // CMONITOR_H
