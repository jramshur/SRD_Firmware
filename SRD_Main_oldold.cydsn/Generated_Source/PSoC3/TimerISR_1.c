/*******************************************************************************
* File Name: TimerISR_1.c  
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

#include <cydevice_trm.h>
#include <CyLib.h>
#include <TimerISR_1.h>

#if !defined(TimerISR_1__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START TimerISR_1_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: TimerISR_1_Start
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
void TimerISR_1_Start(void) 
{
    /* For all we know the interrupt is active. */
    TimerISR_1_Disable();

    /* Set the ISR to point to the TimerISR_1 Interrupt. */
    TimerISR_1_SetVector(&TimerISR_1_Interrupt);

    /* Set the priority. */
    TimerISR_1_SetPriority((uint8)TimerISR_1_INTC_PRIOR_NUMBER);

    /* Enable it. */
    TimerISR_1_Enable();
}


/*******************************************************************************
* Function Name: TimerISR_1_StartEx
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
void TimerISR_1_StartEx(cyisraddress address) 
{
    /* For all we know the interrupt is active. */
    TimerISR_1_Disable();

    /* Set the ISR to point to the TimerISR_1 Interrupt. */
    TimerISR_1_SetVector(address);

    /* Set the priority. */
    TimerISR_1_SetPriority((uint8)TimerISR_1_INTC_PRIOR_NUMBER);

    /* Enable it. */
    TimerISR_1_Enable();
}


/*******************************************************************************
* Function Name: TimerISR_1_Stop
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
void TimerISR_1_Stop(void) 
{
    /* Disable this interrupt. */
    TimerISR_1_Disable();
}


/*******************************************************************************
* Function Name: TimerISR_1_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for TimerISR_1.
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
CY_ISR(TimerISR_1_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START TimerISR_1_Interrupt` */

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (TimerISR_1__ES2_PATCH ))      
            TimerISR_1_ISR_PATCH();
        #endif /* CYDEV_CHIP_REVISION_USED */
    #endif /* (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */
}


/*******************************************************************************
* Function Name: TimerISR_1_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling TimerISR_1_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use TimerISR_1_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void TimerISR_1_SetVector(cyisraddress address) 
{
    CY_SET_REG16(TimerISR_1_INTC_VECTOR, (uint16) address);
}


/*******************************************************************************
* Function Name: TimerISR_1_GetVector
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
cyisraddress TimerISR_1_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(TimerISR_1_INTC_VECTOR);
}


/*******************************************************************************
* Function Name: TimerISR_1_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling TimerISR_1_Start
*   or TimerISR_1_StartEx will override any effect this method would 
*   have had. This method should only be called after TimerISR_1_Start or 
*   TimerISR_1_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void TimerISR_1_SetPriority(uint8 priority) 
{
    *TimerISR_1_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: TimerISR_1_GetPriority
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
uint8 TimerISR_1_GetPriority(void) 
{
    uint8 priority;


    priority = *TimerISR_1_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: TimerISR_1_Enable
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
void TimerISR_1_Enable(void) 
{
    /* Enable the general interrupt. */
    *TimerISR_1_INTC_SET_EN = TimerISR_1__INTC_MASK;
}


/*******************************************************************************
* Function Name: TimerISR_1_GetState
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
uint8 TimerISR_1_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return ((*TimerISR_1_INTC_SET_EN & (uint8)TimerISR_1__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: TimerISR_1_Disable
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
void TimerISR_1_Disable(void) 
{
    /* Disable the general interrupt. */
    *TimerISR_1_INTC_CLR_EN = TimerISR_1__INTC_MASK;
}


/*******************************************************************************
* Function Name: TimerISR_1_SetPending
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
void TimerISR_1_SetPending(void) 
{
    *TimerISR_1_INTC_SET_PD = TimerISR_1__INTC_MASK;
}


/*******************************************************************************
* Function Name: TimerISR_1_ClearPending
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
void TimerISR_1_ClearPending(void) 
{
    *TimerISR_1_INTC_CLR_PD = TimerISR_1__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
