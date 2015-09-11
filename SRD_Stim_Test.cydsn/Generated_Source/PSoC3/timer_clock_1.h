/*******************************************************************************
* File Name: timer_clock_1.h
* Version 1.50
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_CLOCK_timer_clock_1_H)
#define CY_CLOCK_timer_clock_1_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void timer_clock_1_Start(void) ;
void timer_clock_1_Stop(void) ;

#if(!(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3 && \
    CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES2) && \
	!(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 && \
	CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_ES1))
void timer_clock_1_StopBlock(void) ;
#endif

void timer_clock_1_StandbyPower(uint8 state) ;
void timer_clock_1_SetDividerRegister(uint16 clkDivider, uint8 reset) ;
uint16 timer_clock_1_GetDividerRegister(void) ;
void timer_clock_1_SetModeRegister(uint8 modeBitMask) ;
void timer_clock_1_ClearModeRegister(uint8 modeBitMask) ;
uint8 timer_clock_1_GetModeRegister(void) ;
void timer_clock_1_SetSourceRegister(uint8 clkSource) ;
uint8 timer_clock_1_GetSourceRegister(void) ;
#if defined(timer_clock_1__CFG3)
void timer_clock_1_SetPhaseRegister(uint8 clkPhase) ;
uint8 timer_clock_1_GetPhaseRegister(void) ;
#endif

#define timer_clock_1_Enable()                       timer_clock_1_Start()
#define timer_clock_1_Disable()                      timer_clock_1_Stop()
#define timer_clock_1_SetDivider(clkDivider)         timer_clock_1_SetDividerRegister(clkDivider, 1)
#define timer_clock_1_SetDividerValue(clkDivider)    timer_clock_1_SetDividerRegister((clkDivider) - 1, 1)
#define timer_clock_1_SetMode(clkMode)               timer_clock_1_SetModeRegister(clkMode)
#define timer_clock_1_SetSource(clkSource)           timer_clock_1_SetSourceRegister(clkSource)
#if defined(timer_clock_1__CFG3)
#define timer_clock_1_SetPhase(clkPhase)             timer_clock_1_SetPhaseRegister(clkPhase)
#define timer_clock_1_SetPhaseValue(clkPhase)        timer_clock_1_SetPhaseRegister((clkPhase) + 1)
#endif


/***************************************
*           API Constants
***************************************/

/* Constants SetPhase(), clkPhase parameter. Only valid for PSoC 3 ES2 and earlier. See datasheet for details. */
#if CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3 && \
   (CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES1 || \
    CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES2)
#define CYCLK_2_5NS             0x01 /* 2.5 ns delay. */
#define CYCLK_3_5NS             0x02 /* 3.5 ns delay. */
#define CYCLK_4_5NS             0x03 /* 4.5 ns delay. */
#define CYCLK_5_5NS             0x04 /* 5.5 ns delay. */
#define CYCLK_6_5NS             0x05 /* 6.5 ns delay. */
#define CYCLK_7_5NS             0x06 /* 7.5 ns delay. */
#define CYCLK_8_5NS             0x07 /* 8.5 ns delay. */
#define CYCLK_9_5NS             0x08 /* 9.5 ns delay. */
#define CYCLK_10_5NS            0x09 /* 10.5 ns delay. */
#define CYCLK_11_5NS            0x0A /* 11.5 ns delay. */
#define CYCLK_12_5NS            0x0B /* 12.5 ns delay. */
#endif


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define timer_clock_1_CLKEN              (* (reg8 *) timer_clock_1__PM_ACT_CFG)
#define timer_clock_1_CLKEN_PTR          ((reg8 *) timer_clock_1__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define timer_clock_1_CLKSTBY            (* (reg8 *) timer_clock_1__PM_STBY_CFG)
#define timer_clock_1_CLKSTBY_PTR        ((reg8 *) timer_clock_1__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define timer_clock_1_DIV_LSB            (* (reg8 *) timer_clock_1__CFG0)
#define timer_clock_1_DIV_LSB_PTR        ((reg8 *) timer_clock_1__CFG0)
#define timer_clock_1_DIV_PTR            ((reg16 *) timer_clock_1__CFG0)

/* Clock MSB divider configuration register. */
#define timer_clock_1_DIV_MSB            (* (reg8 *) timer_clock_1__CFG1)
#define timer_clock_1_DIV_MSB_PTR        ((reg8 *) timer_clock_1__CFG1)

/* Mode and source configuration register */
#define timer_clock_1_MOD_SRC            (* (reg8 *) timer_clock_1__CFG2)
#define timer_clock_1_MOD_SRC_PTR        ((reg8 *) timer_clock_1__CFG2)

#if defined(timer_clock_1__CFG3)
/* Analog clock phase configuration register */
#define timer_clock_1_PHASE              (* (reg8 *) timer_clock_1__CFG3)
#define timer_clock_1_PHASE_PTR          ((reg8 *) timer_clock_1__CFG3)
#endif


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define timer_clock_1_CLKEN_MASK         timer_clock_1__PM_ACT_MSK
#define timer_clock_1_CLKSTBY_MASK       timer_clock_1__PM_STBY_MSK

/* CFG2 field masks */
#define timer_clock_1_SRC_SEL_MSK        timer_clock_1__CFG2_SRC_SEL_MASK
#define timer_clock_1_MODE_MASK          (~(timer_clock_1_SRC_SEL_MSK))

#if defined(timer_clock_1__CFG3)
/* CFG3 phase mask */
#define timer_clock_1_PHASE_MASK         timer_clock_1__CFG3_PHASE_DLY_MASK
#endif

#endif /* CY_CLOCK_timer_clock_1_H */


/* [] END OF FILE */
