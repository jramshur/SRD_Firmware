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

int main()
{        
    CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */    
    
	
	// Let's flash them all quickly to indicate boot
	LED_R_Write(1);LED_G_Write(1);LED_B_Write(1); // turn all on
	CyDelay(200);
	LED_R_Write(0);LED_G_Write(0);LED_B_Write(0); // turn all off
	CyDelay(200);
	LED_R_Write(1);LED_G_Write(1);LED_B_Write(1); // turn all on
	CyDelay(200);
	LED_R_Write(0);LED_G_Write(0);LED_B_Write(0); // turn all off
	CyDelay(200);
	LED_R_Write(1);LED_G_Write(1);LED_B_Write(1); // turn all on
	CyDelay(200);
	LED_R_Write(0);LED_G_Write(0);LED_B_Write(0); // turn all off
	CyDelay(200);
	
    while(1){
        
		LED_R_Write(1);LED_G_Write(0);LED_B_Write(0); // turn red LED on, others off
        CyDelay(1000);
		LED_R_Write(0);LED_G_Write(1);LED_B_Write(0); // turn green LED on, others off
		CyDelay(1000);
		LED_R_Write(0);LED_G_Write(0);LED_B_Write(1); // turn blue LED on, others off
        CyDelay(1000);
    }
}

/* [] END OF FILE */
