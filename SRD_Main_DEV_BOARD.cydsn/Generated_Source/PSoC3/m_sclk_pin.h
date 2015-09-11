/*******************************************************************************
* File Name: m_sclk_pin.h  
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

#if !defined(CY_PINS_m_sclk_pin_H) /* Pins m_sclk_pin_H */
#define CY_PINS_m_sclk_pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "m_sclk_pin_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    m_sclk_pin_Write(uint8 value) ;
void    m_sclk_pin_SetDriveMode(uint8 mode) ;
uint8   m_sclk_pin_ReadDataReg(void) ;
uint8   m_sclk_pin_Read(void) ;
uint8   m_sclk_pin_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define m_sclk_pin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define m_sclk_pin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define m_sclk_pin_DM_RES_UP          PIN_DM_RES_UP
#define m_sclk_pin_DM_RES_DWN         PIN_DM_RES_DWN
#define m_sclk_pin_DM_OD_LO           PIN_DM_OD_LO
#define m_sclk_pin_DM_OD_HI           PIN_DM_OD_HI
#define m_sclk_pin_DM_STRONG          PIN_DM_STRONG
#define m_sclk_pin_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define m_sclk_pin_MASK               m_sclk_pin__MASK
#define m_sclk_pin_SHIFT              m_sclk_pin__SHIFT
#define m_sclk_pin_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define m_sclk_pin_PS                     (* (reg8 *) m_sclk_pin__PS)
/* Data Register */
#define m_sclk_pin_DR                     (* (reg8 *) m_sclk_pin__DR)
/* Port Number */
#define m_sclk_pin_PRT_NUM                (* (reg8 *) m_sclk_pin__PRT) 
/* Connect to Analog Globals */                                                  
#define m_sclk_pin_AG                     (* (reg8 *) m_sclk_pin__AG)                       
/* Analog MUX bux enable */
#define m_sclk_pin_AMUX                   (* (reg8 *) m_sclk_pin__AMUX) 
/* Bidirectional Enable */                                                        
#define m_sclk_pin_BIE                    (* (reg8 *) m_sclk_pin__BIE)
/* Bit-mask for Aliased Register Access */
#define m_sclk_pin_BIT_MASK               (* (reg8 *) m_sclk_pin__BIT_MASK)
/* Bypass Enable */
#define m_sclk_pin_BYP                    (* (reg8 *) m_sclk_pin__BYP)
/* Port wide control signals */                                                   
#define m_sclk_pin_CTL                    (* (reg8 *) m_sclk_pin__CTL)
/* Drive Modes */
#define m_sclk_pin_DM0                    (* (reg8 *) m_sclk_pin__DM0) 
#define m_sclk_pin_DM1                    (* (reg8 *) m_sclk_pin__DM1)
#define m_sclk_pin_DM2                    (* (reg8 *) m_sclk_pin__DM2) 
/* Input Buffer Disable Override */
#define m_sclk_pin_INP_DIS                (* (reg8 *) m_sclk_pin__INP_DIS)
/* LCD Common or Segment Drive */
#define m_sclk_pin_LCD_COM_SEG            (* (reg8 *) m_sclk_pin__LCD_COM_SEG)
/* Enable Segment LCD */
#define m_sclk_pin_LCD_EN                 (* (reg8 *) m_sclk_pin__LCD_EN)
/* Slew Rate Control */
#define m_sclk_pin_SLW                    (* (reg8 *) m_sclk_pin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define m_sclk_pin_PRTDSI__CAPS_SEL       (* (reg8 *) m_sclk_pin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define m_sclk_pin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) m_sclk_pin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define m_sclk_pin_PRTDSI__OE_SEL0        (* (reg8 *) m_sclk_pin__PRTDSI__OE_SEL0) 
#define m_sclk_pin_PRTDSI__OE_SEL1        (* (reg8 *) m_sclk_pin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define m_sclk_pin_PRTDSI__OUT_SEL0       (* (reg8 *) m_sclk_pin__PRTDSI__OUT_SEL0) 
#define m_sclk_pin_PRTDSI__OUT_SEL1       (* (reg8 *) m_sclk_pin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define m_sclk_pin_PRTDSI__SYNC_OUT       (* (reg8 *) m_sclk_pin__PRTDSI__SYNC_OUT) 


#if defined(m_sclk_pin__INTSTAT)  /* Interrupt Registers */

    #define m_sclk_pin_INTSTAT                (* (reg8 *) m_sclk_pin__INTSTAT)
    #define m_sclk_pin_SNAP                   (* (reg8 *) m_sclk_pin__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins m_sclk_pin_H */


/* [] END OF FILE */
