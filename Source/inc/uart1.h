#ifndef UART1_H
#define UART1_H


//--------------------------------------------------------------------------------------
#define TRA1_BUF_SIZE   300
#define REC1_BUF_SIZE   300


//--------------------------------------------------------------------------------------
extern UINT16 tra1_ind_r;       // transmit  buffer reading index
extern UINT16 tra1_ind_w;       // transmit  buffer writing index
extern UINT16 rec1_ind_r;      // receive  buffer reading index
extern UINT16 rec1_ind_w;      // receive  buffer writing index

extern UINT8 rec1_buf[REC1_BUF_SIZE];   // receive  buffer
extern UINT8 tra1_buf[TRA1_BUF_SIZE];   // transmit  buffer

UINT8 uart1_get_char( UINT8* pData );
UINT8 uart1_send_char( UINT8* pData );
void uart1_set_baudrate( UINT16 baudrate );
void init_uart1_val( void );
void rec1_com( void );



//--------------------------------------------------------------------------------------
#endif