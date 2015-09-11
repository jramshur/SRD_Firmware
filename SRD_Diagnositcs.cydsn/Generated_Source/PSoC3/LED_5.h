/*******************************************************************************
* File Name: LED_5.h  
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

#if !defined(CY_PINS_LED_5_H) /* Pins LED_5_H */
#define CY_PINS_LED_5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED_5_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_5_Write(uint8 value) ;
void    LED_5_SetDriveMode(uint8 mode) ;
uint8   LED_5_ReadDataReg(void) ;
uint8   LED_5_Read(void) ;
uint8   LED_5_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LED_5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LED_5_DM_RES_UP          PIN_DM_RES_UP
#define LED_5_DM_RES_DWN         PIN_DM_RES_DWN
#define LED_5_DM_OD_LO           PIN_DM_OD_LO
#define LED_5_DM_OD_HI           PIN_DM_OD_HI
#define LED_5_DM_STRONG          PIN_DM_STRONG
#define LED_5_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LED_5_MASK               LED_5__MASK
#define LED_5_SHIFT              LED_5__SHIFT
#define LED_5_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_5_PS                     (* (reg8 *) LED_5__PS)
/* Data Register */
#define LED_5_DR                     (* (reg8 *) LED_5__DR)
/* Port Number */
#define LED_5_PRT_NUM                (* (reg8 *) LED_5__PRT) 
/* Connect to Analog Globals */                                                  
#define LED_5_AG                     (* (reg8 *) LED_5__AG)                       
/* Analog MUX bux enable */
#define LED_5_AMUX                   (* (reg8 *) LED_5__AMUX) 
/* Bidirectional Enable */                                                        
#define LED_5_BIE                    (* (reg8 *) LED_5__BIE)
/* Bit-mask for Aliased Register Access */
#define LED_5_BIT_MASK               (* (reg8 *) LED_5__BIT_MASK)
/* Bypass Enable */
#define LED_5_BYP                    (* (reg8 *) LED_5__BYP)
/* Port wide control signals */                                                   
#define LED_5_CTL                    (* (reg8 *) LED_5__CTL)
/* Drive Modes */
#define LED_5_DM0                    (* (reg8 *) LED_5__DM0) 
#define LED_5_DM1                    (* (reg8 *) LED_5__DM1)
#define LED_5_DM2                    (* (reg8 *) LED_5__DM2) 
/* Input Buffer Disable Override */
#define LED_5_INP_DIS                (* (reg8 *) LED_5__INP_DIS)
/* LCD Common or Segment Drive */
#define LED_5_LCD_COM_SEG            (* (reg8 *) LED_5__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED_5_LCD_EN                 (* (reg8 *) LED_5__LCD_EN)
/* Slew Rate Control */
#define LED_5_SLW                    (* (reg8 *) LED_5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED_5_PRTDSI__CAPS_SEL       (* (reg8 *) LED_5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED_5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED_5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED_5_PRTDSI__OE_SEL0        (* (reg8 *) LED_5__PRTDSI__OE_SEL0) 
#define LED_5_PRTDSI__OE_SEL1        (* (reg8 *) LED_5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED_5_PRTDSI__OUT_SEL0       (* (reg8 *) LED_5__PRTDSI__OUT_SEL0) 
#define LED_5_PRTDSI__OUT_SEL1       (* (reg8 *) LED_5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED_5_PRTDSI__SYNC_OUT       (* (reg8 *) LED_5__PRTDSI__SYNC_OUT) 


#if defined(LED_5__INTSTAT)  /* Interrupt Registers */

    #define LED_5_INTSTAT                (* (reg8 *) LED_5__INTSTAT)
    #define LED_5_SNAP                   (* (reg8 *) LED_5__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins LED_5_H */


/* [] END OF FILE */
