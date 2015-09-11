/* ========================================
 *
 * Copyright John Ramshur, 2013
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF John Ramshur.
 *
 * ========================================
*/
#include <device.h>
#include <stdio.h>
#include <Parser.h>
#include <string.h>
#include "INTAN.h"
#include <COMM_UART.h>
#include "math.h"

/* Defines for controlling current steering */
#define STIM_SINK 2 	// Connect current sinking IDAC (2)
#define STIM_SOURCE 0 	// Connect current sourceing IDAC (0)
#define STIM_OPEN 1 	// open or no connection (1)
#define STIM_GROUND 3 	// Ground electrode (3)

/* DMA Configuration for DMA_1 */
#define DMA_1_REQUEST_PER_BURST 1
#define DMA_1_SRC_BASE (CYDEV_SRAM_BASE)
#define DMA_1_DST_BASE (CYDEV_PERIPH_BASE)

/* DMA Configuration for DMA_3 */
#define DMA_3_REQUEST_PER_BURST 1
#define DMA_3_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_3_DST_BASE (CYDEV_SRAM_BASE)

/* DMA Configuration for DMA_ */
#define DMA_2_REQUEST_PER_BURST     1
#define DMA_2_SRC_BASE (CYDEV_SRAM_BASE)
#define DMA_2_DST_BASE (CYDEV_PERIPH_BASE)
//#define DMA_2_DST_BASE (CYDEV_SRAM_BASE)

/* Timer multiplying factors */
/* Timer 1*/
#define MUL_FACTOR_MSEC_TIMER_1   2000   /*multiplying factor for  msec timer timer_1*/
#define MUL_FACTOR_USEC_TIMER_1   2  	/*multiplying factor for usec timer timer_1 */

/* timer 3 */
#define MUL_FACTOR_HOUR_TIMER_3  900000 /* Multiplying factor for hour timer Timer_3*/
#define MUL_FACTOR_MIN_TIMER_3    15000 /* Multiplying factor for minutes timer Timer_3*/
#define MUL_FACTOR_SEC_TIMER_3    250 	/* Multiplying factor for second timer Timer_3*/

 /* Variable declarations for DMA_1 */
uint8 DMA_1_Chan;
uint8 DMA_1_TD[2];

uint8 DMA_3_Chan;
uint8 DMA_3_TD[2];

/* Variable declarations for DMA_2 */
uint8 DMA_2_Chan;
uint8 DMA_2_TD[2];

/* Configurable parameters */
uint8 T5DACVal = 255, T7DACVal = 255, NumberOfChannels = 12;
/* default timing parameters */
uint16 TimerArray[MAX_TIMER] = {10,10,120,120,10,20,10,10,10,1000};
int ADCChannels[ADC_MAX_CH] = {1, 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 , 12};
uint32 SamplingRateValues[9] = {1000 , 2000 , 3000 , 4000 , 5000 , 6000 , 10000 , 12500 , 15000 };
uint8 DataRcvd[MAX_PAYLOAD_SIZE];
uint8 tmpstr[BUFFER_SIZE];
uint8 UARTBuffer[MAX_DATA_SIZE];
uint8 RespBuffer[MAX_DATA_SIZE];
uint8 ADCBuffer[ADC_DATA_BUFF] _at_ 0x20;
uint8 OperationalMode = TRIGGER_MODE;
uint16 ChannelNumber = 1;
uint16 ADCSamplingRate = 1;
uint16 SamplingRateVal, BytesTransfer = 0;
uint8 switchFlag1 = 0, DMA1DoneFlag;
uint8 TriggerSwitchFlag = 0;
uint8 DataReceived, TriggerDSN, UartRXIndex, State, StatusRegister, DMAIntrptCnt, TimerExpired = 1;
uint8 ConversionComplete = 1;
volatile uint8 StartCont; 
uint32 VdacPulseTime = 0;
uint8  T3Cnt = 0, StartADCConversion = 0;
uint16 T4Cnt = 0;
uint16 TransactionNumber = 0;
uint8 DMA1TransferDone = 0;
uint8 GoToSleep =0;
uint16 SleepTicks = 0;
uint16 CalculatedSleepTicks = 0;
uint16 interruptCnt;
uint16 ChannelOffset = 0;
uint8 ShiftCnt = 0;
int CHCnt = 0;
uint8 DMAStatus = 0;
uint16 CurrentChannel = 0;
uint16 ADCvalue = 0;
uint8 LookAheadFix = 0;
uint16 recoveryRetry = 0;
uint8 DeviceInitComplete = 0;

extern uint8 DMAState;
extern uint8 DMAIsr1IntCnt;
extern uint8 DMAIsr2IntCnt;
extern uint8 DMAIsr3IntCnt;
extern volatile uint8 EOCInt;
extern uint16 EOC;
extern uint8 DMABusy;

#define API_SUPPORT
#ifdef API_SUPPORT
uint8 SPI_ReadData(uint16 command, uint16 *dataPtr, uint8 length);
uint8 SPI_WriteData(uint16 command, uint16 *dataPtr, uint8 length);
void INTAN_Configuration(void);
#endif

uint8 TXCommandBuffer[4] = {0x00, 0x00, 0x00, 0x00};

// Function Declarations
void InitDMA_1();
void ConfigureDMA_1();
void InitDMA_2();
void ConfigureDMA_2();
void InitDMA_3();
void ConfigureDMA_3();
void CalculateSamplingRate(uint8 Index);
void CalculateParamsVal();
uint16 Calculate_CH(uint16 Offset);
void SendStartOfPacket();
void SendEndOfPacket();

		
/*******************************************************************************
* Define Interrupt service routine and allocate an vector to the Interrupt
********************************************************************************/
CY_ISR(InterruptHandler_1) //ignore the "function body" error  // Timer3's ISR
{
    GoToSleep = 0;
	StatusRegister = Timer_3_ReadStatusRegister();
	Timer_1_Start();
	Timer_1_WriteCounter(1 * MUL_FACTOR_USEC_TIMER_1);
	Timer_1_WritePeriod((TimerArray[8] + 2) * 100 * MUL_FACTOR_USEC_TIMER_1);
	Timer_3_Stop();
}

