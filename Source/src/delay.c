//--------------------------------------------------------------------------------------
//  Includes
//--------------------------------------------------------------------------------------
#include "..\inc\includes.h"    // all files includes


//--------------------------------------------------------------------------------------
//  function declaration
//--------------------------------------------------------------------------------------
void delay_ms( UINT16 time );
void delay_us( UINT16 time );
//--------------------------------------------------------------------------------------
//  Name:       delay_ms
//  Parameters: time
//  Returns:    None
//  Description: delay time 1ms
//--------------------------------------------------------------------------------------
void delay_ms( UINT16 time )    // ms
{
    UINT16 temp1;
    UINT16 temp2;
    if( time == 0 )
    {
        return;
    }
    temp1 = time / 50; //大于 50ms
    temp2 = time % 50; //小于 50ms
    tb3mr = 0x80;     // f32 = 750K Hz
    tb3ic = 0;            // set timer B2 interrupt priority
    tb3s = 0;         // stop timer B4
    //--------------------------------------------------------------------------------------
    while( temp1 > 0 )
    {
        tb3 = 750 * 50 - 1; // update time
        tb3s = 1;           // start timer
        while( ir_tb3ic == 0 )
        {
            rec_com();    // communication with panel
        }
        tb3s = 0;           // stop timer
        ir_tb3ic = 0;       // clear interrupt flag
        temp1--;
    }
    //--------------------------------------------------------------------------------------
    if( temp2 > 0 )
    {
        tb3 = 750 * temp2 - 1;  // update time
        tb3s = 1;           // start timer
        while( ir_tb3ic == 0 )
        {
            rec_com();    // communication with panel
        }
        tb3s = 0;           // stop timer
        ir_tb3ic = 0;       // clear interrupt flag
    }
    //--------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------
//  Name:       delay_us
//  Parameters: time
//  Returns:    None
//  Description: delay time 1us    time must less than
//--------------------------------------------------------------------------------------
void delay_us( UINT16 time )     // us
{
    UINT16 temp1;
    UINT16 temp2;
    if( time == 0 )
    {
        return;
    }
    temp1 = time / 10000; //大于 10us
    temp2 = time % 10000; //小于 10us
    tb4mr = 0x40;     // f8 = 3M Hz
    tb4ic = 0;            // set timer B4 interrupt priority
    tb4s = 0;         // stop timer B4
    //--------------------------------------------------------------------------------------
    while( temp1 > 0 )
    {
        tb4 = 10000 * 3 - 1; // update time
        tb4s = 1;           // start timer B4
        while( ir_tb4ic == 0 );
        tb4s = 0;           // stop timer B4
        ir_tb4ic = 0;       // clear interrupt flag
        temp1--;
    }
    //--------------------------------------------------------------------------------------
    if( temp2 > 0 )
    {
        tb4 = temp2 * 3 - 1; // update time
        tb4s = 1;           // start timer B4
        while( ir_tb4ic == 0 );
        tb4s = 0;           // stop timer B4
        ir_tb4ic = 0;       // clear interrupt flag
    }
    //--------------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------------