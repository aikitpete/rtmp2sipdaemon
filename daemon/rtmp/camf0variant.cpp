#include "camf0variant.h"
#include <iostream>
using namespace std;

CAmf0Variant::CAmf0Variant()
{
    m_type = AMF0_UNDEFINED;
}

CAmf0Variant::CAmf0Variant(double dNumber)
{
    m_type = AMF0_NUMBER;
    m_dContent = dNumber;
}

CAmf0Variant::CAmf0Variant(bool bBoolean)
{
    m_type = AMF0_BOOLEAN;
    m_bContent = bBoolean;
}

CAmf0Variant::CAmf0Variant(std::string strString)
{
    if (strString.size() < 65535)
        m_type = AMF0_SHORT_STRING;
    else
        m_type = AMF0_LONG_STRING;
    m_strContent = strString;
}

CAmf0Variant::CAmf0Variant(const std::vector<std::pair<std::string,CAmf0Variant> > &object, CAmf0Variant::Type type)
{
    m_type = type;
    if (type != CAmf0Variant::AMF0_OBJECT && type != CAmf0Variant::AMF0_MIXED_ARRAY)
        m_type = CAmf0Variant::AMF0_MIXED_ARRAY;
    m_objContent = object;
}

CAmf0Variant::CAmf0Variant(int iContent, CAmf0Variant::Type type)
{
    m_type = type;
    if (m_type == AMF0_NULL)
        m_iContent = 0;
    if (m_type == AMF0_UNDEFINED)
        m_iContent = -1;
    if (m_type == AMF0_REFERENCE)
        m_iContent = iContent;

}

CAmf0Variant::~CAmf0Variant()
{

}

std::string CAmf0Variant::EncodeAmf0() const
{
    string _out;
    if (m_type == AMF0_NUMBER)
    {
        _out.push_back(char(AMF0_NUMBER));
        const double *_pdContent = &m_dContent;
        const char *_pcContent = (const char *)_pdContent;
        for (int i=7 ; i >= 0 ; --i)
        {
            _out.push_back(char(_pcContent[i]));
        }
    }
    if (m_type == AMF0_BOOLEAN)
    {
        _out.push_back(char(AMF0_BOOLEAN));
        _out.push_back(char(m_bContent));
    }
    if (m_type == AMF0_SHORT_STRING)
    {
        _out.push_back(char(AMF0_SHORT_STRING));
        _out.push_back(char((m_strContent.size() & 0xFF00) >> 8));
        _out.push_back(char(m_strContent.size() & 0xFF));
        _out.append(m_strContent);
    }
    if (m_type == AMF0_OBJECT)
    {
        _out.push_back(char(AMF0_OBJECT));
        for (unsigned int i = 0 ; i < m_objContent.size() ; i++)
        {
            _out.push_back(char((m_objContent[i].first.size() & 0xFF00) >> 8));
            _out.push_back(char(m_objContent[i].first.size() & 0xFF));
            _out.append(m_objContent[i].first);
            _out.append(m_objContent[i].second.EncodeAmf0());
        }

        _out.push_back(char(AMF0_OBJECT_END));
    }

    if (m_type == AMF0_NULL)
    {
        _out.push_back(char(AMF0_NULL));
    }


    if (m_type == AMF0_MIXED_ARRAY)
    {
        _out.push_back(char(AMF0_MIXED_ARRAY));
        for (int i = 3 ; i >= 0 ; --i)
            _out.push_back(char((m_objContent.size() >> 8*i) & 0xFF));

        for (unsigned int i = 0 ; i < m_objContent.size() ; i++)
        {
            _out.push_back(char((m_objContent[i].first.size() & 0xFF00) >> 8));
            _out.push_back(char(m_objContent[i].first.size() & 0xFF));
            _out.append(m_objContent[i].first);
            _out.append(m_objContent[i].second.EncodeAmf0());
        }

        _out.push_back(char(0));
        _out.push_back(char(0));

    }

    if (m_type == AMF0_LONG_STRING)
    {
       _out.push_back(char(AMF0_LONG_STRING));
       _out.push_back(char((m_strContent.size() & 0xFF000000) >> 24));
       _out.push_back(char((m_strContent.size() & 0xFF0000) >> 16));
       _out.push_back(char((m_strContent.size() & 0xFF00) >> 8));
       _out.push_back(char(m_strContent.size() & 0xFF));
       _out.append(m_strContent);
    }
    return _out;
}

CAmf0Variant::Type CAmf0Variant::GetType() const
{
    return m_type;
}

double CAmf0Variant::toDouble() const
{
    if (m_type == AMF0_NUMBER)
        return m_dContent;
    return 0.0;
}

bool CAmf0Variant::toBool() const
{
    if (m_type == AMF0_BOOLEAN)
        return m_bContent;
    return false;
}

std::string CAmf0Variant::toString() const
{
    if (m_type == AMF0_SHORT_STRING || m_type == AMF0_LONG_STRING)
        return m_strContent;
    return std::string();
}

std::vector<std::pair<std::string,CAmf0Variant> > CAmf0Variant::toObject() const
{
    if (m_type == AMF0_OBJECT)
        return m_objContent;
    return std::vector<std::pair<std::string,CAmf0Variant> >();
}