CY_ISR(InterruptHandler) // Timer1's ISR
{
    uint32 Time = 0;
    uint32 Time_new = 0;
    uint8 i=0 , Indx =0 ;
    StatusRegister = Timer_1_ReadStatusRegister();
    TimerExpired = 0;

    if((OperationalMode == TRIGGER_MODE) && (T4Cnt >= (TimerArray[3]/10)))
    {
       /*Go to sleep if total number of epochs overlapped */
        T4Cnt = 0;
        T3Cnt = 0;
        Timer_1_Stop();

		DEBUG_UART_PutString("Entering sleep\r\n");  
		GoToSleep = 1;
    }
    else if((T3Cnt >= (TimerArray[2]/10)) && (OperationalMode == TRIGGER_MODE))
    {         
        /*Stop generation of VDAC pulses if total number of traces overlapped  */
        {  
            T3Cnt = 0;
            Time  = 0; //why do we need to set this to 0 then another value below?
            Time_new = 0; //why do we need to set this to 0 then another value below?
            Time = (VdacPulseTime * 1000);
            Time_new = (TimerArray[2] * TimerArray[7] * 10);
            Time =   Time - Time_new;
            if(Time < 8000)
                Timer_1_WritePeriod(Time * MUL_FACTOR_MSEC_TIMER_1);
            else 
            {
                Time_new = (Time /1000 ) * MUL_FACTOR_SEC_TIMER_3;
				Timer_3_Start();
                Timer_3_WriteCounter(Time_new);
                Timer_1_Stop();
            }           

            T4Cnt++;
			//sprintf(tmpstr, "T4Cnt: %d\r\n", (uint16)T4Cnt);
    		//DEBUG_UART_PutString(tmpstr);
            State = 1;
        }
    }
    else if((StartCont == 0) && (OperationalMode == CONTINUOUS_MODE))
    {
        Timer_1_Stop();
    }
    else
    {   /*state machine to generate VDAC pulse*/
		//Control_Reg_StimSel_Write(STIM_SINK); //switch mux	
        switch(State)
        {
			case 1:
			Control_Reg_StimSel_Write(STIM_GROUND); //switch mux	
			IDAC8_Sink_SetValue(0);
				
				
				Timer_1_WritePeriod(TimerArray[4] * 100 * MUL_FACTOR_USEC_TIMER_1);	
				//Pin_2_Write(1);
				
				ConversionComplete = 0;
                if(OperationalMode == TRIGGER_MODE)
                {
                   	StartADCConversion = 1;
				   	//DEBUG_UART_PutString("SOC - TRIGGER\r\n");
                }
                //DEBUG_UART_PutString("1\r\n");  
				State = 2;
				break;
                
            case 2: //Stim: Phase 1
				//SPI_WriteData(INTAN_REG_0_FS, NULL, 0);
			    Control_Reg_StimSel_Write(STIM_SINK); //switch mux
				IDAC8_Sink_SetValue(T5DACVal);
				
				
				//Timer_1_Start();
               	//DEBUG_UART_PutString("2\r\n");
                if(TimerArray[5])
				{
					Timer_1_WritePeriod(TimerArray[5] * 100 * MUL_FACTOR_USEC_TIMER_1);
					State = 3;
				}
				else // **** BUG: if T6=0 then IDAC8_Sink is never set back to 0 because case 3 is skipped.
				{
					if(TimerArray[6])
					{	
						Timer_1_WritePeriod(TimerArray[6] * 100 * MUL_FACTOR_USEC_TIMER_1);
						State = 4;
					}
					else
					{
						Timer_1_WritePeriod(1 * 10 * MUL_FACTOR_USEC_TIMER_1);
						State = 4;
					}
				}
                break;

            case 3: //Stim: Inter-Phase Delay between biphasic waveforms
			  	
				// **** BUG: if T6=0 then IDAC8_Sink is never set back to 0 because this case is skipped.
				
				Control_Reg_StimSel_Write(STIM_GROUND); //switch mux
				IDAC8_Sink_SetValue(0);
				
                
				Timer_1_WritePeriod(TimerArray[6] * 100 * MUL_FACTOR_USEC_TIMER_1);
	            //DEBUG_UART_PutString("3\r\n");
                State = 4;
				break;
                
            case 4: // Stim: Phase 2
				if(TimerArray[6]){
					Control_Reg_StimSel_Write(STIM_SOURCE); //switch mux
					IDAC8_Source_SetValue(T7DACVal); 
					
                }
				else {
					Control_Reg_StimSel_Write(STIM_GROUND); //switch mux
					IDAC8_Source_SetValue(0); 
					
                }    
					
                if(OperationalMode == TRIGGER_MODE)
                {
                    Time_new = 0;
                    Time = 0;
                    Time = (TimerArray[7] * 100);
                    Time *= 1000;
                    Time_new = ((TimerArray[4] + TimerArray[5] + TimerArray[6] + TimerArray[8]) * 100);
                    Time = (Time - Time_new);
                    Timer_1_WritePeriod( Time * MUL_FACTOR_USEC_TIMER_1);
                }
				//sprintf(tmpstr, "Time: 0x%x%x\r\n", (uint16) (Time >> 16), ((uint16) Time));
    			//DEBUG_UART_PutString(tmpstr);
                State = 5;

				break;
                
            case 5: // Stim: Inter-Stim Interval
                T3Cnt++;
				Control_Reg_StimSel_Write(STIM_GROUND); //switch mux
				IDAC8_Source_SetValue(0);
				//SPI_WriteData(INTAN_REG_0_DEF, NULL, 0);
				
              	
				//DEBUG_UART_PutString("5\r\n");
                State = 1;
                if(OperationalMode == TRIGGER_MODE)
                {
                    Timer_1_WritePeriod((TimerArray[8] + 2) * 100 * MUL_FACTOR_USEC_TIMER_1);
                }
                else if((OperationalMode == EXT_STIMULATION_TRIGGER_MODE))
                {
                    //DEBUG_UART_PutString("Stop\r\n");
                    T3Cnt = 0;
                    Timer_1_Stop();
                    State = 0;
                }
                break;
		}
    }
}

void ADC_StartConvert()
{
	uint16 i = 0 , ADCData = 0, offset = 0 ,CH = 0;
	//DEBUG_UART_PutString("ADC_StartConvert \r\n");	
	//sprintf(tmpstr, " ADC conv BytesTransfer = [%d] \r\n", BytesTransfer);
   // DEBUG_UART_PutString(tmpstr);

	// Fill Tx buffer with commands
	//memset(TXCommandBuffer , 0 , 4);
	//SPIM_Stop();
	//COMM_UART_ClearTxBuffer();
	SPIM_ClearRxBuffer();
	SPIM_ClearTxBuffer();
	
	if(NumberOfChannels >=2) 
	{
		TXCommandBuffer[1] = (uint8)ADCChannels[ChannelOffset+1] >> 8;
		TXCommandBuffer[0] = (uint8)ADCChannels[ChannelOffset+1];
		TXCommandBuffer[3] = (uint8)ADCChannels[ChannelOffset] >> 8;
		TXCommandBuffer[2] = (uint8)ADCChannels[ChannelOffset];
	}
	else
	{
		TXCommandBuffer[0] = (uint8)ADCChannels[0];
		TXCommandBuffer[1] = (uint8)ADCChannels[0] >> 8;
		TXCommandBuffer[2] = (uint8)ADCChannels[0];
		TXCommandBuffer[3] = (uint8)ADCChannels[0] >> 8;
	}

//
//	sprintf(tmpstr, "ChannelOffset = [%d] \r\n",ChannelOffset );
//   	DEBUG_UART_PutString(tmpstr);
	
	// Configure DMA 1 & 3
	//sprintf(tmpstr, "TX: [%x][%x][%x][%x]\r\n", (uint16)TXCommandBuffer[0], (uint16)TXCommandBuffer[1],
	//									(uint16)TXCommandBuffer[2], (uint16)TXCommandBuffer[3]);
   	//DEBUG_UART_PutString(tmpstr);
	ConfigureDMA_3();
	
	/*configure SPI Master*/
	SPIM_Start();
	//Pin_4_Write(0);
	//DEBUG_UART_PutString("SPIS\r\n");
	//Pin_3_Write(0);
}

