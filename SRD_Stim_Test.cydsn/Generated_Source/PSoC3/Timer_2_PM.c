/*******************************************************************************
* File Name: Timer_2_PM.c  
* Version 2.0
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.  
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_2.h"
static Timer_2_backupStruct Timer_2_backup;

/*******************************************************************************
* Function Name: Timer_2_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  Timer_2_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
* Reentrant:
*    No
*
*******************************************************************************/
void Timer_2_SaveConfig(void)
{   
    #if (!Timer_2_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC3 ES2 and PSoC5 ES1*/
        #if (Timer_2_PSOC3_ES2 || Timer_2_PSOC5_ES1)
            Timer_2_backup.TimerUdb = Timer_2_ReadCounter();
            Timer_2_backup.TimerPeriod = Timer_2_ReadPeriod();
            Timer_2_backup.InterruptMaskValue = Timer_2_STATUS_MASK;
            #if (Timer_2_UsingHWCaptureCounter)
                Timer_2_backup.TimerCaptureCounter = Timer_2_ReadCaptureCount();        
            #endif
        #endif
        
        #if (Timer_2_PSOC3_ES3 || Timer_2_PSOC5_ES2)
            Timer_2_backup.TimerUdb = Timer_2_ReadCounter();
            Timer_2_backup.InterruptMaskValue = Timer_2_STATUS_MASK;
            #if (Timer_2_UsingHWCaptureCounter)
                Timer_2_backup.TimerCaptureCounter = Timer_2_ReadCaptureCount();        
            #endif
        #endif
        
        #if(!Timer_2_ControlRegRemoved)
            Timer_2_backup.TimerControlRegister = Timer_2_ReadControlRegister();
        #endif
    #endif
}

/*******************************************************************************
* Function Name: Timer_2_RestoreConfig
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
* Global variables:
*  Timer_2_backup:  Variables of this global structure are used to restore 
*  the values of non retention registers on wakeup from sleep mode.
*
* Reentrant:
*    Yes
*
*******************************************************************************/
void Timer_2_RestoreConfig(void) 
{
    #if (!Timer_2_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC3 ES2 and PSoC5 ES1*/
        #if (Timer_2_PSOC3_ES2 || Timer_2_PSOC5_ES1)
            Timer_2_WriteCounter(Timer_2_backup.TimerUdb);
            Timer_2_WritePeriod(Timer_2_backup.TimerPeriod);
            Timer_2_STATUS_MASK =Timer_2_backup.InterruptMaskValue;
            #if (Timer_2_UsingHWCaptureCounter)
                Timer_2_SetCaptureCount(Timer_2_backup.TimerCaptureCounter);        
            #endif
        #endif
        
        #if (Timer_2_PSOC3_ES3 || Timer_2_PSOC5_ES2)
            Timer_2_WriteCounter(Timer_2_backup.TimerUdb);
            Timer_2_STATUS_MASK =Timer_2_backup.InterruptMaskValue;
            #if (Timer_2_UsingHWCaptureCounter)
                Timer_2_SetCaptureCount(Timer_2_backup.TimerCaptureCounter);           
            #endif
        #endif
        
        #if(!Timer_2_ControlRegRemoved)
            Timer_2_WriteControlRegister(Timer_2_backup.TimerControlRegister);
        #endif
    #endif
}


/*******************************************************************************
* Function Name: Timer_2_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Timer_2_backup.TimerEnableState:  Is modified depending on the enable state
*  of the block before entering sleep mode.
*
* Reentrant:
*    No
*
*******************************************************************************/
void Timer_2_Sleep(void)
{
    #if(!Timer_2_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Timer_2_CTRL_ENABLE == (Timer_2_CONTROL & Timer_2_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_2_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_2_backup.TimerEnableState = 0u;
        }
    #endif
    Timer_2_Stop();
    Timer_2_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_2_Wakeup
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
*  Timer_2_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
* Reentrant:
*    Yes
*
*******************************************************************************/
void Timer_2_Wakeup(void) 
{
    Timer_2_RestoreConfig();
    #if(!Timer_2_ControlRegRemoved)
        if(Timer_2_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_2_Enable();
        } /* Do nothing if Timer was disabled before */ 
    #endif
}


/* [] END OF FILE */
