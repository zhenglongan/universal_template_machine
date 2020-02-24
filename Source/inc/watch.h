//--------------------------------------------------------------------------------------
//         COPYRIGHT(C) 2006 Beijing xingdahao technology Co., Ltd.
//                     ALL RIGHTS RESERVED
//  Project Number: sewing_machine_controller
//  File Name : watch.h
//  Description: common constants definition
//  Version    Date     Author    Description
//  0.01     03/07/07   pbb        created
//  ...
//  ...
//  ...
//--------------------------------------------------------------------------------------

#ifndef WATCH_H
#define WATCH_H

extern INT16 uzk_val;     // vol of UZK
extern INT16 u24_val;     // vol of U24

extern void init_watch( void );
extern UINT8 sys_init_watch( void );
extern UINT8 sys_watch_ticks( void );
extern UINT8 sys_power_check( void );

#endif
//--------------------------------------------------------------------------------------