/*******************************************************************************
* MAIN
********************************************************************************/
int main()
{
	uint16 Data = 0;
	uint8 cntr = 0;
	
    /* Set 32kHz xtal to lowest power in Sleep and Hibernate. */
	CyXTAL_32KHZ_SetPowerMode(CY_X32_LOWPOWER_MODE);
          	 
	//Pin_4_Write(1);
	
   
	    
    /*Start isr connected to switch pin*/
	ISR_Switch_1_Start();
               
    Timer_1_Init();
    Timer_3_Init();
	
	Timer_1_Start();
    Timer_1_WriteCounter((TimerArray[8] + 12) * 100 * MUL_FACTOR_USEC_TIMER_1);
	Timer_1_Stop();
	    
	/* Configur DMA ISR */
	DMA_ISR_Start();
    DMA_ISR_Enable();
        
    /* Configur DMA ISR 1*/
	DMA_ISR_1_Start();
    DMA_ISR_1_Enable();
    
    /* Configur DMA ISR 1*/
	DMA_ISR_2_Start();
    DMA_ISR_2_Disable();
	
    /* Configur DMA ISR 1*/
	DMA_ISR_3_Start();
    DMA_ISR_3_Enable();
	
	/* Init DMA 1*/
	InitDMA_1();
	InitDMA_2();
	InitDMA_3();   
	   
    /* Start VDAC */
    IDAC8_Sink_Start();
	IDAC8_Source_Start();
       
    /* Enabling the UART */
    DEBUG_UART_Start();   
    COMM_UART_Start();
    ISR_COMM_UART_RX_Start();
    DEBUG_UART_PutString("\r\n MAIN \r\n");

    //TimerISR_1_Start();
    //TimerISR_1_Disable();
    
    /* Allocate interrupt handler and set vector to the interrupt*/
    //TimerISR_1_SetVector(InterruptHandler);
    //TimerISR_1_Enable();
	TimerISR_1_StartEx(InterruptHandler);

    /* Start Tick Timer */
    TickTimer_ISR_Start();
    TickTimer_ISR_Enable();
    
     /*Enable the Interrupt component connected to Timer interrupt*/
    //TimerISR_3_Start();
    //TimerISR_3_Enable();
    TimerISR_3_StartEx(InterruptHandler_1);
      
	clock_3_Enable();
	PWM_1_Start();
	
    SetADCConfiguration(ADCSamplingRate);
	CalculateSamplingRate(ADCSamplingRate);
	CalculateParamsVal();
    
    //State = 1;
	//DMA_ISR_4_Start();
    //DMA_ISR_4_Enable();
	
	/* enable global interrupts. */
    CyGlobalIntEnable;
    
	
	//Set initial value to 0
	IDAC8_Sink_SetValue(0);
	IDAC8_Source_SetValue(0);
	
	//Pin_2_Write(0);
	//Pin_3_Write(0);

    
	#ifdef API_SUPPORT	
		SPIM_Start();
		
		SPI_ReadData(INTAN_REG_40_DEF, &Data, 1);
		sprintf(tmpstr, " Cmd = [%x] Data [%x]\r\n", (uint16) INTAN_REG_40_DEF, (uint16) Data);
		DEBUG_UART_PutString(tmpstr);
		
		SPI_ReadData(INTAN_REG_41_DEF, &Data, 1);
		sprintf(tmpstr, " Cmd = [%x] Data [%x]\r\n", (uint16) INTAN_REG_41_DEF, (uint16) Data);
		DEBUG_UART_PutString(tmpstr);
		
		SPI_ReadData(INTAN_REG_42_DEF, &Data, 1);
		sprintf(tmpstr, " Cmd = [%x] Data [%x]\r\n", (uint16) INTAN_REG_42_DEF, (uint16) Data);
		DEBUG_UART_PutString(tmpstr);
		
		SPI_ReadData(INTAN_REG_43_DEF, &Data, 1);
		sprintf(tmpstr, " Cmd = [%x] Data [%x]\r\n", (uint16) INTAN_REG_43_DEF, (uint16) Data);
		DEBUG_UART_PutString(tmpstr);
		
		SPI_ReadData(INTAN_REG_44_DEF, &Data, 1);
		sprintf(tmpstr, " Cmd = [%x] Data [%x]\r\n", (uint16) INTAN_REG_44_DEF, (uint16) Data);
		DEBUG_UART_PutString(tmpstr);

		INTAN_Configuration();
		
		SPIM_ClearFIFO();
		SPIM_Stop();
	#endif
	
	DeviceInitComplete = 1;
    
    LED_B_Write(1); // turn on LED
	
    for(;;)
    {
        /* Check if we are operating the external trigger mode */
        if(OperationalMode == LOOK_AHEAD_EXT_TRIGGER_MODE)
        {
            int CntBuff1 = 0, CntBuff2 = 0, T9Bytes = 0, ByteConversionComplete = 0;
			uint16 i = 0;
            cystatus status;
			
            /* On external trigger pulse total of T10 milliseconds of data to be sent to the PC.
            T9 ms of data occurred before the external trigger 
            T10-T9 ms of data that occurred after the trigger pulse */
            T9Bytes = (BytesTransfer * (TimerArray[8]/10));
            T9Bytes = (T9Bytes / (TimerArray[9]/10));
            
            sprintf(tmpstr, "T9Bytes = [%d]\r\n", T9Bytes);
            DEBUG_UART_PutString(tmpstr);

			sprintf(tmpstr, "ADCchan = [%d]\r\n", (uint16) ADCChannels[0]);
			DEBUG_UART_PutString(tmpstr);						
            
			//DMA_ISR_1_Disable();
            DMA_ISR_Disable();
            DMAIsr2IntCnt = 0;
            DMA_ISR_2_Enable();
			ISR_Switch_1_Enable();
            status = CyDmaChDisable(DMA_1_Chan);
			if(status != CYRET_SUCCESS)
				DEBUG_UART_PutString("Chan1 disable error\r\n");
			status = CyDmaChDisable(DMA_2_Chan);
			if(status != CYRET_SUCCESS)
				DEBUG_UART_PutString("Chan2 disable error\r\n");
			status = CyDmaChDisable(DMA_3_Chan);
			if(status != CYRET_SUCCESS)
				DEBUG_UART_PutString("Chan3 disable error\r\n");
			SPIM_Stop();
			//Pin_4_Write(1);
			
			EOCInt = 0;
			/*configure SPI Master*/
			SPIM_ClearRxBuffer();
			SPIM_ClearTxBuffer();
			SPIM_Start();
			//Pin_4_Write(0);
			
            /*continuously sample ONE channel of data in look ahead extrenal trigger mode*/
            while((OperationalMode == LOOK_AHEAD_EXT_TRIGGER_MODE) && (DataReceived != 1))
            {
				if(ByteConversionComplete == 0)
				{
				 	//DEBUG_UART_PutString("## \r\n");  
					while( ! (SPIM_ReadTxStatus() & SPIM_STS_TX_FIFO_EMPTY ) );
					SPIM_WriteTxData(ADCChannels[0]);
					SPIM_WriteTxData(0);
				}
					
                if((EOCInt >= 1) && (!switchFlag1))
                {	
					if(EOCInt == 1)
						ADCvalue = SPIM_ReadRxData();
					else if(EOCInt >= 2)
					{
						ADCvalue |= (SPIM_ReadRxData() << 8);
						EOCInt = 0;	
					}
					
//					sprintf(tmpstr, "ADCvalue = [%d] \r\n", (uint16) ADCvalue);
//					DEBUG_UART_PutString(tmpstr);
//					
					ADCBuffer[CntBuff1] = (uint8)((ADCvalue >> 8) & 0xFF);
                    CntBuff1++;
                    ADCBuffer[CntBuff1] = (uint8)(ADCvalue & 0xFF);
                    CntBuff1++;

//					sprintf(tmpstr, "* CntBuff1 = [%d] \r\n", CntBuff1);
//                  DEBUG_UART_PutString(tmpstr);
                    if(CntBuff1 >= T9Bytes)
                        CntBuff1 = 0;   
                }
                else if((EOCInt >= 1) && (switchFlag1))
                {	
					if(EOCInt == 1)
						ADCvalue = SPIM_ReadRxData();
					else if(EOCInt >= 2)
					{
						ADCvalue |= (SPIM_ReadRxData() << 8);
						EOCInt = 0;
					}
					
//					sprintf(tmpstr, "*ADCvalue = [%d] \r\n", (uint16) ADCvalue);
//					DEBUG_UART_PutString(tmpstr);
//					
					ADCBuffer[(ADC_DATA_BUFF + 1000) + CntBuff2] = (uint8) ((ADCvalue >> 8) & 0xFF);
                    CntBuff2++;                 		
                    ADCBuffer[(ADC_DATA_BUFF + 1000) + CntBuff2] = (uint8) (ADCvalue & 0xFF);
                    CntBuff2++;
                    
//					sprintf(tmpstr, "* CntBuff2 = [%d] \r\n", CntBuff2);
//                    DEBUG_UART_PutString(tmpstr);
										
                    if(CntBuff2 > BytesTransfer)
                    {
                        SendStartOfPacket();
                        DMAIsr2IntCnt = 0;
                        switchFlag1 = 0;
						SPIM_Stop();
						//Pin_4_Write(1);
						
						ByteConversionComplete = 1;   
                    }    
                }
                /* After capture complete */
                if(ByteConversionComplete)
                {
                    /* Copy CntBuff1 = T9 ms of data occurred before the external trigger */
                    for(i=(CntBuff1);i<T9Bytes;)
                    {
                        //DEBUG_UART_PutString("1");
                        DMAStatus = COMM_UART_ReadTxStatus();
                        if((DMAStatus & COMM_UART_TX_STS_FIFO_EMPTY) == COMM_UART_TX_STS_FIFO_EMPTY)
                        {
                            COMM_UART_PutArray(&ADCBuffer[i], 2);
                            i+= 2;     
                        }
                    }
                    for(i=0;i<CntBuff1;)
                    {
                        //DEBUG_UART_PutString("2");
                        DMAStatus = COMM_UART_ReadTxStatus();
                        if((DMAStatus & COMM_UART_TX_STS_FIFO_EMPTY) == COMM_UART_TX_STS_FIFO_EMPTY)
                        {
                            COMM_UART_PutArray(&ADCBuffer[i], 2);
                            i+= 2;
                        }  
                    }
					
				
                    /* Copy T10-T9 ms of data that occurred after the trigger pulse */
                    for(i=0;i<(BytesTransfer - T9Bytes);)
                    {
                    	//DEBUG_UART_PutString("3");
                        DMAStatus = COMM_UART_ReadTxStatus();
                        if((DMAStatus & COMM_UART_TX_STS_FIFO_EMPTY) == COMM_UART_TX_STS_FIFO_EMPTY)
                        {
                            COMM_UART_PutArray(&ADCBuffer[(ADC_DATA_BUFF + 1000) + i], 2);  
                            i+= 2;
                        }       
					}
                    SendEndOfPacket();
                    CntBuff1 = 0;
                    CntBuff2 = 0;
					ByteConversionComplete = 0; 
					SPIM_Start();
					//Pin_4_Write(0);
   					break;
                }
            }
			
			if(DataReceived == 1)
			{
				DEBUG_UART_PutString("Clear LookAhead\r\n");
				while(!(SPIM_ReadTxStatus() & SPIM_STS_TX_FIFO_EMPTY ));
				DEBUG_UART_PutString("Tx complete\r\n");
				while((SPIM_ReadRxStatus() & SPIM_STS_RX_FIFO_NOT_EMPTY))
				{
					ADCvalue = SPIM_ReadRxData();
					DEBUG_UART_PutString(".");
				}
				
				EOCInt = 0;
				CntBuff1 = 0;
                CntBuff2 = 0;
				ByteConversionComplete = 0;
				DMAIsr2IntCnt = 0;
            	DMA_ISR_2_Disable();
				SPIM_Stop();
				//Pin_4_Write(1);
				
				status = CyDmaChFree(DMA_1_Chan);
				if(status != CYRET_SUCCESS)
					DEBUG_UART_PutString("Chan1 free error\r\n");
				CyDmaTdFree(DMA_1_TD[0]);
				status = CyDmaChFree(DMA_3_Chan);
				if(status != CYRET_SUCCESS)
					DEBUG_UART_PutString("Chan3 free error\r\n");
				CyDmaTdFree(DMA_3_TD[0]);
				CyDmaTdFree(DMA_3_TD[1]);
				InitDMA_1();
				InitDMA_3();
				LookAheadFix = 1;
			}
        }
        
        if(GoToSleep == 1)
        {                 
			/* Launch low-power routine. */
            /* Prepare for Sleep and enter it. */
            sprintf(tmpstr, "BytesTransfer = [%d] \r\n", BytesTransfer);
    		DEBUG_UART_PutString(tmpstr);
			
          
		  	SleepTicks = 0;
			/* Prepare for Sleep and start RTC. */
			CyDmaChDisable(DMA_1_Chan);
			CyDmaChDisable(DMA_2_Chan);
			CyDmaChDisable(DMA_3_Chan);		
			CyDmaTdFree(DMA_1_TD[0]);
			CyDmaTdFree(DMA_2_TD[0]);
			CyDmaTdFree(DMA_2_TD[1]);
			CyDmaTdFree(DMA_3_TD[0]);
			CyDmaTdFree(DMA_3_TD[1]);
			
			SPIM_Stop();
			//Pin_4_Write(1);
			
			/*configure SPI Master*/
			SPIM_ClearRxBuffer();
			SPIM_ClearTxBuffer();
			PWM_1_Stop();
			SleepComponents();			
			RTC_Start();
			RTC_EnableInt();
	
			/* Go to Sleep and stay in low-power mode until the button is pressed again. */
			do
			{
				CyPmSaveClocks();
                
				/* Enter low power. */
				CyPmSleep(PM_SLEEP_TIME_NONE, PM_SLEEP_SRC_ONE_PPS | PM_SLEEP_SRC_PICU);
          
				/* The PSoC wakes up here. Clear wakeup interrupts. */
				CyPmRestoreClocks();
                
                if(SleepTicks++ >= CalculatedSleepTicks)
                {
                    SleepTicks = 0;
                    GoToSleep = 0;
               //     StatusRegister = Timer_3_ReadStatusRegister();
                }
                
				
                
            } while((Button_ClearInterrupt() == 0) && (GoToSleep == 1));
            
            /* Restore everything after Sleep. */
			SleepTicks = 0;
			GoToSleep = 0;
			RTC_Stop();
           
			/*configure SPI Master*/
			SPIM_ClearRxBuffer();
			SPIM_ClearTxBuffer();
			
			//SPIM_Start();
//			/* Init DMA 1*/
			InitDMA_1();
			InitDMA_2();
			InitDMA_3();			
//			CalculateSamplingRate(ADCSamplingRate);
			WakeComponents();
    		DMA_ISR_3_Enable();
			sprintf(tmpstr, "* BytesTransfer = [%d] \r\n", BytesTransfer);
    		DEBUG_UART_PutString(tmpstr);  		
			PWM_1_Start();
			SetADCConfiguration(ADCSamplingRate);
			
            Timer_1_Start();
            Timer_1_WriteCounter(1 * MUL_FACTOR_USEC_TIMER_1);
            Timer_1_WritePeriod((TimerArray[8] + 2) * 100 * MUL_FACTOR_USEC_TIMER_1);
         //  Timer_3_Stop();
		}
        
        if(DMA1TransferDone)
        {
            DMA1TransferDone = 0;
            TransactionNumber++;
        //    Pin_3_Write(1);
			//sprintf(tmpstr, "EOC - Sending pkt - %d\r\n", TransactionNumber);
            //DEBUG_UART_PutString(tmpstr);
			
			ConfigureDMA_2();
			while(!ConversionComplete);
			//ConversionComplete = 0;
            //DEBUG_UART_PutString();
			
//            while(!ConversionComplete)
//            {
//                DMAStatus = COMM_UART_ReadTxStatus();
//                if((DMAStatus & COMM_UART_TX_STS_FIFO_EMPTY) == COMM_UART_TX_STS_FIFO_EMPTY)
//                    CyDmaChSetRequest(DMA_2_Chan, CPU_REQ);
//            }

            if((TransactionNumber != 2) && (NumberOfChannels >= 2))
            {
                ConversionComplete = 0;
            }
			
            if((StartCont == 2) && (OperationalMode == CONTINUOUS_MODE))
            {
                ConversionComplete = 0;
                StartADCConversion = 1;
            }
        //    DEBUG_UART_PutString("D2: 2\r\n");
        }
        
        /*Start ADC conversion*/
        if(StartADCConversion == 1)
        {
           //DEBUG_UART_PutString("SOC\r\n");
          //  CH = AMuxSeq_GetChannel();
			//Pin_3_Write(1);
            //Pin_2_Write(0);
			
			DMAStatus = 0;
           	TransactionNumber = 0;
            ISR_Switch_1_Disable();
            
            /* Configure DMA */
            //ConfigureDMA_1();
            //ConfigureDMA_2();
            
            /*Enable DMA*/
        	DMA_ISR_Enable();
            //DMA_ISR_1_Enable();
            
            DMAIsr1IntCnt = 0;
            DMAIsr2IntCnt = 0;
			DMAIsr3IntCnt = 0;

         	CHCnt = 0;
            /* Start the ADC conversion */
			ConfigureDMA_1();
			if(LookAheadFix)
			{
				LookAheadFix = 0;
            	memset(ADCBuffer, 0, ADC_DATA_BUFF);
			}		
			
			ADC_StartConvert();
			StartADCConversion = 0;
			if(OperationalMode == TRIGGER_MODE)
            {
               SendStartOfPacket();
            }
        }
		//StartCont = 1;
		/* ADC data transfer in continuous mode */
        if(StartCont == 1)
        {
			uint16 i = 0;
			
            T3Cnt = 0;
            T4Cnt = 0;
            State = 1;
            
            StartCont = 2;
			
			//sprintf(tmpstr, "cnt ADC ch = [%d] \r\n", ADCChannels[0]);
            //DEBUG_UART_PutString(tmpstr); 
			
			if(ConversionComplete)
            {
                ConversionComplete = 0;
			    StartADCConversion = 1;
          	}
        }
       
        /* Check whether data is received on UART or not */
		if (DataReceived == 1)
		{
            uint8 i=0;
            DataReceived =0;
     
			/* Read the UART data */
//            for(i= 0;i< UartRXIndex ;i++)
//            {                 
//                /* Sending the data to UART */
//                sprintf(tmpstr,"[%x]",UARTBuffer[i]);
//                DEBUG_UART_PutString(tmpstr);
//            }          
           /*send the received data for parsing*/
            UartPacketParser(UARTBuffer, UartRXIndex);
            UartRXIndex = 0;
            memset(UARTBuffer,0,sizeof(UARTBuffer));
        }
#if 0        
		/* Sending the response data to UART */
        if(DMABusy)
        {
			if(DMABusy == 1)
			{
				recoveryRetry = 0;
				DMABusy = 2;
			}
			else if((DMABusy == 2) && (recoveryRetry > 65500))
			{
				DEBUG_UART_PutString("Recovered response\r\n");
            	recoveryRetry = 0;
				DMABusy = 0;
            	COMM_UART_PutArray(&RespBuffer[1] , RespBuffer[0]); 
			}
			recoveryRetry++;
        }
#endif

        /* ADC data transfer in trigger mode */
        if(TriggerSwitchFlag && ConversionComplete && (OperationalMode == TRIGGER_MODE))
     	{          
			uint16 i = 0 ;
            TriggerSwitchFlag = 0;
            
            ConversionComplete = 0;
			
			if(NumberOfChannels > 1)
			{
				//number of channels greater than 1
				 DMAState = 0;
			}
                
			T3Cnt = 0;
            T4Cnt = 0;
            State = 1;
            
            /*Start the timer for generation of VDAC pulses according to set time*/
            Timer_1_Start();
			//Timer_1_WriteCounter(5 * MUL_FACTOR_USEC_TIMER_1);
		    Timer_1_WriteCounter((TimerArray[8] + 2) * 100 * MUL_FACTOR_USEC_TIMER_1);
			Timer_1_WritePeriod(TimerArray[4] * 100 * MUL_FACTOR_USEC_TIMER_1);
			State = 2;
			StartADCConversion = 1;
        }
        else if(switchFlag1 && (OperationalMode == EXT_STIMULATION_TRIGGER_MODE))
        {
           /*if operation mode is external stimulation trigger*/
           /*VDAC pulses begins on receiving a trigger pulse on switch.*/
            switchFlag1 = 0;
            
            T3Cnt = 0;
            T4Cnt = 0;
            State = 2;
            
            //IDAC8_Sink_SetValue(DACVal[1]);
			IDAC8_Sink_SetValue(0);
			IDAC8_Source_SetValue(0); //john
            
            Timer_1_Start();
			//Timer_1_WriteCounter(1 * MUL_FACTOR_USEC_TIMER_1);
            Timer_1_WritePeriod(TimerArray[4] * 100 * MUL_FACTOR_USEC_TIMER_1);
            //DEBUG_UART_PutString("1 ,5\r\n");
        }
        else if(switchFlag1 && ConversionComplete && (OperationalMode == EXT_RECORDING_TRIGGER_MODE))
        {
			uint16 j = 0;
			
            /*if switch is pressed and converion of DMA is complete and operation mode is external trigger*/
            /* we have to select channel 1 and start ADC converion to collect samples of both channels*/
			//switchFlag1 = 0;
            sprintf(tmpstr, " switchFlag1 \r\n");
            DEBUG_UART_PutString(tmpstr);
			State = 0;
			
            ConversionComplete = 0;
	
			if(NumberOfChannels > 1)
			{
        		DMAState = 0;
			}
            SendStartOfPacket();
                                 
            StartADCConversion = 1;
        }
        else
        {
            if(OperationalMode != EXT_RECORDING_TRIGGER_MODE)
				switchFlag1 = 0;
			else if((OperationalMode == EXT_RECORDING_TRIGGER_MODE) && (ChannelOffset >= NumberOfChannels))
			{
				switchFlag1 = 0;
				ChannelOffset = 0;
			}
        }
    }
}

