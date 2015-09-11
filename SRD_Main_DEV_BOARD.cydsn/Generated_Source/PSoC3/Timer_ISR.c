/*******************************************************************************
* File Name: Timer_ISR.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <Timer_ISR.H>

#if !defined(Timer_ISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START Timer_ISR_intc` */
#include <Parser.h>
#include "CyDmac.h"

uint8 TimerStatusRegister = 0;
uint8 DMA_Current_TD = 0, DMA_State = 0;
uint16 P1 = 0 , P2 = 0;
extern uint8 ByteConversionComplete;
extern uint8 DMA_3_Chan;
/* `#END` */


/*******************************************************************************
* Function Name: Timer_ISR_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Timer_ISR_Start(void) 
{
    /* For all we know the interrupt is active. */
    Timer_ISR_Disable();

    /* Set the ISR to point to the Timer_ISR Interrupt. */
    Timer_ISR_SetVector(&Timer_ISR_Interrupt);

    /* Set the priority. */
    Timer_ISR_SetPriority((uint8)Timer_ISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    Timer_ISR_Enable();
}


/*******************************************************************************
* Function Name: Timer_ISR_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void Timer_ISR_StartEx(cyisraddress address) 
{
    /* For all we know the interrupt is active. */
    Timer_ISR_Disable();

    /* Set the ISR to point to the Timer_ISR Interrupt. */
    Timer_ISR_SetVector(address);

    /* Set the priority. */
    Timer_ISR_SetPriority((uint8)Timer_ISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    Timer_ISR_Enable();
}


/*******************************************************************************
* Function Name: Timer_ISR_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Timer_ISR_Stop(void) 
{
    /* Disable this interrupt. */
    Timer_ISR_Disable();
}


/*******************************************************************************
* Function Name: Timer_ISR_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for Timer_ISR.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(Timer_ISR_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START Timer_ISR_Interrupt` */
		uint8 tmpstr1[20];
		ByteConversionComplete = 1;
		
		 /*Reads the status register and returns it's state.*/
        TimerStatusRegister = Timer_Look_ahead_mode_ReadStatusRegister();
		
		Timer_Look_ahead_mode_Stop();
		
		CyDmaChStatus(DMA_3_Chan, &DMA_Current_TD , &DMA_State);
		sprintf(tmpstr1, "TD [%d] \r\n", DMA_Current_TD);
	   	DEBUG_UART_PutString(tmpstr1);
		
		CyDmaTdGetAddress(DMA_3_Chan, &P1 , &P2);
		sprintf(tmpstr1, "P1 [%d] \r\n", P1);
	   	DEBUG_UART_PutString(tmpstr1);
		sprintf(tmpstr1, "P2 [%d] \r\n", P2);
	   	DEBUG_UART_PutString(tmpstr1);
		DEBUG_UART_PutString("\r\n");
		
	
    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (Timer_ISR__ES2_PATCH ))      
            Timer_ISR_ISR_PATCH();
        #endif /* CYDEV_CHIP_REVISION_USED */
    #endif /* (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */
}


/*******************************************************************************
* Function Name: Timer_ISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling Timer_ISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use Timer_ISR_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void Timer_ISR_SetVector(cyisraddress address) 
{
    CY_SET_REG16(Timer_ISR_INTC_VECTOR, (uint16) address);
}


/*******************************************************************************
* Function Name: Timer_ISR_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress Timer_ISR_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(Timer_ISR_INTC_VECTOR);
}


/*******************************************************************************
* Function Name: Timer_ISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling Timer_ISR_Start
*   or Timer_ISR_StartEx will override any effect this method would 
*   have had. This method should only be called after Timer_ISR_Start or 
*   Timer_ISR_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void Timer_ISR_SetPriority(uint8 priority) 
{
    *Timer_ISR_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: Timer_ISR_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*******************************************************************************/
uint8 Timer_ISR_GetPriority(void) 
{
    uint8 priority;


    priority = *Timer_ISR_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: Timer_ISR_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Timer_ISR_Enable(void) 
{
    /* Enable the general interrupt. */
    *Timer_ISR_INTC_SET_EN = Timer_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: Timer_ISR_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 Timer_ISR_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return ((*Timer_ISR_INTC_SET_EN & (uint8)Timer_ISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: Timer_ISR_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Timer_ISR_Disable(void) 
{
    /* Disable the general interrupt. */
    *Timer_ISR_INTC_CLR_EN = Timer_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: Timer_ISR_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Timer_ISR_SetPending(void) 
{
    *Timer_ISR_INTC_SET_PD = Timer_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: Timer_ISR_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void Timer_ISR_ClearPending(void) 
{
    *Timer_ISR_INTC_CLR_PD = Timer_ISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
