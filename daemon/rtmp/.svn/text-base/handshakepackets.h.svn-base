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
 *
 */

#ifndef HANDSHAKEPACKETS_H
#define HANDSHAKEPACKETS_H

/*!
*  \brief Virtual class. It serve as abstract class for higher Classes;
*/
class HSPacketVirtual
{
    public:
        HSPacketVirtual(int ic_size);
        HSPacketVirtual(const HSPacketVirtual &input);
        virtual ~HSPacketVirtual();
        HSPacketVirtual & operator=(const HSPacketVirtual &input);


        virtual const char *  GetContent() const;
        virtual int GetSize() const;
        virtual bool SetContent(const char * pucContent, int iSize);

    protected:
        virtual char GetByte(int iPos) const;
        virtual bool SetByte(char ucByte, int iPos);

    private:
        char * m_pucContent;
        int m_iSize;

};

/*!
*  \brief Class for C0/S0 packet.
*/
class HSPacketC0S0: public HSPacketVirtual
{
    public:
        HSPacketC0S0();
        ~HSPacketC0S0();

        bool SetVersion(int iVersion);
        int GetVersion() const;

    private:
        int m_iVersion;

};

/*!
*  \brief Class for C1/S1 packet.
*/
class HSPacketC1S1: public HSPacketVirtual
{
    public:
        HSPacketC1S1();
        ~HSPacketC1S1();

        virtual bool SetTime(int iTime);
        virtual unsigned int GetTime() const;
        virtual bool SetRandomData(const char *pucRData, int iSize);
        virtual bool SetRandomizeData();
        virtual const char * GetRandomData() const;

    protected:
        int m_iVersion;

};

/*!
*  \brief Class for C2/S2 packet.
*/
class HSPacketC2S2: public HSPacketC1S1
{
    public:
        HSPacketC2S2();
        ~HSPacketC2S2();

        virtual bool SetTime2(int iTime);
        virtual unsigned int GetTime2() const;

};

#endif // HANDSHAKEPACKETS_H
