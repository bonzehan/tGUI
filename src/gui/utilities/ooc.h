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

#ifndef __OBJECT_ORIENTED_C_H__
#define __OBJECT_ORIENTED_C_H__

/*============================ INCLUDES ======================================*/
/*============================ MACROS ========================================*/
#define EVENT_RT_UNREGISTER         4

/*============================ MACROFIED FUNCTIONS ===========================*/

#define CLASS(__NAME)               __##__NAME

//! \brief macro for initializing an event
#define INIT_DELEGATE(__NAME/*,__ASYN*/)           delegate_init(&(__NAME)/*, (__ASYN)*/)


#define DEF_CLASS(__NAME,...)\
    typedef union __NAME __NAME;\
    __VA_ARGS__\
    typedef struct __##__NAME __##__NAME;\
    struct __##__NAME {

#define END_DEF_CLASS(__NAME) \
    };\
    union __NAME {\
        uint_fast8_t chMask[(sizeof(__##__NAME) + sizeof(uint_fast8_t) - 1) / sizeof(uint_fast8_t)];\
    };
    

#define DEF_CLASS_IMPLEMENT(__NAME,__INTERFACE,...)\
    typedef union __NAME __NAME;\
    __VA_ARGS__\
    typedef struct __##__NAME __##__NAME;\
    struct __##__NAME {\
        const __INTERFACE method;

#define END_DEF_CLASS_IMPLEMENT(__NAME,__INTERFACE)\
    };\
    union __NAME {\
        const __INTERFACE method;\
        uint_fast8_t chMask[(sizeof(__##__NAME) + sizeof(uint_fast8_t) - 1) / sizeof(uint_fast8_t)];\
    };


#define EXTERN_CLASS(__NAME,...) \
    typedef union __NAME __NAME;\
    __VA_ARGS__\
    union __NAME {\
        uint_fast8_t chMask[(sizeof(struct {

#define END_EXTERN_CLASS(__NAME) \
        }) + sizeof(uint_fast8_t) - 1) / sizeof(uint_fast8_t)];\
    };

#define EXTERN_CLASS_IMPLEMENT(__NAME,__INTERFACE,...) \
    typedef union __NAME __NAME;\
    __VA_ARGS__\
    union __NAME {\
        const __INTERFACE method;\
        uint_fast8_t chMask[(sizeof(struct {\
            const __INTERFACE method;

#define END_EXTERN_CLASS_IMPLEMENT(__NAME, __INTERFACE) \
        }) + sizeof(uint_fast8_t) - 1) / sizeof(uint_fast8_t)];\
    };

//! \name interface definition
//! @{
#define DEF_INTERFACE(__NAME,...)   \
            typedef struct __NAME __NAME;\
            __VA_ARGS__\
            struct __NAME {

#define END_DEF_INTERFACE(__NAME)   \
            };
//! @}


//! \brief macro for inheritance

#define INHERIT_EX(__TYPE, __NAME)  \
            union {                 \
                __TYPE;             \
                __TYPE  __NAME;     \
            };
#define INHERIT(__TYPE)             INHERIT_EX(__TYPE, base);

#define IMPLEMENT(__INTERFACE)      INHERIT_EX(__INTERFACE, __##__INTERFACE)

#define OBJ_CONVERT_AS(__OBJ, __INTERFACE)  (__OBJ.__##__INTERFACE)
            

/*============================ TYPES =========================================*/



//! \name general event handler
//! @{
EXTERN_CLASS( DELEGATE_HANDLE,
        typedef fsm_rt_t DELEGATE_HANDLE_FUNC(void *pArg, void *pParam);
    )
    DELEGATE_HANDLE_FUNC   *fnHandler;      //!< event handler
    void                   *pArg;           //!< Argument
    DELEGATE_HANDLE        *ptNext;         //!< next 
END_EXTERN_CLASS(DELEGATE_HANDLE)
//! @}

//! \name event
//! @{
EXTERN_CLASS(DELEGATE)
    DELEGATE_HANDLE     *ptEvent;
    DELEGATE_HANDLE     *ptBlockedList;
    DELEGATE_HANDLE     **pptHandler;
END_EXTERN_CLASS(DELEGATE)
//! @}

//! \name interface: u32_property_t
//! @{
DEF_INTERFACE(u32_property_t)
    bool (*Set)(uint32_t wValue);
    uint32_t (*Get)(void);
END_DEF_INTERFACE(u32_property_t)
//! @}

//! \name interface: u16_property_t
//! @{
DEF_INTERFACE(u16_property_t)
    bool (*Set)(uint_fast16_t wValue);
    uint_fast16_t (*Get)(void);
END_DEF_INTERFACE(u16_property_t)
//! @}

//! \name interface: u8_property_t
//! @{
DEF_INTERFACE(u8_property_t)
    bool (*Set)(uint_fast8_t wValue);
    uint_fast8_t (*Get)(void);
END_DEF_INTERFACE(u8_property_t)
//! @}


//! \name interface: i32_property_t
//! @{
DEF_INTERFACE(i32_property_t)
    bool (*Set)(int32_t wValue);
    int32_t (*Get)(void);
END_DEF_INTERFACE(i32_property_t)
//! @}

//! \name interface: i16_property_t
//! @{
DEF_INTERFACE(i16_property_t)
    bool (*Set)(int_fast16_t wValue);
    int_fast16_t (*Get)(void);
END_DEF_INTERFACE(i16_property_t)
//! @}

//! \name interface: u8_property_t
//! @{
DEF_INTERFACE(i8_property_t)
    bool (*Set)(int_fast8_t wValue);
    int_fast8_t (*Get)(void);
END_DEF_INTERFACE(i8_property_t)
//! @}

//! \name interface: bool_property_t
//! @{
DEF_INTERFACE(bool_property_t)
    bool (*Set)(bool bValue);
    bool (*Get)(void);
END_DEF_INTERFACE(bool_property_t)
//! @}

//! \name interface: bool_property_t
//! @{
DEF_INTERFACE(en_property_t)
    bool (*Enable)(void);
    bool (*Disable)(void);
END_DEF_INTERFACE(en_property_t)
//! @}


/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

/*! \brief initialize event 
 *! \param ptEvent target event
 *! \return the address of event item
 */
extern DELEGATE *delegate_init(DELEGATE *ptEvent);

/*! \brief initialize event handler item
 *! \param ptHandler the target event handler item
 *! \param fnRoutine event handler routine
 *! \param pArg handler extra arguments
 *! \return the address of event handler item
 */
extern DELEGATE_HANDLE *delegate_handler_init(
    DELEGATE_HANDLE *ptHandler, DELEGATE_HANDLE_FUNC *fnRoutine, void *pArg);

/*! \brief register event handler to specified event
 *! \param ptEvent target event
 *! \param ptHandler target event handler
 *! \return access result
 */
extern gsf_err_t register_delegate_handler(DELEGATE *ptEvent, DELEGATE_HANDLE *ptHandler);

/*! \brief unregister a specified event handler
 *! \param ptEvent target event
 *! \param ptHandler target event handler
 *! \return access result
 */
extern gsf_err_t unregister_delegate_handler( DELEGATE *ptEvent, DELEGATE_HANDLE *ptHandler);

/*! \brief raise target event
 *! \param ptEvent the target event
 *! \param pArg event argument
 *! \return access result
 */
extern fsm_rt_t invoke_delegate( DELEGATE *ptEvent, void *pParam);
#endif
/* EOF */