/*******************************************************************************
* File Name: pin_DAC2.h  
* Version 2.0
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_pin_DAC2_H) /* Pins pin_DAC2_H */
#define CY_PINS_pin_DAC2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pin_DAC2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    pin_DAC2_Write(uint8 value) ;
void    pin_DAC2_SetDriveMode(uint8 mode) ;
uint8   pin_DAC2_ReadDataReg(void) ;
uint8   pin_DAC2_Read(void) ;
uint8   pin_DAC2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pin_DAC2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pin_DAC2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pin_DAC2_DM_RES_UP          PIN_DM_RES_UP
#define pin_DAC2_DM_RES_DWN         PIN_DM_RES_DWN
#define pin_DAC2_DM_OD_LO           PIN_DM_OD_LO
#define pin_DAC2_DM_OD_HI           PIN_DM_OD_HI
#define pin_DAC2_DM_STRONG          PIN_DM_STRONG
#define pin_DAC2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pin_DAC2_MASK               pin_DAC2__MASK
#define pin_DAC2_SHIFT              pin_DAC2__SHIFT
#define pin_DAC2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pin_DAC2_PS                     (* (reg8 *) pin_DAC2__PS)
/* Data Register */
#define pin_DAC2_DR                     (* (reg8 *) pin_DAC2__DR)
/* Port Number */
#define pin_DAC2_PRT_NUM                (* (reg8 *) pin_DAC2__PRT) 
/* Connect to Analog Globals */                                                  
#define pin_DAC2_AG                     (* (reg8 *) pin_DAC2__AG)                       
/* Analog MUX bux enable */
#define pin_DAC2_AMUX                   (* (reg8 *) pin_DAC2__AMUX) 
/* Bidirectional Enable */                                                        
#define pin_DAC2_BIE                    (* (reg8 *) pin_DAC2__BIE)
/* Bit-mask for Aliased Register Access */
#define pin_DAC2_BIT_MASK               (* (reg8 *) pin_DAC2__BIT_MASK)
/* Bypass Enable */
#define pin_DAC2_BYP                    (* (reg8 *) pin_DAC2__BYP)
/* Port wide control signals */                                                   
#define pin_DAC2_CTL                    (* (reg8 *) pin_DAC2__CTL)
/* Drive Modes */
#define pin_DAC2_DM0                    (* (reg8 *) pin_DAC2__DM0) 
#define pin_DAC2_DM1                    (* (reg8 *) pin_DAC2__DM1)
#define pin_DAC2_DM2                    (* (reg8 *) pin_DAC2__DM2) 
/* Input Buffer Disable Override */
#define pin_DAC2_INP_DIS                (* (reg8 *) pin_DAC2__INP_DIS)
/* LCD Common or Segment Drive */
#define pin_DAC2_LCD_COM_SEG            (* (reg8 *) pin_DAC2__LCD_COM_SEG)
/* Enable Segment LCD */
#define pin_DAC2_LCD_EN                 (* (reg8 *) pin_DAC2__LCD_EN)
/* Slew Rate Control */
#define pin_DAC2_SLW                    (* (reg8 *) pin_DAC2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pin_DAC2_PRTDSI__CAPS_SEL       (* (reg8 *) pin_DAC2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pin_DAC2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pin_DAC2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pin_DAC2_PRTDSI__OE_SEL0        (* (reg8 *) pin_DAC2__PRTDSI__OE_SEL0) 
#define pin_DAC2_PRTDSI__OE_SEL1        (* (reg8 *) pin_DAC2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pin_DAC2_PRTDSI__OUT_SEL0       (* (reg8 *) pin_DAC2__PRTDSI__OUT_SEL0) 
#define pin_DAC2_PRTDSI__OUT_SEL1       (* (reg8 *) pin_DAC2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pin_DAC2_PRTDSI__SYNC_OUT       (* (reg8 *) pin_DAC2__PRTDSI__SYNC_OUT) 


#if defined(pin_DAC2__INTSTAT)  /* Interrupt Registers */

    #define pin_DAC2_INTSTAT                (* (reg8 *) pin_DAC2__INTSTAT)
    #define pin_DAC2_SNAP                   (* (reg8 *) pin_DAC2__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins pin_DAC2_H */


/* [] END OF FILE */
