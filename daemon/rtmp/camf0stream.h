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
 * Classes implementing interface for working with AMF format stream.
 */

#ifndef CAMF0STREAM_H
#define CAMF0STREAM_H

#include <vector>
#include <queue>
#include <utility>
#include "camf0variant.h"

/**
 * @brief
 * Basic class for stream AMF Variants
 */
class CAmf0Stream
{
    public:
        /**
         * @brief
         * Default constructor.
        */
        CAmf0Stream();

        /**
         * @brief
         * Constructor with initialized content.
        */
        CAmf0Stream(const char *ucContent, int iSize);

        /**
         * @brief
         * Destructor.
        */
        virtual ~CAmf0Stream();

    public:
        /**
         * @brief
         * Returns content of the stream encoded to AMF format.
         *
         * @return
         * Returns string from stl that contain formated content of the stream.
        */
        std::string EncodeAmf() const;

        /**
         * @brief
         * Function for set up content and decode it from whole string.
         *
         * @param ucContent
         * Pointer to constant array of chars represents AMF formated text.
         *
         * @param iSize
         * Size of ucContent array.
         *
         * @return
         * Returns true or false if decoding was successfull or not.
        */
        bool DecodeAmf(const char *ucContent, int iSize);

        /**
         * @brief
         * Function for set up content from vector full of CAmfVariant objects.
         *
         * @param content
         * Vector full of CAmfVariant objects.
         *
         * @return
         * Returns true or false if transaction was successfull
        */
        bool SetContent(const std::vector<CAmf0Variant> &content);

    protected:
        /**
         * @brief
         * Member for store content of the stream.
        */
        std::vector<CAmf0Variant> m_Content;

    private:

        /**
         * @brief
         * Ancillary function for reading next element from the queue.
         * It is usually called from DecodeAmf function.
         *
         * @param qContent;
         * Queue of char represents array of bytes contains AMF coded string.
         *
         * @return
         * Returns CAmf0Variant object read from the input queue.
        */
        CAmf0Variant ReadNext(std::queue<char> &qContent);

        /**
         * @brief
         * Ancillary function for read one string from the queue.
         * It is usually called from DecodeAmf function.
         *
         * @param ucContent
         * Queue of char represents array of bytes contains AMF coded string.
         *
         * @return
         * Returns string read from queue.
         *
         * @see CAmf0Stream::DecodeAmf
         *
        */
        std::string ReadString(std::queue<char> &qContent);

        /**
         * @brief
         * Function for count length UTF8 string.
         *
         * @param str
         * Pointer to the string int UTF8.
         *
         * @param size
         * Size of str array.
         *
         * @return
         * Returns length of string formated in UTF8.
        */
        int UTF8Len( const char * str , int size);
};

/**
 * @brief
 * Class for input stream AMF Variants.
 */
class CAmf0StreamIn: public CAmf0Stream
{
    public:
        /**
         * @brief
         * Default constructor.
        */
        CAmf0StreamIn();

    public:
        /**
         * @brief
         * Operator >> for forwarding object from the content.
         *
         * @param val
         * Reference to object for store Amf variant content.
         *
         * @return
         * Returns reference to its own object.
        */
        CAmf0StreamIn& operator>> (CAmf0Variant  &val);


        CAmf0Variant At(int i);
    private:

};


/**
 * @brief
 * Class for output stream AMF Variants.
 */
class CAmf0StreamOut: public CAmf0Stream
{
    public:
        /**
         * @brief
         * Default constructor.
        */
        CAmf0StreamOut();

    public:
        /**
         * @brief
         * Operator << loading Amf variant  to the stream.
         *
         * @param val
         * Constant eference to object for load Amf variant content.
         *
         * @return
         * Returns reference to its own object.
        */
        CAmf0StreamOut& operator<< (const CAmf0Variant& val );

    private:


};

#endif // CAmf0Stream_H
