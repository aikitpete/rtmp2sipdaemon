#include <cstdlib>
#include <cstring>

#include "handshakepackets.h"


HSPacketVirtual::HSPacketVirtual(int iSize)
{
    m_iSize = iSize;
    m_pucContent = new char[m_iSize];
    memset(m_pucContent,0,m_iSize);
}

HSPacketVirtual::HSPacketVirtual(const HSPacketVirtual &input)
{
    m_iSize = input.m_iSize;
    m_pucContent = new char[m_iSize];
    memcpy(m_pucContent,input.m_pucContent,m_iSize);
}

HSPacketVirtual::~HSPacketVirtual()
{
    delete [] m_pucContent;
}

HSPacketVirtual & HSPacketVirtual::operator=(const HSPacketVirtual &input)
{
    if (&input==this)
        return *this;
    delete [] m_pucContent;
    m_iSize = input.m_iSize;
    m_pucContent = new char[m_iSize];
    memcpy(m_pucContent,input.m_pucContent,m_iSize);
    return *this;
}

const char * HSPacketVirtual::GetContent() const
{
    return m_pucContent;
}

int HSPacketVirtual::GetSize() const
{
  return m_iSize;
}

bool HSPacketVirtual::SetContent(const char * pucContent, int iSize)
{
    if (iSize > m_iSize || iSize < 0)
        return false;
    memset(m_pucContent,0,m_iSize);
    memcpy(m_pucContent,pucContent,iSize);
    return true;
}

char HSPacketVirtual::GetByte(int iPos) const
{
    if (iPos > m_iSize-1 || iPos < 0)
        return -1;
    return m_pucContent[iPos];
}

bool HSPacketVirtual::SetByte(char ucByte, int iPos)
{
    if ( iPos > m_iSize-1 || iPos < 0)
        return false;
    m_pucContent[iPos]=ucByte;
    return true;
}

/*=====================================================================*/

HSPacketC0S0::HSPacketC0S0(): HSPacketVirtual(1)
{

}

HSPacketC0S0::~HSPacketC0S0()
{

}

bool HSPacketC0S0::SetVersion(int iVersion)
{
    if (iVersion<0 || iVersion>31)
        return false;
    SetByte((char)iVersion,0);
    return true;
}

int HSPacketC0S0::GetVersion() const
{
    return int(GetByte(0));
}

/*=====================================================================*/

HSPacketC1S1::HSPacketC1S1(): HSPacketVirtual(1536)
{
    for ( int i=4 ; i < 8 ; ++i )
    {
        SetByte(0,i);
    }
}

HSPacketC1S1::~HSPacketC1S1()
{

}

bool HSPacketC1S1::SetTime(int iTime)
{
  int _shift = 24;
  int _mask = 0xFF << _shift;
  for ( int i=0 ; i<4 ; ++i )
  {
    SetByte( (iTime & _mask) >> _shift, i );
    _shift -= 8;
    _mask >>= 8;
  }
  return true;
}

unsigned int HSPacketC1S1::GetTime() const
{
    unsigned int _uiOut = 0;
    for ( int i = 0,shift = 24 ; i < 4 ; ++i,shift -= 8 )
    {
       _uiOut+=((unsigned int)GetByte(i)) << shift;
    }
    return _uiOut;
}

bool HSPacketC1S1::SetRandomData(const char *pucRData, int io_size)
{
    for ( int i = 8 ; i < 1536 ; ++i )
    {
        SetByte(pucRData[(i-8)%io_size],i);
    }
    return true;
}

bool HSPacketC1S1::SetRandomizeData()
{
    for ( int i = 8 ; i < 1536 ; ++i )
    {
        SetByte((char)(rand()%255),i);
    }
    return true;
}

const char * HSPacketC1S1::GetRandomData() const
{
    return GetContent()+8;
}

/*=====================================================================*/

HSPacketC2S2::HSPacketC2S2()
{

}


HSPacketC2S2::~HSPacketC2S2()
{

}

bool HSPacketC2S2::SetTime2(int iTime)
{
  int _shift = 24;
  int _mask = 0xFF << _shift;
  for ( int i=4 ; i<8 ; ++i )
  {
    SetByte( (iTime & _mask) >> _shift, i );
    _shift -= 8;
    _mask >>= 8;
  }

  return true;
}

unsigned int HSPacketC2S2::GetTime2() const
{
    unsigned int _ucOut = 0;
    for ( int i=4,shift=24 ; i < 8; ++i,shift-=8 )
    {
       _ucOut+=((unsigned int)GetByte(i)) << shift;
    }
    return _ucOut;
}
