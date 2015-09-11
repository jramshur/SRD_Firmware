/*******************************************************************************
* File Name: ISR_COMM_UART_RX.c  
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
#include <ISR_COMM_UART_RX.h>

#if !defined(ISR_COMM_UART_RX__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START ISR_COMM_UART_RX_intc` */
#include <Tick_timer.h>
#include <COMM_UART.h>

extern uint8 UartRXIndex;
extern uint8 UARTBuffer[];
/* `#END` */


/*******************************************************************************
* Function Name: ISR_COMM_UART_RX_Start
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
void ISR_COMM_UART_RX_Start(void) 
{
    /* For all we know the interrupt is active. */
    ISR_COMM_UART_RX_Disable();

    /* Set the ISR to point to the ISR_COMM_UART_RX Interrupt. */
    ISR_COMM_UART_RX_SetVector(&ISR_COMM_UART_RX_Interrupt);

    /* Set the priority. */
    ISR_COMM_UART_RX_SetPriority((uint8)ISR_COMM_UART_RX_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ISR_COMM_UART_RX_Enable();
}


/*******************************************************************************
* Function Name: ISR_COMM_UART_RX_StartEx
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
void ISR_COMM_UART_RX_StartEx(cyisraddress address) 
{
    /* For all we know the interrupt is active. */
    ISR_COMM_UART_RX_Disable();

    /* Set the ISR to point to the ISR_COMM_UART_RX Interrupt. */
    ISR_COMM_UART_RX_SetVector(address);

    /* Set the priority. */
    ISR_COMM_UART_RX_SetPriority((uint8)ISR_COMM_UART_RX_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ISR_COMM_UART_RX_Enable();
}


/*******************************************************************************
* Function Name: ISR_COMM_UART_RX_Stop
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
void ISR_COMM_UART_RX_Stop(void) 
{
    /* Disable this interrupt. */
    ISR_COMM_UART_RX_Disable();
}


/*******************************************************************************
* Function Name: ISR_COMM_UART_RX_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for ISR_COMM_UART_RX.
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
CY_ISR(ISR_COMM_UART_RX_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START ISR_COMM_UART_RX_Interrupt` */
 
    /* To clear the interrrupts */
	    COMM_UART_GetRxInterruptSource();    
    /*Read the data from UART untill we received complete packet*/
        UARTBuffer[UartRXIndex++] = COMM_UART_ReadRxData();
        
        Tick_Timer_Start();
        
    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (ISR_COMM_UART_RX__ES2_PATCH ))      
            ISR_COMM_UART_RX_ISR_PATCH();
        #endif /* CYDEV_CHIP_REVISION_USED */
    #endif /* (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */
}


/*******************************************************************************
* Function Name: ISR_COMM_UART_RX_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling ISR_COMM_UART_RX_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use ISR_COMM_UART_RX_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void ISR_COMM_UART_RX_SetVector(cyisraddress address) 
{
    CY_SET_REG16(ISR_COMM_UART_RX_INTC_VECTOR, (uint16) address);
}


/*******************************************************************************
* Function Name: ISR_COMM_UART_RX_GetVector
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
cyisraddress ISR_COMM_UART_RX_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(ISR_COMM_UART_RX_INTC_VECTOR);
}


/*******************************************************************************
* Function Name: ISR_COMM_UART_RX_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling ISR_COMM_UART_RX_Start
*   or ISR_COMM_UART_RX_StartEx will override any effect this method would 
*   have had. This method should only be called after ISR_COMM_UART_RX_Start or 
*   ISR_COMM_UART_RX_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void ISR_COMM_UART_RX_SetPriority(uint8 priority) 
{
    *ISR_COMM_UART_RX_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: ISR_COMM_UART_RX_GetPriority
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
uint8 ISR_COMM_UART_RX_GetPriority(void) 
{
    uint8 priority;


    priority = *ISR_COMM_UART_RX_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: ISR_COMM_UART_RX_Enable
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
void ISR_COMM_UART_RX_Enable(void) 
{
    /* Enable the general interrupt. */
    *ISR_COMM_UART_RX_INTC_SET_EN = ISR_COMM_UART_RX__INTC_MASK;
}


/*******************************************************************************
* Function Name: ISR_COMM_UART_RX_GetState
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
uint8 ISR_COMM_UART_RX_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return ((*ISR_COMM_UART_RX_INTC_SET_EN & (uint8)ISR_COMM_UART_RX__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: ISR_COMM_UART_RX_Disable
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
void ISR_COMM_UART_RX_Disable(void) 
{
    /* Disable the general interrupt. */
    *ISR_COMM_UART_RX_INTC_CLR_EN = ISR_COMM_UART_RX__INTC_MASK;
}


/*******************************************************************************
* Function Name: ISR_COMM_UART_RX_SetPending
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
void ISR_COMM_UART_RX_SetPending(void) 
{
    *ISR_COMM_UART_RX_INTC_SET_PD = ISR_COMM_UART_RX__INTC_MASK;
}


/*******************************************************************************
* Function Name: ISR_COMM_UART_RX_ClearPending
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
void ISR_COMM_UART_RX_ClearPending(void) 
{
    *ISR_COMM_UART_RX_INTC_CLR_PD = ISR_COMM_UART_RX__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
