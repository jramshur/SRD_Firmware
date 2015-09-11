/*******************************************************************************
* File Name: pin_iSource.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_pin_iSource_H) /* Pins pin_iSource_H */
#define CY_PINS_pin_iSource_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pin_iSource_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    pin_iSource_Write(uint8 value) ;
void    pin_iSource_SetDriveMode(uint8 mode) ;
uint8   pin_iSource_ReadDataReg(void) ;
uint8   pin_iSource_Read(void) ;
uint8   pin_iSource_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pin_iSource_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pin_iSource_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pin_iSource_DM_RES_UP          PIN_DM_RES_UP
#define pin_iSource_DM_RES_DWN         PIN_DM_RES_DWN
#define pin_iSource_DM_OD_LO           PIN_DM_OD_LO
#define pin_iSource_DM_OD_HI           PIN_DM_OD_HI
#define pin_iSource_DM_STRONG          PIN_DM_STRONG
#define pin_iSource_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pin_iSource_MASK               pin_iSource__MASK
#define pin_iSource_SHIFT              pin_iSource__SHIFT
#define pin_iSource_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pin_iSource_PS                     (* (reg8 *) pin_iSource__PS)
/* Data Register */
#define pin_iSource_DR                     (* (reg8 *) pin_iSource__DR)
/* Port Number */
#define pin_iSource_PRT_NUM                (* (reg8 *) pin_iSource__PRT) 
/* Connect to Analog Globals */                                                  
#define pin_iSource_AG                     (* (reg8 *) pin_iSource__AG)                       
/* Analog MUX bux enable */
#define pin_iSource_AMUX                   (* (reg8 *) pin_iSource__AMUX) 
/* Bidirectional Enable */                                                        
#define pin_iSource_BIE                    (* (reg8 *) pin_iSource__BIE)
/* Bit-mask for Aliased Register Access */
#define pin_iSource_BIT_MASK               (* (reg8 *) pin_iSource__BIT_MASK)
/* Bypass Enable */
#define pin_iSource_BYP                    (* (reg8 *) pin_iSource__BYP)
/* Port wide control signals */                                                   
#define pin_iSource_CTL                    (* (reg8 *) pin_iSource__CTL)
/* Drive Modes */
#define pin_iSource_DM0                    (* (reg8 *) pin_iSource__DM0) 
#define pin_iSource_DM1                    (* (reg8 *) pin_iSource__DM1)
#define pin_iSource_DM2                    (* (reg8 *) pin_iSource__DM2) 
/* Input Buffer Disable Override */
#define pin_iSource_INP_DIS                (* (reg8 *) pin_iSource__INP_DIS)
/* LCD Common or Segment Drive */
#define pin_iSource_LCD_COM_SEG            (* (reg8 *) pin_iSource__LCD_COM_SEG)
/* Enable Segment LCD */
#define pin_iSource_LCD_EN                 (* (reg8 *) pin_iSource__LCD_EN)
/* Slew Rate Control */
#define pin_iSource_SLW                    (* (reg8 *) pin_iSource__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pin_iSource_PRTDSI__CAPS_SEL       (* (reg8 *) pin_iSource__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pin_iSource_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pin_iSource__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pin_iSource_PRTDSI__OE_SEL0        (* (reg8 *) pin_iSource__PRTDSI__OE_SEL0) 
#define pin_iSource_PRTDSI__OE_SEL1        (* (reg8 *) pin_iSource__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pin_iSource_PRTDSI__OUT_SEL0       (* (reg8 *) pin_iSource__PRTDSI__OUT_SEL0) 
#define pin_iSource_PRTDSI__OUT_SEL1       (* (reg8 *) pin_iSource__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pin_iSource_PRTDSI__SYNC_OUT       (* (reg8 *) pin_iSource__PRTDSI__SYNC_OUT) 


#if defined(pin_iSource__INTSTAT)  /* Interrupt Registers */

    #define pin_iSource_INTSTAT                (* (reg8 *) pin_iSource__INTSTAT)
    #define pin_iSource_SNAP                   (* (reg8 *) pin_iSource__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins pin_iSource_H */


/* [] END OF FILE */
