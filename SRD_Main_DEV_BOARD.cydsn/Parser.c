/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <Parser.h>
#include <PWM_1.h>

uint8 CalCRC=0 ,  RcvdCRC = 0 ,Index = 0;
uint8 ConfigData[MAX_PAYLOAD_SIZE];
uint8 DMABusy;
uint32 Period = 0;
extern uint8 tmpstr[];
extern uint8 switchFlag1;
extern uint8 TriggerSwitchFlag;
extern uint8 T5DACVal, T7DACVal, NumberOfChannels;
extern uint8 FilterSetting[7];

extern int ADCChannels[];
extern uint16 ChannelOffset;
extern uint8 INTAN_Configuration(void);

#define NEW_CHANGES

/*Calculate CRC*/
uint8 Calculate_CRC(uint8* Buffer , uint8 Len)
{   
    uint8 cnt, CRC;
    CRC = *Buffer++;
    for(cnt = 1;cnt < Len ; cnt ++)
    {
        CRC ^= *Buffer++;
    } 
//	sprintf(tmpstr, "CRC : [%x] ", CRC);
//	DEBUG_UART_PutString(tmpstr);
    return CRC;
}

void SetADCConfiguration(uint16 SamplingRate)
{	
	switch(SamplingRate)
		{
			case 0 :	
					DEBUG_UART_PutString("\r\n 1 KSPS \r\n");
					if(NumberOfChannels >= 2)
					{
						PWM_1_WriteCompare(188);
						PWM_1_WritePeriod(375);
					}
					else
					{
						PWM_1_WriteCompare(375);
						PWM_1_WritePeriod(750);
					}
					break;
					
			case 1 :	
					DEBUG_UART_PutString("\r\n 2 KSPS \r\n");
					if(NumberOfChannels >= 2)
					{
						PWM_1_WriteCompare(94);
						PWM_1_WritePeriod(188);
					}
					else
					{
						PWM_1_WriteCompare(188);
						PWM_1_WritePeriod(375);
					}
					break;
					
			case 2 :
					DEBUG_UART_PutString("\r\n 3 KSPS \r\n");
					if(NumberOfChannels >= 2)
					{
						PWM_1_WriteCompare(63);
						PWM_1_WritePeriod(125);
					}
					else
					{
						PWM_1_WriteCompare(125);
						PWM_1_WritePeriod(250);
					}
					break;
					
			case 3 :	
					DEBUG_UART_PutString("\r\n 4 KSPS \r\n");
					if(NumberOfChannels >= 2)
					{
						PWM_1_WriteCompare(47);
						PWM_1_WritePeriod(94);
					}
					else
					{
						PWM_1_WriteCompare(94);
						PWM_1_WritePeriod(188);
					}
					break;
					
			case 4 :
					DEBUG_UART_PutString("\r\n 5 KSPS \r\n");
					if(NumberOfChannels >= 2)
					{
						PWM_1_WriteCompare(38);
						PWM_1_WritePeriod(75);
					}
					else
					{
						PWM_1_WriteCompare(75);
						PWM_1_WritePeriod(150);
					}
					break;
					
			case 5 :
					DEBUG_UART_PutString("\r\n 6 KSPS \r\n");
					if(NumberOfChannels >= 2)
					{
						PWM_1_WriteCompare(32);
						PWM_1_WritePeriod(63);
					}
					else
					{
						PWM_1_WriteCompare(63);
						PWM_1_WritePeriod(125);
					}
					break;
					
			case 6 :	
					DEBUG_UART_PutString("\r\n 10 KSPS \r\n");
					if(NumberOfChannels >= 2)
					{
						PWM_1_WriteCompare(19);
						PWM_1_WritePeriod(38);
					}
					else
					{
						PWM_1_WriteCompare(38);
						PWM_1_WritePeriod(75);
					}
					break;
					
			case 7 :	
					DEBUG_UART_PutString("\r\n 12 KSPS \r\n");
					if(NumberOfChannels >= 2)
					{
						PWM_1_WriteCompare(16);
						PWM_1_WritePeriod(32);
					}
					else
					{
						PWM_1_WriteCompare(32);
						PWM_1_WritePeriod(63);
					}
					break;
					
		 	case 8 :	
					DEBUG_UART_PutString("\r\n 15 KSPS \r\n");
					if(NumberOfChannels >= 2)
					{
						PWM_1_WriteCompare(13);
						PWM_1_WritePeriod(25);
					}
					else
					{
						PWM_1_WriteCompare(25);
						PWM_1_WritePeriod(50);
					}
					break;
					
			default : 
					DEBUG_UART_PutString("\r\n Sampling rate not matched.\r\n");
					break;		
		}
}
 /* packet parser for received buffer from UART*/
