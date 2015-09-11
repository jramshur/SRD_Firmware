/*******************************************************************************
* File Name: Input_Channel_2.h  
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

#if !defined(CY_PINS_Input_Channel_2_H) /* Pins Input_Channel_2_H */
#define CY_PINS_Input_Channel_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Input_Channel_2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Input_Channel_2_Write(uint8 value) ;
void    Input_Channel_2_SetDriveMode(uint8 mode) ;
uint8   Input_Channel_2_ReadDataReg(void) ;
uint8   Input_Channel_2_Read(void) ;
uint8   Input_Channel_2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Input_Channel_2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Input_Channel_2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Input_Channel_2_DM_RES_UP          PIN_DM_RES_UP
#define Input_Channel_2_DM_RES_DWN         PIN_DM_RES_DWN
#define Input_Channel_2_DM_OD_LO           PIN_DM_OD_LO
#define Input_Channel_2_DM_OD_HI           PIN_DM_OD_HI
#define Input_Channel_2_DM_STRONG          PIN_DM_STRONG
#define Input_Channel_2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Input_Channel_2_MASK               Input_Channel_2__MASK
#define Input_Channel_2_SHIFT              Input_Channel_2__SHIFT
#define Input_Channel_2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Input_Channel_2_PS                     (* (reg8 *) Input_Channel_2__PS)
/* Data Register */
#define Input_Channel_2_DR                     (* (reg8 *) Input_Channel_2__DR)
/* Port Number */
#define Input_Channel_2_PRT_NUM                (* (reg8 *) Input_Channel_2__PRT) 
/* Connect to Analog Globals */                                                  
#define Input_Channel_2_AG                     (* (reg8 *) Input_Channel_2__AG)                       
/* Analog MUX bux enable */
#define Input_Channel_2_AMUX                   (* (reg8 *) Input_Channel_2__AMUX) 
/* Bidirectional Enable */                                                        
#define Input_Channel_2_BIE                    (* (reg8 *) Input_Channel_2__BIE)
/* Bit-mask for Aliased Register Access */
#define Input_Channel_2_BIT_MASK               (* (reg8 *) Input_Channel_2__BIT_MASK)
/* Bypass Enable */
#define Input_Channel_2_BYP                    (* (reg8 *) Input_Channel_2__BYP)
/* Port wide control signals */                                                   
#define Input_Channel_2_CTL                    (* (reg8 *) Input_Channel_2__CTL)
/* Drive Modes */
#define Input_Channel_2_DM0                    (* (reg8 *) Input_Channel_2__DM0) 
#define Input_Channel_2_DM1                    (* (reg8 *) Input_Channel_2__DM1)
#define Input_Channel_2_DM2                    (* (reg8 *) Input_Channel_2__DM2) 
/* Input Buffer Disable Override */
#define Input_Channel_2_INP_DIS                (* (reg8 *) Input_Channel_2__INP_DIS)
/* LCD Common or Segment Drive */
#define Input_Channel_2_LCD_COM_SEG            (* (reg8 *) Input_Channel_2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Input_Channel_2_LCD_EN                 (* (reg8 *) Input_Channel_2__LCD_EN)
/* Slew Rate Control */
#define Input_Channel_2_SLW                    (* (reg8 *) Input_Channel_2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Input_Channel_2_PRTDSI__CAPS_SEL       (* (reg8 *) Input_Channel_2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Input_Channel_2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Input_Channel_2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Input_Channel_2_PRTDSI__OE_SEL0        (* (reg8 *) Input_Channel_2__PRTDSI__OE_SEL0) 
#define Input_Channel_2_PRTDSI__OE_SEL1        (* (reg8 *) Input_Channel_2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Input_Channel_2_PRTDSI__OUT_SEL0       (* (reg8 *) Input_Channel_2__PRTDSI__OUT_SEL0) 
#define Input_Channel_2_PRTDSI__OUT_SEL1       (* (reg8 *) Input_Channel_2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Input_Channel_2_PRTDSI__SYNC_OUT       (* (reg8 *) Input_Channel_2__PRTDSI__SYNC_OUT) 


#if defined(Input_Channel_2__INTSTAT)  /* Interrupt Registers */

    #define Input_Channel_2_INTSTAT                (* (reg8 *) Input_Channel_2__INTSTAT)
    #define Input_Channel_2_SNAP                   (* (reg8 *) Input_Channel_2__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Input_Channel_2_H */


/* [] END OF FILE */
