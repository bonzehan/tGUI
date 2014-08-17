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


#ifndef __USE_ARM_COMPILER_H__
#define __USE_ARM_COMPILER_H__

/*============================ INCLUDES ======================================*/
#if __IS_COMPILER_IAR__
    #include<intrinsics.h>
#endif

/*============================ MACROS ========================================*/

#ifndef DEF_REG
#define DEF_REG                     \
        union  {                    \
            struct {
#endif
    
#ifndef END_DEF_REG
#define END_DEF_REG(__NAME)         \
            };                      \
            reg32_t Value;          \
        }__NAME;
#endif

#ifndef __REG_MACRO__
#define __REG_MACRO__
#endif


#ifndef REG_RSVD_0x10
#define REG_RSVD_0x10                   \
    reg32_t                     : 32;   \
    reg32_t                     : 32;   \
    reg32_t                     : 32;   \
    reg32_t                     : 32;   
#endif
#ifndef REG_RSVD_0x80       
#define REG_RSVD_0x80                   \
            REG_RSVD_0x10               \
            REG_RSVD_0x10               \
            REG_RSVD_0x10               \
            REG_RSVD_0x10               \
            REG_RSVD_0x10               \
            REG_RSVD_0x10               \
            REG_RSVD_0x10               \
            REG_RSVD_0x10
#endif

#ifndef REG_RSVD_0x100                 
#define REG_RSVD_0x100                  \
            REG_RSVD_0x80               \
            REG_RSVD_0x80
#endif

#ifndef REG_RSVD_0x800
#define REG_RSVD_0x800                  \
            REG_RSVD_0x100              \
            REG_RSVD_0x100              \
            REG_RSVD_0x100              \
            REG_RSVD_0x100              \
            REG_RSVD_0x100              \
            REG_RSVD_0x100              \
            REG_RSVD_0x100              \
            REG_RSVD_0x100
#endif

//! ALU integer width in byte
# define ATOM_INT_SIZE                   4

//! \brief The mcu memory align mode
# define MCU_MEM_ALIGN_SIZE             ATOM_INT_SIZE

#ifndef __volatile__
#define __volatile__
#endif

//! \brief 1 cycle nop operation
#ifndef NOP
    #define NOP()                       __asm__ __volatile__ ("nop");
#endif


//! \brief none standard memory types
#if __IS_COMPILER_IAR__
#   define FLASH            const
#   define EEPROM           const
#   define NO_INIT          __no_init
#   define ROOT             __root
#   define IN_LINE          inline
#   define WEAK             __weak
#   define RAMFUNC          __ramfunc
#   define __asm__          __asm
#   define ALIGN(__N)       _Pragma(__STR(data_alignment=__N))
#   define AT_ADDR(__ADDR)  @ __ADDR
#   define SECTION(__SEC)   _Pragma(__STR(location=__SEC))
#elif __IS_COMPILER_GCC__
#   define FLASH            const
#   define EEPROM           const
#   define NO_INIT          __attribute__(( section( "noinit"))
#   define ROOT             __attribute__((used))    
#   define IN_LINE          inline
#   define WEAK             __attribute__((weak))
#   define RAMFUNC          __attribute__((section ("textrw")))
#   define __asm__          __asm
#   define ALIGN(__N)       __attribute__((aligned (__N)))
#   define AT_ADDR(__ADDR)  __attribute__((at(__ADDR))) 
#   define SECTION(__SEC)   __attribute__((section (__SEC)))
#elif __IS_COMPILER_MDK__
#   define FLASH            const
#   define EEPROM           const
#   define NO_INIT          __attribute__( ( section( "noinit"),zero_init) )
#   define ROOT             __attribute__((used))    
#   define IN_LINE          __inline
#   define WEAK             __attribute__((weak))
#   define RAMFUNC          __attribute__((section ("textrw")))
#   define __asm__          __asm
#   define ALIGN(__N)       __attribute__((aligned (__N))) 
#   define AT_ADDR(__ADDR)  __attribute__((at(__ADDR)))
#   define SECTION(__SEC)   __attribute__((section (__SEC)))
#endif

/*----------------------------------------------------------------------------*
 * Signal & Interrupt Definition                                              *
 *----------------------------------------------------------------------------*/

  /*!< Macro to enable all interrupts. */
#if __IS_COMPILER_IAR__
#define ENABLE_GLOBAL_INTERRUPT()       __enable_interrupt()
#else
#define ENABLE_GLOBAL_INTERRUPT()       __asm__ __volatile__ (" CPSIE i")
#endif

  /*!< Macro to disable all interrupts. */
#if __IS_COMPILER_IAR__
#define DISABLE_GLOBAL_INTERRUPT()      __disable_interrupt()
#else
#define DISABLE_GLOBAL_INTERRUPT        __asm__ __volatile__ (" CPSID i");
#endif

#if __IS_COMPILER_IAR__
#define GET_GLOBAL_INTERRUPT_STATE()        __get_interrupt_state()
#define SET_GLOBAL_INTERRUPT_STATE(__STATE) __set_interrupt_state(__STATE)
typedef __istate_t   istate_t;
#else
#error No support for interrupt state access
#endif

/*============================ TYPES =========================================*/
/*============================ INCLUDES ======================================*/

/*----------------------------------------------------------------------------*
 * Device Dependent Compiler Files                                            *
 *----------------------------------------------------------------------------*/
#if     defined(__CORTEX_M0__)
#include "cortex_m0_compiler.h"
#elif   defined(__CORTEX_M0P__)
#include "cortex_m0p_compiler.h"
#elif   defined(__CORTEX_M3__)
#include "cortex_m3_compiler.h"
#elif   defined(__CORTEX_M4__)
#include "cortex_m4_compiler.h"
#else
#error No supported compiler.h file!
#endif

/*!  \note using the ANSI-C99 standard type,if the file stdint.h dose not exit
 *!        you should define it all by yourself.
 *!
 */
#include ".\app_type.h"

//! \brief for interrupt 
#include ".\signal.h"

#endif