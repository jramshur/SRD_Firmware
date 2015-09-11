/*******************************************************************************
* File Name: pin_iSink.h  
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

#if !defined(CY_PINS_pin_iSink_H) /* Pins pin_iSink_H */
#define CY_PINS_pin_iSink_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pin_iSink_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    pin_iSink_Write(uint8 value) ;
void    pin_iSink_SetDriveMode(uint8 mode) ;
uint8   pin_iSink_ReadDataReg(void) ;
uint8   pin_iSink_Read(void) ;
uint8   pin_iSink_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pin_iSink_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pin_iSink_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pin_iSink_DM_RES_UP          PIN_DM_RES_UP
#define pin_iSink_DM_RES_DWN         PIN_DM_RES_DWN
#define pin_iSink_DM_OD_LO           PIN_DM_OD_LO
#define pin_iSink_DM_OD_HI           PIN_DM_OD_HI
#define pin_iSink_DM_STRONG          PIN_DM_STRONG
#define pin_iSink_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pin_iSink_MASK               pin_iSink__MASK
#define pin_iSink_SHIFT              pin_iSink__SHIFT
#define pin_iSink_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pin_iSink_PS                     (* (reg8 *) pin_iSink__PS)
/* Data Register */
#define pin_iSink_DR                     (* (reg8 *) pin_iSink__DR)
/* Port Number */
#define pin_iSink_PRT_NUM                (* (reg8 *) pin_iSink__PRT) 
/* Connect to Analog Globals */                                                  
#define pin_iSink_AG                     (* (reg8 *) pin_iSink__AG)                       
/* Analog MUX bux enable */
#define pin_iSink_AMUX                   (* (reg8 *) pin_iSink__AMUX) 
/* Bidirectional Enable */                                                        
#define pin_iSink_BIE                    (* (reg8 *) pin_iSink__BIE)
/* Bit-mask for Aliased Register Access */
#define pin_iSink_BIT_MASK               (* (reg8 *) pin_iSink__BIT_MASK)
/* Bypass Enable */
#define pin_iSink_BYP                    (* (reg8 *) pin_iSink__BYP)
/* Port wide control signals */                                                   
#define pin_iSink_CTL                    (* (reg8 *) pin_iSink__CTL)
/* Drive Modes */
#define pin_iSink_DM0                    (* (reg8 *) pin_iSink__DM0) 
#define pin_iSink_DM1                    (* (reg8 *) pin_iSink__DM1)
#define pin_iSink_DM2                    (* (reg8 *) pin_iSink__DM2) 
/* Input Buffer Disable Override */
#define pin_iSink_INP_DIS                (* (reg8 *) pin_iSink__INP_DIS)
/* LCD Common or Segment Drive */
#define pin_iSink_LCD_COM_SEG            (* (reg8 *) pin_iSink__LCD_COM_SEG)
/* Enable Segment LCD */
#define pin_iSink_LCD_EN                 (* (reg8 *) pin_iSink__LCD_EN)
/* Slew Rate Control */
#define pin_iSink_SLW                    (* (reg8 *) pin_iSink__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pin_iSink_PRTDSI__CAPS_SEL       (* (reg8 *) pin_iSink__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pin_iSink_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pin_iSink__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pin_iSink_PRTDSI__OE_SEL0        (* (reg8 *) pin_iSink__PRTDSI__OE_SEL0) 
#define pin_iSink_PRTDSI__OE_SEL1        (* (reg8 *) pin_iSink__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pin_iSink_PRTDSI__OUT_SEL0       (* (reg8 *) pin_iSink__PRTDSI__OUT_SEL0) 
#define pin_iSink_PRTDSI__OUT_SEL1       (* (reg8 *) pin_iSink__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pin_iSink_PRTDSI__SYNC_OUT       (* (reg8 *) pin_iSink__PRTDSI__SYNC_OUT) 


#if defined(pin_iSink__INTSTAT)  /* Interrupt Registers */

    #define pin_iSink_INTSTAT                (* (reg8 *) pin_iSink__INTSTAT)
    #define pin_iSink_SNAP                   (* (reg8 *) pin_iSink__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins pin_iSink_H */


/* [] END OF FILE */
