/*******************************************************************************
* File Name: pin_DAC2.c  
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
#include "pin_DAC2.h"


/*******************************************************************************
* Function Name: pin_DAC2_Write
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
void pin_DAC2_Write(uint8 value) 
{
    uint8 staticBits = (pin_DAC2_DR & (uint8)(~pin_DAC2_MASK));
    pin_DAC2_DR = staticBits | ((uint8)(value << pin_DAC2_SHIFT) & pin_DAC2_MASK);
}


/*******************************************************************************
* Function Name: pin_DAC2_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  pin_DAC2_DM_STRONG     Strong Drive 
*  pin_DAC2_DM_OD_HI      Open Drain, Drives High 
*  pin_DAC2_DM_OD_LO      Open Drain, Drives Low 
*  pin_DAC2_DM_RES_UP     Resistive Pull Up 
*  pin_DAC2_DM_RES_DWN    Resistive Pull Down 
*  pin_DAC2_DM_RES_UPDWN  Resistive Pull Up/Down 
*  pin_DAC2_DM_DIG_HIZ    High Impedance Digital 
*  pin_DAC2_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void pin_DAC2_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(pin_DAC2_0, mode);
}


/*******************************************************************************
* Function Name: pin_DAC2_Read
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
*  Macro pin_DAC2_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 pin_DAC2_Read(void) 
{
    return (pin_DAC2_PS & pin_DAC2_MASK) >> pin_DAC2_SHIFT;
}


/*******************************************************************************
* Function Name: pin_DAC2_ReadDataReg
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
uint8 pin_DAC2_ReadDataReg(void) 
{
    return (pin_DAC2_DR & pin_DAC2_MASK) >> pin_DAC2_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(pin_DAC2_INTSTAT) 

    /*******************************************************************************
    * Function Name: pin_DAC2_ClearInterrupt
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
    uint8 pin_DAC2_ClearInterrupt(void) 
    {
        return (pin_DAC2_INTSTAT & pin_DAC2_MASK) >> pin_DAC2_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
