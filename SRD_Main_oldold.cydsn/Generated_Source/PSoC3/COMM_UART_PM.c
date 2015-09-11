/*******************************************************************************
* File Name: COMM_UART_PM.c
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

#include "COMM_UART.h"


/***************************************
* Local data allocation
***************************************/

static COMM_UART_BACKUP_STRUCT  COMM_UART_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: COMM_UART_SaveConfig
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
*  COMM_UART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void COMM_UART_SaveConfig(void)
{
    #if (CY_UDB_V0)

        #if(COMM_UART_CONTROL_REG_REMOVED == 0u)
            COMM_UART_backup.cr = COMM_UART_CONTROL_REG;
        #endif /* End COMM_UART_CONTROL_REG_REMOVED */

        #if( (COMM_UART_RX_ENABLED) || (COMM_UART_HD_ENABLED) )
            COMM_UART_backup.rx_period = COMM_UART_RXBITCTR_PERIOD_REG;
            COMM_UART_backup.rx_mask = COMM_UART_RXSTATUS_MASK_REG;
            #if (COMM_UART_RXHW_ADDRESS_ENABLED)
                COMM_UART_backup.rx_addr1 = COMM_UART_RXADDRESS1_REG;
                COMM_UART_backup.rx_addr2 = COMM_UART_RXADDRESS2_REG;
            #endif /* End COMM_UART_RXHW_ADDRESS_ENABLED */
        #endif /* End COMM_UART_RX_ENABLED | COMM_UART_HD_ENABLED*/

        #if(COMM_UART_TX_ENABLED)
            #if(COMM_UART_TXCLKGEN_DP)
                COMM_UART_backup.tx_clk_ctr = COMM_UART_TXBITCLKGEN_CTR_REG;
                COMM_UART_backup.tx_clk_compl = COMM_UART_TXBITCLKTX_COMPLETE_REG;
            #else
                COMM_UART_backup.tx_period = COMM_UART_TXBITCTR_PERIOD_REG;
            #endif /*End COMM_UART_TXCLKGEN_DP */
            COMM_UART_backup.tx_mask = COMM_UART_TXSTATUS_MASK_REG;
        #endif /*End COMM_UART_TX_ENABLED */


    #else /* CY_UDB_V1 */

        #if(COMM_UART_CONTROL_REG_REMOVED == 0u)
            COMM_UART_backup.cr = COMM_UART_CONTROL_REG;
        #endif /* End COMM_UART_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: COMM_UART_RestoreConfig
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
*  COMM_UART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void COMM_UART_RestoreConfig(void)
{

    #if (CY_UDB_V0)

        #if(COMM_UART_CONTROL_REG_REMOVED == 0u)
            COMM_UART_CONTROL_REG = COMM_UART_backup.cr;
        #endif /* End COMM_UART_CONTROL_REG_REMOVED */

        #if( (COMM_UART_RX_ENABLED) || (COMM_UART_HD_ENABLED) )
            COMM_UART_RXBITCTR_PERIOD_REG = COMM_UART_backup.rx_period;
            COMM_UART_RXSTATUS_MASK_REG = COMM_UART_backup.rx_mask;
            #if (COMM_UART_RXHW_ADDRESS_ENABLED)
                COMM_UART_RXADDRESS1_REG = COMM_UART_backup.rx_addr1;
                COMM_UART_RXADDRESS2_REG = COMM_UART_backup.rx_addr2;
            #endif /* End COMM_UART_RXHW_ADDRESS_ENABLED */
        #endif  /* End (COMM_UART_RX_ENABLED) || (COMM_UART_HD_ENABLED) */

        #if(COMM_UART_TX_ENABLED)
            #if(COMM_UART_TXCLKGEN_DP)
                COMM_UART_TXBITCLKGEN_CTR_REG = COMM_UART_backup.tx_clk_ctr;
                COMM_UART_TXBITCLKTX_COMPLETE_REG = COMM_UART_backup.tx_clk_compl;
            #else
                COMM_UART_TXBITCTR_PERIOD_REG = COMM_UART_backup.tx_period;
            #endif /*End COMM_UART_TXCLKGEN_DP */
            COMM_UART_TXSTATUS_MASK_REG = COMM_UART_backup.tx_mask;
        #endif /*End COMM_UART_TX_ENABLED */

    #else /* CY_UDB_V1 */

        #if(COMM_UART_CONTROL_REG_REMOVED == 0u)
            COMM_UART_CONTROL_REG = COMM_UART_backup.cr;
        #endif /* End COMM_UART_CONTROL_REG_REMOVED */

    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: COMM_UART_Sleep
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
*  COMM_UART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void COMM_UART_Sleep(void)
{

    #if(COMM_UART_RX_ENABLED || COMM_UART_HD_ENABLED)
        if((COMM_UART_RXSTATUS_ACTL_REG  & COMM_UART_INT_ENABLE) != 0u)
        {
            COMM_UART_backup.enableState = 1u;
        }
        else
        {
            COMM_UART_backup.enableState = 0u;
        }
    #else
        if((COMM_UART_TXSTATUS_ACTL_REG  & COMM_UART_INT_ENABLE) !=0u)
        {
            COMM_UART_backup.enableState = 1u;
        }
        else
        {
            COMM_UART_backup.enableState = 0u;
        }
    #endif /* End COMM_UART_RX_ENABLED || COMM_UART_HD_ENABLED*/

    COMM_UART_Stop();
    COMM_UART_SaveConfig();
}


/*******************************************************************************
* Function Name: COMM_UART_Wakeup
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
*  COMM_UART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void COMM_UART_Wakeup(void)
{
    COMM_UART_RestoreConfig();
    #if( (COMM_UART_RX_ENABLED) || (COMM_UART_HD_ENABLED) )
        COMM_UART_ClearRxBuffer();
    #endif /* End (COMM_UART_RX_ENABLED) || (COMM_UART_HD_ENABLED) */
    #if(COMM_UART_TX_ENABLED || COMM_UART_HD_ENABLED)
        COMM_UART_ClearTxBuffer();
    #endif /* End COMM_UART_TX_ENABLED || COMM_UART_HD_ENABLED */

    if(COMM_UART_backup.enableState != 0u)
    {
        COMM_UART_Enable();
    }
}


/* [] END OF FILE */
