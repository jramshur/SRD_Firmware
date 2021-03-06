/*******************************************************************************
* File Name: DMA_ISR.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <DMA_ISR.h>

#if !defined(DMA_ISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START DMA_ISR_intc` */
#include <ISR_Switch_1.h>
#include <ISR_Switch_2.h>
#include <Parser.h>

extern uint8 DMAIntrptCnt;
extern uint8 DMAIsr4IntCnt;
extern uint8 switchFlag1 ;
extern volatile uint8 ConversionComplete;
extern uint8 tmpstr[];
extern volatile uint8 TriggerDSN;
extern uint8 DMA_2_TD[2];
extern uint8 DMABusy;
extern uint8 ADCBuffer[ADC_DATA_BUFF];
uint8 DMAIsrIntCnt = 0;
extern uint8 NumberOfChannels;

uint8 DMAState = 0; 
uint8 i , Indx;
/* `#END` */


/*******************************************************************************
* Function Name: DMA_ISR_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it. This function disables the interrupt, 
*  sets the default interrupt vector, sets the priority from the value in the
*  Design Wide Resources Interrupt Editor, then enables the interrupt to the 
*  interrupt controller.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void DMA_ISR_Start(void) 
{
    /* For all we know the interrupt is active. */
    DMA_ISR_Disable();

    /* Set the ISR to point to the DMA_ISR Interrupt. */
    DMA_ISR_SetVector(&DMA_ISR_Interrupt);

    /* Set the priority. */
    DMA_ISR_SetPriority((uint8)DMA_ISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    DMA_ISR_Enable();
}


/*******************************************************************************
* Function Name: DMA_ISR_StartEx
********************************************************************************
*
* Summary:
*  Sets up the interrupt and enables it. This function disables the interrupt,
*  sets the interrupt vector based on the address passed in, sets the priority 
*  from the value in the Design Wide Resources Interrupt Editor, then enables 
*  the interrupt to the interrupt controller.
*  
*  When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*  used to provide consistent definition across compilers:
*  
*  Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*   Function prototype example:
*   CY_ISR_PROTO(MyISR);
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void DMA_ISR_StartEx(cyisraddress address) 
{
    /* For all we know the interrupt is active. */
    DMA_ISR_Disable();

    /* Set the ISR to point to the DMA_ISR Interrupt. */
    DMA_ISR_SetVector(address);

    /* Set the priority. */
    DMA_ISR_SetPriority((uint8)DMA_ISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    DMA_ISR_Enable();
}


/*******************************************************************************
* Function Name: DMA_ISR_Stop
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
void DMA_ISR_Stop(void) 
{
    /* Disable this interrupt. */
    DMA_ISR_Disable();
}


/*******************************************************************************
* Function Name: DMA_ISR_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for DMA_ISR.
*
*   Add custom code between the START and END comments to keep the next version
*   of this file from over-writing your code.
*
*   Note You may use either the default ISR by using this API, or you may define
*   your own separate ISR through ISR_StartEx().
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(DMA_ISR_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START DMA_ISR_Interrupt` */
    DMAIsrIntCnt++;

    if((DMAIsrIntCnt == 1) && (NumberOfChannels >= 2))
    {
        /*conversion completed for both channels*/
        ConversionComplete = 1;
        return;
    }
    
    DMAState = 0;
	
	if(OperationalMode != EXT_RECORDING_TRIGGER_MODE)
    	switchFlag1 = 0; 
		
    DMAIsrIntCnt = 0;
    ConversionComplete = 1;
	
   /*Stop ADC conversion and disable DMA as conversion is completed*/
    DMA_ISR_Disable();
    ISR_Switch_1_Enable();
    
    /*In trigger mode we have to send end of packet */
    if((OperationalMode == TRIGGER_MODE) || (OperationalMode == EXT_RECORDING_TRIGGER_MODE))
    {
        SendEndOfPacket();
    }

    /* Sending the response data to UART */
    if(DMABusy)
    {
		//DEBUG_UART_PutString("Delayed response\r\n");
        DMABusy = 0;
        COMM_UART_PutArray(&RespBuffer[1] , RespBuffer[0]); 
    }
    
    /*Clear a pending interrupt and enable interrupt*/
    ISR_Switch_1_ClearPending();
    ISR_Switch_1_Enable();
    
    CyDmaChDisable(DMA_2_Chan);
    DMA_ISR_Disable();

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (DMA_ISR__ES2_PATCH ))      
            DMA_ISR_ISR_PATCH();
        #endif /* CYDEV_CHIP_REVISION_USED */
    #endif /* (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */
}


/*******************************************************************************
* Function Name: DMA_ISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling DMA_ISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use DMA_ISR_StartEx instead.
* 
*   When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*   used to provide consistent definition across compilers:
*
*   Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*
*   Function prototype example:
*     CY_ISR_PROTO(MyISR);
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void DMA_ISR_SetVector(cyisraddress address) 
{
    CY_SET_REG16(DMA_ISR_INTC_VECTOR, (uint16) address);
}


/*******************************************************************************
* Function Name: DMA_ISR_GetVector
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
cyisraddress DMA_ISR_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(DMA_ISR_INTC_VECTOR);
}


/*******************************************************************************
* Function Name: DMA_ISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. 
*
*   Note calling DMA_ISR_Start or DMA_ISR_StartEx will 
*   override any effect this API would have had. This API should only be called
*   after DMA_ISR_Start or DMA_ISR_StartEx has been called. 
*   To set the initial priority for the component, use the Design-Wide Resources
*   Interrupt Editor.
*
*   Note This API has no effect on Non-maskable interrupt NMI).
*
* Parameters:
*   priority: Priority of the interrupt, 0 being the highest priority
*             PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*             PSoC 4: Priority is from 0 to 3.
*
* Return:
*   None
*
*******************************************************************************/
void DMA_ISR_SetPriority(uint8 priority) 
{
    *DMA_ISR_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: DMA_ISR_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt, 0 being the highest priority
*    PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*    PSoC 4: Priority is from 0 to 3.
*
*******************************************************************************/
uint8 DMA_ISR_GetPriority(void) 
{
    uint8 priority;


    priority = *DMA_ISR_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: DMA_ISR_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt to the interrupt controller. Do not call this function
*   unless ISR_Start() has been called or the functionality of the ISR_Start() 
*   function, which sets the vector and the priority, has been called.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void DMA_ISR_Enable(void) 
{
    /* Enable the general interrupt. */
    *DMA_ISR_INTC_SET_EN = DMA_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: DMA_ISR_GetState
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
uint8 DMA_ISR_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return ((*DMA_ISR_INTC_SET_EN & (uint8)DMA_ISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: DMA_ISR_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt in the interrupt controller.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void DMA_ISR_Disable(void) 
{
    /* Disable the general interrupt. */
    *DMA_ISR_INTC_CLR_EN = DMA_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: DMA_ISR_SetPending
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
* Side Effects:
*   If interrupts are enabled and the interrupt is set up properly, the ISR is
*   entered (depending on the priority of this interrupt and other pending 
*   interrupts).
*
*******************************************************************************/
void DMA_ISR_SetPending(void) 
{
    *DMA_ISR_INTC_SET_PD = DMA_ISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: DMA_ISR_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt in the interrupt controller.
*
*   Note Some interrupt sources are clear-on-read and require the block 
*   interrupt/status register to be read/cleared with the appropriate block API 
*   (GPIO, UART, and so on). Otherwise the ISR will continue to remain in 
*   pending state even though the interrupt itself is cleared using this API.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void DMA_ISR_ClearPending(void) 
{
    *DMA_ISR_INTC_CLR_PD = DMA_ISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
