/*******************************************************************************
* File Name: SwClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_SwClock_H)
#define CY_CLOCK_SwClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void SwClock_Start(void) ;
void SwClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void SwClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void SwClock_StandbyPower(uint8 state) ;
void SwClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 SwClock_GetDividerRegister(void) ;
void SwClock_SetModeRegister(uint8 modeBitMask) ;
void SwClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 SwClock_GetModeRegister(void) ;
void SwClock_SetSourceRegister(uint8 clkSource) ;
uint8 SwClock_GetSourceRegister(void) ;
#if defined(SwClock__CFG3)
void SwClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 SwClock_GetPhaseRegister(void) ;
#endif /* defined(SwClock__CFG3) */

#define SwClock_Enable()                       SwClock_Start()
#define SwClock_Disable()                      SwClock_Stop()
#define SwClock_SetDivider(clkDivider)         SwClock_SetDividerRegister(clkDivider, 1u)
#define SwClock_SetDividerValue(clkDivider)    SwClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define SwClock_SetMode(clkMode)               SwClock_SetModeRegister(clkMode)
#define SwClock_SetSource(clkSource)           SwClock_SetSourceRegister(clkSource)
#if defined(SwClock__CFG3)
#define SwClock_SetPhase(clkPhase)             SwClock_SetPhaseRegister(clkPhase)
#define SwClock_SetPhaseValue(clkPhase)        SwClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(SwClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define SwClock_CLKEN              (* (reg8 *) SwClock__PM_ACT_CFG)
#define SwClock_CLKEN_PTR          ((reg8 *) SwClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define SwClock_CLKSTBY            (* (reg8 *) SwClock__PM_STBY_CFG)
#define SwClock_CLKSTBY_PTR        ((reg8 *) SwClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define SwClock_DIV_LSB            (* (reg8 *) SwClock__CFG0)
#define SwClock_DIV_LSB_PTR        ((reg8 *) SwClock__CFG0)
#define SwClock_DIV_PTR            ((reg16 *) SwClock__CFG0)

/* Clock MSB divider configuration register. */
#define SwClock_DIV_MSB            (* (reg8 *) SwClock__CFG1)
#define SwClock_DIV_MSB_PTR        ((reg8 *) SwClock__CFG1)

/* Mode and source configuration register */
#define SwClock_MOD_SRC            (* (reg8 *) SwClock__CFG2)
#define SwClock_MOD_SRC_PTR        ((reg8 *) SwClock__CFG2)

#if defined(SwClock__CFG3)
/* Analog clock phase configuration register */
#define SwClock_PHASE              (* (reg8 *) SwClock__CFG3)
#define SwClock_PHASE_PTR          ((reg8 *) SwClock__CFG3)
#endif /* defined(SwClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define SwClock_CLKEN_MASK         SwClock__PM_ACT_MSK
#define SwClock_CLKSTBY_MASK       SwClock__PM_STBY_MSK

/* CFG2 field masks */
#define SwClock_SRC_SEL_MSK        SwClock__CFG2_SRC_SEL_MASK
#define SwClock_MODE_MASK          (~(SwClock_SRC_SEL_MSK))

#if defined(SwClock__CFG3)
/* CFG3 phase mask */
#define SwClock_PHASE_MASK         SwClock__CFG3_PHASE_DLY_MASK
#endif /* defined(SwClock__CFG3) */

#endif /* CY_CLOCK_SwClock_H */


/* [] END OF FILE */
