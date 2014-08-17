
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

#ifndef __USE_AVR_COMPILER_H__
#define __USE_AVR_COMPILER_H__

/*============================ INCLUDES ======================================*/
/*============================ MACROS ========================================*/
#ifndef NOP
    #define NOP()               __asm__ __volatile__ ("nop");
#endif


//! ALU integer width in byte
# define ATOM_INT_SIZE           1

//! \brief The mcu memory align mode
# define MCU_MEM_ALIGN_SIZE     ATOM_INT_SIZE


//! \brief The mcu memory endian mode
# define __BIG_ENDIAN__         false


//! \brief none standard memory types
#if __IS_COMPILER_IAR__
    # define FLASH		__flash
    # define EEPROM     __eeprom
    # define NO_INIT    __no_init
    # define ROOT       __root
    # define RAM
#elif __IS_COMPILER_GCC__
    # define FLASH		const
    # define EEPROM     const
    # define NO_INIT
    # define ROOT       
    # define RAM
#endif


/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ INCLUDES ======================================*/

//! \brief include I/O head file
#if __IS_COMPILER_ICC__
    #include <iccioavr.h>
#elif __IS_COMPILER_GCC__
    #include <avr/io.h>
    #include <avr/pgmspace.h>
#elif __IS_COMPILER_IAR__
#ifndef _USE_IGNORE_IAR_IOAVR_H_
    #ifndef _DEVICE_IO
    #define _DEVICE_IO
        #include <ioavr.h>
    #endif
    #include<intrinsics.h>
#endif
#endif


/*!  \note using the ANSI-C99 standard type,if the file stdint.h dose not exit
 *!        you should define it all by yourself.
 *!
 */
#include ".\app_type.h"

//! \brief for interrupt 
#include "signal.h"

#endif