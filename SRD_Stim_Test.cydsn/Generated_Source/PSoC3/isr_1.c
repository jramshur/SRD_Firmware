/*******************************************************************************
* File Name: isr_1.c  
* Version 1.50
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include <CYDEVICE.H>
#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <isr_1.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START isr_1_intc` */

#include <Timer_1.h>
#include <VDAC8_1.h>
#include <Control_Reg_StimSel.h>
#include <Control_Reg_VDAC.h>

#define PERIOD_T1 	20000 //1000ms
#define PERIOD_T2	10000 //500ms
#define PERIOD_T3	40000 //2000ms
#define PERIOD_T4	30000 //3000ms

#define VDAC_V1		200
#define VDAC_V2		100

#define GREEN 1 //rt
#define RED 2   //lt
#define OFF 0
#define BOTH 3

/* `#END` */


/*******************************************************************************
* Function Name: isr_1_Start
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void isr_1_Start(void)
{
    /* For all we know the interrupt is active. */
    isr_1_Disable();

    /* Set the ISR to point to the isr_1 Interrupt. */
    isr_1_SetVector(isr_1_Interrupt);

    /* Set the priority. */
    isr_1_SetPriority(isr_1_INTC_PRIOR_NUMBER);

    /* Enable it. */
    isr_1_Enable();
}

/*******************************************************************************
* Function Name: isr_1_StartEx
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*******************************************************************************/
void isr_1_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    isr_1_Disable();

    /* Set the ISR to point to the isr_1 Interrupt. */
    isr_1_SetVector(address);

    /* Set the priority. */
    isr_1_SetPriority(isr_1_INTC_PRIOR_NUMBER);

    /* Enable it. */
    isr_1_Enable();
}

/*******************************************************************************
* Function Name: isr_1_Stop
********************************************************************************
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
void isr_1_Stop(void) 
{
    /* Disable this interrupt. */
    isr_1_Disable();
}

/*******************************************************************************
* Function Name: isr_1_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for isr_1.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
*
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
CY_ISR(isr_1_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START isr_1_Interrupt` */
	
    static uint8 state = 0;
	
	Timer_1_ReadStatusRegister();
	
	switch (state)
	{
		case 0:									
			VDAC8_1_SetValue(VDAC_V1); //set vdac            
            Control_Reg_VDAC_Write(1); //turn on vdac pin
			Control_Reg_StimSel_Write(GREEN); //switch mux
            Timer_1_WritePeriod(PERIOD_T1);			
			state = 1;
			break;
			
		case 1:									
            VDAC8_1_SetValue(0); //set vdac 
            Control_Reg_VDAC_Write(0); //turn OFF vdac pin
			Control_Reg_StimSel_Write(OFF); //switch mux
			Timer_1_WritePeriod(PERIOD_T2);
			state = 2;
			break;
			
		case 2:									
			VDAC8_1_SetValue(VDAC_V2); //set vdac         
            Control_Reg_VDAC_Write(1); //turn on vdac pin
			Control_Reg_StimSel_Write(RED); //switch mux
			Timer_1_WritePeriod(PERIOD_T3);			
			state = 3;
			break;
			
		case 3:									
			VDAC8_1_SetValue(0); //set vdac            
            Control_Reg_VDAC_Write(0); //turn OFF vdac pin
			Control_Reg_StimSel_Write(OFF); //switch mux
			Timer_1_WritePeriod(PERIOD_T4);
			state = 0;
			break;
			
		default:
			state = 0;
	}

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (isr_1__ES2_PATCH ))      
            isr_1_ISR_PATCH();
        #endif
    #endif
}

/*******************************************************************************
* Function Name: isr_1_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling isr_1_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use isr_1_StartEx instead.
*
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_1_SetVector(cyisraddress address) 
{
    CY_SET_REG16(isr_1_INTC_VECTOR, (uint16) address);
}

/*******************************************************************************
* Function Name: isr_1_GetVector
********************************************************************************
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*
*******************************************************************************/
cyisraddress isr_1_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(isr_1_INTC_VECTOR);
}

/*******************************************************************************
* Function Name: isr_1_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling isr_1_Start
*   or isr_1_StartEx will override any effect this method would have had. 
*	This method should only be called after isr_1_Start or 
*	isr_1_StartEx has been called. To set the initial
*	priority for the component use the cydwr file in the tool.
*
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_1_SetPriority(uint8 priority) 
{
    *isr_1_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: isr_1_GetPriority
********************************************************************************
* Summary:
*   Gets the Priority of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
*******************************************************************************/
uint8 isr_1_GetPriority(void) 
{
    uint8 priority;


    priority = *isr_1_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: isr_1_Enable
********************************************************************************
* Summary:
*   Enables the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_1_Enable(void) 
{
    /* Enable the general interrupt. */
    *isr_1_INTC_SET_EN = isr_1__INTC_MASK;
}

/*******************************************************************************
* Function Name: isr_1_GetState
********************************************************************************
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   1 if enabled, 0 if disabled.
*
*
*******************************************************************************/
uint8 isr_1_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*isr_1_INTC_SET_EN & isr_1__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: isr_1_Disable
********************************************************************************
* Summary:
*   Disables the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_1_Disable(void) 
{
    /* Disable the general interrupt. */
    *isr_1_INTC_CLR_EN = isr_1__INTC_MASK;
}

/*******************************************************************************
* Function Name: isr_1_SetPending
********************************************************************************
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_1_SetPending(void) 
{
    *isr_1_INTC_SET_PD = isr_1__INTC_MASK;
}

/*******************************************************************************
* Function Name: isr_1_ClearPending
********************************************************************************
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void isr_1_ClearPending(void) 
{
    *isr_1_INTC_CLR_PD = isr_1__INTC_MASK;
}
