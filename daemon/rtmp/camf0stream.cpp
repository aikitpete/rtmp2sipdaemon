#include "camf0stream.h"
#include <iostream>
#include <iomanip>



using namespace std;

CAmf0Stream::CAmf0Stream()
{

}

CAmf0Stream::~CAmf0Stream()
{

}

CAmf0Stream::CAmf0Stream(const char *ucContent, int iSize)
{
    DecodeAmf(ucContent, iSize);
}

string CAmf0Stream::EncodeAmf() const
{
    string _out;
    for ( unsigned int i = 0 ; i < m_Content.size() ; ++i)
        _out.append(m_Content[i].EncodeAmf0());

    _out.push_back(char(0x09));
    return _out;
}

bool CAmf0Stream::DecodeAmf(const char *ucContent, int iSize)
{
    queue<char> _qContent;
    for (int i = 0 ; i < iSize ; ++i)
        _qContent.push(ucContent[i]);

    CAmf0Variant::Type _type = CAmf0Variant::AMF0_NULL;
    while (_type != CAmf0Variant::AMF0_UNDEFINED && !_qContent.empty())
    {
        CAmf0Variant _variantBuffer = ReadNext(_qContent);
        m_Content.push_back(_variantBuffer);
        _type = _variantBuffer.GetType();
    }

    return true;
}


CAmf0Variant CAmf0Stream::ReadNext(queue<char> &qContent)
{

    char _type = qContent.front();
    qContent.pop();
    if (_type == CAmf0Variant::AMF0_NUMBER)
    {
        cout << "Number found:";
        double _dContent;
        char *_pcContent = (char *)&_dContent;
        for (int i = 7 ; i >= 0 ; --i)
        {
            _pcContent[i] = qContent.front();
            qContent.pop();
        }
        cout << " content: " << _dContent << endl;
        return CAmf0Variant(_dContent);
    }

    if (_type == CAmf0Variant::AMF0_BOOLEAN)
    {
        cout << "Bool found:";
        bool _bContent;
        _bContent = bool(qContent.front());
        qContent.pop();
        cout << " content: " << _bContent << endl;
        return CAmf0Variant(_bContent);
    }

    if (_type == CAmf0Variant::AMF0_SHORT_STRING)
    {
        return CAmf0Variant(ReadString(qContent));

    }
    if (_type == CAmf0Variant::AMF0_OBJECT)
    {
         cout << "Object found" << endl;
         std::vector<std::pair<std::string,CAmf0Variant> > _vContent;

         while (qContent.front() != char(CAmf0Variant::AMF0_OBJECT_END) && !qContent.empty())
         {
             string _strBuffer = ReadString(qContent);
             if (_strBuffer.empty())
                 break;
             cout << "Next object member." << endl;
             _vContent.push_back(pair<std::string,CAmf0Variant>(_strBuffer,ReadNext(qContent)));
         }

         if (qContent.front() == char(CAmf0Variant::AMF0_OBJECT_END) && !qContent.empty())
             qContent.pop();
         return CAmf0Variant(_vContent);
    }

    if (_type == CAmf0Variant::AMF0_NULL)
    {
        cout << "Null type found" << endl;
        return CAmf0Variant(0,CAmf0Variant::AMF0_NULL);
    }

    if (_type == CAmf0Variant::AMF0_MIXED_ARRAY)
    {
        cout << "Mixed array found" << endl;
        std::vector<std::pair<std::string,CAmf0Variant> > _vContent;

        int _iArraySize = 0;
        for ( int i = 3 ; i >=0 ; --i)
        {
            _iArraySize += int(qContent.front()) << 8*i;
            qContent.pop();
        }
        cout << "Array size: " << _iArraySize << endl;
         for (int i = 0 ; i < _iArraySize ; i++)
         {
             string _strBuffer = ReadString(qContent);
             if (_strBuffer.empty())
                 break;
             cout << "Next object member." << endl;
             _vContent.push_back(pair<std::string,CAmf0Variant>(_strBuffer,ReadNext(qContent)));
         }

         if (qContent.front() == char(0) && !qContent.empty())
             qContent.pop();
         if (qContent.front() == char(0) && !qContent.empty())
             qContent.pop();

         return CAmf0Variant(_vContent);
    }

    cout << "Unimplemented type: " << int(_type) << endl;
    return CAmf0Variant();
}

