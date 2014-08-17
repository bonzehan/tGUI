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
#ifndef _USE_COMPILER_H_
#define _USE_COMPILER_H_

//! \name The macros to identify the compiler
//! @{

//! \note for IAR
#ifdef __IS_COMPILER_IAR__
    #undef __IS_COMPILER_IAR__
#endif
#define __IS_COMPILER_IAR__ defined(__IAR_SYSTEMS_ICC__)

//! \note for gcc
#ifdef __IS_COMPILER_GCC__
    #undef __IS_COMPILER_GCC__
#endif
#define __IS_COMPILER_GCC__ defined(__GNUC__)
//! @}

//! \note for arm_mdk
#ifdef __IS_COMPILER_MDK__
    #undef __IS_COMPILER_MDK__
#endif
#define __IS_COMPILER_MDK__ defined(__CC_ARM)
//! @}

//! \note for gcc
#ifdef __IS_COMPILER_MDK__
    #undef __IS_COMPILER_MDK__
#endif
#define __IS_COMPILER_MDK__ defined(__CC_ARM)
//! @}


/* -------------------  Start of section using anonymous unions  ------------------ */
#if     __IS_COMPILER_MDK__
    #pragma push
    #pragma anon_unions
#elif   __IS_COMPILER_IAR__
    #pragma language=extended
#elif   __IS_COMPILER_GCC__
    /* anonymous unions are enabled by default */
#else
    #warning Not supported compiler type
#endif

#define __STR(__N)      #__N  
#define STR(__N)        __STR(__N)    

#include ".\error.h"
#include ".\preprocessor\mrepeat.h"
     
//! \brief CPU io
#if     defined(__CPU_ARM__)                    //!< ARM series
    #include ".\arm\arm_compiler.h"
#elif   defined(__CPU_AVR__)                    //!< Atmel AVR series
    #include ".\avr\avr_compiler.h"
#else
#error No specified MCU type!
#endif
   
#ifndef ATOM_INT_SIZE
#define ATOM_INT_SIZE           2
#endif 
     

//! \brief system macros
#define MAX(__A,__B)  (((__A) > (__B)) ? (__A) : (__B))
#define MIN(__A,__B)  (((__A) < (__B)) ? (__A) : (__B))

#define UBOUND(__ARRAY) (sizeof(__ARRAY)/sizeof(__ARRAY[0]))

#define ABS(__NUM)    (((__NUM) < 0)?(-(__NUM)):(__NUM))

#ifndef BIT
#define BIT(__N)		((uint32_t)1 << (__N))
#endif
#ifndef _BV
#define _BV(__N)        ((uint32_t)1 << (__N))
#endif
#ifndef _BM
#define __MASK(__N)     (_BV(__N) - 1)
#define _BM(__FROM,__TO)\
                        (__MASK((__TO)+1)-__MASK(__FROM))
#endif

#ifndef __CONNECT
#	define __CONNECT(a, b)			a ## b
#endif

#ifndef REFERENCE_PARAMETER
# define REFERENCE_PARAMETER(a)		(a) = (a)
#endif

#ifndef dimof
#	define dimof(arr)				(sizeof(arr) / sizeof((arr)[0]))
#endif
     
     
//! \brief This macro convert variable types between different datatypes.
# define TYPE_CONVERT(__ADDR,__TYPE)     (*((__TYPE *)(__ADDR)))

//! \brief initialize large object
# define OBJECT_INIT_ZERO(__OBJECT) \
            do\
            {\
                struct OBJECT_INIT\
                {\
                    uint8_t StructMask[sizeof(__OBJECT)];\
                }NULL_OBJECT = {{0}};\
                \
                (*((struct OBJECT_INIT *)&(__OBJECT))) = NULL_OBJECT;\
            }\
            while (false)


#include ".\ooc.h"

#endif
