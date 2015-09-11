/*******************************************************************************
* File Name: P0_5.h  
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

#if !defined(CY_PINS_P0_5_H) /* Pins P0_5_H */
#define CY_PINS_P0_5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "P0_5_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    P0_5_Write(uint8 value) ;
void    P0_5_SetDriveMode(uint8 mode) ;
uint8   P0_5_ReadDataReg(void) ;
uint8   P0_5_Read(void) ;
uint8   P0_5_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define P0_5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define P0_5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define P0_5_DM_RES_UP          PIN_DM_RES_UP
#define P0_5_DM_RES_DWN         PIN_DM_RES_DWN
#define P0_5_DM_OD_LO           PIN_DM_OD_LO
#define P0_5_DM_OD_HI           PIN_DM_OD_HI
#define P0_5_DM_STRONG          PIN_DM_STRONG
#define P0_5_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define P0_5_MASK               P0_5__MASK
#define P0_5_SHIFT              P0_5__SHIFT
#define P0_5_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P0_5_PS                     (* (reg8 *) P0_5__PS)
/* Data Register */
#define P0_5_DR                     (* (reg8 *) P0_5__DR)
/* Port Number */
#define P0_5_PRT_NUM                (* (reg8 *) P0_5__PRT) 
/* Connect to Analog Globals */                                                  
#define P0_5_AG                     (* (reg8 *) P0_5__AG)                       
/* Analog MUX bux enable */
#define P0_5_AMUX                   (* (reg8 *) P0_5__AMUX) 
/* Bidirectional Enable */                                                        
#define P0_5_BIE                    (* (reg8 *) P0_5__BIE)
/* Bit-mask for Aliased Register Access */
#define P0_5_BIT_MASK               (* (reg8 *) P0_5__BIT_MASK)
/* Bypass Enable */
#define P0_5_BYP                    (* (reg8 *) P0_5__BYP)
/* Port wide control signals */                                                   
#define P0_5_CTL                    (* (reg8 *) P0_5__CTL)
/* Drive Modes */
#define P0_5_DM0                    (* (reg8 *) P0_5__DM0) 
#define P0_5_DM1                    (* (reg8 *) P0_5__DM1)
#define P0_5_DM2                    (* (reg8 *) P0_5__DM2) 
/* Input Buffer Disable Override */
#define P0_5_INP_DIS                (* (reg8 *) P0_5__INP_DIS)
/* LCD Common or Segment Drive */
#define P0_5_LCD_COM_SEG            (* (reg8 *) P0_5__LCD_COM_SEG)
/* Enable Segment LCD */
#define P0_5_LCD_EN                 (* (reg8 *) P0_5__LCD_EN)
/* Slew Rate Control */
#define P0_5_SLW                    (* (reg8 *) P0_5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define P0_5_PRTDSI__CAPS_SEL       (* (reg8 *) P0_5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define P0_5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) P0_5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define P0_5_PRTDSI__OE_SEL0        (* (reg8 *) P0_5__PRTDSI__OE_SEL0) 
#define P0_5_PRTDSI__OE_SEL1        (* (reg8 *) P0_5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define P0_5_PRTDSI__OUT_SEL0       (* (reg8 *) P0_5__PRTDSI__OUT_SEL0) 
#define P0_5_PRTDSI__OUT_SEL1       (* (reg8 *) P0_5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define P0_5_PRTDSI__SYNC_OUT       (* (reg8 *) P0_5__PRTDSI__SYNC_OUT) 


#if defined(P0_5__INTSTAT)  /* Interrupt Registers */

    #define P0_5_INTSTAT                (* (reg8 *) P0_5__INTSTAT)
    #define P0_5_SNAP                   (* (reg8 *) P0_5__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins P0_5_H */


/* [] END OF FILE */
