/*******************************************************************************
* File Name: pin_vdac.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "pin_vdac.h"


/*******************************************************************************
* Function Name: pin_vdac_Write
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
void pin_vdac_Write(uint8 value) 
{
    uint8 staticBits = (pin_vdac_DR & (uint8)(~pin_vdac_MASK));
    pin_vdac_DR = staticBits | ((uint8)(value << pin_vdac_SHIFT) & pin_vdac_MASK);
}


/*******************************************************************************
* Function Name: pin_vdac_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void pin_vdac_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(pin_vdac_0, mode);
}


/*******************************************************************************
* Function Name: pin_vdac_Read
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
*  Macro pin_vdac_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 pin_vdac_Read(void) 
{
    return (pin_vdac_PS & pin_vdac_MASK) >> pin_vdac_SHIFT;
}


/*******************************************************************************
* Function Name: pin_vdac_ReadDataReg
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
uint8 pin_vdac_ReadDataReg(void) 
{
    return (pin_vdac_DR & pin_vdac_MASK) >> pin_vdac_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(pin_vdac_INTSTAT) 

    /*******************************************************************************
    * Function Name: pin_vdac_ClearInterrupt
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
    uint8 pin_vdac_ClearInterrupt(void) 
    {
        return (pin_vdac_INTSTAT & pin_vdac_MASK) >> pin_vdac_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
