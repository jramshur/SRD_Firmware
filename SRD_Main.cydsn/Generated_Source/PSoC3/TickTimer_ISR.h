/*******************************************************************************
* File Name: TickTimer_ISR.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_ISR_TickTimer_ISR_H)
#define CY_ISR_TickTimer_ISR_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void TickTimer_ISR_Start(void) ;
void TickTimer_ISR_StartEx(cyisraddress address) ;
void TickTimer_ISR_Stop(void) ;

CY_ISR_PROTO(TickTimer_ISR_Interrupt);

void TickTimer_ISR_SetVector(cyisraddress address) ;
cyisraddress TickTimer_ISR_GetVector(void) ;

void TickTimer_ISR_SetPriority(uint8 priority) ;
uint8 TickTimer_ISR_GetPriority(void) ;

void TickTimer_ISR_Enable(void) ;
uint8 TickTimer_ISR_GetState(void) ;
void TickTimer_ISR_Disable(void) ;

void TickTimer_ISR_SetPending(void) ;
void TickTimer_ISR_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the TickTimer_ISR ISR. */
#define TickTimer_ISR_INTC_VECTOR            ((reg16 *) TickTimer_ISR__INTC_VECT)

/* Address of the TickTimer_ISR ISR priority. */
#define TickTimer_ISR_INTC_PRIOR             ((reg8 *) TickTimer_ISR__INTC_PRIOR_REG)

/* Priority of the TickTimer_ISR interrupt. */
#define TickTimer_ISR_INTC_PRIOR_NUMBER      TickTimer_ISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable TickTimer_ISR interrupt. */
#define TickTimer_ISR_INTC_SET_EN            ((reg8 *) TickTimer_ISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the TickTimer_ISR interrupt. */
#define TickTimer_ISR_INTC_CLR_EN            ((reg8 *) TickTimer_ISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the TickTimer_ISR interrupt state to pending. */
#define TickTimer_ISR_INTC_SET_PD            ((reg8 *) TickTimer_ISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the TickTimer_ISR interrupt. */
#define TickTimer_ISR_INTC_CLR_PD            ((reg8 *) TickTimer_ISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_TickTimer_ISR_H */


/* [] END OF FILE */
