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
#include <device.h>

#define PERIOD_P1 	    1 // milliseconds
#define PERIOD_DELAY	2
#define PERIOD_P2	    1 
#define PERIOD_INTERVAL 1000 

#define DAC_V1 100
#define DAC_V2 100
#define DAC_Offset 13 // offset based on calibration of stim output

#define STIM_POS 0
#define STIM_NEG 2
#define STIM_OPEN 1
#define STIM_GROUND 3

int8 adjDACval(int8 input,int8 offset);

int main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	CYGlobalIntEnable; /* Uncomment this line to enable global interrupts. */

	IDAC8_1_Start(); 
	
	IDAC8_2_Start();

    CyDelay(1000);    

    //Control_Reg_StimSel_Write(STIM_POS);
    for(;;)
    {
        
        IDAC8_1_SetValue(DAC_V1); //set vdac            
		Control_Reg_StimSel_Write(STIM_POS); //switch mux
		CyDelay(PERIOD_P1);
        
        IDAC8_1_SetValue(0); //set vdac 
		Control_Reg_StimSel_Write(STIM_GROUND); //switch mux						
        CyDelay(PERIOD_DELAY);                              
        
        IDAC8_2_SetValue(DAC_V2); //set vdac         
		Control_Reg_StimSel_Write(STIM_NEG); //switch mux        
        CyDelay(PERIOD_P2);
              
		IDAC8_2_SetValue(0); //set vdac            
		Control_Reg_StimSel_Write(STIM_GROUND); //switch mux
    	CyDelay(PERIOD_INTERVAL);
        
		LED_B_Write(~LED_B_Read()); //Toggle LED  		
		
    }
}

int8 adjDACval(int8 input,int8 offset)
{
    int8 tmp;
    if (input<offset) tmp=0;
    else tmp=input-offset;
    
    return tmp;
}
/* [] END OF FILE */