uint8 UartPacketParser(uint8* UartDataBuffer , uint8 Length)
{
    uint8 ErrorCode = 0;
    uint8 *RecvdDataPtr;
//    uint16 RSOF;
    
    RequestPacket *pPkt = (RequestPacket*)UartDataBuffer;
    
    RecvdDataPtr = (uint8 *)UartDataBuffer;
    
    /*Check start of frame*/
    while((RecvdDataPtr[0] != 0x55) && (RecvdDataPtr[1] != 0xAA) && Length) 
    {
        RecvdDataPtr++;
        Length--;   
    }
   
    /*Check payload length*/
    if(Length < 5)
    {
        ErrorCode = INVALID_DATA;
        COMM_UART_ClearRxBuffer();
        return 0;
    }
    
    /*Check for invalid data*/
    if(Length < (6 + RecvdDataPtr[5]))
    {
        ErrorCode = INVALID_DATA;
        COMM_UART_ClearRxBuffer();
        return 0;
    }
    
    pPkt = RecvdDataPtr;
    RcvdCRC = RecvdDataPtr[Length-1];
        
    CalCRC = Calculate_CRC(RecvdDataPtr ,(Length-1));
   
    RecvdDataPtr = (RecvdDataPtr + sizeof(RequestPacket));
    for(Index = 0 ; Index < pPkt->DataLen;Index++)
    {
        DataRcvd[Index]= *(RecvdDataPtr);
        RecvdDataPtr++;
    }

    /*Check received CRC and calculated CRC are same or not*/
    if(CalCRC == RcvdCRC)
    {
        /*Check start of frame*/
        if(pPkt->StartOfFrame == 0x55AA)
        {
             /*Check protocol version*/
            if( pPkt->ProtocolVersion <= PROTOCOL_VERSION)
            {
                /*send the payload for parsing */
                RequestPacketParser(pPkt->DSN ,pPkt->RequestID , pPkt->DataLen , DataRcvd);
            }
            else
            {
                ErrorCode = INVALID_PROTOCOL_VERSION;
            }
        }
        else
        {
            ErrorCode = INVALID_DATA;
        }
    }
    else
    {
        ErrorCode = INVALID_CRC;
    }
    /*Send error response*/
    if(ErrorCode > 0)
    {
        PrepareResponsePacket(pPkt->DSN,ErrorCode, 0,0);
        COMM_UART_ClearRxBuffer();
        return ErrorCode;
    }
    return 0;
}

