/*******************************************************************************
* File Name: CounterISR.c  
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
#include <CounterISR.H>

#if !defined(CounterISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START CounterISR_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: CounterISR_Start
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
void CounterISR_Start(void) 
{
    /* For all we know the interrupt is active. */
    CounterISR_Disable();

    /* Set the ISR to point to the CounterISR Interrupt. */
    CounterISR_SetVector(&CounterISR_Interrupt);

    /* Set the priority. */
    CounterISR_SetPriority((uint8)CounterISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    CounterISR_Enable();
}


/*******************************************************************************
* Function Name: CounterISR_StartEx
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
void CounterISR_StartEx(cyisraddress address) 
{
    /* For all we know the interrupt is active. */
    CounterISR_Disable();

    /* Set the ISR to point to the CounterISR Interrupt. */
    CounterISR_SetVector(address);

    /* Set the priority. */
    CounterISR_SetPriority((uint8)CounterISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    CounterISR_Enable();
}


/*******************************************************************************
* Function Name: CounterISR_Stop
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
void CounterISR_Stop(void) 
{
    /* Disable this interrupt. */
    CounterISR_Disable();
}


/*******************************************************************************
* Function Name: CounterISR_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for CounterISR.
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
CY_ISR(CounterISR_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START CounterISR_Interrupt` */

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (CounterISR__ES2_PATCH ))      
            CounterISR_ISR_PATCH();
        #endif /* CYDEV_CHIP_REVISION_USED */
    #endif /* (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */
}


/*******************************************************************************
* Function Name: CounterISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling CounterISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use CounterISR_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void CounterISR_SetVector(cyisraddress address) 
{
    CY_SET_REG16(CounterISR_INTC_VECTOR, (uint16) address);
}


/*******************************************************************************
* Function Name: CounterISR_GetVector
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
cyisraddress CounterISR_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(CounterISR_INTC_VECTOR);
}


/*******************************************************************************
* Function Name: CounterISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling CounterISR_Start
*   or CounterISR_StartEx will override any effect this method would 
*   have had. This method should only be called after CounterISR_Start or 
*   CounterISR_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void CounterISR_SetPriority(uint8 priority) 
{
    *CounterISR_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: CounterISR_GetPriority
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
uint8 CounterISR_GetPriority(void) 
{
    uint8 priority;


    priority = *CounterISR_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: CounterISR_Enable
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
void CounterISR_Enable(void) 
{
    /* Enable the general interrupt. */
    *CounterISR_INTC_SET_EN = CounterISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: CounterISR_GetState
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
uint8 CounterISR_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return ((*CounterISR_INTC_SET_EN & (uint8)CounterISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: CounterISR_Disable
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
void CounterISR_Disable(void) 
{
    /* Disable the general interrupt. */
    *CounterISR_INTC_CLR_EN = CounterISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: CounterISR_SetPending
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
void CounterISR_SetPending(void) 
{
    *CounterISR_INTC_SET_PD = CounterISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: CounterISR_ClearPending
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
void CounterISR_ClearPending(void) 
{
    *CounterISR_INTC_CLR_PD = CounterISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