/*******************************************************************************
* Function Definitions
********************************************************************************/

/* configure DMA 1*/
/* SPI transmit DMA */
void InitDMA_1()
{
	 /* Iniitialize DMA_1 channel */
    DMA_1_Chan = DMA_1_DmaInitialize(DMA_BYTES_PER_BURST_1, DMA_1_REQUEST_PER_BURST, 
                                     HI16(DMA_1_SRC_BASE), HI16(DMA_1_DST_BASE));
                                     
    /* Allocate TD */
    DMA_1_TD[0] = CyDmaTdAllocate();
}

	
void ConfigureDMA_1()
{            
	//DEBUG_UART_PutString("ConfigureDMA_1\r\n");  
	
	CyDmaClearPendingDrq(DMA_1_Chan);
	
	/* Configure this Td chain as follows:
    *  - The TD is looping on itself
    *  - Increment the source address, but not the destination address   
    */
    CyDmaTdSetConfiguration(DMA_1_TD[0], 4u, DMA_1_TD[0], TD_TERMIN_EN | DMA_1__TD_TERMOUT_EN | TD_INC_SRC_ADR);
    //CyDmaTdSetConfiguration(DMA_1_TD[1], 1u, DMA_1_TD[0], TD_AUTO_EXEC_NEXT);
	
	/* From the memory to the SPIM */
    CyDmaTdSetAddress(DMA_1_TD[0], LO16((uint32)&TXCommandBuffer[0]), LO16((uint32)SPIM_TXDATA_PTR));
    //CyDmaTdSetAddress(DMA_1_TD[1], LO16((uint32)TXCommandBuffer), LO16((uint32)TXCommandBuffer));
	
	/* TD initialization */
    CyDmaChSetInitialTd(DMA_1_Chan, DMA_1_TD[0]);
	//Pin_2_Write(1);
	/* Enable the DMA channel */
    CyDmaChEnable(DMA_1_Chan, 1);
	
	return ;
}


