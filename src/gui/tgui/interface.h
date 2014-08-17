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

#ifndef __TGUI_INTERFACE_H__
#define __TGUI_INTERFACE_H__

/*============================ INCLUDES ======================================*/
#include ".\app_cfg.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
#if  TGUI_SIZE_INT_TYPE == TGUI_TINY
typedef int_fast8_t     tgui_int_t;
#elif   TGUI_SIZE_INT_TYPE == TGUI_MEDIUM
typedef int_fast16_t    tgui_int_t;
#else
typedef int_fast32_t    tgui_int_t;
#endif

//! \name point
//! @{
typedef struct {
    union {
        tgui_int_t  tX;
        tgui_int_t  tLeft;
    };
    union {
        tgui_int_t  tY;
        tgui_int_t  tTop;
    };
} point_t;
//! @}

//! \name rectangle
//! @{
typedef struct {
    union {
        point_t;
        point_t __point_t;
    };
    tgui_int_t  tWidth;             //!< Width in pix
    tgui_int_t  tHeight;            //!< Height in pix
} rect_t;
//! @}

#if     TGUI_COLOR_BITS == TGUI_24BITS
typedef union {
    uint32_t    tValue;
    struct {
        uint8_t chR;
        uint8_t chG;
        uint8_t ghB;
    };
} color_t;
#elif   TGUI_COLOR_BITS == TGUI_8BITS
typedef union {
    uint8_t     tValue;         
} color_t;
#else   /*TGUI_COLOR_BITS == TGUI_4BITS*/
typedef union {
    uint8_t     tValue;
} color_t;
#endif

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/


#endif
/* EOF */