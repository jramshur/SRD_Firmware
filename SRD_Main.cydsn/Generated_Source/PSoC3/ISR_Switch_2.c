/*******************************************************************************
* File Name: ISR_Switch_2.c  
* Version 1.60
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
#include <ISR_Switch_2.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START ISR_Switch_2_intc` */
#include "Pin_Switch_2.h"
/* `#END` */


/*******************************************************************************
* Function Name: ISR_Switch_2_Start
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
void ISR_Switch_2_Start(void)
{
    /* For all we know the interrupt is active. */
    ISR_Switch_2_Disable();

    /* Set the ISR to point to the ISR_Switch_2 Interrupt. */
    ISR_Switch_2_SetVector(ISR_Switch_2_Interrupt);

    /* Set the priority. */
    ISR_Switch_2_SetPriority(ISR_Switch_2_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ISR_Switch_2_Enable();
}

/*******************************************************************************
* Function Name: ISR_Switch_2_StartEx
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
void ISR_Switch_2_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    ISR_Switch_2_Disable();

    /* Set the ISR to point to the ISR_Switch_2 Interrupt. */
    ISR_Switch_2_SetVector(address);

    /* Set the priority. */
    ISR_Switch_2_SetPriority(ISR_Switch_2_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ISR_Switch_2_Enable();
}

/*******************************************************************************
* Function Name: ISR_Switch_2_Stop
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
void ISR_Switch_2_Stop(void) 
{
    /* Disable this interrupt. */
    ISR_Switch_2_Disable();
}

/*******************************************************************************
* Function Name: ISR_Switch_2_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for ISR_Switch_2.
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
CY_ISR(ISR_Switch_2_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START ISR_Switch_2_Interrupt` */
	/* Read the PICU status register to clear the interrupt */
	    CY_GET_REG8(Pin_Switch_2_INTSTAT);	
    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (ISR_Switch_2__ES2_PATCH ))      
            ISR_Switch_2_ISR_PATCH();
        #endif
    #endif
}

/*******************************************************************************
* Function Name: ISR_Switch_2_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling ISR_Switch_2_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use ISR_Switch_2_StartEx instead.
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
void ISR_Switch_2_SetVector(cyisraddress address) 
{
    CY_SET_REG16(ISR_Switch_2_INTC_VECTOR, (uint16) address);
}

/*******************************************************************************
* Function Name: ISR_Switch_2_GetVector
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
cyisraddress ISR_Switch_2_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(ISR_Switch_2_INTC_VECTOR);
}

/*******************************************************************************
* Function Name: ISR_Switch_2_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling ISR_Switch_2_Start
*   or ISR_Switch_2_StartEx will override any effect this method would have had. 
*	This method should only be called after ISR_Switch_2_Start or 
*	ISR_Switch_2_StartEx has been called. To set the initial
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
void ISR_Switch_2_SetPriority(uint8 priority) 
{
    *ISR_Switch_2_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: ISR_Switch_2_GetPriority
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
uint8 ISR_Switch_2_GetPriority(void) 
{
    uint8 priority;


    priority = *ISR_Switch_2_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: ISR_Switch_2_Enable
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
void ISR_Switch_2_Enable(void) 
{
    /* Enable the general interrupt. */
    *ISR_Switch_2_INTC_SET_EN = ISR_Switch_2__INTC_MASK;
}

/*******************************************************************************
* Function Name: ISR_Switch_2_GetState
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
uint8 ISR_Switch_2_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*ISR_Switch_2_INTC_SET_EN & ISR_Switch_2__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: ISR_Switch_2_Disable
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
void ISR_Switch_2_Disable(void) 
{
    /* Disable the general interrupt. */
    *ISR_Switch_2_INTC_CLR_EN = ISR_Switch_2__INTC_MASK;
}

/*******************************************************************************
* Function Name: ISR_Switch_2_SetPending
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
void ISR_Switch_2_SetPending(void) 
{
    *ISR_Switch_2_INTC_SET_PD = ISR_Switch_2__INTC_MASK;
}

/*******************************************************************************
* Function Name: ISR_Switch_2_ClearPending
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
void ISR_Switch_2_ClearPending(void) 
{
    *ISR_Switch_2_INTC_CLR_PD = ISR_Switch_2__INTC_MASK;
}
