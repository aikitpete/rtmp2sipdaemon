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
 * crtmpexception.h
 *
 * @author
 * Ales Podskalsky (<a href="mailto:podskale@fel.cvut.cz">podskale@fel.cvut.cz</a>)
 *
 * @brief
 * Exceptions for RTMP connection.
 */

#ifndef CRTMPEXCEPTION_H
#define CRTMPEXCEPTION_H

#include <string>


class CRtmpException
{
    public:
        CRtmpException();
        virtual ~CRtmpException();
        CRtmpException(std::string strMessage);

        std::string GetMessage() const;

    private:
        std::string m_strMessage;
};

#endif // CRTMPEXCEPTION_H