/*parse the payload as per request ID and take appropriate action*/
void RequestPacketParser(uint8 DSN, uint8 RcvdRequestID, uint8 RcvdDataLen, uint8*DataRcvd)
{
    uint8 Index = 0 ,i = 0, j = 0;
	uint8 SetupConfirmation = 0;
	
    //DEBUG_UART_PutString("\r\n");
    switch(RcvdRequestID)
    {           
        case HANDSHAKE_WIRELESS_DEVICE:
                DEBUG_UART_PutString("\r\n HANDSHAKE_WIRELESS_DEVICE\r\n");
                PrepareResponsePacket(DSN,NORMAL_RESPONSE, 0,0);
                break;
                   
        case SET_CONFIGURATION:
                Timer_1_Stop();
                Timer_3_Stop();
                DEBUG_UART_PutString("\r\n SET_CONFIGURATION\r\n");
//                for(Index= 0;Index< RcvdDataLen ;Index++)
//                {                    
//                    /* received data to UART */
//                    sprintf(tmpstr, "[%d][%x] \r\n", (uint16)Index, (uint16)DataRcvd[Index]);
//                    DEBUG_UART_PutString(tmpstr);
//                }
			 	/* Clear ADC channel Array */
				memset(ADCChannels, 0, ADC_MAX_CH);
					   
			 	// Start of Data Validation
				if((DataRcvd[0] > 5) || (DataRcvd[1] > ADC_MAX_CH) || (DataRcvd[2] > 15) || (DataRcvd[3] > 255))
				{
					PrepareResponsePacket(DSN, INVALID_DATA, 0, 0);
                	break;
				}
				for(i = 18; i < RcvdDataLen; i += 2)
                {
					//No zero validation for T6, T7 & T9
					if((i == 28) || (i == 30) || (i == 34))
						continue;
					
					if((DataRcvd[i] == 0x00) && (DataRcvd[i+1] == 0x00))
					{
                        PrepareResponsePacket(DSN, INVALID_DATA, 0, 0);
                		break;
					}
					
				}
				if(i < RcvdDataLen)
					break;
				// End of Data Validation
				
                Index = 0;
                /* fill the received data to appropriate variables for further process*/
                OperationalMode = DataRcvd[Index++];
                sprintf(tmpstr, "MODE :[%x] ", (uint16)OperationalMode);
                DEBUG_UART_PutString(tmpstr);
                    
				NumberOfChannels = 	DataRcvd[Index++];
				sprintf(tmpstr, "NumberOfChannels :[%x] ", (uint16)NumberOfChannels);
                DEBUG_UART_PutString(tmpstr);
				
				ChannelOffset = 0;	//Clear present channel offset
                ChannelNumber  = DataRcvd[Index++];
				ChannelNumber = ChannelNumber << 8;
				ChannelNumber  |= DataRcvd[Index++];
				sprintf(tmpstr, "ChannelNumber :[%x] ", (uint16)ChannelNumber);
                DEBUG_UART_PutString(tmpstr);
				
                ADCSamplingRate = DataRcvd[Index++];
				sprintf(tmpstr, "ADCSamplingRate :[%x]\r\n", (uint16)ADCSamplingRate);
                DEBUG_UART_PutString(tmpstr);
				
#ifdef NEW_CHANGES				
				T5DACVal = DataRcvd[Index++];
				T7DACVal = DataRcvd[Index++];
				sprintf(tmpstr, "T5DAC:[%x] T7DAC:[%x]\r\n", (uint16)T5DACVal, (uint16)T7DACVal);
				DEBUG_UART_PutString(tmpstr);
				
				FilterSetting[0] = DataRcvd[Index++];
				FilterSetting[1] = DataRcvd[Index++];
				FilterSetting[2] = DataRcvd[Index++];
				FilterSetting[3] = DataRcvd[Index++];
				FilterSetting[4] = DataRcvd[Index++];
				FilterSetting[5] = DataRcvd[Index++];
				FilterSetting[6] = DataRcvd[Index++];
				sprintf(tmpstr, "Filter:[%x, %x, %x, %x, %x, %x, %x]\r\n", (uint16)FilterSetting[0], 
										(uint16)FilterSetting[1], (uint16)FilterSetting[2],
										(uint16)FilterSetting[3], (uint16)FilterSetting[4],
										(uint16)FilterSetting[5], (uint16)FilterSetting[6]);
				DEBUG_UART_PutString(tmpstr);
#else
				T5DACVal = DataRcvd[Index++];
				T7DACVal = DataRcvd[Index++];
#endif
				
                j=0 ; 
				/*Fill ADC channels received buffer to ADC channel array*/
                for(i = 0 ; i < ADC_MAX_CH ; i++)
                {					
					if((((ChannelNumber >> i) & 0X0001)) == 1 )
					{
                   	 	ADCChannels[j] =  (i);
                     	j++;
					}
                }
				
				DEBUG_UART_PutString("New ADC Channels: ");
				for(i= 0;i< NumberOfChannels ;i++)
                {                    
                    /* received ADC channels */
                    sprintf(tmpstr, "[%x] ", (uint16)ADCChannels[i]);
                    DEBUG_UART_PutString(tmpstr);
                }
                DEBUG_UART_PutString("\r\n");
				
				j = 0;
                /*Fill timing parameters from received buffer to timer array*/
#ifdef NEW_CHANGES
                sprintf(tmpstr, "Rcvd Len: [%x]\r\n", (uint16)RcvdDataLen);
                DEBUG_UART_PutString(tmpstr);
                
                DEBUG_UART_PutString("Calculate timing: ");
				for(i = Index ; i < RcvdDataLen ; i+=2)
#else      
				for(i = 7 ; i < RcvdDataLen ;)
#endif
                {					
                    TimerArray[j] =  DataRcvd[Index++];
                    TimerArray[j] = TimerArray[j] << 8;
                    TimerArray[j] |= DataRcvd[Index++];
                    sprintf(tmpstr, "[%x] ", (uint16)TimerArray[j]);
                    DEBUG_UART_PutString(tmpstr);
                    j++;
                }
				
				DEBUG_UART_PutString("Timing parameters: ");
				for(i = 0; i < 10; i++)
				{
					sprintf(tmpstr, "[%x] ", (uint16)TimerArray[i]);
                	DEBUG_UART_PutString(tmpstr);
				}
				DEBUG_UART_PutString("\r\n");
				
				SetADCConfiguration(ADCSamplingRate);
				CalculateSamplingRate(ADCSamplingRate);
                CalculateParamsVal(); 
                PrepareResponsePacket(DSN ,NORMAL_RESPONSE, 0,0);
                if(OperationalMode == TRIGGER_MODE)
				{
                    StartCont = 0;
				    TriggerSwitchFlag = 1;
					
					// Setup will not be done as mode is not OFF mode.
					// Send setup fail to GUI
					SetupConfirmation = 1;
					PrepareResponsePacket(DSN ,SETUP_CONFIRMATION, 1, &SetupConfirmation);
					DEBUG_UART_PutString("Wrong Mode Intan setup fail\r\n");
                }
				if(OperationalMode == OFF_MODE)
				{
					SetupConfirmation = INTAN_Configuration();
					PrepareResponsePacket(DSN ,SETUP_CONFIRMATION, 1, &SetupConfirmation);
					if(SetupConfirmation)
						DEBUG_UART_PutString("Intan setup fail\r\n");
					else
						DEBUG_UART_PutString("Intan setup success\r\n");
				}	
                break;
                    
        case START_CONTINUOUS:
                DEBUG_UART_PutString("\r\n START_CONTINUOUS\r\n");
                PrepareResponsePacket(DSN ,NORMAL_RESPONSE, 0,0);
                OperationalMode = CONTINUOUS_MODE;
                StartCont = 1;
                break;               
               
        case STOP_CONTINUOUS:
                DEBUG_UART_PutString("\r\n STOP_CONTINUOUS\r\n");
                StartCont = 0;
                PrepareResponsePacket(DSN ,NORMAL_RESPONSE, 0,0);
                break;
                    
        case GET_CONFIGURATION:
                DEBUG_UART_PutString("\r\n GET_CONFIGURATION\r\n");
                i = 0;
                memset(ConfigData, 0, MAX_PAYLOAD_SIZE);
                ConfigData[i++] =   OperationalMode;
				ConfigData[i++] =   NumberOfChannels;  
				
				sprintf(tmpstr, "ChannelNumber :[%x] \r\n", ChannelNumber);
	            DEBUG_UART_PutString(tmpstr);
              
				ConfigData[i++] = (uint8)(ChannelNumber >> 8);
				ConfigData[i++] = ChannelNumber;  
                       
				ConfigData[i++] =   ADCSamplingRate;  
				
#ifdef NEW_CHANGES
				ConfigData[i++] = T5DACVal;
				ConfigData[i++] = T7DACVal;
				
				/* Filter settings */
				ConfigData[i++] = FilterSetting[0];
				ConfigData[i++] = FilterSetting[1];
				ConfigData[i++] = FilterSetting[2];
				ConfigData[i++] = FilterSetting[3];
				ConfigData[i++] = FilterSetting[4];
				ConfigData[i++] = FilterSetting[5];
				ConfigData[i++] = FilterSetting[6];
#else
				ConfigData[i++] = T5DACVal;
				ConfigData[i++] = T7DACVal;
#endif	
				for(j = 0 ; j < MAX_TIMER; j++ )
                {
                    ConfigData[i++] = (uint8)TimerArray[j];
                    ConfigData[i++] = (uint8)(TimerArray[j] >> 8);
                }

                PrepareResponsePacket(DSN ,NORMAL_RESPONSE, i ,ConfigData);
                break;
                                       
        default:
                break;
    }
}
    
