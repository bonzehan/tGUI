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


/*============================ INCLUDES ======================================*/
#ifndef __STORE_ENVIRONMENT_CFG_IN_PROJ__
#include "..\..\environment_cfg.h"
#endif

#include ".\compiler.h"

/*============================ MACROS ========================================*/

#define this             (*ptThis)

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

//! \name general event handler
//! @{
//DEF_CLASS(DELEGATE_HANDLE)
typedef struct __delegate_handler CLASS(DELEGATE_HANDLE);
struct __delegate_handler {
    DELEGATE_HANDLE_FUNC    *fnHandler;         //!< event handler
    void                    *pArg;              //!< Argument
    CLASS(DELEGATE_HANDLE)  *ptNext;            //!< next 
};
//END_DEF_CLASS(DELEGATE_HANDLE)
//! @}

//! \name event
//! @{
//EXTERN_CLASS(DELEGATE)
typedef struct __delegate CLASS(DELEGATE);
struct __delegate {
    DELEGATE_HANDLE *ptEvent;
    DELEGATE_HANDLE *ptBlockedList;
    CLASS(DELEGATE_HANDLE) **pptHandler;
};
//END_EXTERN_CLASS(DELEGATE)
//! @}

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

/*! \brief initialize event 
 *! \param ptEvent target event
 *! \return the address of event item
 */
DELEGATE *delegate_init(DELEGATE *ptEvent)
{
    CLASS(DELEGATE) *ptThis = (CLASS(DELEGATE) *)ptEvent;
    do {
        if (NULL == ptEvent) {
            break;
        }

        this.ptEvent = NULL;
        this.ptBlockedList = NULL;
        this.pptHandler = (CLASS(DELEGATE_HANDLE) **)&(this.ptEvent);
        
    } while (0);

    return ptEvent;
}

/*! \brief initialize event handler item
 *! \param ptHandler the target event handler item
 *! \param fnRoutine event handler routine
 *! \param pArg handler extra arguments
 *! \return the address of event handler item
 */
DELEGATE_HANDLE *delegate_handler_init(
    DELEGATE_HANDLE *ptHandler, DELEGATE_HANDLE_FUNC *fnRoutine, void *pArg)
{

    CLASS(DELEGATE_HANDLE) *ptHND = (CLASS(DELEGATE_HANDLE) *)ptHandler;
    if (NULL == ptHandler || NULL == fnRoutine) {
        return NULL;
    }
    ptHND->fnHandler = fnRoutine;
    ptHND->pArg = pArg;
    ptHND->ptNext = NULL;

    return ptHandler;
}


static CLASS(DELEGATE_HANDLE) **search_list(
    CLASS(DELEGATE_HANDLE) **pptHandler, CLASS(DELEGATE_HANDLE) *ptHND)
{
    //! search event handler chain
    while (NULL != (*pptHandler)) {
        if ((*pptHandler) == ptHND) {
            return pptHandler;
        }
        pptHandler = &((*pptHandler)->ptNext);      //!< get next item
    }
    return NULL;
}

/*! \brief register event handler to specified event
 *! \param ptEvent target event
 *! \param ptHandler target event handler
 *! \return access result
 */
gsf_err_t register_delegate_handler(DELEGATE *ptEvent, DELEGATE_HANDLE *ptHandler)
{
    CLASS(DELEGATE) *ptThis = (CLASS(DELEGATE) *)ptEvent;
    CLASS(DELEGATE_HANDLE) *ptHND = (CLASS(DELEGATE_HANDLE) *)ptHandler;
    if ((NULL == ptEvent) || (NULL == ptHandler) || (NULL == ptHND->fnHandler)) {
        return GSF_ERR_INVALID_PTR;
    } else if (NULL != ptHND->ptNext) {     
        //! search ready list
        CLASS(DELEGATE_HANDLE) **pptHandler = search_list(   
            (CLASS(DELEGATE_HANDLE) **)&(this.ptBlockedList), ptHND );

        if (NULL != pptHandler) {
            //! safe to remove
            (*pptHandler) = ptHND->ptNext;
            ptHND->ptNext = NULL;
        } else {        
            return GSF_ERR_REQ_ALREADY_REGISTERED;
        }
    }

    //! add handler to the ready list
    ptHND->ptNext = (CLASS(DELEGATE_HANDLE) *)(this.ptEvent);
    this.ptEvent = ptHandler;

    return GSF_ERR_NONE;
}



/*! \brief unregister a specified event handler
 *! \param ptEvent target event
 *! \param ptHandler target event handler
 *! \return access result
 */
