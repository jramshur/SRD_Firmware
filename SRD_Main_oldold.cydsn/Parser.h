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

#include <device.h>
#include <stdio.h>

#define BUFFER_SIZE         52
#define MAX_DATA_SIZE       52
#define ADC_DATA_BUFF       7168    
#define MAX_TIMER           10
#define MAX_PAYLOAD_SIZE    40
#define PROTOCOL_VERSION    1
#define SOF                 0x55AA
#define HEADER_SIZE         6  

/* Operational modes*/
#define TRIGGER_MODE                    1
#define CONTINUOUS_MODE                 2
#define EXT_STIMULATION_TRIGGER_MODE    3
#define EXT_RECORDING_TRIGGER_MODE      4
#define LOOK_AHEAD_EXT_TRIGGER_MODE     5

/* bytes per burst*/
#define DMA_BYTES_PER_BURST_1      1
#define DMA_BYTES_PER_BURST_2      2

/*REQUEST IDS*/
#define HANDSHAKE_WIRELESS_DEVICE 	0X01
#define SET_CONFIGURATION	        0X02
#define START_CONTINUOUS 	        0X03
#define STOP_CONTINUOUS	            0X04
#define GET_CONFIGURATION	        0X05
#define READ_ADC_SAMPLES	        0X06
#define END_OF_ADC_SAMPLES	        0X07

/*RESPONSE IDS*/
#define NORMAL_RESPONSE 	        0X00
#define INVALID_LENGTH	            0X01
#define INVALID_DATA 	            0X02        //If SOF not matched
#define INVALID_PROTOCOL_VERSION    0X03
#define INVALID_CRC	                0X04
#define INVALID_RESPONS_HANDLER	    0X05


#define ADC_MAX_CH	12

/*Request Packet PayLoad Structure*/
typedef struct
{
  uint16 StartOfFrame;
  uint8 ProtocolVersion;
  uint8 DSN;
  uint8 RequestID;
  uint8 DataLen;
}RequestPacket;

void RequestPacketParser(uint8 DSN ,uint8 RcvdRequestID,uint8 RcvdDataLen, uint8*DataRcvd);
void PrepareResponsePacket(uint8 DSN , uint8 ResponceID, uint8 DataLen, uint8*Data );
uint8 UartPacketParser(uint8* UartDataBuffer, uint8 Length);
uint8 Calculate_CRC(uint8* Buffer , uint8 Len);
uint8 SendResponsePacket(uint8* Packet_Buffer , uint8 Len );
void CalculateParamsVal();
void ConfigureDMA_1();
void ConfigureDMA_2();
void ButtonDebounce(void);		/* Adds a short delay for debounce and clears the interrupt. */
void SleepComponents(void);		/* Shuts down components that are not used in any sleep mode demo. */
void WakeComponents(void);		/* Wakes components that were slept in the SleepComponents() function. */

void SetADCConfiguration(uint16 SamplingRate);
void CalculateSamplingRate(uint8 Index);
void WriteCh(uint16 Channel);
void ADC_StartConvert();
uint16 Calculate_CH(uint16 Offset);
void SendEndOfPacket();

extern volatile uint8 StartCont;
extern uint8 ConfigData[];
extern uint8 OperationalMode;
extern uint16 ChannelNumber;
extern uint8 CalCRC;
extern uint16  ADCSamplingRate;
extern uint16 TimerArray[] ;
extern uint8 DSN;  
extern uint8 DMA_1_Chan , DMA_2_Chan;
extern uint8 DataRcvd[];
extern uint8 RespBuffer[MAX_DATA_SIZE];
extern uint8 ConversionComplete;

//[] END OF FILE
