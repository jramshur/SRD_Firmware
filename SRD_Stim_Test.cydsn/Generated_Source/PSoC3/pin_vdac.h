/*******************************************************************************
* File Name: pin_vdac.h  
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

#if !defined(CY_PINS_pin_vdac_H) /* Pins pin_vdac_H */
#define CY_PINS_pin_vdac_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pin_vdac_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    pin_vdac_Write(uint8 value) ;
void    pin_vdac_SetDriveMode(uint8 mode) ;
uint8   pin_vdac_ReadDataReg(void) ;
uint8   pin_vdac_Read(void) ;
uint8   pin_vdac_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pin_vdac_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pin_vdac_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pin_vdac_DM_RES_UP          PIN_DM_RES_UP
#define pin_vdac_DM_RES_DWN         PIN_DM_RES_DWN
#define pin_vdac_DM_OD_LO           PIN_DM_OD_LO
#define pin_vdac_DM_OD_HI           PIN_DM_OD_HI
#define pin_vdac_DM_STRONG          PIN_DM_STRONG
#define pin_vdac_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pin_vdac_MASK               pin_vdac__MASK
#define pin_vdac_SHIFT              pin_vdac__SHIFT
#define pin_vdac_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pin_vdac_PS                     (* (reg8 *) pin_vdac__PS)
/* Data Register */
#define pin_vdac_DR                     (* (reg8 *) pin_vdac__DR)
/* Port Number */
#define pin_vdac_PRT_NUM                (* (reg8 *) pin_vdac__PRT) 
/* Connect to Analog Globals */                                                  
#define pin_vdac_AG                     (* (reg8 *) pin_vdac__AG)                       
/* Analog MUX bux enable */
#define pin_vdac_AMUX                   (* (reg8 *) pin_vdac__AMUX) 
/* Bidirectional Enable */                                                        
#define pin_vdac_BIE                    (* (reg8 *) pin_vdac__BIE)
/* Bit-mask for Aliased Register Access */
#define pin_vdac_BIT_MASK               (* (reg8 *) pin_vdac__BIT_MASK)
/* Bypass Enable */
#define pin_vdac_BYP                    (* (reg8 *) pin_vdac__BYP)
/* Port wide control signals */                                                   
#define pin_vdac_CTL                    (* (reg8 *) pin_vdac__CTL)
/* Drive Modes */
#define pin_vdac_DM0                    (* (reg8 *) pin_vdac__DM0) 
#define pin_vdac_DM1                    (* (reg8 *) pin_vdac__DM1)
#define pin_vdac_DM2                    (* (reg8 *) pin_vdac__DM2) 
/* Input Buffer Disable Override */
#define pin_vdac_INP_DIS                (* (reg8 *) pin_vdac__INP_DIS)
/* LCD Common or Segment Drive */
#define pin_vdac_LCD_COM_SEG            (* (reg8 *) pin_vdac__LCD_COM_SEG)
/* Enable Segment LCD */
#define pin_vdac_LCD_EN                 (* (reg8 *) pin_vdac__LCD_EN)
/* Slew Rate Control */
#define pin_vdac_SLW                    (* (reg8 *) pin_vdac__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pin_vdac_PRTDSI__CAPS_SEL       (* (reg8 *) pin_vdac__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pin_vdac_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pin_vdac__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pin_vdac_PRTDSI__OE_SEL0        (* (reg8 *) pin_vdac__PRTDSI__OE_SEL0) 
#define pin_vdac_PRTDSI__OE_SEL1        (* (reg8 *) pin_vdac__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pin_vdac_PRTDSI__OUT_SEL0       (* (reg8 *) pin_vdac__PRTDSI__OUT_SEL0) 
#define pin_vdac_PRTDSI__OUT_SEL1       (* (reg8 *) pin_vdac__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pin_vdac_PRTDSI__SYNC_OUT       (* (reg8 *) pin_vdac__PRTDSI__SYNC_OUT) 


#if defined(pin_vdac__INTSTAT)  /* Interrupt Registers */

    #define pin_vdac_INTSTAT                (* (reg8 *) pin_vdac__INTSTAT)
    #define pin_vdac_SNAP                   (* (reg8 *) pin_vdac__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins pin_vdac_H */


/* [] END OF FILE */
