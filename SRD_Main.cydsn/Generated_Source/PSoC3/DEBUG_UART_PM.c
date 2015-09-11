/*******************************************************************************
* File Name: DEBUG_UART_PM.c
* Version 2.30
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DEBUG_UART.h"


/***************************************
* Local data allocation
***************************************/

static DEBUG_UART_BACKUP_STRUCT  DEBUG_UART_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: DEBUG_UART_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  DEBUG_UART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void DEBUG_UART_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(DEBUG_UART_CONTROL_REG_REMOVED == 0u)
            DEBUG_UART_backup.cr = DEBUG_UART_CONTROL_REG;
        #endif /* End DEBUG_UART_CONTROL_REG_REMOVED */

        #if( (DEBUG_UART_RX_ENABLED) || (DEBUG_UART_HD_ENABLED) )
            DEBUG_UART_backup.rx_period = DEBUG_UART_RXBITCTR_PERIOD_REG;
            DEBUG_UART_backup.rx_mask = DEBUG_UART_RXSTATUS_MASK_REG;
            #if (DEBUG_UART_RXHW_ADDRESS_ENABLED)
                DEBUG_UART_backup.rx_addr1 = DEBUG_UART_RXADDRESS1_REG;
                DEBUG_UART_backup.rx_addr2 = DEBUG_UART_RXADDRESS2_REG;
            #endif /* End DEBUG_UART_RXHW_ADDRESS_ENABLED */
        #endif /* End DEBUG_UART_RX_ENABLED | DEBUG_UART_HD_ENABLED*/

        #if(DEBUG_UART_TX_ENABLED)
            #if(DEBUG_UART_TXCLKGEN_DP)
                DEBUG_UART_backup.tx_clk_ctr = DEBUG_UART_TXBITCLKGEN_CTR_REG;
                DEBUG_UART_backup.tx_clk_compl = DEBUG_UART_TXBITCLKTX_COMPLETE_REG;
            #else
                DEBUG_UART_backup.tx_period = DEBUG_UART_TXBITCTR_PERIOD_REG;
            #endif /*End DEBUG_UART_TXCLKGEN_DP */
            DEBUG_UART_backup.tx_mask = DEBUG_UART_TXSTATUS_MASK_REG;
        #endif /*End DEBUG_UART_TX_ENABLED */


    #else /* CY_UDB_V1 */

        #if(DEBUG_UART_CONTROL_REG_REMOVED == 0u)
            DEBUG_UART_backup.cr = DEBUG_UART_CONTROL_REG;
        #endif /* End DEBUG_UART_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: DEBUG_UART_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  DEBUG_UART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void DEBUG_UART_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(DEBUG_UART_CONTROL_REG_REMOVED == 0u)
            DEBUG_UART_CONTROL_REG = DEBUG_UART_backup.cr;
        #endif /* End DEBUG_UART_CONTROL_REG_REMOVED */

        #if( (DEBUG_UART_RX_ENABLED) || (DEBUG_UART_HD_ENABLED) )
            DEBUG_UART_RXBITCTR_PERIOD_REG = DEBUG_UART_backup.rx_period;
            DEBUG_UART_RXSTATUS_MASK_REG = DEBUG_UART_backup.rx_mask;
            #if (DEBUG_UART_RXHW_ADDRESS_ENABLED)
                DEBUG_UART_RXADDRESS1_REG = DEBUG_UART_backup.rx_addr1;
                DEBUG_UART_RXADDRESS2_REG = DEBUG_UART_backup.rx_addr2;
            #endif /* End DEBUG_UART_RXHW_ADDRESS_ENABLED */
        #endif  /* End (DEBUG_UART_RX_ENABLED) || (DEBUG_UART_HD_ENABLED) */

        #if(DEBUG_UART_TX_ENABLED)
            #if(DEBUG_UART_TXCLKGEN_DP)
                DEBUG_UART_TXBITCLKGEN_CTR_REG = DEBUG_UART_backup.tx_clk_ctr;
                DEBUG_UART_TXBITCLKTX_COMPLETE_REG = DEBUG_UART_backup.tx_clk_compl;
            #else
                DEBUG_UART_TXBITCTR_PERIOD_REG = DEBUG_UART_backup.tx_period;
            #endif /*End DEBUG_UART_TXCLKGEN_DP */
            DEBUG_UART_TXSTATUS_MASK_REG = DEBUG_UART_backup.tx_mask;
        #endif /*End DEBUG_UART_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(DEBUG_UART_CONTROL_REG_REMOVED == 0u)
            DEBUG_UART_CONTROL_REG = DEBUG_UART_backup.cr;
        #endif /* End DEBUG_UART_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: DEBUG_UART_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration. Should be called
*  just prior to entering sleep.
*
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  DEBUG_UART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void DEBUG_UART_Sleep(void)
{

    #if(DEBUG_UART_RX_ENABLED || DEBUG_UART_HD_ENABLED)
        if((DEBUG_UART_RXSTATUS_ACTL_REG  & DEBUG_UART_INT_ENABLE) != 0u)
        {
            DEBUG_UART_backup.enableState = 1u;
        }
        else
        {
            DEBUG_UART_backup.enableState = 0u;
        }
    #else
        if((DEBUG_UART_TXSTATUS_ACTL_REG  & DEBUG_UART_INT_ENABLE) !=0u)
        {
            DEBUG_UART_backup.enableState = 1u;
        }
        else
        {
            DEBUG_UART_backup.enableState = 0u;
        }
    #endif /* End DEBUG_UART_RX_ENABLED || DEBUG_UART_HD_ENABLED*/

    DEBUG_UART_Stop();
    DEBUG_UART_SaveConfig();
}


/*******************************************************************************
* Function Name: DEBUG_UART_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  DEBUG_UART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void DEBUG_UART_Wakeup(void)
{
    DEBUG_UART_RestoreConfig();
    #if( (DEBUG_UART_RX_ENABLED) || (DEBUG_UART_HD_ENABLED) )
        DEBUG_UART_ClearRxBuffer();
    #endif /* End (DEBUG_UART_RX_ENABLED) || (DEBUG_UART_HD_ENABLED) */
    #if(DEBUG_UART_TX_ENABLED || DEBUG_UART_HD_ENABLED)
        DEBUG_UART_ClearTxBuffer();
    #endif /* End DEBUG_UART_TX_ENABLED || DEBUG_UART_HD_ENABLED */

    if(DEBUG_UART_backup.enableState != 0u)
    {
        DEBUG_UART_Enable();
    }
}


/* [] END OF FILE */