/* SPI Receive DMA */
void InitDMA_3()
{
	/* Iniitialize DMA_1 channel */
	DMA_3_Chan = DMA_3_DmaInitialize(DMA_BYTES_PER_BURST_1, DMA_1_REQUEST_PER_BURST, 
	                                     HI16(DMA_3_SRC_BASE), HI16(DMA_3_DST_BASE));
	                            
    /* Allocate TD */
    DMA_3_TD[0] = CyDmaTdAllocate();
	DMA_3_TD[1] = CyDmaTdAllocate();
}


void ConfigureDMA_3()
{         
	//DEBUG_UART_PutString("ConfigureDMA_3\r\n");
	//sprintf(tmpstr, "## BytesTransfer = [%d] \r\n", BytesTransfer);
   	//DEBUG_UART_PutString(tmpstr);

	/*Set bytes transferred to actual number of samples required from ADC * 2 */
	/* Set Source and Destination address */
	CyDmaClearPendingDrq(DMA_3_Chan);
	
    if(NumberOfChannels == 1)
    {
        /* TD configuration setting */
        CyDmaTdSetConfiguration(DMA_3_TD[0], (BytesTransfer + 2), DMA_INVALID_TD, TD_TERMIN_EN | DMA_3__TD_TERMOUT_EN | TD_INC_DST_ADR);
		CyDmaTdSetAddress(DMA_3_TD[0], LO16((uint32)SPIM_RXDATA_PTR), LO16((uint32)&ADCBuffer[0]));
    }
    else if(NumberOfChannels >= 2) 
    {
        CyDmaTdSetConfiguration(DMA_3_TD[0], ((BytesTransfer / 2)+2) , DMA_3_TD[1], TD_TERMIN_EN | DMA_3__TD_TERMOUT_EN |TD_INC_DST_ADR);
		CyDmaTdSetAddress(DMA_3_TD[0],LO16((uint32)SPIM_RXDATA_PTR), LO16((uint32)&ADCBuffer[0]));
		
        CyDmaTdSetConfiguration(DMA_3_TD[1], ((BytesTransfer / 2)), DMA_INVALID_TD, TD_TERMIN_EN | DMA_3__TD_TERMOUT_EN | TD_INC_DST_ADR);
       	CyDmaTdSetAddress(DMA_3_TD[1], LO16((uint32)SPIM_RXDATA_PTR) ,LO16((uint32)&ADCBuffer[ADC_DATA_BUFF/2]));
    }
		
	/* TD initialization */
    CyDmaChSetInitialTd(DMA_3_Chan, DMA_3_TD[0]);
	
	/* Enable the DMA channel */
    CyDmaChEnable(DMA_3_Chan, 0);
	
	return ;
}
	
