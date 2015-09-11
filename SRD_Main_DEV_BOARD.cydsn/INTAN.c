/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

//#include <device.h>
#include <INTAN.h>
#if 0
// Upper Bandwidth
uint8 FilterLowCutVal = 23;     // 19=100Hz; 20=150Hz; 21=200; 22=250; 23=300; 24=500Hz
// Lower Bandwidth
uint8 FilterHighCutVal = 7 ;    // 7=1.0kHz; 8=1.5k; 9=2.0k; 10=2.5k; 11=3.0k; 12=5.0kHz
uint8 FilterDSPVal = 3 ;       	//anything > 15 will disable the DSP filter
#endif

extern uint8 FilterSetting[7];

// Define Default register values for filter related registers reg 4 and 8-12 
uint16 INTAN_REG_4_DEF =  0x84D3;		// REG4: Define Default
uint16 INTAN_REG_8_DEF =  0x8800;       // REG8: Define Default
uint16 INTAN_REG_9_DEF =  0x8900;       // REG9: Define Default
uint16 INTAN_REG_10_DEF = 0x8A25;       // REG10: Define Default
uint16 INTAN_REG_11_DEF = 0x8B00;       // REG11: Define Default
uint16 INTAN_REG_12_DEF = 0x8C11;       // REG12: Define default
uint16 INTAN_REG_13_DEF = 0x8D00;       // REG13: Define default

#if 0
// Define array of register values for on-chip filter settings
uint8 RH1DAC1[17] = {38,44,24,42,6,30,41,46,1,27,13,3,33,22,17,11,8};
uint8 RH1DAC2[17] = {26,17,13,10,9,5,3,2,2,1,1,1,0,0,0,0,0};
uint8 RH2DAC1[17] = {5,8,7,5,2,43,36,30,23,44,25,13,37,23,16,8,4};
uint8 RH2DAC2[17] = {31,21,16,13,11,6,4,3,2,1,1,1,0,0,0,0,0};
uint8 RLDAC1[25] = {16,56,1,35,49,44,9,8,42,20,40,18,5,62,54,48,44,34,28,25,21,18,17,15,13};
uint8 RLDAC2[14] = {60,54,40,17,9,6,4,3,2,2,1,1,1,0}; //removed repeating zeros to save memory.
uint8 RLDAC3[2] = {1,0}; //removed repeating zeros to save memory. Requires using if statement below for reg13
#endif

void Calculate_Filter_Registers(void)
{
#if 0
	uint8 tmp;
    
    // DSP offset filter
    INTAN_REG_4_DEF = 0x8400 | 0x00C0;
    if(FilterDSPVal < 16)  // determine if using DSP filter (values > 15 are interpreted as unenable DSP offset removal
            INTAN_REG_4_DEF = INTAN_REG_4_DEF | 0x0010 | FilterDSPVal;    
        
    // High cut off filter (LPF)
    INTAN_REG_8_DEF = 0x8800 | RH1DAC1[FilterHighCutVal];
    INTAN_REG_9_DEF = 0x8900 | RH1DAC2[FilterHighCutVal];
    INTAN_REG_10_DEF = 0x8A00 | RH2DAC1[FilterHighCutVal];
    INTAN_REG_11_DEF = 0x8B00 | RH2DAC2[FilterHighCutVal];   
    // Low cut off fitler (HPF)
    INTAN_REG_12_DEF = 0x8C00 | RLDAC1[FilterLowCutVal];    
    INTAN_REG_13_DEF = 0x8D00;
    if(FilterLowCutVal < 13)   
        INTAN_REG_13_DEF = INTAN_REG_13_DEF | RLDAC2[FilterLowCutVal];    
    if(FilterLowCutVal < 1)
        INTAN_REG_13_DEF = INTAN_REG_13_DEF | (RLDAC3[FilterLowCutVal]<<6);    
#endif
	// DSP offset filter
    INTAN_REG_4_DEF =  0x8400 | FilterSetting[0];
	// High cut off filter (LPF)
    INTAN_REG_8_DEF =  0x8800 | FilterSetting[1];
    INTAN_REG_9_DEF =  0x8900 | FilterSetting[2];
    INTAN_REG_10_DEF = 0x8A00 | FilterSetting[3];
    INTAN_REG_11_DEF = 0x8B00 | FilterSetting[4];
    // Low cut off fitler (HPF)
    INTAN_REG_12_DEF = 0x8C00 | FilterSetting[5];
    INTAN_REG_13_DEF = 0x8D00 | FilterSetting[6];
}


/* [] END OF FILE */
