/*******************************************************************************
* File Name: pin_Vcon.h  
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

#if !defined(CY_PINS_pin_Vcon_H) /* Pins pin_Vcon_H */
#define CY_PINS_pin_Vcon_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pin_Vcon_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    pin_Vcon_Write(uint8 value) ;
void    pin_Vcon_SetDriveMode(uint8 mode) ;
uint8   pin_Vcon_ReadDataReg(void) ;
uint8   pin_Vcon_Read(void) ;
uint8   pin_Vcon_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pin_Vcon_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pin_Vcon_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pin_Vcon_DM_RES_UP          PIN_DM_RES_UP
#define pin_Vcon_DM_RES_DWN         PIN_DM_RES_DWN
#define pin_Vcon_DM_OD_LO           PIN_DM_OD_LO
#define pin_Vcon_DM_OD_HI           PIN_DM_OD_HI
#define pin_Vcon_DM_STRONG          PIN_DM_STRONG
#define pin_Vcon_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pin_Vcon_MASK               pin_Vcon__MASK
#define pin_Vcon_SHIFT              pin_Vcon__SHIFT
#define pin_Vcon_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pin_Vcon_PS                     (* (reg8 *) pin_Vcon__PS)
/* Data Register */
#define pin_Vcon_DR                     (* (reg8 *) pin_Vcon__DR)
/* Port Number */
#define pin_Vcon_PRT_NUM                (* (reg8 *) pin_Vcon__PRT) 
/* Connect to Analog Globals */                                                  
#define pin_Vcon_AG                     (* (reg8 *) pin_Vcon__AG)                       
/* Analog MUX bux enable */
#define pin_Vcon_AMUX                   (* (reg8 *) pin_Vcon__AMUX) 
/* Bidirectional Enable */                                                        
#define pin_Vcon_BIE                    (* (reg8 *) pin_Vcon__BIE)
/* Bit-mask for Aliased Register Access */
#define pin_Vcon_BIT_MASK               (* (reg8 *) pin_Vcon__BIT_MASK)
/* Bypass Enable */
#define pin_Vcon_BYP                    (* (reg8 *) pin_Vcon__BYP)
/* Port wide control signals */                                                   
#define pin_Vcon_CTL                    (* (reg8 *) pin_Vcon__CTL)
/* Drive Modes */
#define pin_Vcon_DM0                    (* (reg8 *) pin_Vcon__DM0) 
#define pin_Vcon_DM1                    (* (reg8 *) pin_Vcon__DM1)
#define pin_Vcon_DM2                    (* (reg8 *) pin_Vcon__DM2) 
/* Input Buffer Disable Override */
#define pin_Vcon_INP_DIS                (* (reg8 *) pin_Vcon__INP_DIS)
/* LCD Common or Segment Drive */
#define pin_Vcon_LCD_COM_SEG            (* (reg8 *) pin_Vcon__LCD_COM_SEG)
/* Enable Segment LCD */
#define pin_Vcon_LCD_EN                 (* (reg8 *) pin_Vcon__LCD_EN)
/* Slew Rate Control */
#define pin_Vcon_SLW                    (* (reg8 *) pin_Vcon__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pin_Vcon_PRTDSI__CAPS_SEL       (* (reg8 *) pin_Vcon__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pin_Vcon_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pin_Vcon__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pin_Vcon_PRTDSI__OE_SEL0        (* (reg8 *) pin_Vcon__PRTDSI__OE_SEL0) 
#define pin_Vcon_PRTDSI__OE_SEL1        (* (reg8 *) pin_Vcon__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pin_Vcon_PRTDSI__OUT_SEL0       (* (reg8 *) pin_Vcon__PRTDSI__OUT_SEL0) 
#define pin_Vcon_PRTDSI__OUT_SEL1       (* (reg8 *) pin_Vcon__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pin_Vcon_PRTDSI__SYNC_OUT       (* (reg8 *) pin_Vcon__PRTDSI__SYNC_OUT) 


#if defined(pin_Vcon__INTSTAT)  /* Interrupt Registers */

    #define pin_Vcon_INTSTAT                (* (reg8 *) pin_Vcon__INTSTAT)
    #define pin_Vcon_SNAP                   (* (reg8 *) pin_Vcon__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins pin_Vcon_H */


/* [] END OF FILE */
