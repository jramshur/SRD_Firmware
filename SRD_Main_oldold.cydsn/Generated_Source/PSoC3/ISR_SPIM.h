/*******************************************************************************
* File Name: ISR_SPIM.h
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

#if !defined(CY_ISR_ISR_SPIM_H)
#define CY_ISR_ISR_SPIM_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ISR_SPIM_Start(void) ;
void ISR_SPIM_StartEx(cyisraddress address) ;
void ISR_SPIM_Stop(void) ;

CY_ISR_PROTO(ISR_SPIM_Interrupt);

void ISR_SPIM_SetVector(cyisraddress address) ;
cyisraddress ISR_SPIM_GetVector(void) ;

void ISR_SPIM_SetPriority(uint8 priority) ;
uint8 ISR_SPIM_GetPriority(void) ;

void ISR_SPIM_Enable(void) ;
uint8 ISR_SPIM_GetState(void) ;
void ISR_SPIM_Disable(void) ;

void ISR_SPIM_SetPending(void) ;
void ISR_SPIM_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ISR_SPIM ISR. */
#define ISR_SPIM_INTC_VECTOR            ((reg16 *) ISR_SPIM__INTC_VECT)

/* Address of the ISR_SPIM ISR priority. */
#define ISR_SPIM_INTC_PRIOR             ((reg8 *) ISR_SPIM__INTC_PRIOR_REG)

/* Priority of the ISR_SPIM interrupt. */
#define ISR_SPIM_INTC_PRIOR_NUMBER      ISR_SPIM__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ISR_SPIM interrupt. */
#define ISR_SPIM_INTC_SET_EN            ((reg8 *) ISR_SPIM__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ISR_SPIM interrupt. */
#define ISR_SPIM_INTC_CLR_EN            ((reg8 *) ISR_SPIM__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ISR_SPIM interrupt state to pending. */
#define ISR_SPIM_INTC_SET_PD            ((reg8 *) ISR_SPIM__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ISR_SPIM interrupt. */
#define ISR_SPIM_INTC_CLR_PD            ((reg8 *) ISR_SPIM__INTC_CLR_PD_REG)



#endif /* CY_ISR_ISR_SPIM_H */


/* [] END OF FILE */
