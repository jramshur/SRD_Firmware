/*******************************************************************************
* File Name: Tick_Timer_PM.c
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

#include "Tick_Timer.h"
static Tick_Timer_backupStruct Tick_Timer_backup;


/*******************************************************************************
* Function Name: Tick_Timer_SaveConfig
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
*  Tick_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Tick_Timer_SaveConfig(void) 
{
    #if (!Tick_Timer_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            Tick_Timer_backup.TimerUdb = Tick_Timer_ReadCounter();
            Tick_Timer_backup.TimerPeriod = Tick_Timer_ReadPeriod();
            Tick_Timer_backup.InterruptMaskValue = Tick_Timer_STATUS_MASK;
            #if (Tick_Timer_UsingHWCaptureCounter)
                Tick_Timer_backup.TimerCaptureCounter = Tick_Timer_ReadCaptureCount();
            #endif /* Backup the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Backup the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            Tick_Timer_backup.TimerUdb = Tick_Timer_ReadCounter();
            Tick_Timer_backup.InterruptMaskValue = Tick_Timer_STATUS_MASK;
            #if (Tick_Timer_UsingHWCaptureCounter)
                Tick_Timer_backup.TimerCaptureCounter = Tick_Timer_ReadCaptureCount();
            #endif /* Back Up capture counter register  */
        #endif /* Backup non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!Tick_Timer_ControlRegRemoved)
            Tick_Timer_backup.TimerControlRegister = Tick_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Tick_Timer_RestoreConfig
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
*  Tick_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Tick_Timer_RestoreConfig(void) 
{   
    #if (!Tick_Timer_UsingFixedFunction)
        /* Restore the UDB non-rentention registers for CY_UDB_V0 */
        #if (CY_UDB_V0)
            /* Interrupt State Backup for Critical Region*/
            uint8 Tick_Timer_interruptState;

            Tick_Timer_WriteCounter(Tick_Timer_backup.TimerUdb);
            Tick_Timer_WritePeriod(Tick_Timer_backup.TimerPeriod);
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Tick_Timer_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            Tick_Timer_STATUS_AUX_CTRL |= Tick_Timer_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(Tick_Timer_interruptState);
            Tick_Timer_STATUS_MASK =Tick_Timer_backup.InterruptMaskValue;
            #if (Tick_Timer_UsingHWCaptureCounter)
                Tick_Timer_SetCaptureCount(Tick_Timer_backup.TimerCaptureCounter);
            #endif /* Restore the UDB non-rentention register capture counter for CY_UDB_V0 */
        #endif /* Restore the UDB non-rentention registers for CY_UDB_V0 */

        #if (CY_UDB_V1)
            Tick_Timer_WriteCounter(Tick_Timer_backup.TimerUdb);
            Tick_Timer_STATUS_MASK =Tick_Timer_backup.InterruptMaskValue;
            #if (Tick_Timer_UsingHWCaptureCounter)
                Tick_Timer_SetCaptureCount(Tick_Timer_backup.TimerCaptureCounter);
            #endif /* Restore Capture counter register*/
        #endif /* Restore up non retention registers, interrupt mask and capture counter for CY_UDB_V1 */

        #if(!Tick_Timer_ControlRegRemoved)
            Tick_Timer_WriteControlRegister(Tick_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Tick_Timer_Sleep
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
*  Tick_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Tick_Timer_Sleep(void) 
{
    #if(!Tick_Timer_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Tick_Timer_CTRL_ENABLE == (Tick_Timer_CONTROL & Tick_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Tick_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Tick_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Tick_Timer_Stop();
    Tick_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Tick_Timer_Wakeup
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
*  Tick_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Tick_Timer_Wakeup(void) 
{
    Tick_Timer_RestoreConfig();
    #if(!Tick_Timer_ControlRegRemoved)
        if(Tick_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Tick_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