void InitDMA_2()
{
	/* Iniitialize DMA_2 channel */
    DMA_2_Chan = DMA_2_DmaInitialize(DMA_BYTES_PER_BURST_1, DMA_1_REQUEST_PER_BURST, 
                                     HI16(DMA_2_SRC_BASE), HI16(DMA_2_DST_BASE));                                     
    /* Allocate TD */
    DMA_2_TD[0] = CyDmaTdAllocate();
	DMA_2_TD[1] = CyDmaTdAllocate();
}

void ConfigureDMA_2()
{
	//DEBUG_UART_PutString("ConfigureDMA_2\r\n"); 
	
    /* Set Source and Destination address */
    if(NumberOfChannels == 1)
    {
        /* TD configuration setting */
		CyDmaTdSetConfiguration(DMA_2_TD[0], (BytesTransfer-2) , DMA_INVALID_TD , DMA_2__TD_TERMOUT_EN | TD_INC_SRC_ADR);
        CyDmaTdSetAddress(DMA_2_TD[0], LO16((uint32)&ADCBuffer[4]),LO16((uint32)COMM_UART_TXDATA_PTR));
    }
    else if(NumberOfChannels >= 2) 
    {
        CyDmaTdSetConfiguration(DMA_2_TD[0], ((BytesTransfer/2)-2), DMA_2_TD[1], DMA_2__TD_TERMOUT_EN | TD_INC_SRC_ADR);
        CyDmaTdSetAddress(DMA_2_TD[0], LO16((uint32)&ADCBuffer[4]),LO16((uint32)COMM_UART_TXDATA_PTR));
        
        CyDmaTdSetConfiguration(DMA_2_TD[1], ((BytesTransfer/2) + 1), DMA_INVALID_TD, DMA_2__TD_TERMOUT_EN | TD_INC_SRC_ADR);
        CyDmaTdSetAddress(DMA_2_TD[1], LO16((uint32)&ADCBuffer[ADC_DATA_BUFF/2]), LO16((uint32)COMM_UART_TXDATA_PTR));
    }
    
    /* TD initialization */
    CyDmaChSetInitialTd(DMA_2_Chan, DMA_2_TD[0]);
    
    /* Enable the DMA channel */
    CyDmaChEnable(DMA_2_Chan, 0);
}

