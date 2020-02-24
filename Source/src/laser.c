//--------------------------------------------------------------------------------------
//  Includes
//--------------------------------------------------------------------------------------
#include "..\inc\includes.h"    // all files includes

//--------------------------------------------------------------------------------------
void laser_time_enable( UINT8 speed )
{
    UINT16 dly;
    dly = speed + speed * 8 / 5 + 2;
    dly = dly * 100 + 250;
    if( dly > 2730 )
    {
        dly = 2730;
    }
    dly = 24 * dly;
    tb5s = 0;                   // stop timer B5
    tb5mr = 0x00;
    tb5 = dly;                  //(SYS_FREQ/10000 - 1);// Set up Timer B4 Reload Register for 100 us interval interrupt
    tb5ic = TB5_IPL;            // set timer B5 interrupt priority
    tb5s = 1;                   // start timer B5
}
//--------------------------------------------------------------------------------------
void laser_time_disable( void )
{
    //delay_ms(16);
    tb5s = 0;                       // stop timer B5
    {
        laser_action_ind_w = 0;
        laser_action_ind_r = 0;
        laser_action_busy = 0;
        laser_cutter_aciton_flag = 0;
    }
}
//--------------------------------------------------------------------------------------
