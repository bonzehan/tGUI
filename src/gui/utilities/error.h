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

#ifndef _USE_ERROR_H_
#define _USE_ERROR_H_

/*============================ INCLUDES ======================================*/
#include "compiler.h"


/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
//! \brief setting error code
# define SET_ERROR(__ERROR_ADDR,__CODE,__HANDLER)    \
        do{(*(__ERROR_ADDR)) = (__CODE);} while(false)
                      
//! \brief getting error code  
# define GET_ERROR(__ERROR_ADDR)                    (*(__ERROR_ADDR))

/*============================ TYPES =========================================*/

//! \name standard error code
//! @{
typedef enum {
    GSF_ERR_NONE                       =0,     //!< none error
    GSF_ERR_GENERAL                    =-1,    //!< unspecified error
    GSF_ERR_NOT_SUPPORT                =-2,    //!< function not supported
    GSF_ERR_NOT_READY                  =-3,    //!< service not ready yet
    GSF_ERR_NOT_AVAILABLE              =-4,    //!< service not available
    GSF_ERR_NOT_ACCESSABLE             =-5,    //!< target not acceesable
    GSF_ERR_NOT_ENOUGH_RESOURCES       =-6,    //!< no enough resources
    GSF_ERR_FAIL                       =-7,    //!< failed
    GSF_ERR_INVALID_PARAMETER          =-8,    //!< invalid parameter
    GSF_ERR_INVALID_RANGE              =-9,    //!< invalid range
    GSF_ERR_INVALID_PTR                =-10,   //!< invalid pointer
    GSF_ERR_INVALID_KEY                =-11,   //!< invalid key
    GSF_ERR_IO                         =-12,   //!< IO error
    GSF_ERR_REQ_ALREADY_REGISTERED     =-13,   //!< request all ready exist
    GSF_ERR_UNKNOWN                    =-128,  //!< unknown error
} gsf_err_t;
//! @}

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/





#endif