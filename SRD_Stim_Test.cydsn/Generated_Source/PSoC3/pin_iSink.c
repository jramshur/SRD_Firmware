/*******************************************************************************
* File Name: pin_iSink.c  
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
#include "pin_iSink.h"


/*******************************************************************************
* Function Name: pin_iSink_Write
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
void pin_iSink_Write(uint8 value) 
{
    uint8 staticBits = (pin_iSink_DR & (uint8)(~pin_iSink_MASK));
    pin_iSink_DR = staticBits | ((uint8)(value << pin_iSink_SHIFT) & pin_iSink_MASK);
}


/*******************************************************************************
* Function Name: pin_iSink_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  pin_iSink_DM_STRONG     Strong Drive 
*  pin_iSink_DM_OD_HI      Open Drain, Drives High 
*  pin_iSink_DM_OD_LO      Open Drain, Drives Low 
*  pin_iSink_DM_RES_UP     Resistive Pull Up 
*  pin_iSink_DM_RES_DWN    Resistive Pull Down 
*  pin_iSink_DM_RES_UPDWN  Resistive Pull Up/Down 
*  pin_iSink_DM_DIG_HIZ    High Impedance Digital 
*  pin_iSink_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void pin_iSink_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(pin_iSink_0, mode);
}


/*******************************************************************************
* Function Name: pin_iSink_Read
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
*  Macro pin_iSink_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 pin_iSink_Read(void) 
{
    return (pin_iSink_PS & pin_iSink_MASK) >> pin_iSink_SHIFT;
}


/*******************************************************************************
* Function Name: pin_iSink_ReadDataReg
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
uint8 pin_iSink_ReadDataReg(void) 
{
    return (pin_iSink_DR & pin_iSink_MASK) >> pin_iSink_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(pin_iSink_INTSTAT) 

    /*******************************************************************************
    * Function Name: pin_iSink_ClearInterrupt
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
    uint8 pin_iSink_ClearInterrupt(void) 
    {
        return (pin_iSink_INTSTAT & pin_iSink_MASK) >> pin_iSink_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
