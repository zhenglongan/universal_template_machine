//--------------------------------------------------------------------------------------
//  Includes
//--------------------------------------------------------------------------------------
#include "..\inc\includes.h"    // all files includes

//--------------------------------------------------------------------------------------
void app_SetDacVal( UINT8 ch, UINT8 val )
{
    switch( ch )
    {
        case DAC_CH_0:
            da0 = val;
            break;
        case DAC_CH_1:
            da1 = val;
            break;
        default:
            break;
    }
}
//--------------------------------------------------------------------------------------
UINT8 app_GetDacVal( UINT8 ch )
{
    UINT8 val;
    switch( ch )
    {
        case DAC_CH_0:
            val = da0;
            break;
        case DAC_CH_1:
            val = da1;
            break;
        default:
            val = 0;
            break;
    }
    return val;
}
//--------------------------------------------------------------------------------------
UINT16 app_GetAdcVal( UINT8 ch )
{
    UINT16 val;
    switch( ch )
    {
        case ADC_CH_0:
            val = ad0;
            break;
        case ADC_CH_1:
            val = ad1;
            break;
        case ADC_CH_2:
            val = ad2;
            break;
        case ADC_CH_3:
            val = ad3;
            break;
        case ADC_CH_4:
            val = ad4;
            break;
        case ADC_CH_5:
            val = ad5;
            break;
        case ADC_CH_6:
            val = ad6;
            break;
        case ADC_CH_7:
            val = ad7;
            break;
        default:
            val = 0;
            break;
    }
    return val;
}
//--------------------------------------------------------------------------------------
//系统中断开启
void system_interrupt_enable( void )
{
    asm( "fset I" ); //enable interrupts
}
//--------------------------------------------------------------------------------------
//系统中断关闭
void system_interrupt_disable( void )
{
    asm( "fclr I" ); //disable interrupts
}
//--------------------------------------------------------------------------------------
//系统时钟初始化
void system_clock_control( void )
{
    UINT32 i;
    //24MHz (12M*2 PLL)
    prcr = 0x07;                          // Protect mode reg
    pm0 = 0x00;                           // Processor mode reg0
    pm1 = 0x08;                           // Processor mode reg1
    pm2 = 0x00;                           // Processor mode reg2
    cm0 = 0x00;                           // System clock control register 0
    cm1 = 0x20;                           // System clock control register 1
    cm2 = 0x00;                           // System clock control register 2
    plc0 = 0x11;                          // 12MHz X 2
    plc0 |= 0x80;
    for( i = 0; i < 480000; i++ );        // delay 20ms
    cm1 |= 0x02;
    pclkr = 0x03;                         // f1,Peripheral Clock Select Register
    prcr = 0x00;                          // Protect mode reg
}
//--------------------------------------------------------------------------------------
//滴答时钟初始化
void system_ticks_control( UINT8 cmd )
{
    if( cmd != DEF_DISABLED )
    {
        ta0mr = 0x00;               // 0000 0000
        ta0 = ( SYS_FREQ / 1000 - 1 ); // Set up Timer A0 Reload Register for 1 ms interval interrupt
        ta0ic = TA0_IPL;            // set timer A0 interrupt priority
        ta0s = 1;
    }
    else
    {
        ta0mr = 0x00;               // 0000 0000
        ta0 = ( SYS_FREQ / 1000 - 1 ); // Set up Timer A0 Reload Register for 1 ms interval interrupt
        ta0ic = 0;                  // set timer A0 interrupt priority
        ta0s = 0;
    }
}
//--------------------------------------------------------------------------------------
//IO口受限，用变量替换，避免程序出错
#ifndef FL_ON
UINT8 FL_ON = 0;
#endif

#ifndef SEWING_OK
UINT8 SEWING_OK = 0;
#endif

#ifndef ERROR_OUT
UINT8 ERROR_OUT = 0;
#endif

#ifndef NEEDLE_COOL
UINT8 NEEDLE_COOL = 0;
#endif

#ifndef FILL_OIL
UINT8 FILL_OIL = 0;
#endif
//--------------------------------------------------------------------------------------
#ifndef LED_R
UINT8 LED_R;
#endif

#ifndef LED_G
UINT8 LED_G;
#endif

#ifndef LED_Y
UINT8 LED_Y;
#endif

//--------------------------------------------------------------------------------------





