std::string CAmf0Stream::ReadString(std::queue<char> &qContent)
{
    cout << "String found:" ;
    int _iStrSize = 0;
    _iStrSize = (int(qContent.front()) << 8);
    qContent.pop();
    _iStrSize += int(qContent.front());
    qContent.pop();

    cout << " size = " << _iStrSize;
    string _strContent;
    while (UTF8Len(_strContent.data(),_strContent.size()) < _iStrSize && !qContent.empty())
    {
        _strContent += qContent.front();
        qContent.pop();
    }

    cout << " content: " << _strContent << endl;
    return _strContent;
}

bool CAmf0Stream::SetContent(const std::vector<CAmf0Variant> &content)
{
    m_Content = content;
    return true;
}



CAmf0StreamIn::CAmf0StreamIn()
{

}

CAmf0StreamIn& CAmf0StreamIn::operator>> (CAmf0Variant  &val)
{
    val = m_Content.front();
    m_Content.erase(m_Content.begin());
    return *this;
}

CAmf0Variant CAmf0StreamIn::At(int i)
{
    return m_Content.at(i);
}


CAmf0StreamOut::CAmf0StreamOut()
{

}

CAmf0StreamOut& CAmf0StreamOut::operator<< (const CAmf0Variant& val )
{
    m_Content.push_back(val);
    return *this;
}

int CAmf0Stream::UTF8Len ( const char * str , int size )
{
  int i=0;
  const unsigned char *s = reinterpret_cast<const unsigned char *>(str);
  unsigned char ch=s[i];
  unsigned char mask=0x7F;
  int posun=0;
  int cnt=0;
  long tmp=0;
  while (i < size)
  {
    cnt++;
    tmp=0;
    mask=0x7F;
    posun=0;
    if (ch>=0xF5 || (ch<0xC2 && ch>0x7F)) return -1;
    /*if (ch>=0xC0 && ch<=0xC1)
    {
      i++;
      mask=0x1F;
      tmp<<=6;
      tmp+=(unsigned char)s[i]&0x3F;
      if ((unsigned char)s[i]>=0x80  || (unsigned char)s[i]==0) return -1;
    } */
    if (ch>=0xC2)
    {
      i++;
      mask=0x1F;
      posun++;
      //tmp<<=6;
      tmp+=(unsigned char)s[i]&0x3F;

      //if ((unsigned char)s[i]<0x80 || (unsigned char)s[i]>0xBF) return -1;
    }
    if (ch>=0xE0)
    {
      i++;
      mask=0xF;
      posun++;
      tmp<<=6;
      tmp+=(unsigned char)s[i]&0x3F;
     // if ((unsigned char)s[i]<0x80 || (unsigned char)s[i]>0xBF) return -1;
    }
    if (ch>=0xF0)
    {
      i++;
      mask=0x7;
      posun++;
      tmp<<=6;
      tmp+=(unsigned char)s[i]&0x3F;
     // if ((unsigned char)s[i]<0x80 || (unsigned char)s[i]>0xBF) return -1;
    }
    //cout << int(tmp) << endl;
    tmp+=((ch&mask)<<6*posun);

    if (tmp>0x10FFFF || (tmp>=0xD800 && tmp<=0xDFFF) || (tmp>=0xFDD0 && tmp<=0xFDEF) || tmp==0xFFFE || tmp==0xFFFF) return -1;
    ch=s[++i];
  }
  return cnt;
}

