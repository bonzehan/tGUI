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


#ifndef __USE_ARM_M4_COMPILER_H__
#define __USE_ARM_M4_COMPILER_H__


/*----------------------------------------------------------------------------*
 * Device IO Definition                                                       *
 *----------------------------------------------------------------------------*/

/* 
 * Include the cpu specific header file 
 */
/*============================ Freescale =====================================*/

/*----------------------------------------------------------------------------*
 * Architecture Definition                                                    *
 *----------------------------------------------------------------------------*/
//! \brief The mcu memory endian mode
# define __BIG_ENDIAN__                 false

/*ARM Cortex M4 implementation for interrupt priority shift*/
# define ARM_INTERRUPT_LEVEL_BITS       4


#endif

