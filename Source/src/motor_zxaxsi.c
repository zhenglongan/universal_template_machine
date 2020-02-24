//--------------------------------------------------------------------------------------
//  Includes
//--------------------------------------------------------------------------------------
#include "..\inc\includes.h"    // all files includes

//--------------------------------------------------------------------------------------
//中压脚电机 功能函数
//--------------------------------------------------------------------------------------
//IORG
//--------------------------------------------------------------------------------------
UINT8 get_motor_zx_org_statu( void )
{
    UINT16 command;
    command = send_dspn_command( DSP_NUM_2, 0x0029 );
    command = send_dspn_command( DSP_NUM_2, 0xa000 );
    command = send_dspn_command( DSP_NUM_2, 0x5555 );
    if( command != 0 )
    {
        return DEF_HIG;
    }
    else
    {
        return DEF_LOW;
    }
}
//--------------------------------------------------------------------------------------
//  Name:        movestep_zx
//  Parameters:  None
//  Returns:     None
//  Description: move zx step motor (中压脚)
//--------------------------------------------------------------------------------------
#ifndef DEBUG_MOVE_ZX_AXSI
void movestep_zx( INT16 steps, UINT16 time )
{
    UINT16 command;
    if( steps == 0 )//if( ( sys.status == ERROR ) || ( steps == 0 ) )
    {
        return;
    }
    if( time > fabsm( steps ) * 20 )
    {
        time = fabsm( steps ) * 20;
    }
    if( time > 63 )
    {
        time = 63;
    }
    if( steps > 0 )
    {
        if( steps > 255 )
        {
            steps = 255;
        }
        if( zx_motor_dir == 0 )
        {
            command = ( UINT16 )0xc000 + ( ( UINT16 )steps << 6 ) + ( UINT16 )time;
        }
        else
        {
            command = ( UINT16 )0x8000 + ( ( UINT16 )steps << 6 ) + ( UINT16 )time;
        }
    }
    else
    {
        steps = -steps;
        if( steps > 255 )
        {
            steps = 255;
        }
        if( zx_motor_dir == 0 )
        {
            command = ( UINT16 )0x8000 + ( ( UINT16 )steps << 6 ) + ( UINT16 )time;
        }
        else
        {
            command = ( UINT16 )0xc000 + ( ( UINT16 )steps << 6 ) + ( UINT16 )time;
        }
    }
    if( command == 0x5555 )
    {
        command++;
    }
    command_direct_to_dspn( DSP_NUM_2, command );
}
//--------------------------------------------------------------------------------------
void quickmove_zx( UINT16 time, INT32 steps )
{
    UINT16 low16, hig16;
    UINT32 tmp32;
    send_dspn_command( DSP_NUM_2, 0x0000 );
    delay_us( 500 );
    if( steps > 0 )
    {
        tmp32 = steps;
        low16  = tmp32 & 0xffff;
        if( zx_motor_dir == 0 )
        {
            hig16 = ( UINT16 )0xc000 + ( ( tmp32 >> 16 ) & 0xff );
        }
        else
        {
            hig16 = ( UINT16 )0x8000 + ( ( tmp32 >> 16 ) & 0xff );
        }
    }
    else
    {
        tmp32 = - steps;
        low16  = tmp32 & 0xffff;
        if( zx_motor_dir == 0 )
        {
            hig16 = ( UINT16 )0x8000 + ( ( tmp32 >> 16 ) & 0xff );
        }
        else
        {
            hig16 = ( UINT16 )0xc000 + ( ( tmp32 >> 16 ) & 0xff );
        }
    }
    hig16 |= ( 1 << 13 ); //强制使用闭环横幅值
    send_dspn_command( DSP_NUM_2, hig16 );
    //delay_ms(1);
    if( low16 == 0x5555 )
    {
        low16++;
    }
    send_dspn_command( DSP_NUM_2, low16 );
    //delay_ms(1);
    if( time == 0x5555 )
    {
        time++;
    }
    send_dspn_command( DSP_NUM_2, time );
    //delay_ms(1);
}
#else
void movestep_zx( INT16 steps, UINT16 time )
{
}
void quickmove_zx( UINT16 time, INT32 steps )
{
}
#endif

