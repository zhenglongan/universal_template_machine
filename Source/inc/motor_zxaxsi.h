#ifndef MOTOR_ZXAXSI_H
#define MOTOR_ZXAXSI_H

//------------------------------------------------------------------------------------
//#define   DEBUG_GO_ORIGIN_ZX      //调试用时开启，关闭ZX找原点功能
//#define   DEBUG_MOVE_ZX_AXSI      //调试用时开启，关闭ZX移动功能


//------------------------------------------------------------------------------------
UINT8 get_motor_zx_org_statu( void );

void movestep_zx( INT16 steps, UINT16 time );
void quickmove_zx( UINT16 time, INT32 steps );
void go_origin_zx( void );












//------------------------------------------------------------------------------------
#endif