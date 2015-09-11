/*******************************************************************************
* File Name: P0_1.h  
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

#if !defined(CY_PINS_P0_1_H) /* Pins P0_1_H */
#define CY_PINS_P0_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "P0_1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    P0_1_Write(uint8 value) ;
void    P0_1_SetDriveMode(uint8 mode) ;
uint8   P0_1_ReadDataReg(void) ;
uint8   P0_1_Read(void) ;
uint8   P0_1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define P0_1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define P0_1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define P0_1_DM_RES_UP          PIN_DM_RES_UP
#define P0_1_DM_RES_DWN         PIN_DM_RES_DWN
#define P0_1_DM_OD_LO           PIN_DM_OD_LO
#define P0_1_DM_OD_HI           PIN_DM_OD_HI
#define P0_1_DM_STRONG          PIN_DM_STRONG
#define P0_1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define P0_1_MASK               P0_1__MASK
#define P0_1_SHIFT              P0_1__SHIFT
#define P0_1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P0_1_PS                     (* (reg8 *) P0_1__PS)
/* Data Register */
#define P0_1_DR                     (* (reg8 *) P0_1__DR)
/* Port Number */
#define P0_1_PRT_NUM                (* (reg8 *) P0_1__PRT) 
/* Connect to Analog Globals */                                                  
#define P0_1_AG                     (* (reg8 *) P0_1__AG)                       
/* Analog MUX bux enable */
#define P0_1_AMUX                   (* (reg8 *) P0_1__AMUX) 
/* Bidirectional Enable */                                                        
#define P0_1_BIE                    (* (reg8 *) P0_1__BIE)
/* Bit-mask for Aliased Register Access */
#define P0_1_BIT_MASK               (* (reg8 *) P0_1__BIT_MASK)
/* Bypass Enable */
#define P0_1_BYP                    (* (reg8 *) P0_1__BYP)
/* Port wide control signals */                                                   
#define P0_1_CTL                    (* (reg8 *) P0_1__CTL)
/* Drive Modes */
#define P0_1_DM0                    (* (reg8 *) P0_1__DM0) 
#define P0_1_DM1                    (* (reg8 *) P0_1__DM1)
#define P0_1_DM2                    (* (reg8 *) P0_1__DM2) 
/* Input Buffer Disable Override */
#define P0_1_INP_DIS                (* (reg8 *) P0_1__INP_DIS)
/* LCD Common or Segment Drive */
#define P0_1_LCD_COM_SEG            (* (reg8 *) P0_1__LCD_COM_SEG)
/* Enable Segment LCD */
#define P0_1_LCD_EN                 (* (reg8 *) P0_1__LCD_EN)
/* Slew Rate Control */
#define P0_1_SLW                    (* (reg8 *) P0_1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define P0_1_PRTDSI__CAPS_SEL       (* (reg8 *) P0_1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define P0_1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) P0_1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define P0_1_PRTDSI__OE_SEL0        (* (reg8 *) P0_1__PRTDSI__OE_SEL0) 
#define P0_1_PRTDSI__OE_SEL1        (* (reg8 *) P0_1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define P0_1_PRTDSI__OUT_SEL0       (* (reg8 *) P0_1__PRTDSI__OUT_SEL0) 
#define P0_1_PRTDSI__OUT_SEL1       (* (reg8 *) P0_1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define P0_1_PRTDSI__SYNC_OUT       (* (reg8 *) P0_1__PRTDSI__SYNC_OUT) 


#if defined(P0_1__INTSTAT)  /* Interrupt Registers */

    #define P0_1_INTSTAT                (* (reg8 *) P0_1__INTSTAT)
    #define P0_1_SNAP                   (* (reg8 *) P0_1__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins P0_1_H */


/* [] END OF FILE */
