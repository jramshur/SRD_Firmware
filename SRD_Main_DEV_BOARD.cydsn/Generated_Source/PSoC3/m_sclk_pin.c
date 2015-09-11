/*******************************************************************************
* File Name: m_sclk_pin.c  
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
#include "m_sclk_pin.h"


/*******************************************************************************
* Function Name: m_sclk_pin_Write
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
void m_sclk_pin_Write(uint8 value) 
{
    uint8 staticBits = (m_sclk_pin_DR & (uint8)(~m_sclk_pin_MASK));
    m_sclk_pin_DR = staticBits | ((uint8)(value << m_sclk_pin_SHIFT) & m_sclk_pin_MASK);
}


/*******************************************************************************
* Function Name: m_sclk_pin_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  m_sclk_pin_DM_STRONG     Strong Drive 
*  m_sclk_pin_DM_OD_HI      Open Drain, Drives High 
*  m_sclk_pin_DM_OD_LO      Open Drain, Drives Low 
*  m_sclk_pin_DM_RES_UP     Resistive Pull Up 
*  m_sclk_pin_DM_RES_DWN    Resistive Pull Down 
*  m_sclk_pin_DM_RES_UPDWN  Resistive Pull Up/Down 
*  m_sclk_pin_DM_DIG_HIZ    High Impedance Digital 
*  m_sclk_pin_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void m_sclk_pin_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(m_sclk_pin_0, mode);
}


/*******************************************************************************
* Function Name: m_sclk_pin_Read
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
*  Macro m_sclk_pin_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 m_sclk_pin_Read(void) 
{
    return (m_sclk_pin_PS & m_sclk_pin_MASK) >> m_sclk_pin_SHIFT;
}


/*******************************************************************************
* Function Name: m_sclk_pin_ReadDataReg
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
uint8 m_sclk_pin_ReadDataReg(void) 
{
    return (m_sclk_pin_DR & m_sclk_pin_MASK) >> m_sclk_pin_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(m_sclk_pin_INTSTAT) 

    /*******************************************************************************
    * Function Name: m_sclk_pin_ClearInterrupt
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
    uint8 m_sclk_pin_ClearInterrupt(void) 
    {
        return (m_sclk_pin_INTSTAT & m_sclk_pin_MASK) >> m_sclk_pin_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
