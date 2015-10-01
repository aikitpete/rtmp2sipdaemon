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
 * Contain CAmf0Variant class for represent one of AMF0 types.
 */

#ifndef CAMF0VARIANT_H
#define CAMF0VARIANT_H

#include <string>
#include <vector>


/**
 * @brief
 * Class for one of type used in AMF0 formating.
 */
class CAmf0Variant
{
    public:
       enum Type { AMF0_NUMBER = 0x00 , AMF0_BOOLEAN = 0x01 , AMF0_SHORT_STRING = 0x02 , AMF0_OBJECT = 0x03 ,
                   AMF0_MOVIE = 0X04 , AMF0_NULL = 0x05 , AMF0_UNDEFINED = 0x06 , AMF0_REFERENCE = 0x07,
                   AMF0_MIXED_ARRAY = 0x08 , AMF0_OBJECT_END = 0x09 , AMF0_ARRAY = 0x0A , AMF0_TIMESTAMP = 0x0B ,
                   AMF0_LONG_STRING = 0x0C , AMF0_UNSUPPORTED = 0x0D , AMF0_RECORD_SET = 0x0E , AMF0_XML_DOC = 0x0F ,
                   AMF0_TYPED_OBJECT = 0x10 , AMF0_AMF3_OBJECT = 0x11 };


    public:
        /**
         * @brief
         * Default constructor. Set up m_type to AMF0_UNDEFINED.
        */
        CAmf0Variant();

        /**
         * @brief
         * Destructor.
        */
        virtual ~CAmf0Variant();

        /**
         * @brief
         * Constructor for initialize with double value.
        */
        CAmf0Variant(double dNumber);

        /**
         * @brief
         * Constructor for initialize with boolean value.
        */
        CAmf0Variant(bool bBoolean);

        /**
         * @brief
         * Constructor for initialize with string value.
        */
        CAmf0Variant(std::string strString);

        /**
         * @brief
         * Constructor for initialize with object value or with EMCA Array.
         * Object is represented by vector where member is pair of string and CAmf0Variant object.
        */
        CAmf0Variant(const std::vector<std::pair<std::string,CAmf0Variant> > &object, CAmf0Variant::Type type = CAmf0Variant::AMF0_MIXED_ARRAY);

        /**
         * @brief
         * Constructor for initialize with int value.
         * This is universal contructor for types: AMF0_NULL, AMF0_UNDEFINED, AMF0_REFERENCE.
        */
        CAmf0Variant(int iContent, CAmf0Variant::Type type);


    public:
        /**
         * @brief
         * [getter] Returns type used in object.
         *
         * @return
         * Returns one of the types defined in Type enumeration
         *
         * @see
         * CAmf0Variant::Type
        */
        CAmf0Variant::Type GetType() const;

        /**
         * @brief
         * Function for return double value of the content.
         *
         * @return
         * Returns double value.
        */
        double toDouble() const;

        /**
         * @brief
         * Function for return boolean value of the content.
         *
         * @return
         * Returns boolean value.
        */
        bool toBool() const;

        /**
         * @brief
         * Function for return string value of the content.
         *
         * @return
         * Returns string value.
        */
        std::string toString() const;

        /**
         * @brief
         * Function for return object value of the content.
         *
         * @return
         * Returns std::vector<std::pair<std::string,CAmf0Variant> > value.
        */
        std::vector<std::pair<std::string,CAmf0Variant> > toObject() const;

        std::string EncodeAmf0() const;

    private:
        Type m_type;
        double m_dContent;
        bool m_bContent;
        std::string m_strContent;
        std::vector<std::pair<std::string,CAmf0Variant> > m_objContent;
        int m_iContent;

};

#endif // CAmf0Variant_H