/*send response packet through BT to application*/
uint8 SendResponsePacket(uint8* Packet_Buffer, uint8 Len )
{    
    DEBUG_UART_PutString("\r\n Resp PKT : ");
    for(Index= 0;Index< Len ;Index++)
    {                    
       /* Sending the data to UART */
       sprintf(tmpstr, "[%x] ", (uint16)Packet_Buffer[Index]);
       DEBUG_UART_PutString(tmpstr);
    }    
    DEBUG_UART_PutString("\r\n");

    /*check for DMA busy or not before sending to UART.*/
    /*If it is busy store data in response buffer and send it when DMA is free*/
    //if(ConversionComplete)
    {
        COMM_UART_PutArray(Packet_Buffer,Len);
    }
    /*
    else
    {
		DEBUG_UART_PutString("!");
        DMABusy = 1;
        RespBuffer[0] = Len;
         for(Index = 1 ; Index <= Len;Index++)
        {
            RespBuffer[Index]= *(Packet_Buffer);
            Packet_Buffer++;
        }
    }
    */
    return 0;
}

/*Prepare response packet*/
void PrepareResponsePacket(uint8 DSN, uint8 ResponceID, uint8 DataLen, uint8*Data)
{
    uint8 i = 0 , j = 0;
    uint8 RespBuffer[50];
    
    RespBuffer[i++]   =   0x55;
    RespBuffer[i++]   =   0xAA;
    RespBuffer[i++]   =   PROTOCOL_VERSION;
    RespBuffer[i++]   =   DSN;
    RespBuffer[i++]   =   ResponceID;
    RespBuffer[i++]   =   DataLen;
    
    for(j=0 ; j < DataLen;j++ )
    {
        RespBuffer[i++] = Data[j];
    }  
    
    CalCRC = Calculate_CRC(RespBuffer , (HEADER_SIZE+DataLen));
    RespBuffer[i++] =   CalCRC;
          
//    for(Index= 0;Index< i ;Index++)
//    {                    
//        /* Sending the data to UART */
//        sprintf(tmpstr, "[%x] ", (uint16)RespBuffer[Index]);
//        DEBUG_UART_PutString(tmpstr);
//    }  
 
    SendResponsePacket((uint8*)RespBuffer ,i);
}

/* [] END OF FILE */
