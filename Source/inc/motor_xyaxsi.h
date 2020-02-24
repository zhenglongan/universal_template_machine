#ifndef MOTOR_XYAXSI_H
#define MOTOR_XYAXSI_H

//------------------------------------------------------------------------------------
//#define   DEBUG_GO_ORIGIN_SYNC_XY     //������ʱ�������ر�XYͬ����ԭ�㹦��

//#define   DEBUG_GO_ORIGIN_X           //������ʱ�������ر�X��ԭ�㹦��
//#define   DEBUG_GO_ORIGIN_Y           //������ʱ�������ر�X��ԭ�㹦��

//#define   DEBUG_MOVE_X_AXSI           //������ʱ�������ر�X������
//#define   DEBUG_MOVE_Y_AXSI           //������ʱ�������ر�Y������

//------------------------------------------------------------------------------------
extern INT32 motor_x_axsi_pos;      //x�����ǰλ��
extern INT32 motor_y_axsi_pos;      //y�����ǰλ��

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
