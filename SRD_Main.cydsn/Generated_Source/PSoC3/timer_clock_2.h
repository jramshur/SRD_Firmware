/*******************************************************************************
* File Name: timer_clock_2.h
* Version 2.0
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

#if !defined(CY_CLOCK_timer_clock_2_H)
#define CY_CLOCK_timer_clock_2_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void timer_clock_2_Start(void) ;
void timer_clock_2_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void timer_clock_2_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void timer_clock_2_StandbyPower(uint8 state) ;
void timer_clock_2_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 timer_clock_2_GetDividerRegister(void) ;
void timer_clock_2_SetModeRegister(uint8 modeBitMask) ;
void timer_clock_2_ClearModeRegister(uint8 modeBitMask) ;
uint8 timer_clock_2_GetModeRegister(void) ;
void timer_clock_2_SetSourceRegister(uint8 clkSource) ;
uint8 timer_clock_2_GetSourceRegister(void) ;
#if defined(timer_clock_2__CFG3)
void timer_clock_2_SetPhaseRegister(uint8 clkPhase) ;
uint8 timer_clock_2_GetPhaseRegister(void) ;
#endif /* defined(timer_clock_2__CFG3) */

#define timer_clock_2_Enable()                       timer_clock_2_Start()
#define timer_clock_2_Disable()                      timer_clock_2_Stop()
#define timer_clock_2_SetDivider(clkDivider)         timer_clock_2_SetDividerRegister(clkDivider, 1)
#define timer_clock_2_SetDividerValue(clkDivider)    timer_clock_2_SetDividerRegister((clkDivider) - 1, 1)
#define timer_clock_2_SetMode(clkMode)               timer_clock_2_SetModeRegister(clkMode)
#define timer_clock_2_SetSource(clkSource)           timer_clock_2_SetSourceRegister(clkSource)
#if defined(timer_clock_2__CFG3)
#define timer_clock_2_SetPhase(clkPhase)             timer_clock_2_SetPhaseRegister(clkPhase)
#define timer_clock_2_SetPhaseValue(clkPhase)        timer_clock_2_SetPhaseRegister((clkPhase) + 1)
#endif /* defined(timer_clock_2__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define timer_clock_2_CLKEN              (* (reg8 *) timer_clock_2__PM_ACT_CFG)
#define timer_clock_2_CLKEN_PTR          ((reg8 *) timer_clock_2__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define timer_clock_2_CLKSTBY            (* (reg8 *) timer_clock_2__PM_STBY_CFG)
#define timer_clock_2_CLKSTBY_PTR        ((reg8 *) timer_clock_2__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define timer_clock_2_DIV_LSB            (* (reg8 *) timer_clock_2__CFG0)
#define timer_clock_2_DIV_LSB_PTR        ((reg8 *) timer_clock_2__CFG0)
#define timer_clock_2_DIV_PTR            ((reg16 *) timer_clock_2__CFG0)

/* Clock MSB divider configuration register. */
#define timer_clock_2_DIV_MSB            (* (reg8 *) timer_clock_2__CFG1)
#define timer_clock_2_DIV_MSB_PTR        ((reg8 *) timer_clock_2__CFG1)

/* Mode and source configuration register */
#define timer_clock_2_MOD_SRC            (* (reg8 *) timer_clock_2__CFG2)
#define timer_clock_2_MOD_SRC_PTR        ((reg8 *) timer_clock_2__CFG2)

#if defined(timer_clock_2__CFG3)
/* Analog clock phase configuration register */
#define timer_clock_2_PHASE              (* (reg8 *) timer_clock_2__CFG3)
#define timer_clock_2_PHASE_PTR          ((reg8 *) timer_clock_2__CFG3)
#endif /* defined(timer_clock_2__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define timer_clock_2_CLKEN_MASK         timer_clock_2__PM_ACT_MSK
#define timer_clock_2_CLKSTBY_MASK       timer_clock_2__PM_STBY_MSK

/* CFG2 field masks */
#define timer_clock_2_SRC_SEL_MSK        timer_clock_2__CFG2_SRC_SEL_MASK
#define timer_clock_2_MODE_MASK          (~(timer_clock_2_SRC_SEL_MSK))

#if defined(timer_clock_2__CFG3)
/* CFG3 phase mask */
#define timer_clock_2_PHASE_MASK         timer_clock_2__CFG3_PHASE_DLY_MASK
#endif /* defined(timer_clock_2__CFG3) */

#endif /* CY_CLOCK_timer_clock_2_H */


/* [] END OF FILE */