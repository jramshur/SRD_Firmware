/*******************************************************************************
* File Name: Pin_StimSel.h  
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

#if !defined(CY_PINS_Pin_StimSel_H) /* Pins Pin_StimSel_H */
#define CY_PINS_Pin_StimSel_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_StimSel_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Pin_StimSel_Write(uint8 value) ;
void    Pin_StimSel_SetDriveMode(uint8 mode) ;
uint8   Pin_StimSel_ReadDataReg(void) ;
uint8   Pin_StimSel_Read(void) ;
uint8   Pin_StimSel_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Pin_StimSel_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Pin_StimSel_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Pin_StimSel_DM_RES_UP          PIN_DM_RES_UP
#define Pin_StimSel_DM_RES_DWN         PIN_DM_RES_DWN
#define Pin_StimSel_DM_OD_LO           PIN_DM_OD_LO
#define Pin_StimSel_DM_OD_HI           PIN_DM_OD_HI
#define Pin_StimSel_DM_STRONG          PIN_DM_STRONG
#define Pin_StimSel_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Pin_StimSel_MASK               Pin_StimSel__MASK
#define Pin_StimSel_SHIFT              Pin_StimSel__SHIFT
#define Pin_StimSel_WIDTH              2u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_StimSel_PS                     (* (reg8 *) Pin_StimSel__PS)
/* Data Register */
#define Pin_StimSel_DR                     (* (reg8 *) Pin_StimSel__DR)
/* Port Number */
#define Pin_StimSel_PRT_NUM                (* (reg8 *) Pin_StimSel__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_StimSel_AG                     (* (reg8 *) Pin_StimSel__AG)                       
/* Analog MUX bux enable */
#define Pin_StimSel_AMUX                   (* (reg8 *) Pin_StimSel__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_StimSel_BIE                    (* (reg8 *) Pin_StimSel__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_StimSel_BIT_MASK               (* (reg8 *) Pin_StimSel__BIT_MASK)
/* Bypass Enable */
#define Pin_StimSel_BYP                    (* (reg8 *) Pin_StimSel__BYP)
/* Port wide control signals */                                                   
#define Pin_StimSel_CTL                    (* (reg8 *) Pin_StimSel__CTL)
/* Drive Modes */
#define Pin_StimSel_DM0                    (* (reg8 *) Pin_StimSel__DM0) 
#define Pin_StimSel_DM1                    (* (reg8 *) Pin_StimSel__DM1)
#define Pin_StimSel_DM2                    (* (reg8 *) Pin_StimSel__DM2) 
/* Input Buffer Disable Override */
#define Pin_StimSel_INP_DIS                (* (reg8 *) Pin_StimSel__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_StimSel_LCD_COM_SEG            (* (reg8 *) Pin_StimSel__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_StimSel_LCD_EN                 (* (reg8 *) Pin_StimSel__LCD_EN)
/* Slew Rate Control */
#define Pin_StimSel_SLW                    (* (reg8 *) Pin_StimSel__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_StimSel_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_StimSel__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_StimSel_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_StimSel__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_StimSel_PRTDSI__OE_SEL0        (* (reg8 *) Pin_StimSel__PRTDSI__OE_SEL0) 
#define Pin_StimSel_PRTDSI__OE_SEL1        (* (reg8 *) Pin_StimSel__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_StimSel_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_StimSel__PRTDSI__OUT_SEL0) 
#define Pin_StimSel_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_StimSel__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_StimSel_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_StimSel__PRTDSI__SYNC_OUT) 


#if defined(Pin_StimSel__INTSTAT)  /* Interrupt Registers */

    #define Pin_StimSel_INTSTAT                (* (reg8 *) Pin_StimSel__INTSTAT)
    #define Pin_StimSel_SNAP                   (* (reg8 *) Pin_StimSel__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Pin_StimSel_H */


/* [] END OF FILE */