void CalculateSamplingRate(uint8 Index)
{
	SamplingRateVal =  SamplingRateValues[Index];
	if(NumberOfChannels > 1)
		SamplingRateVal *= 2;
		
	sprintf(tmpstr, "SamplingRateVal = [%d] \r\n", (uint8)SamplingRateVal);
    DEBUG_UART_PutString(tmpstr);
}

void CalculateParamsVal()
{
    /* calculate count of bytes tranfer */   
    BytesTransfer = ((TimerArray[9] / 10) * (SamplingRateVal/1000) * (DMA_BYTES_PER_BURST_2));
    sprintf(tmpstr, "BytesTransfer = [%d] \r\n", BytesTransfer);
    DEBUG_UART_PutString(tmpstr);
    
	//if(NumberOfChannels >= 2) 
    //    BytesTransfer = BytesTransfer/2;
     
   /* calculate VDAC pulse time*/  
	VdacPulseTime = ((TimerArray[0] * 3600) / (TimerArray[3]));
    
    CalculatedSleepTicks = TimerArray[1] * 6;    
    CalculatedSleepTicks *= 60;
}           

/* Calculate current ADC channels*/ 
uint16 Calculate_CH(uint16 Offset)
{   
   	uint16 CH;
   	if(NumberOfChannels >= 2)
   	{
	   	CH = (1 << (ADCChannels[Offset] - 1)); 
	   	CH ^= (1 << (ADCChannels[Offset + 1] - 1));
	}
	else if(NumberOfChannels == 1)
	{
		CH = (1 << (ADCChannels[0] - 1)); 
	}
	
   //sprintf(tmpstr, "Current ADC ch = [%d] \r\n", CH);
   //DEBUG_UART_PutString(tmpstr);
   return CH;
}

/*  send start of packet before sending actual data as per 
    protocol between device and PC app */
void SendStartOfPacket()
{
    uint8 j=0 , Index = 0;
    memset(ConfigData, 0, MAX_PAYLOAD_SIZE);
	
    /* 0x55 0xAA is start of frame*/
    ConfigData[j++] =   0x55;
    ConfigData[j++] =   0xAA;
	
     /* protocol version */
    ConfigData[j++] =   PROTOCOL_VERSION;
	
    /*DSN */
    ConfigData[j++] =   TriggerDSN++;
	
    /*Request Id : read ADC sample*/
    ConfigData[j++] =   READ_ADC_SAMPLES;
	
    /* length of payload*/
    ConfigData[j++] =   5;
	
	/* Channel number*/
	CurrentChannel = Calculate_CH(ChannelOffset);
	ConfigData[j++] = (uint8)(CurrentChannel >> 8);
	ConfigData[j++] = CurrentChannel;  	
	/* Sampling Rate */
	
    ConfigData[j++] =   ADCSamplingRate;  
  
    ConfigData[j++] =   (BytesTransfer/2);
    ConfigData[j++] =   ((BytesTransfer/2) >> 8);
  
    CalCRC = Calculate_CRC(ConfigData , j);
    ConfigData[j++] =   CalCRC;
           
//	DEBUG_UART_PutString("\r\n SOF\r\n");*
//    for(Index= 0;Index< j ;Index++)
//    {                    
//        /* received data to UART */
//        sprintf(tmpstr, "[%x] ", ConfigData[Index]);
//        DEBUG_UART_PutString(tmpstr);
//    }
    /* Send packet on bluetooth */
    COMM_UART_PutArray(ConfigData,j);  
}

/*  send end of packet*/
void SendEndOfPacket()
{
    uint8 j=0;
    memset(ConfigData, 0, MAX_PAYLOAD_SIZE);
    ConfigData[j++] =   0x55;
    ConfigData[j++] =   0xAA;
    ConfigData[j++] =   PROTOCOL_VERSION;
    ConfigData[j++] =   TriggerDSN++;
    ConfigData[j++] =   END_OF_ADC_SAMPLES;
    ConfigData[j++] =   0;
        
    CalCRC = Calculate_CRC(ConfigData , j);
    ConfigData[j++] =   CalCRC;

     /* Send packet on bluetooth */
    COMM_UART_PutArray(ConfigData,j);  
}





/*****************************************************************************
* Function Name: SleepComponents()-+
******************************************************************************
* Summary:
*   This function puts the unused components into a low-power state in 
*   preparation for power mode transitions.  
*
* Notes:
*   This function is not used with AltAct mode because the components will 
*   continue to operate.
*
*****************************************************************************/
void SleepComponents(void)
{
	//SPIM_Sleep();
    DEBUG_UART_Sleep();
    COMM_UART_Sleep();
    IDAC8_Sink_Sleep();	
}

/*****************************************************************************
* Function Name: WakeComponents()
******************************************************************************
* Summary:
*   This function wakes the unused components from sleep and restores their 
*   operation. 
*
* Notes:
*   None
*
*****************************************************************************/
void WakeComponents(void)
{
    DEBUG_UART_Wakeup();
    COMM_UART_Wakeup();
    IDAC8_Sink_Wakeup();
	//SPIM_Wakeup();
}

/*****************************************************************************
* Function Name: ButtonDebounce()
******************************************************************************
* Summary:
*   This function adds a slight delay and clears any pending interrupts caused
*   by bouncing of the pushbutton on the DVK board. This helps prevent 
*   unwanted mode transitions.
*
*****************************************************************************/
void ButtonDebounce(void)
{
	CyDelay(5000);
	Button_ClearInterrupt();
}


