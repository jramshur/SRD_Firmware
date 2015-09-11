/*******************************************************************************
* File Name: AMuxSeq.h
* Version 1.60
*
*  Description:
*    This file contains the constants and function prototypes for the AMuxSeq.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUXSEQ_AMuxSeq_H)
#define CY_AMUXSEQ_AMuxSeq_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void AMuxSeq_Start(void);
void AMuxSeq_Init(void);
void AMuxSeq_Stop(void);
void AMuxSeq_Next(void);
void AMuxSeq_DisconnectAll(void);
int8 AMuxSeq_GetChannel(void);


/***************************************
*     Initial Parameter Constants
***************************************/
#define AMuxSeq_CHANNELS  2
#define AMuxSeq_MUXTYPE   1


/***************************************
*             API Constants
***************************************/

#define AMuxSeq_MUX_SINGLE   1
#define AMuxSeq_MUX_DIFF     2

#endif /* CY_AMUXSEQ_AMuxSeq_H */


/* [] END OF FILE */
