///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016 Edouard Griffiths, F4EXB.                                  //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#ifndef SERIALDATACONTROLLER_H_
#define SERIALDATACONTROLLER_H_

#if defined(__WINDOWS__)
#include <windows.h>
#endif

#include <string>

namespace SerialDV
{

const unsigned char DV3000_START_BYTE   = 0x61U;

const unsigned char DV3000_TYPE_CONTROL = 0x00U;
const unsigned char DV3000_TYPE_AMBE    = 0x01U;
const unsigned char DV3000_TYPE_AUDIO   = 0x02U;

const unsigned char DV3000_CONTROL_RATEP  = 0x0AU;
const unsigned char DV3000_CONTROL_PRODID = 0x30U;
const unsigned char DV3000_CONTROL_READY  = 0x39U;

const unsigned char DV3000_REQ_PRODID[] = {DV3000_START_BYTE, 0x00U, 0x01U, DV3000_TYPE_CONTROL, DV3000_CONTROL_PRODID};
const unsigned int DV3000_REQ_PRODID_LEN = 5U;

const unsigned char DV3000_REQ_3600X2400_RATEP[] = {DV3000_START_BYTE, 0x00U, 0x0DU, DV3000_TYPE_CONTROL, DV3000_CONTROL_RATEP, 0x01U, 0x30U, 0x07U, 0x63U, 0x40U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x48U};
const unsigned char DV3000_REQ_3600X2450_RATEP[] = {DV3000_START_BYTE, 0x00U, 0x0DU, DV3000_TYPE_CONTROL, DV3000_CONTROL_RATEP, 0x04U, 0x31U, 0x07U, 0x54U, 0x24U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x6FU, 0x48U};
const unsigned int DV3000_REQ_RATEP_LEN = 17U;

const unsigned char DV3000_AUDIO_HEADER[] = {DV3000_START_BYTE, 0x01U, 0x42U, DV3000_TYPE_AUDIO, 0x00U, 0xA0U};
const unsigned char DV3000_AUDIO_HEADER_LEN = 6U;

const unsigned char DV3000_AMBE_HEADER[] = {DV3000_START_BYTE, 0x00U, 0x0BU, DV3000_TYPE_AMBE, 0x01U, 0x48U};
const unsigned char DV3000_AMBE_HEADER_LEN  = 6U;

const unsigned int DV3000_HEADER_LEN = 4U;

const unsigned int BUFFER_LENGTH = 400U;

const unsigned int MBE_AUDIO_BLOCK_SIZE  = 160U;
const unsigned int MBE_AUDIO_BLOCK_BYTES = MBE_AUDIO_BLOCK_SIZE * 2U;

const unsigned int MBE_FRAME_LENGTH_BITS = 72U;
const unsigned int MBE_FRAME_LENGTH_BYTES = MBE_FRAME_LENGTH_BITS / 8U;

enum SERIAL_SPEED {
	SERIAL_NONE   = 0,
    SERIAL_1200   = 1200,
    SERIAL_2400   = 2400,
    SERIAL_4800   = 4800,
    SERIAL_9600   = 9600,
    SERIAL_19200  = 19200,
    SERIAL_38400  = 38400,
    SERIAL_76800  = 76800,
    SERIAL_115200 = 115200,
    SERIAL_230400 = 230400,
    SERIAL_460800 = 460800
};

class SerialDataController {
public:
    SerialDataController();
    ~SerialDataController();

    bool open(const std::string& device, SERIAL_SPEED speed);

    int  read(unsigned char* buffer, unsigned int length);
    int  write(const unsigned char* buffer, unsigned int length);

    void close();

private:
    std::string    m_device;
    SERIAL_SPEED   m_speed;
#if defined(__WINDOWS__)
    HANDLE         m_handle;
    OVERLAPPED     m_readOverlapped;
    OVERLAPPED     m_writeOverlapped;
    unsigned char* m_readBuffer;
    unsigned int   m_readLength;
    bool           m_readPending;
#else
    int            m_fd;
#endif

#if defined(__WINDOWS__)
    int readNonblock(unsigned char* buffer, unsigned int length);
#endif
};

} // namespace SerialDV

#endif /* SERIALDATACONTROLLER_H_ */
