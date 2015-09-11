/*******************************************************************************
* File Name: pin_IDAC.h  
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

#if !defined(CY_PINS_pin_IDAC_H) /* Pins pin_IDAC_H */
#define CY_PINS_pin_IDAC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pin_IDAC_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    pin_IDAC_Write(uint8 value) ;
void    pin_IDAC_SetDriveMode(uint8 mode) ;
uint8   pin_IDAC_ReadDataReg(void) ;
uint8   pin_IDAC_Read(void) ;
uint8   pin_IDAC_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pin_IDAC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pin_IDAC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pin_IDAC_DM_RES_UP          PIN_DM_RES_UP
#define pin_IDAC_DM_RES_DWN         PIN_DM_RES_DWN
#define pin_IDAC_DM_OD_LO           PIN_DM_OD_LO
#define pin_IDAC_DM_OD_HI           PIN_DM_OD_HI
#define pin_IDAC_DM_STRONG          PIN_DM_STRONG
#define pin_IDAC_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pin_IDAC_MASK               pin_IDAC__MASK
#define pin_IDAC_SHIFT              pin_IDAC__SHIFT
#define pin_IDAC_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pin_IDAC_PS                     (* (reg8 *) pin_IDAC__PS)
/* Data Register */
#define pin_IDAC_DR                     (* (reg8 *) pin_IDAC__DR)
/* Port Number */
#define pin_IDAC_PRT_NUM                (* (reg8 *) pin_IDAC__PRT) 
/* Connect to Analog Globals */                                                  
#define pin_IDAC_AG                     (* (reg8 *) pin_IDAC__AG)                       
/* Analog MUX bux enable */
#define pin_IDAC_AMUX                   (* (reg8 *) pin_IDAC__AMUX) 
/* Bidirectional Enable */                                                        
#define pin_IDAC_BIE                    (* (reg8 *) pin_IDAC__BIE)
/* Bit-mask for Aliased Register Access */
#define pin_IDAC_BIT_MASK               (* (reg8 *) pin_IDAC__BIT_MASK)
/* Bypass Enable */
#define pin_IDAC_BYP                    (* (reg8 *) pin_IDAC__BYP)
/* Port wide control signals */                                                   
#define pin_IDAC_CTL                    (* (reg8 *) pin_IDAC__CTL)
/* Drive Modes */
#define pin_IDAC_DM0                    (* (reg8 *) pin_IDAC__DM0) 
#define pin_IDAC_DM1                    (* (reg8 *) pin_IDAC__DM1)
#define pin_IDAC_DM2                    (* (reg8 *) pin_IDAC__DM2) 
/* Input Buffer Disable Override */
#define pin_IDAC_INP_DIS                (* (reg8 *) pin_IDAC__INP_DIS)
/* LCD Common or Segment Drive */
#define pin_IDAC_LCD_COM_SEG            (* (reg8 *) pin_IDAC__LCD_COM_SEG)
/* Enable Segment LCD */
#define pin_IDAC_LCD_EN                 (* (reg8 *) pin_IDAC__LCD_EN)
/* Slew Rate Control */
#define pin_IDAC_SLW                    (* (reg8 *) pin_IDAC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pin_IDAC_PRTDSI__CAPS_SEL       (* (reg8 *) pin_IDAC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pin_IDAC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pin_IDAC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pin_IDAC_PRTDSI__OE_SEL0        (* (reg8 *) pin_IDAC__PRTDSI__OE_SEL0) 
#define pin_IDAC_PRTDSI__OE_SEL1        (* (reg8 *) pin_IDAC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pin_IDAC_PRTDSI__OUT_SEL0       (* (reg8 *) pin_IDAC__PRTDSI__OUT_SEL0) 
#define pin_IDAC_PRTDSI__OUT_SEL1       (* (reg8 *) pin_IDAC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pin_IDAC_PRTDSI__SYNC_OUT       (* (reg8 *) pin_IDAC__PRTDSI__SYNC_OUT) 


#if defined(pin_IDAC__INTSTAT)  /* Interrupt Registers */

    #define pin_IDAC_INTSTAT                (* (reg8 *) pin_IDAC__INTSTAT)
    #define pin_IDAC_SNAP                   (* (reg8 *) pin_IDAC__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins pin_IDAC_H */


/* [] END OF FILE */
