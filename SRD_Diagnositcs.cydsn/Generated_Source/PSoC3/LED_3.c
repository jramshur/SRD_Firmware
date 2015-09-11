/*******************************************************************************
* File Name: LED_3.c  
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
#include "LED_3.h"


/*******************************************************************************
* Function Name: LED_3_Write
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
void LED_3_Write(uint8 value) 
{
    uint8 staticBits = (LED_3_DR & (uint8)(~LED_3_MASK));
    LED_3_DR = staticBits | ((uint8)(value << LED_3_SHIFT) & LED_3_MASK);
}


/*******************************************************************************
* Function Name: LED_3_SetDriveMode
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
void LED_3_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(LED_3_0, mode);
}


/*******************************************************************************
* Function Name: LED_3_Read
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
*  Macro LED_3_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 LED_3_Read(void) 
{
    return (LED_3_PS & LED_3_MASK) >> LED_3_SHIFT;
}


/*******************************************************************************
* Function Name: LED_3_ReadDataReg
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
uint8 LED_3_ReadDataReg(void) 
{
    return (LED_3_DR & LED_3_MASK) >> LED_3_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(LED_3_INTSTAT) 

    /*******************************************************************************
    * Function Name: LED_3_ClearInterrupt
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
    uint8 LED_3_ClearInterrupt(void) 
    {
        return (LED_3_INTSTAT & LED_3_MASK) >> LED_3_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