gsf_err_t unregister_delegate_handler( DELEGATE *ptEvent, DELEGATE_HANDLE *ptHandler)
{
    CLASS(DELEGATE) *ptThis = (CLASS(DELEGATE) *)ptEvent;
    CLASS(DELEGATE_HANDLE) *ptHND = (CLASS(DELEGATE_HANDLE) *)ptHandler;
    CLASS(DELEGATE_HANDLE) **pptHandler;
    if ((NULL == ptEvent) || (NULL == ptHandler)) {
        return GSF_ERR_INVALID_PTR;
    } 

    do {
        //! search ready list
        pptHandler = search_list(   (CLASS(DELEGATE_HANDLE) **)&(this.ptEvent), 
                                    ptHND );
        if (NULL != pptHandler) {
            //! safe to remove
            (*pptHandler) = ptHND->ptNext;
            ptHND->ptNext = NULL;
            if (this.pptHandler == &(ptHND->ptNext)) {
                this.pptHandler = pptHandler;
            }
            break;
        }
        //! search ready list
        pptHandler = search_list(   (CLASS(DELEGATE_HANDLE) **)&(this.ptBlockedList), 
                                    ptHND );
        if (NULL != pptHandler) {
            //! safe to remove
            (*pptHandler) = ptHND->ptNext;
            ptHND->ptNext = NULL;
            if (this.pptHandler == &(ptHND->ptNext)) {
                this.pptHandler = pptHandler;
            }
            break;
        }
    } while(false);
    
    return GSF_ERR_NONE;
}

static fsm_rt_t __move_to_block_list(CLASS(DELEGATE) *ptThis, CLASS(DELEGATE_HANDLE) *ptHandler)
{
    CLASS(DELEGATE_HANDLE) *ptHND = ptHandler;
    //! remove handler from ready list
    (*this.pptHandler) = ptHND->ptNext;
    //! add handler to block list
    ptHND->ptNext = (CLASS(DELEGATE_HANDLE) *)this.ptBlockedList;
    this.ptBlockedList = (DELEGATE_HANDLE *)ptHND;

    if (NULL == this.ptEvent) {
        return fsm_rt_cpl;
    }

    return fsm_rt_on_going;
}

#define RAISE_EVENT_START               0
#define RAISE_EVENT_CHECK_HANDLER       1
#define RAISE_EVENT_RUN_HANDLER         2
#define RAISE_EVENT_RESET_FSM()     do { this.chState = 0; } while (0)

/*! \brief raise target event
 *! \param ptEvent the target event
 *! \param pParam event parameter
 *! \return access result
 */
fsm_rt_t invoke_delegate( DELEGATE *ptEvent, void *pParam)
{
    CLASS(DELEGATE) *ptThis = (CLASS(DELEGATE) *)ptEvent;
    if (NULL == ptEvent) {
        return (fsm_rt_t)GSF_ERR_INVALID_PTR;
    }

    if (NULL == this.ptEvent) {
        if (NULL == this.ptBlockedList) {
            //! nothing to do
            return fsm_rt_cpl;
        }
        
        //! initialize state
        this.ptEvent = this.ptBlockedList;
        this.ptBlockedList = NULL;
        this.pptHandler = (CLASS(DELEGATE_HANDLE) **)&(this.ptEvent);
    } 

    if (NULL == (*this.pptHandler)) {
        //! finish visiting the ready list
        this.pptHandler = (CLASS(DELEGATE_HANDLE) **)&(this.ptEvent);
        if (NULL == (*this.pptHandler)) {
            //! complete
            return fsm_rt_cpl;
        }
    } else {
        CLASS(DELEGATE_HANDLE) *ptHandler = (*this.pptHandler);
        
        if (NULL != ptHandler->fnHandler) {
            //! run the event handler
            fsm_rt_t tFSM = ptHandler->fnHandler(ptHandler->pArg,pParam);

            if (fsm_rt_on_going == tFSM) { 
                this.pptHandler = &(ptHandler->ptNext);    //!< get next item
            } else if (EVENT_RT_UNREGISTER == tFSM) {
                //! return EVENT_RT_UNREGISTER means event handler could be removed
                CLASS(DELEGATE_HANDLE) *ptHND = ptHandler;
                (*this.pptHandler) = ptHND->ptNext;
                ptHND->ptNext = NULL;
            } else {
                return __move_to_block_list(ptThis, ptHandler);
            }
        } else {
            return __move_to_block_list(ptThis, ptHandler);
        }
    }

    return fsm_rt_on_going;
}




/* EOF */

