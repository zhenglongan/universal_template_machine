//--------------------------------------------------------------------------------------
//  Includes
//--------------------------------------------------------------------------------------
#include "..\inc\includes.h"    // all files includes


//--------------------------------------------------------------------------------------
UINT8 barcode_config( void )
{
    u1mr = 0x00;
    u1mr = 0x05;
    u1c0 = 0x10;
    u1c1 = 0x04;
    ucon &= ~0x00;
    u1brg = BAUD_RATE_CONFIG( 9600 );
    re_u1c1 = 1;
    s1tic = 0;//关闭发送中断 UART1_TRANSMIT_IPL;
    s1ric = UART1_RECEIVE_IPL;//关闭接收中断 UART1_RECEIVE_IPL;
    init_uart1_val();
    return DEF_OK;
}
//--------------------------------------------------------------------------------------
UINT8 barcode_scan( void )
{
    //情况1：“DH”+“123”+ 0x0D+ 0x0A
    //情况2：“97”+“123”+ 0x0D+ 0x0A
    if( ( rec1_buf[rec1_ind_w - 1] == 0x0A ) && ( rec1_buf[rec1_ind_w - 2] == 0x0D ) )
    {
        if( ( ( rec1_buf[rec1_ind_w - 7] == 'D' ) && ( rec1_buf[rec1_ind_w - 6] == 'H' ) )
                || ( ( rec1_buf[rec1_ind_w - 7] == '9' ) && ( rec1_buf[rec1_ind_w - 6] == '7' ) ) )
        {
            serail_number = ( rec1_buf[rec1_ind_w - 5] - 0x30 ) * 100 + ( rec1_buf[rec1_ind_w - 4] - 0x30 ) * 10 + ( rec1_buf[rec1_ind_w - 3] - 0x30 );
            while( serail_number > 999 )
            {
                serail_number -= 999;
            }
        }
        //buzzer_control_time = 2000;//条码识别到花样
        rec1_ind_w = 0;
        rec1_ind_r = 0;
        rec1_buf[0] = 0;
        return DEF_OK;
    }
    return DEF_FAIL;
}
//--------------------------------------------------------------------------------------