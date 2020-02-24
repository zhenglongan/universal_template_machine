//--------------------------------------------------------------------------------------
//  Includes
//--------------------------------------------------------------------------------------
#include "..\inc\includes.h"    // all files includes

//--------------------------------------------------------------------------------------
//剪线电机 功能函数
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
UINT8 get_motor_yj_org_statu( void )
{
    UINT16 command;
    command = send_dspn_command( DSP_NUM_2, 0x0029 );
    command = send_dspn_command( DSP_NUM_2, 0x2000 );
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
//  Name:        movestep_yj
//  Parameters:  None
//  Returns:     None
//  Description: move yj step motor (剪线电机)
//--------------------------------------------------------------------------------------
#ifndef DEBUG_MOVE_YJ_AXSI
void movestep_yj( INT16 steps, UINT16 time )
{
    UINT16 command;
    if( steps > 0 )
    {
        if( para.yj_org_direction == 0 )
        {
            command = ( UINT16 )0x4000 + ( ( UINT16 )steps << 6 ) + ( UINT16 )time;
        }
        else
        {
            command = ( UINT16 )0x0000 + ( ( UINT16 )steps << 6 ) + ( UINT16 )time;
        }
    }
    else
    {
        steps = -steps;
        if( para.yj_org_direction == 0 )
        {
            command = ( UINT16 )0x0000 + ( ( UINT16 )steps << 6 ) + ( UINT16 )time;
        }
        else
        {
            command = ( UINT16 )0x4000 + ( ( UINT16 )steps << 6 ) + ( UINT16 )time;
        }
    }
    if( command == 0x5555 )
    {
        command++;
    }
    command_direct_to_dspn( DSP_NUM_2, command );
}
//--------------------------------------------------------------------------------------
void quickmove_yj( UINT16 time, INT32 tempz_step )
{
    UINT16 low16, hig16;
    UINT32 tmp32;
    send_dspn_command( DSP_NUM_2, 0x0000 );
    delay_us( 500 );
    if( tempz_step > 0 )
    {
        tmp32 = tempz_step;
        low16  = tmp32 & 0xffff;
        if( para.yj_org_direction == 0 )
        {
            hig16 = ( UINT16 )0x4000 + ( ( tmp32 >> 16 ) & 0xff );
        }
        else
        {
            hig16 = ( UINT16 )0x0000 + ( ( tmp32 >> 16 ) & 0xff );
        }
    }
    else
    {
        tmp32 = - tempz_step;
        low16  = tmp32 & 0xffff;
        if( para.yj_org_direction == 0 )
        {
            hig16 = ( UINT16 )0x0000 + ( ( tmp32 >> 16 ) & 0xff );
        }
        else
        {
            hig16 = ( UINT16 )0x4000 + ( ( tmp32 >> 16 ) & 0xff );
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
void movestep_yj( INT16 steps, UINT16 time )
{
}
void quickmove_yj( UINT16 time, INT32 tempz_step )
{
}
#endif
//--------------------------------------------------------------------------------------
//  Name:       go_origin_yj
//  Parameters: None
//  Returns:    None
//  Description: presser motor go origin
//--------------------------------------------------------------------------------------
#ifndef DEBUG_GO_ORIGIN_YJ
void go_origin_yj( void )
{
    UINT8 i;
    UINT16 temp16, j = 0;
    if( get_motor_yj_org_statu() != DEF_LOW )         // sensor is not covered
    {
        temp16 = 0;
        while( get_motor_yj_org_statu() != DEF_LOW )
        {
            delay_us( 1000 );
            movestep_yj( -1, 1 );
            if( j < 2 )
            {
                delay_ms( 2 );    //
            }
            else if( j < 4 )
            {
                delay_us( 1000 );
            }
            else
            {
                delay_us( 500 );    //1500
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
                sys.error = ERROR_85;
                return;
            }
            rec_com();
        }
    }
    else                    // sensor is covered
    {
        temp16 = 0;
        j = 0;
        while( get_motor_yj_org_statu() == DEF_LOW )  //0--对应Z高电平
        {
            delay_us( 1000 );
            movestep_yj( 1, 1 );
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
                sys.error = ERROR_85;
                return;
            }
            rec_com();
        }
        for( i = 2; i > 0; i-- )         // continue running
        {
            movestep_yj( 1, 1 );
            delay_ms( 2 );
        }
        delay_ms( 2 );
        temp16 = 0;
        j = 0;
        while( get_motor_yj_org_statu() == DEF_LOW ) //等低电平到高电平
        {
            delay_us( 1000 );
            movestep_yj( -1, 1 );
            delay_ms( 3 );
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
                sys.error = ERROR_85;
                return;
            }
            rec_com();
        }
    }
}
#else
void go_origin_yj( void )
{
}
#endif
//--------------------------------------------------------------------------------------