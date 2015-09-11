/*******************************************************************************
* File Name: CounterISR.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_ISR_CounterISR_H)
#define CY_ISR_CounterISR_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void CounterISR_Start(void) ;
void CounterISR_StartEx(cyisraddress address) ;
void CounterISR_Stop(void) ;

CY_ISR_PROTO(CounterISR_Interrupt);

void CounterISR_SetVector(cyisraddress address) ;
cyisraddress CounterISR_GetVector(void) ;

void CounterISR_SetPriority(uint8 priority) ;
uint8 CounterISR_GetPriority(void) ;

void CounterISR_Enable(void) ;
uint8 CounterISR_GetState(void) ;
void CounterISR_Disable(void) ;

void CounterISR_SetPending(void) ;
void CounterISR_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the CounterISR ISR. */
#define CounterISR_INTC_VECTOR            ((reg16 *) CounterISR__INTC_VECT)

/* Address of the CounterISR ISR priority. */
#define CounterISR_INTC_PRIOR             ((reg8 *) CounterISR__INTC_PRIOR_REG)

/* Priority of the CounterISR interrupt. */
#define CounterISR_INTC_PRIOR_NUMBER      CounterISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable CounterISR interrupt. */
#define CounterISR_INTC_SET_EN            ((reg8 *) CounterISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the CounterISR interrupt. */
#define CounterISR_INTC_CLR_EN            ((reg8 *) CounterISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the CounterISR interrupt state to pending. */
#define CounterISR_INTC_SET_PD            ((reg8 *) CounterISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the CounterISR interrupt. */
#define CounterISR_INTC_CLR_PD            ((reg8 *) CounterISR__INTC_CLR_PD_REG)



#endif /* CY_ISR_CounterISR_H */


/* [] END OF FILE */
