/*******************************************************************************
* File Name: Waveform.c  
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
#include "Waveform.h"


/*******************************************************************************
* Function Name: Waveform_Write
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
void Waveform_Write(uint8 value) 
{
    uint8 staticBits = (Waveform_DR & (uint8)(~Waveform_MASK));
    Waveform_DR = staticBits | ((uint8)(value << Waveform_SHIFT) & Waveform_MASK);
}


/*******************************************************************************
* Function Name: Waveform_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Waveform_DM_STRONG     Strong Drive 
*  Waveform_DM_OD_HI      Open Drain, Drives High 
*  Waveform_DM_OD_LO      Open Drain, Drives Low 
*  Waveform_DM_RES_UP     Resistive Pull Up 
*  Waveform_DM_RES_DWN    Resistive Pull Down 
*  Waveform_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Waveform_DM_DIG_HIZ    High Impedance Digital 
*  Waveform_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Waveform_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Waveform_0, mode);
}


/*******************************************************************************
* Function Name: Waveform_Read
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
*  Macro Waveform_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Waveform_Read(void) 
{
    return (Waveform_PS & Waveform_MASK) >> Waveform_SHIFT;
}


/*******************************************************************************
* Function Name: Waveform_ReadDataReg
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
uint8 Waveform_ReadDataReg(void) 
{
    return (Waveform_DR & Waveform_MASK) >> Waveform_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Waveform_INTSTAT) 

    /*******************************************************************************
    * Function Name: Waveform_ClearInterrupt
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
    uint8 Waveform_ClearInterrupt(void) 
    {
        return (Waveform_INTSTAT & Waveform_MASK) >> Waveform_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
