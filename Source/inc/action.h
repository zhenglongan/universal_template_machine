#ifndef ACTION_H
#define ACTION_H

//--------------------------------------------------------------------------------------
INT16 ChangeX( PATTERN_DATA* pp );
INT16 ChangeY( PATTERN_DATA* pp );

void go_origin_allmotor( void );
void go_origin_xy( void );
void foot_up( void );
void foot_down( void );
void foot_half_up( void );
void foot_half_down( void );
void footer_both_up( void );
void footer_both_down( void );
void footer_procedure( void );
void inpress_up( void );
void inpress_down( INT16 pos );
void find_dead_center( void );
void find_dead_point( void );
void find_stop_point( INT16 stop_angle );
void keep_running_for_dead_center( void );
void needle_down( void );
void go_startpoint( void );
void check_data( UINT8 control_flag );
void calculate_angle( void );
void process_data( void );
void process_edit_data( void );
UINT32 calculate_quickmove_time( UINT16 temp16_x, UINT16 temp16_y );
#if NOPMOVE_JUMP_ENABLE
void back_endpoint( void );
#endif
void go_beginpoint( void );
void conprocess_data( void );
void conprocess_edit_data( void );
void single_next( void );
void single_edit_continue_next( void );
void single_back( void );
void single_edit_continue_back( void );
void back_startpoint( void );
void single_end( void );
void single_start( void );
void single_stop( void );
void move_next( void );
void move_continue_next( void );
void move_back( void );
void move_continue_back( void );
void move_startpoint( void );
void move_edit_startpoint( void );
//void course_next(void);
void course_back( void );

void shift_12( void );
void shift_01( void );
void shift_02( void );
void shift_03( void );
void shift_04( void );
void shift_06( void );
void shift_07( void );
void shift_09( void );
void shift_10( void );

void remove_12( void );
void remove_01( void );
void remove_03( void );
void remove_04( void );
void remove_06( void );
void remove_07( void );
void remove_09( void );
void remove_10( void );

void remove_stop( void );
void go_setoutpoint( void );

void turn_off_led( void );
void turn_off_buz( void );
void turn_on_led( void );
void turn_on_buz( void );

void flash_led( void );
void flash_buz( void );
void led_clour_control( UINT8 clour );

void emergency( void );
void para_confirm( void );
void sewing_stop( void );
void pause_stop( void );
UINT8 detect_position( void );
void reset_panel( void );
void init_mainmotor( void );
void go_absoluteposition( INT16 target_x, INT16 target_y );
void go_commandpoint( INT16 commandpointcoorx, INT16 commandpointcoory );
void move_xy( void );

void zpl_process( void );

void inpress_to( INT16 obj_position );
void inpress_to_forsingle( INT16 obj_position );

void do_pat_point_add_one( void );
void do_pat_point_sub_one( void );

void coor_com_fun( void );
UINT8 scan_pause_func( UINT8* pause_flag_tmp, UINT8 system_staus_tmp );
void special_sewing( UINT8 dir, UINT8 cnt );
void zoom_in_one_stitch( void );
void head_sewing( void );
void tail_sewing( void );
UINT8 check_footer_status( void );


#if BOBBIN_THREAD_DETECT
UINT8 detect_bottom_thread_status( void );
#endif

#if BOBBIN_CHANGER_ENABLE
void bobbin_change_process( void );
#endif

void process_making_pen_signal( UINT8 flag ); //0：前进 1：后退

void find_start_point_x( void );

void disable_24V_output( void );
void enable_24V_output( void );

void disable_33V_output( void );
void enable_33V_output( void );

void laser_add_one_action( UINT8 coder );

void PBP_Line( INT16 target_x, INT16 target_y );

void turn_on_laser( void );
void turn_off_laser( void );

void pump_wait( void );
void pump_open( void );
void pump_close( void );

void tension_mechanical_control( UINT8 val );
void tension_electronic_control( UINT8 val );
void tension_nop_move_control( UINT16 time );
//--------------------------------------------------------------------------------------
UINT8 check_x_over_range( INT16 x );
UINT8 check_y_over_range( INT16 y );
UINT8 check_xy_over_range( INT16 x, INT16 y );

UINT8 action_pause_add_one( void );

void trim_io_control( UINT8 action );
void trim_action( void );
void trim_pause( void );


//--------------------------------------------------------------------------------------
extern const UINT8  DEF_MoveTime_Speed_X_Positive[33];  //X+动框时间
extern const UINT16 DEF_MoveStartAngle_X_Positive[33];  //X+动框角度

extern const UINT8  DEF_MoveTime_Speed_X_Negative[33];  //X-动框时间
extern const UINT16 DEF_MoveStartAngle_X_Negative[33];  //X-动框角度

extern const UINT8  DEF_MoveTime_Speed_Y_Positive[33];  //Y+动框时间
extern const UINT16 DEF_MoveStartAngle_Y_Positive[33];  //Y+动框角度

extern const UINT8  DEF_MoveTime_Speed_Y_Negative[33];  //Y-动框时间
extern const UINT16 DEF_MoveStartAngle_Y_Negative[33];  //Y-动框角度
//--------------------------------------------------------------------------------------
extern UINT8  MoveTime_Speed_X_Positive[33];    //X+动框时间
extern UINT16 MoveStartAngle_X_Positive[33];    //X+动框角度

extern UINT8  MoveTime_Speed_X_Negative[33];    //X-动框时间
extern UINT16 MoveStartAngle_X_Negative[33];    //X-动框角度

extern UINT8  MoveTime_Speed_Y_Positive[33];    //Y+动框时间
extern UINT16 MoveStartAngle_Y_Positive[33];    //Y+动框角度

extern UINT8  MoveTime_Speed_Y_Negative[33];    //Y-动框时间
extern UINT16 MoveStartAngle_Y_Negative[33];    //Y-动框角度
//--------------------------------------------------------------------------------------
extern UINT8*  pMoveTime_Speed_X_Positive;  //X+动框时间
extern UINT16* pMoveStartAngle_X_Positive;  //X+动框角度

extern UINT8*  pMoveTime_Speed_X_Negative;  //X-动框时间
extern UINT16* pMoveStartAngle_X_Negative;  //X-动框角度

extern UINT8*  pMoveTime_Speed_Y_Positive;  //Y+动框时间
extern UINT16* pMoveStartAngle_Y_Positive;  //Y+动框角度

extern UINT8*  pMoveTime_Speed_Y_Negative;  //Y-动框时间
extern UINT16* pMoveStartAngle_Y_Negative;  //Y-动框角度
//--------------------------------------------------------------------------------------


#endif
//--------------------------------------------------------------------------------------
