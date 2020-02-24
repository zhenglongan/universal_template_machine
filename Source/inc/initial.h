#ifndef INITIAL_H
#define INITIAL_H

extern void restore_para_from_eeprom( void );
//--------------------------------------------------------------------------------------
void copy_data_to_adjust( UINT8* pData,
                          UINT16* pXAnglePositive,
                          UINT8* pXTimePositive,
                          UINT16* pXAngleNegative,
                          UINT8* pXTimeNegative,
                          UINT16* pYAnglePositive,
                          UINT8* pYTimePositive,
                          UINT16* pYAngleNegative,
                          UINT8* pYTimeNegative );
void copy_adjust_to_data( UINT8* pData,
                          UINT16* pXAnglePositive,
                          UINT8* pXTimePositive,
                          UINT16* pXAngleNegative,
                          UINT8* pXTimeNegative,
                          UINT16* pYAnglePositive,
                          UINT8* pYTimePositive,
                          UINT16* pYAngleNegative,
                          UINT8* pYTimeNegative );
//--------------------------------------------------------------------------------------
#endif

