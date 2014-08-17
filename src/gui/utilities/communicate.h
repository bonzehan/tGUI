/***************************************************************************
 *   Copyright(C)2009-2012 by Gorgon Meducer<Embedded_zhuoran@hotmail.com> *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef __UTILITIES_COMMUNICATE_H__
#define __UTILITIES_COMMUNICATE_H__

/*============================ INCLUDES ======================================*/
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

//! \name interface: byte pipe
//! @{
DEF_INTERFACE(i_byte_pipe_t)
    //!< read a byte
    bool (*ReadByte)(uint8_t *pchByte);
    //!< write a byte
    bool (*WriteByte)(uint_fast8_t chByte);
END_DEF_INTERFACE(i_byte_pipe_t)
//! @}

//! \name interface: pipe
//! @{
DEF_INTERFACE(i_pipe_t)
    //!< read a byte
    bool (*ReadByte)(uint8_t *pchByte);
    //!< write a byte
    bool (*WriteByte)(uint_fast8_t chByte);
    
    //! read a block
    uint_fast16_t  (*ReadStream)(uint8_t *pchStream, uint_fast16_t hwSize);
    //! write a block
    uint_fast16_t  (*WriteStream)(uint8_t *pchStream, uint_fast16_t hwSize);

END_DEF_INTERFACE(i_pipe_t)
//! @}

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/


#endif
/* EOF */