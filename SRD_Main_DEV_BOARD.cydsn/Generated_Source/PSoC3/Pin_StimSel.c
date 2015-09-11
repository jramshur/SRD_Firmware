/*******************************************************************************
* File Name: Pin_StimSel.c  
* Version 2.0
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Pin_StimSel.h"


/*******************************************************************************
* Function Name: Pin_StimSel_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void Pin_StimSel_Write(uint8 value) 
{
    uint8 staticBits = (Pin_StimSel_DR & (uint8)(~Pin_StimSel_MASK));
    Pin_StimSel_DR = staticBits | ((uint8)(value << Pin_StimSel_SHIFT) & Pin_StimSel_MASK);
}


/*******************************************************************************
* Function Name: Pin_StimSel_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Pin_StimSel_DM_STRONG     Strong Drive 
*  Pin_StimSel_DM_OD_HI      Open Drain, Drives High 
*  Pin_StimSel_DM_OD_LO      Open Drain, Drives Low 
*  Pin_StimSel_DM_RES_UP     Resistive Pull Up 
*  Pin_StimSel_DM_RES_DWN    Resistive Pull Down 
*  Pin_StimSel_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Pin_StimSel_DM_DIG_HIZ    High Impedance Digital 
*  Pin_StimSel_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Pin_StimSel_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Pin_StimSel_0, mode);
	CyPins_SetPinDriveMode(Pin_StimSel_1, mode);
}


/*******************************************************************************
* Function Name: Pin_StimSel_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Pin_StimSel_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Pin_StimSel_Read(void) 
{
    return (Pin_StimSel_PS & Pin_StimSel_MASK) >> Pin_StimSel_SHIFT;
}


/*******************************************************************************
* Function Name: Pin_StimSel_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Pin_StimSel_ReadDataReg(void) 
{
    return (Pin_StimSel_DR & Pin_StimSel_MASK) >> Pin_StimSel_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Pin_StimSel_INTSTAT) 

    /*******************************************************************************
    * Function Name: Pin_StimSel_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Pin_StimSel_ClearInterrupt(void) 
    {
        return (Pin_StimSel_INTSTAT & Pin_StimSel_MASK) >> Pin_StimSel_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
