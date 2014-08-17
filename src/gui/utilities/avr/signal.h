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

#ifndef _USE_SIGNAL_H_
#define _USE_SIGNAL_H_

/*============================ INCLUDES ======================================*/
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
//! \brief interrupt / signal
#if __IS_COMPILER_GCC__
    #include <avr/interrupt.h>

    #define REGISTER_ISR(__VECTOR, __ISR)       \
            extern void __ISR(void);\
            ISR(__VECTOR)\
            {\
                __ISR();\
            }

#elif __IS_COMPILER_IAR__
    #ifndef PRAGMA
        #define PRAGMA(__STRING)   _Pragma(#__STRING)
    #endif
    #ifndef ISR
        #define ISR(num) PRAGMA( vector = num ) __interrupt void isr_##num(void)
    #endif

    #define REGISTER_ISR(__VECTOR, __ISR)       \
            extern __task void __ISR(void);\
            PRAGMA( vector = __VECTOR ) __interrupt void isr_##__VECTOR(void)\
            {\
                __ISR();\
            }
#endif

#define ENABLE_GLOBAL_INTERRUPT()      __asm__ __volatile__ ("sei")
#define DISABLE_GLOBAL_INTERRUPT()     __asm__ __volatile__ ("cli")

#define GLOBAL_INTERRUPT_ENABLED()     ((0 != (SREG & 0x80)) ? true : false)

            
//! \brief The safe ATOM code section macro
# define SAFE_ATOM_CODE(__CODE)     {\
        volatile uint8_t chSREG = SREG;\
        DISABLE_GLOBAL_INTERRUPT();\
        __CODE;\
        SREG = chSREG;\
    }

//! \brief Exit from the safe atom operations
# define EXIT_SAFE_ATOM_CODE()          SREG = chSREG;\

//! \brief ATOM code section macro
# define ATOM_CODE(__CODE)      {\
                DISABLE_GLOBAL_INTERRUPT();\
                __CODE;\
                ENABLE_GLOBAL_INTERRUPT();\
            }

//! \brief Exit from the atom operations
# define EXIT_ATOM_CODE()   ENABLE_GLOBAL_INTERRUPT();



//! \name ES_LOCKER value
//! @{
#define LOCKED          true            //!< locked
#define UNLOCKED        false           //!< unlocked
//! @}

//! \note critical code section protection
//! \param __LOCKER ES_LOCKER variable
//! \param __CODE   target code segment
#define LOCK(__LOCKER, __CODE)  \
            {\
                volatile uint8_t chSREG = SREG;\
                locker_t *pLocker = &(__LOCKER);\
                DISABLE_GLOBAL_INTERRUPT();\
                if (!(*pLocker)) {\
                    (*pLocker) = LOCKED;\
                    __CODE;\
                    (*pLocker) = UNLOCKED;\
                }\
                SREG = chSREG;\
            }


#define LOCK_INIT(__LOCKER)     do {(__LOCKER) = UNLOCKED;}while(false)


#define EXIT_LOCK()    do {\
        (*pLocker) = UNLOCKED;\
        SREG = chSREG;\
    } while(false)

//! \brief exit lock checker structure
#define EXIT_LOCK_CHECKER() EXIT_SAFE_ATOM_CODE()

/*! \note check specified locker and run code segment
 *! \param __LOCKER a ES_LOCKER variable
 *! \param __CODE target code segment
 */
#define LOCK_CHECKER(__LOCKER, __CODE)  {\
                SAFE_ATOM_CODE  (\
                    if (UNLOCKED == (__LOCKER)) {\
                        __CODE;\
                    }\
                )\
            }

/*============================ TYPES =========================================*/
typedef volatile bool locker_t;


/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/


#endif