#ifdef API_SUPPORT
/*******************************************************************************
* Function Name: INTAN_Setup
********************************************************************************
*
* Summary:
*  Setup INTAN settings defined in header file.
*
*******************************************************************************/
void INTAN_Configuration(void)
{
	uint16 ConfigData;
	int i = 0;
	
    Calculate_Filter_Registers();
    
    // Setup Registers 0-7    
    SPI_WriteData(INTAN_REG_0_DEF, NULL, 0);   // REG0: ADC Config and Fast Settle 
    SPI_WriteData(INTAN_REG_1_DEF, NULL, 0);   // REG1: Supply Sensor and ADC Buffer Bias Current 
    SPI_WriteData(INTAN_REG_2_DEF, NULL, 0);   // REG2: MUX Bias Current
    SPI_WriteData(INTAN_REG_3_DEF, NULL, 0);   // REG3: MUX Load, Temp Sensor, Aux Dout
    SPI_WriteData(INTAN_REG_4_DEF, NULL, 0);   // REG4: ADC Output Format and DSP offset Removal
    SPI_WriteData(INTAN_REG_5_DEF, NULL, 0);   // REG5: Impedance Check Control
    SPI_WriteData(INTAN_REG_6_DEF, NULL, 0);   // REG6: Impedance Check ADC
    SPI_WriteData(INTAN_REG_7_DEF, NULL, 0);   // REG7: Impedance Amp Select

    // Setup On-Chip Amplifer Bandwidth Registers
    SPI_WriteData(INTAN_REG_8_DEF, NULL, 0);   // REG8: On-Chip Amp Bandwidth Select
    SPI_WriteData(INTAN_REG_9_DEF, NULL, 0);   // REG9: On-Chip Amp Bandwidth Select
    SPI_WriteData(INTAN_REG_10_DEF, NULL, 0);  // REG10: On-Chip Amp Bandwidth Select
    SPI_WriteData(INTAN_REG_11_DEF, NULL, 0);  // REG11: On-Chip Amp Bandwidth Select
    SPI_WriteData(INTAN_REG_12_DEF, NULL, 0);  // REG12: On-Chip Amp Bandwidth Select
    SPI_WriteData(INTAN_REG_13_DEF, NULL, 0);  // REG13: On-Chip Amp Bandwidth Select

    // Setup Individual Amplifier Power Registers
    SPI_WriteData(INTAN_REG_14_DEF, NULL, 0);  // REG14: Individual Amp Power
    SPI_WriteData(INTAN_REG_15_DEF, NULL, 0);  // REG15: Individual Amp Power
    SPI_WriteData(INTAN_REG_16_DEF, NULL, 0);  // REG16: Individual Amp Power
    SPI_WriteData(INTAN_REG_17_DEF, NULL, 0);  // REG17: Individual Amp Power
	
	CyDelayUs(100);	// Wait 100usec after register write and before ADC calibration 
	
	SPI_WriteData(INTAN_CALIBRATE_ADC, NULL, 0);  // Calibrate ADC
	
	DEBUG_UART_PutString("Dummy Read after ADC configuration\r\n");
	for(i=0;i<10;i++)
	{
		SPI_ReadData(INTAN_DUMMY, &ConfigData, 1);
		sprintf(tmpstr, " Cmd = [%x] Data [%x]\r\n", (uint16) INTAN_REG_40_DEF, (uint16) ConfigData);
		DEBUG_UART_PutString(tmpstr);
	}
}

/*****************************************************************************
* Function Name: SPI_WriteData(uint16 command, uint16 *dataPtr, uint8 length)
*
* Summary:
*   This function will send the 16 data of size length using the data 
*   pointer txPtr to the SPI slave.
*
* Parameters:
*   command: INTAN command
*   dataPtr: pointer to the data to be transmitted over SPI
*	length: number of words to be transmitted
*
* Return:
* 	uint8: number of words transmitted
*
* Notes:
*   None
*****************************************************************************/
uint8 SPI_WriteData(uint16 command, uint16 *dataPtr, uint8 length)
{
	int i = 0;
	uint8 *tmpPtr = (uint8 *)dataPtr;
	
	if(DeviceInitComplete)
	{
		DEBUG_UART_PutString("Err: init completed\r\n");
		return 0;
	}
	
	while( ! (SPIM_ReadTxStatus() & SPIM_STS_TX_FIFO_EMPTY ) );
	
	//Pin_4_Write(0);
	
	SPIM_WriteTxData((command >> 8) & 0xFF);
	SPIM_WriteTxData((command >> 0) & 0xFF);
	while( !(SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE)); // wait to complete
    
	SPIM_ReadRxData();	//Discard dummy reads
	SPIM_ReadRxData();	//Discard dummy reads
	
    for(i=0;i<length;i++)
    {
        SPIM_WriteTxData(*tmpPtr++);
		SPIM_WriteTxData(*tmpPtr++);
        while( !(SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE));
		
		SPIM_ReadRxData();	//Discard dummy reads
		SPIM_ReadRxData();	//Discard dummy reads
    }
	//Pin_4_Write(1);
	
	return length;
}

/*****************************************************************************
* Function Name: SPI_ReadData(uint16 command, uint16 *dataPtr, uint8 length)
*
* Summary:
*   This function will send the 16 data of size length using the data 
*   pointer txPtr to the SPI slave.
*
* Parameters:
*   command: INTAN command
*   dataPtr: pointer to the data to be transmitted over SPI
*	length: number of words to be transmitted
*
* Return:
* 	uint8: number of words transmitted
*
* Notes:
*   None
*****************************************************************************/
uint8 SPI_ReadData(uint16 command, uint16 *dataPtr, uint8 length)
{
	int i = 0;
	uint8 *tmpPtr = (uint8 *)dataPtr;
	
	if(DeviceInitComplete)
	{
		DEBUG_UART_PutString("Err: init completed\r\n");
		return 0;
	}
	
	while( ! (SPIM_ReadTxStatus() & SPIM_STS_TX_FIFO_EMPTY ) );
	
	//Pin_4_Write(0);
	
	SPIM_WriteTxData((command >> 8) & 0xFF);
	//while( !(SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE)); // wait to complete
	SPIM_WriteTxData((command >> 0) & 0xFF);
	while( !(SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE)); // wait to complete
	SPIM_WriteTxData((INTAN_DUMMY >> 8) & 0xFF);
	//while( !(SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE)); // wait to complete
	SPIM_WriteTxData((INTAN_DUMMY >> 0) & 0xFF);
	while( !(SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE)); // wait to complete
    
	//while((SPIM_ReadRxStatus() & SPIM_STS_RX_FIFO_NOT_EMPTY))
	{
		SPIM_ReadRxData();	//Discard dummy reads
		SPIM_ReadRxData();	//Discard dummy reads
		SPIM_ReadRxData();	//Discard dummy reads
		SPIM_ReadRxData();	//Discard dummy reads
	}
	
    for(i=0;i<length;i++)
    {
        SPIM_WriteTxData((INTAN_DUMMY >> 8) & 0xFF);
		//while( !(SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE));
		SPIM_WriteTxData((INTAN_DUMMY >> 0) & 0xFF);
        while( !(SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE));
		
		*tmpPtr = SPIM_ReadRxData();
		tmpPtr++;
		*tmpPtr = SPIM_ReadRxData();
		tmpPtr++;
    }
	//Pin_4_Write(1);
	return length;
}
#endif

/* END OF FILE */
