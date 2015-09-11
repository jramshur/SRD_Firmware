/*******************************************************************************
* File Name: IDAC8_Sink.c
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


#include "IDAC8_Sink.h"

static IDAC8_Sink_backupStruct IDAC8_Sink_backup;


/*******************************************************************************
* Function Name: IDAC8_Sink_SaveConfig
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
void IDAC8_Sink_SaveConfig(void) 
{
    if (!((IDAC8_Sink_CR1 & IDAC8_Sink_SRC_MASK) == IDAC8_Sink_SRC_UDB))
    {
        IDAC8_Sink_backup.data_value = IDAC8_Sink_Data;
    }
}


/*******************************************************************************
* Function Name: IDAC8_Sink_RestoreConfig
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
void IDAC8_Sink_RestoreConfig(void) 
{
    if (!((IDAC8_Sink_CR1 & IDAC8_Sink_SRC_MASK) == IDAC8_Sink_SRC_UDB))
    {
        if((IDAC8_Sink_Strobe & IDAC8_Sink_STRB_MASK) == IDAC8_Sink_STRB_EN)
        {
            IDAC8_Sink_Strobe &= (uint8)(~IDAC8_Sink_STRB_MASK);
            IDAC8_Sink_Data = IDAC8_Sink_backup.data_value;
            IDAC8_Sink_Strobe |= IDAC8_Sink_STRB_EN;
        }
        else
        {
            IDAC8_Sink_Data = IDAC8_Sink_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: IDAC8_Sink_Sleep
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
*  IDAC8_Sink_backup.enableState: Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void IDAC8_Sink_Sleep(void) 
{
    if(IDAC8_Sink_ACT_PWR_EN == (IDAC8_Sink_PWRMGR & IDAC8_Sink_ACT_PWR_EN))
    {
        /* IDAC8 is enabled */
        IDAC8_Sink_backup.enableState = 1u;
    }
    else
    {
        /* IDAC8 is disabled */
        IDAC8_Sink_backup.enableState = 0u;
    }

    IDAC8_Sink_Stop();
    IDAC8_Sink_SaveConfig();
}


/*******************************************************************************
* Function Name: IDAC8_Sink_Wakeup
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
*  IDAC8_Sink_backup.enableState: Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void IDAC8_Sink_Wakeup(void) 
{
    IDAC8_Sink_RestoreConfig();
    
    if(IDAC8_Sink_backup.enableState == 1u)
    {
        /* Enable IDAC8's operation */
        IDAC8_Sink_Enable();
        
        /* Set the data register */
        IDAC8_Sink_SetValue(IDAC8_Sink_Data);
    } /* Do nothing if IDAC8 was disabled before */    
}


/* [] END OF FILE */
