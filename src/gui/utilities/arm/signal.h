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
//! \brief The safe ATOM code section macro
# define SAFE_ATOM_CODE(...)     {\
        istate_t tState = GET_GLOBAL_INTERRUPT_STATE();\
        DISABLE_GLOBAL_INTERRUPT();\
        __VA_ARGS__;\
        SET_GLOBAL_INTERRUPT_STATE(tState);\
    }

//! \brief Exit from the safe atom operations
# define EXIT_SAFE_ATOM_CODE()          SET_GLOBAL_INTERRUPT_STATE(tState);

//! \brief ATOM code section macro
# define ATOM_CODE(...)      {\
                DISABLE_GLOBAL_INTERRUPT();\
                __VA_ARGS__;\
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
#define LOCK(__LOCKER,...)  \
            {\
                istate_t tState = GET_GLOBAL_INTERRUPT_STATE();\
                locker_t *pLocker = &(__LOCKER);\
                DISABLE_GLOBAL_INTERRUPT();\
                if (!(*pLocker)) {\
                    (*pLocker) = LOCKED;\
                    ENABLE_GLOBAL_INTERRUPT();\
                    __VA_ARGS__;\
                    (*pLocker) = UNLOCKED;\
                }\
                SET_GLOBAL_INTERRUPT_STATE(tState);\
            }


#define LOCK_INIT(__LOCKER)     do {(__LOCKER) = UNLOCKED;}while(false)


#define EXIT_LOCK()     do {\
                            (*pLocker) = UNLOCKED;\
                            SET_GLOBAL_INTERRUPT_STATE(tState);\
                        } while(false)

#define ENTER_LOCK(__LOCKER)    \
                        enter_lock(__LOCKER)

#define LEAVE_LOCK(__LOCKER)    \
                        leave_lock(__LOCKER)

//! \brief exit lock checker structure
#define EXIT_LOCK_CHECKER() EXIT_SAFE_ATOM_CODE()

/*! \note check specified locker and run code segment
 *! \param __LOCKER a ES_LOCKER variable
 *! \param __CODE target code segment
 */
#define LOCK_CHECKER(__LOCKER, ...)  {\
                SAFE_ATOM_CODE  (\
                    if (UNLOCKED == (__LOCKER)) {\
                        __VA_ARGS__;\
                    }\
                )\
            }
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
typedef volatile bool locker_t;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

/*! \brief try to enter a section
 *! \param ptLock locker object
 *! \retval lock section is entered
 *! \retval The section is locked
 */
extern bool enter_lock(locker_t *ptLock);

/*! \brief leave a section
 *! \param ptLock locker object
 *! \return none
 */
extern void leave_lock(locker_t *ptLock);
#endif
