/*******************************************************************************
* File Name: pin_VDAC.h  
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

#if !defined(CY_PINS_pin_VDAC_H) /* Pins pin_VDAC_H */
#define CY_PINS_pin_VDAC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pin_VDAC_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    pin_VDAC_Write(uint8 value) ;
void    pin_VDAC_SetDriveMode(uint8 mode) ;
uint8   pin_VDAC_ReadDataReg(void) ;
uint8   pin_VDAC_Read(void) ;
uint8   pin_VDAC_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pin_VDAC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pin_VDAC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pin_VDAC_DM_RES_UP          PIN_DM_RES_UP
#define pin_VDAC_DM_RES_DWN         PIN_DM_RES_DWN
#define pin_VDAC_DM_OD_LO           PIN_DM_OD_LO
#define pin_VDAC_DM_OD_HI           PIN_DM_OD_HI
#define pin_VDAC_DM_STRONG          PIN_DM_STRONG
#define pin_VDAC_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pin_VDAC_MASK               pin_VDAC__MASK
#define pin_VDAC_SHIFT              pin_VDAC__SHIFT
#define pin_VDAC_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pin_VDAC_PS                     (* (reg8 *) pin_VDAC__PS)
/* Data Register */
#define pin_VDAC_DR                     (* (reg8 *) pin_VDAC__DR)
/* Port Number */
#define pin_VDAC_PRT_NUM                (* (reg8 *) pin_VDAC__PRT) 
/* Connect to Analog Globals */                                                  
#define pin_VDAC_AG                     (* (reg8 *) pin_VDAC__AG)                       
/* Analog MUX bux enable */
#define pin_VDAC_AMUX                   (* (reg8 *) pin_VDAC__AMUX) 
/* Bidirectional Enable */                                                        
#define pin_VDAC_BIE                    (* (reg8 *) pin_VDAC__BIE)
/* Bit-mask for Aliased Register Access */
#define pin_VDAC_BIT_MASK               (* (reg8 *) pin_VDAC__BIT_MASK)
/* Bypass Enable */
#define pin_VDAC_BYP                    (* (reg8 *) pin_VDAC__BYP)
/* Port wide control signals */                                                   
#define pin_VDAC_CTL                    (* (reg8 *) pin_VDAC__CTL)
/* Drive Modes */
#define pin_VDAC_DM0                    (* (reg8 *) pin_VDAC__DM0) 
#define pin_VDAC_DM1                    (* (reg8 *) pin_VDAC__DM1)
#define pin_VDAC_DM2                    (* (reg8 *) pin_VDAC__DM2) 
/* Input Buffer Disable Override */
#define pin_VDAC_INP_DIS                (* (reg8 *) pin_VDAC__INP_DIS)
/* LCD Common or Segment Drive */
#define pin_VDAC_LCD_COM_SEG            (* (reg8 *) pin_VDAC__LCD_COM_SEG)
/* Enable Segment LCD */
#define pin_VDAC_LCD_EN                 (* (reg8 *) pin_VDAC__LCD_EN)
/* Slew Rate Control */
#define pin_VDAC_SLW                    (* (reg8 *) pin_VDAC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pin_VDAC_PRTDSI__CAPS_SEL       (* (reg8 *) pin_VDAC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pin_VDAC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pin_VDAC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pin_VDAC_PRTDSI__OE_SEL0        (* (reg8 *) pin_VDAC__PRTDSI__OE_SEL0) 
#define pin_VDAC_PRTDSI__OE_SEL1        (* (reg8 *) pin_VDAC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pin_VDAC_PRTDSI__OUT_SEL0       (* (reg8 *) pin_VDAC__PRTDSI__OUT_SEL0) 
#define pin_VDAC_PRTDSI__OUT_SEL1       (* (reg8 *) pin_VDAC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pin_VDAC_PRTDSI__SYNC_OUT       (* (reg8 *) pin_VDAC__PRTDSI__SYNC_OUT) 


#if defined(pin_VDAC__INTSTAT)  /* Interrupt Registers */

    #define pin_VDAC_INTSTAT                (* (reg8 *) pin_VDAC__INTSTAT)
    #define pin_VDAC_SNAP                   (* (reg8 *) pin_VDAC__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins pin_VDAC_H */


/* [] END OF FILE */
