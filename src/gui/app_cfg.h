/***************************************************************************
 *   Copyright(C)2009-2014 by Gorgon Meducer<Embedded_zhuoran@hotmail.com> *
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

//! \note do not move this pre-processor statement to other places
#include "..\app_cfg.h"

#ifndef __GUI_APP_CFG_H__
#define __GUI_APP_CFG_H__

/*============================ INCLUDES ======================================*/
//! \brief import head files
#include ".\utilities\compiler.h"
#include ".\utilities\usebits.h"
#include ".\utilities\tiny_fsm.h"
#include ".\utilities\communicate.h"
#include ".\utilities\template\template.h"

/*============================ MACROS ========================================*/

//! define enable macro
#ifdef ENABLED
#   undef ENABLE
#endif
#define ENABLED                     1

//! define disabled macro
#ifdef DISABLED
#   undef DISABLED
#endif
#define DISABLED                    0

//! \brief enable gui service
#define USE_SERVICE_GUI_TGUI    ENABLED

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
 

#endif
/* EOF */
