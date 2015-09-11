/*******************************************************************************
* File Name: IDAC8_Source.c
* Version 2.0
*
* Description:
*  This file provides the power management source code to API for the
*  IDAC8.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include "IDAC8_Source.h"

static IDAC8_Source_backupStruct IDAC8_Source_backup;


/*******************************************************************************
* Function Name: IDAC8_Source_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void IDAC8_Source_SaveConfig(void) 
{
    if (!((IDAC8_Source_CR1 & IDAC8_Source_SRC_MASK) == IDAC8_Source_SRC_UDB))
    {
        IDAC8_Source_backup.data_value = IDAC8_Source_Data;
    }
}


/*******************************************************************************
* Function Name: IDAC8_Source_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void IDAC8_Source_RestoreConfig(void) 
{
    if (!((IDAC8_Source_CR1 & IDAC8_Source_SRC_MASK) == IDAC8_Source_SRC_UDB))
    {
        if((IDAC8_Source_Strobe & IDAC8_Source_STRB_MASK) == IDAC8_Source_STRB_EN)
        {
            IDAC8_Source_Strobe &= (uint8)(~IDAC8_Source_STRB_MASK);
            IDAC8_Source_Data = IDAC8_Source_backup.data_value;
            IDAC8_Source_Strobe |= IDAC8_Source_STRB_EN;
        }
        else
        {
            IDAC8_Source_Data = IDAC8_Source_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: IDAC8_Source_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
* Global variables:
*  IDAC8_Source_backup.enableState: Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void IDAC8_Source_Sleep(void) 
{
    if(IDAC8_Source_ACT_PWR_EN == (IDAC8_Source_PWRMGR & IDAC8_Source_ACT_PWR_EN))
    {
        /* IDAC8 is enabled */
        IDAC8_Source_backup.enableState = 1u;
    }
    else
    {
        /* IDAC8 is disabled */
        IDAC8_Source_backup.enableState = 0u;
    }

    IDAC8_Source_Stop();
    IDAC8_Source_SaveConfig();
}


/*******************************************************************************
* Function Name: IDAC8_Source_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  IDAC8_Source_backup.enableState: Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void IDAC8_Source_Wakeup(void) 
{
    IDAC8_Source_RestoreConfig();
    
    if(IDAC8_Source_backup.enableState == 1u)
    {
        /* Enable IDAC8's operation */
        IDAC8_Source_Enable();
        
        /* Set the data register */
        IDAC8_Source_SetValue(IDAC8_Source_Data);
    } /* Do nothing if IDAC8 was disabled before */    
}


/* [] END OF FILE */