//--------------------------------------------------------------------------------------
void inpress_step_control( UINT8 flag )
{
    if( inpress_type == AIR_INPRESSER )
    {
        return ;
    }
    if( flag == 1 )
    {
        //释放
        send_dspn_command( DSP_NUM_2, 0x0013 );
        send_dspn_command( DSP_NUM_2, 0x0002 );
        send_dspn_command( DSP_NUM_2, 0x0000 );
    }
    else
    {
        //锁轴
        send_dspn_command( DSP_NUM_2, 0x0013 );
        send_dspn_command( DSP_NUM_2, 0x0003 );
        send_dspn_command( DSP_NUM_2, 0x0000 );
    }
    delay_ms( 300 );
}
//--------------------------------------------------------------------------------------
//  Name:       go_origin_zx
//  Parameters: None
//  Returns:    None
//  Description: presser motor go origin
//--------------------------------------------------------------------------------------
#ifndef DEBUG_GO_ORIGIN_ZX
void go_origin_zx( void )
{
    UINT8 i;
    UINT16 temp16, j ;
    j = 0;
    if( inpress_type == AIR_INPRESSER )
    {
        inpress_up();
        return ;
    }
    if( get_motor_zx_org_statu() != DEF_LOW )         // sensor is not covered
    {
        temp16 = 0;
        if( sys.status == ERROR )
        {
            sys.status = ERROR;
            sys.StatusChangeLatch = ERROR;
            return;
        }
        while( get_motor_zx_org_statu() != DEF_LOW )
        {
            delay_us( 500 );
            movestep_zx( -1, 1 );
            if( j < 2 )
            {
                delay_ms( 2 );
            }
            else if( j < 4 )
            {
                delay_us( 1000 );
            }
            else
            {
                delay_us( 500 );
            }
            if( j < 4 )
            {
                j++;
            }
            temp16 = temp16 + 1;
            if( sys.status == ERROR )
            {
                sys.status = ERROR;
                sys.StatusChangeLatch = ERROR;
                return;
            }
            if( temp16 > 1600 )
            {
                sys.status = ERROR;
                sys.StatusChangeLatch = ERROR;
                sys.error = ERROR_29;
                return;
            }
            rec_com();
        }
    }
    else                    // sensor is covered
    {
        temp16 = 0;
        j = 0;
        if( sys.status == ERROR )
        {
            sys.status = ERROR;
            sys.StatusChangeLatch = ERROR;
            return;
        }
        while( get_motor_zx_org_statu() == DEF_LOW )
        {
            delay_us( 500 );
            movestep_zx( 1, 1 );
            if( j < 2 )
            {
                delay_ms( 2 );
            }
            else if( j < 4 )
            {
                delay_us( 1000 );
            }
            else
            {
                delay_us( 500 );
            }
            if( j < 4 )
            {
                j++;
            }
            temp16 = temp16 + 1;
            if( sys.status == ERROR )
            {
                sys.status = ERROR;
                sys.StatusChangeLatch = ERROR;
                return;
            }
            if( temp16 > 1600 )
            {
                sys.status = ERROR;
                sys.StatusChangeLatch = ERROR;
                sys.error = ERROR_29;
                return;
            }
            rec_com();
        }
        for( i = 2; i > 0; i-- )         // continue running
        {
            movestep_zx( 1, 1 );
            delay_ms( 2 );
        }
        delay_ms( 1 );
        temp16 = 0;
        j = 0;
        while( get_motor_zx_org_statu() != DEF_LOW )
        {
            delay_us( 500 );
            movestep_zx( -1, 1 );
            delay_us( 500 );
            delay_ms( 1 );
            temp16 = temp16 + 1;
            if( sys.status == ERROR )
            {
                sys.status = ERROR;
                sys.StatusChangeLatch = ERROR;
                return;
            }
            if( temp16 > 1600 )
            {
                sys.status = ERROR;
                sys.StatusChangeLatch = ERROR;
                sys.error = ERROR_29;
                return;
            }
            rec_com();
        }
    }
#if INPRESS_CHECK_MODER
    for( i = 0; i < 5; i++ ) // running ensure IORG = 1
    {
        movestep_zx( 1, 1 );
        delay_ms( 2 );
    }
#else
    for( i = 0; i < 3; i++ ) // running ensure IORG = 1
    {
        movestep_zx( -1, 1 );
        delay_ms( 4 );
    }
#endif
    inpress_flag = 1;
    inpress_position = inpress_origin;
    steper_footer_position = 0;
    inpress_first_flag = 0;
    inpress_follow_high_flag = FOLLOW_INPRESS_LOW;
    delay_ms( 10 );
    app_GpioYSetVal( R_AIR, DEF_LOW ); //R_AIR = 0;//辅助压脚 抬起
}
#else
void go_origin_zx( void )
{
    inpress_flag = 1;
    //inpress_com = 0;
    inpress_position = inpress_origin;
    steper_footer_position = 0;
    inpress_first_flag = 0;
    inpress_follow_high_flag = FOLLOW_INPRESS_LOW;
    delay_ms( 10 );
    app_GpioYSetVal( R_AIR, DEF_LOW ); //R_AIR = 0;//辅助压脚 抬起
}
#endif
//--------------------------------------------------------------------------------------