//--------------------------------------------------------------------------------------
//  Includes
//--------------------------------------------------------------------------------------

#include "..\inc\includes.h"    // all files includes



//--------------------------------------------------------------------------------------
UINT16 tra1_ind_r;      // transmit  buffer reading index
UINT16 tra1_ind_w;      // transmit  buffer writing index
UINT16 rec1_ind_r;      // receive  buffer reading index
UINT16 rec1_ind_w;      // receive  buffer writing index

UINT8 rec1_buf[REC1_BUF_SIZE];  // receive  buffer
UINT8 tra1_buf[TRA1_BUF_SIZE];  // transmit  buffer

//--------------------------------------------------------------------------------------
#pragma INTERRUPT/E uart1_tra_int
void uart1_tra_int( void );

#pragma INTERRUPT/E uart1_rec_int
void uart1_rec_int( void );

//--------------------------------------------------------------------------------------
void init_uart1_val( void )
{
    UINT16 i;
    tra1_ind_r = 0;
    tra1_ind_w = 0;
    rec1_ind_r = 0;
    rec1_ind_w = 0;
    for( i = 0; i < sizeof( tra1_buf ); i++ )
    {
        tra1_buf[i] = 0;
    }
    for( i = 0; i < sizeof( rec1_buf ); i++ )
    {
        rec1_buf[i] = 0;
    }
}
//--------------------------------------------------------------------------------------
//����1�����ж�
void uart1_tra_int( void )
{
    if( formwork_identify_device == 1 )
    {
        if( tra1_ind_r != tra1_ind_w )
        {
            u1tb = tra1_buf[tra1_ind_r++];
        }
        else
        {
            te_u1c1 = 0;
        }
    }
    else if( formwork_identify_device == 2 )
    {
    }
}
//--------------------------------------------------------------------------------------
//����1�����ж�
void uart1_rec_int( void )
{
    if( formwork_identify_device == 1 )
    {
        if( rec1_ind_w >= sizeof( rec1_buf ) )
        {
            rec1_ind_w = 0;
        }
        rec1_buf[rec1_ind_w++] = ( UINT8 )u1rb;
    }
}
//--------------------------------------------------------------------------------------
void rec1_com( void )
{
    switch( formwork_identify_device )
    {
        //--------------------------------------------------------------------------------------
        case 1://����ģ�鴦������
            if( barcode_config_flag == 0 )
            {
                if( barcode_config() == DEF_OK ) //�����ʼ��
                {
                    barcode_config_flag = 1;
                }
            }
            //����ģ�鴦��
            if( identify_scan_counter > 2 )
            {
                barcode_scan();
                identify_scan_counter = 0;
            }
            break;
        //--------------------------------------------------------------------------------------
        case 2://RFIDģ�鴦�� ---- ��
            if( rfid_config_flag == 0 )
            {
                if( rfid_config() == DEF_OK ) //RFID��ʼ��
                {
                    rfid_config_flag = 1;
                }
            }
            if( identify_scan_counter > 100 )
            {
                rfid_scan();
                identify_scan_counter = 0;
            }
            break;
        //--------------------------------------------------------------------------------------
        case 3://RFIDģ�鴦�� ---- ˫
            break;
        //--------------------------------------------------------------------------------------
        default://��������
            break;
            //--------------------------------------------------------------------------------------
    }
    if( ( formwork_identify_device == 0 ) || ( auto_function_flag == 0 ) )
    {
        serail_number = 0;
        //last_pattern_number = 0;
    }
    if( ( formwork_identify_device != 0 ) && ( auto_function_flag == 1 ) && ( return_from_setout == 1 ) )
    {
        pattern_process();
    }
}

//--------------------------------------------------------------------------------------
UINT8 uart1_send_char( UINT8* pData )
{
    ri_u1c1 = 0;//������ձ�ʶ
    ti_u1c1 = 0;//������ͱ�־
    u1tb = *pData;
    te_u1c1 = 1;
    while( !ti_u1c1 )
    {
        //rec_com();//�˴������������rfidͨ�Ŵ��� 2019.12.21
    }
    ti_u1c1 = 0;
    return DEF_TRUE;
}
//--------------------------------------------------------------------------------------
UINT8 uart1_get_char( UINT8* pData )
{
    UINT8 ret;
    UINT32 time_start;
    ret = DEF_TRUE;
    time_start = g_system_ticks;
    while( ri_u1c1 == 0 )
    {
        if( ( g_system_ticks - time_start ) >= 10 )
        {
            ret = DEF_FALSE;
            break;
        }
        rec_com();
    }
    ri_u1c1 = 0;
    *pData = ( UINT8 )u1rb;
    return ret;
}
//--------------------------------------------------------------------------------------
void uart1_set_baudrate( UINT16 baudrate )
{
    u1mr = 0x00;
    u1mr = 0x05;
    u1c0 = 0x10;
    u1c1 = 0x04;
    ucon &= ~0x00;
    u1brg = baudrate;
    s1tic = 0;//�رշ����ж� UART1_TRANSMIT_IPL;
    s1ric = 0;//�رս����ж� UART1_RECEIVE_IPL;
    re_u1c1 = 1;
}
//--------------------------------------------------------------------------------------
