#ifndef MOTOR_XYAXSI_H
#define MOTOR_XYAXSI_H

//------------------------------------------------------------------------------------
//#define   DEBUG_GO_ORIGIN_SYNC_XY     //调试用时开启，关闭XY同步找原点功能

//#define   DEBUG_GO_ORIGIN_X           //调试用时开启，关闭X找原点功能
//#define   DEBUG_GO_ORIGIN_Y           //调试用时开启，关闭X找原点功能

//#define   DEBUG_MOVE_X_AXSI           //调试用时开启，关闭X动框功能
//#define   DEBUG_MOVE_Y_AXSI           //调试用时开启，关闭Y动框功能

//------------------------------------------------------------------------------------
extern INT32 motor_x_axsi_pos;      //x电机当前位置
extern INT32 motor_y_axsi_pos;      //y电机当前位置

//------------------------------------------------------------------------------------
UINT8 get_motor_x_org_statu( void );
UINT8 get_motor_y_org_statu( void );

void movestep_x( INT16 steps, UINT16 time );
void movestep_y( INT16 steps, UINT16 time );

void quickmove_x( UINT16 time, INT32 steps );
void quickmove_y( UINT16 time, INT32 steps );

void go_origin_x( void );
void go_origin_y( void );
void go_origin_xy_both( void );

UINT8 check_y_action_done( void );
UINT8 check_y_action_done( void );
UINT8 check_xy_action_done( void );

void nop_move_emergency( UINT16 x, UINT16 y );
UINT8 nop_move_emergency_wait_done( UINT16 time );
UINT8 nop_move_emergency_process( INT16 tempx_step, INT16 tempy_step );

UINT16 get_x_distance( void );
UINT16 get_y_distance( void );
//------------------------------------------------------------------------------------
#endif
