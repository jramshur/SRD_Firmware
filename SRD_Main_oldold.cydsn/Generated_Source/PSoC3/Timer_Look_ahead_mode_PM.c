/*******************************************************************************
* File Name: Timer_Look_ahead_mode_PM.c
* Version 2.50
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_Look_ahead_mode.h"
static Timer_Look_ahead_mode_backupStruct Timer_Look_ahead_mode_backup;


/*******************************************************************************
* Function Name: Timer_Look_ahead_mode_SaveConfig
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
*  Timer_Look_ahead_mode_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Look_ahead_mode_SaveConfig(void) 
{
    #if (!Timer_Look_ahead_mode_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            Timer_Look_ahead_mode_backup.TimerUdb = Timer_Look_ahead_mode_ReadCounter();
            Timer_Look_ahead_mode_backup.TimerPeriod = Timer_Look_ahead_mode_ReadPeriod();
            Timer_Look_ahead_mode_backup.InterruptMaskValue = Timer_Look_ahead_mode_STATUS_MASK;
            #if (Timer_Look_ahead_mode_UsingHWCaptureCounter)
                Timer_Look_ahead_mode_backup.TimerCaptureCounter = Timer_Look_ahead_mode_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Backup the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            Timer_Look_ahead_mode_backup.TimerUdb = Timer_Look_ahead_mode_ReadCounter();
            Timer_Look_ahead_mode_backup.InterruptMaskValue = Timer_Look_ahead_mode_STATUS_MASK;
            #if (Timer_Look_ahead_mode_UsingHWCaptureCounter)
                Timer_Look_ahead_mode_backup.TimerCaptureCounter = Timer_Look_ahead_mode_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!Timer_Look_ahead_mode_ControlRegRemoved)
            Timer_Look_ahead_mode_backup.TimerControlRegister = Timer_Look_ahead_mode_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Look_ahead_mode_RestoreConfig
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
*  Timer_Look_ahead_mode_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Look_ahead_mode_RestoreConfig(void) 
{   
    #if (!Timer_Look_ahead_mode_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            /* Interrupt State Backup for Critical Region*/
            uint8 Timer_Look_ahead_mode_interruptState;

            Timer_Look_ahead_mode_WriteCounter(Timer_Look_ahead_mode_backup.TimerUdb);
            Timer_Look_ahead_mode_WritePeriod(Timer_Look_ahead_mode_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Timer_Look_ahead_mode_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            Timer_Look_ahead_mode_STATUS_AUX_CTRL |= Timer_Look_ahead_mode_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(Timer_Look_ahead_mode_interruptState);
            Timer_Look_ahead_mode_STATUS_MASK =Timer_Look_ahead_mode_backup.InterruptMaskValue;
            #if (Timer_Look_ahead_mode_UsingHWCaptureCounter)
                Timer_Look_ahead_mode_SetCaptureCount(Timer_Look_ahead_mode_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Restore the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            Timer_Look_ahead_mode_WriteCounter(Timer_Look_ahead_mode_backup.TimerUdb);
            Timer_Look_ahead_mode_STATUS_MASK =Timer_Look_ahead_mode_backup.InterruptMaskValue;
            #if (Timer_Look_ahead_mode_UsingHWCaptureCounter)
                Timer_Look_ahead_mode_SetCaptureCount(Timer_Look_ahead_mode_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!Timer_Look_ahead_mode_ControlRegRemoved)
            Timer_Look_ahead_mode_WriteControlRegister(Timer_Look_ahead_mode_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Look_ahead_mode_Sleep
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
*  Timer_Look_ahead_mode_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Look_ahead_mode_Sleep(void) 
{
    #if(!Timer_Look_ahead_mode_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Timer_Look_ahead_mode_CTRL_ENABLE == (Timer_Look_ahead_mode_CONTROL & Timer_Look_ahead_mode_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Look_ahead_mode_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Look_ahead_mode_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Look_ahead_mode_Stop();
    Timer_Look_ahead_mode_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Look_ahead_mode_Wakeup
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
*  Timer_Look_ahead_mode_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Look_ahead_mode_Wakeup(void) 
{
    Timer_Look_ahead_mode_RestoreConfig();
    #if(!Timer_Look_ahead_mode_ControlRegRemoved)
        if(Timer_Look_ahead_mode_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Look_ahead_mode_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
