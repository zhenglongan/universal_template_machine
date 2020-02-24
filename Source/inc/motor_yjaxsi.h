#ifndef MOTOR_YJAXSI_H
#define MOTOR_YJAXSI_H

//------------------------------------------------------------------------------------
//#define   DEBUG_GO_ORIGIN_YJ      //调试用时开启，关闭YJ找原点功能
//#define   DEBUG_MOVE_YJ_AXSI      //调试用时开启，关闭YJ移动功能


//------------------------------------------------------------------------------------
UINT8 get_motor_yj_org_statu( void );

void movestep_yj( INT16 steps, UINT16 time );
void quickmove_yj( UINT16 time, INT32 steps );
void go_origin_yj( void );











//------------------------------------------------------------------------------------
#endif