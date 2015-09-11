/* ==============================================================================
 * BCI_Diagnostics
 *
 * This program is intended to be used to diagnose BCI PCB problems and/or test 
 * it after initial construction. It will test the following items and provide 
 * feed back via LED's and BT connection. 
 * 
 * 1. Test communication between INTAN and PSoC
 * 2. Test ability to setup INTAN parameters
 * 3. Test tx communication to BT module
 * 
 * ==============================================================================
*/

#include <device.h>
#include <INTAN.h>
#include <string.h>
#include <stdio.h>
#include <cytypes.h>

// Function Prototypes (helper functions)
int INTAN_Test_SPI(void);
void INTAN_Setup(void);
int INTAN_Verify_Setup(void);
void INTAN_Calibrate_ADC(void);
uint16 get_read(uint16 word);
void write_reg(uint16 word,int8 n);


int main()
{   
    char cha_str[15];
    char chb_str[15];
    int flagSPI_Pass=0; 
    int flagSetup_Pass=0;
    uint16 result=0x000u;
	uint8 ch;
    
    
    CyGlobalIntEnable;   
    
    // Start SPI Master, UART
    SPIM_Start();
    UART_Start();	
    
    // Prep SPIM
    SPIM_ClearTxBuffer();
    SPIM_ClearRxBuffer();
    CyDelay(50); 
    
    // Send some serial data
    UART_PutString("\nStartup... ");

	//////////////////////////////////////////////         
    // TEST 1. TEST INTAN SPI COMMUNICATION //    
	//////////////////////////////////////////////
    if (INTAN_Test_SPI())
    {   flagSPI_Pass=1;    
        UART_PutString("SPI Comm PASS. ");
    }
    else UART_PutString("SPI Comm FAIL. ");

    //////////////////////////////////////////////
    // TEST 2. Test ability to setup INTAN CHIP //
	//////////////////////////////////////////////
    INTAN_Setup(); // set parameters 
    CyDelay(50);       
    if (INTAN_Verify_Setup()) // verify parameters were set
    {   flagSetup_Pass=1;     
        UART_PutString("Setup PASS. ");
    }
    else  UART_PutString("Setup FAIL. ");

    //////////////////////////////////////////////  
    // Test 3. Calibrate ADC //
	//////////////////////////////////////////////
    INTAN_Calibrate_ADC();
    SPIM_ClearRxBuffer(); // clear read buffer.         
	
	
	// Check flags for pass/fail and set LED blink rate to notify user of tests
	PWM_1_Start();
	if (flagSPI_Pass && flagSetup_Pass) // both test pass
	{
		PWM_1_WriteCompare(255); // solid led
		PWM_1_WritePeriod(255);		
	} 
	else if (~flagSPI_Pass)	// SPI Failed
	{
		PWM_1_WriteCompare(32); // Fast blink
		PWM_1_WritePeriod(65);		
	}
	else if (~flagSetup_Pass) // Setup only failed
	{
		PWM_1_WriteCompare(128); // slow blink
		PWM_1_WritePeriod(255);			
	}
	else // all test fail
	{
		PWM_1_WriteCompare(0); // LED Off
		PWM_1_WritePeriod(0);	
	}		
	
    UART_PutString("\nCh0\tCh1"); 
    for(;;)
    {                         
		
//        //if (~flagSetup_Pass) LED_4_Write(~LED_4_Read());  // Toggle LED if test failed
//        
//        // Read from Ch0
//        write_reg(INTAN_CONVERT_CH_0,0);    // Send read command
//        write_reg(INTAN_DUMMY,0);           // Send dummy command
//        write_reg(INTAN_DUMMY,0);           // Send dummy command
//        result=SPIM_ReadRxData();           // read result of the read command
//        sprintf(cha_str, "%d ", result);    // convert to string        
//        // Read from Ch1
//        write_reg(INTAN_CONVERT_CH_1,0);    // Send read command
//        write_reg(INTAN_DUMMY,0);           // Send dummy command
//        write_reg(INTAN_DUMMY,0);           // Send dummy command
//        result=SPIM_ReadRxData();           // read result of the read command
//        sprintf(chb_str, "%d ", result);    // convert  to string
//       
//        
//        // send to uart
//        UART_PutString("\n");
//        UART_PutString(cha_str);
//        UART_PutString("\t");
//        UART_PutString(chb_str); 

        
        
        ch = UART_GetChar();
        if(0u != ch)
        { 
            UART_PutChar(97); // Echo char back              
            //LED_5_Write(1); //toggle led to indicate byte recieved 
            //CyDelay(60);
            //LED_5_Write(0); //toggle led            
            //UART_PutChar(97);
        }
        //UART_PutChar(97);
        //CyDelay(1000);
           
    }//End For
    
}//End Main


/*******************************************************************************
* Function Name: INTAN_Test_SPI
********************************************************************************
*
* Summary:
*  Test SPI communication with INTAN chip.
*
* Parameters:
*  None.
*
* Return:
*  Results of test (1=successful, 0=fail).
*
*******************************************************************************/
int INTAN_Test_SPI(void) 
{
    uint8 data i;   // loop index. Stored in data space for efficiency.    
    int flag=0;     //flag for matching correct response (1=true)    
    unsigned short response[5];
	
    // Expected return values defined by INTAN are:
    // ['I','N','T','A','N'] or [0x49,0x4E,0x54,0x41,0x4E] or [73,78,84,65,78]
//    uint16 expected[5]={'I','N','T','A','N'};
    unsigned short expected[5]={0x0049u,0x004Eu,0x0054u,0x0041u,0x004Eu};
    
    // Build look-up table of commands to send
    unsigned short command[7]={INTAN_REG_40_DEF,INTAN_REG_41_DEF,INTAN_REG_42_DEF, \
                        INTAN_REG_43_DEF,INTAN_REG_44_DEF,INTAN_DUMMY,INTAN_DUMMY};
    
    
    // Send several dummy commands to clear any buffers...etc.
    write_reg(INTAN_DUMMY,10);
    SPIM_ClearRxBuffer(); // clear read buffer. Test fails unless I clear the buffer here.
    
    // loop through each command and read the result
    for(i=0;i<(5+2);i++)
    {
        if (i<2)      //
        {            
            write_reg(command[i],0);            // Send command[i]        
            SPIM_ReadRxData();                  // Read and discard response			
        }
        else if ((i>=2) && (i<6))
        {     
            write_reg(command[i],0);            // Send command[i]  
            response[i-2]=SPIM_ReadRxData();    // Read response into response[i]
               
            // Compare response to expected
            if (response[i-2] == expected[i-2])
                flag=1;
            else
            {
                flag=0;
                break;
            }
        }
        else
        {      
            write_reg(command[i],0);            // Send command[i]    
            response[i-2]=SPIM_ReadRxData();    // Capture response into response[i]
            
            // Compare response to expected
            if (response[i-2] == expected[i-2])
                flag=1;
            else
            {
                flag=0;
                break;
            }
        }
	
		
		
    }

    return flag;//((response[i-2]<<8)|expected[i-2]);
}



/*******************************************************************************
* Function Name: INTAN_Setup
********************************************************************************
*
* Summary:
*  Setup INTAN settings defined in header file.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void INTAN_Setup(void)
{
    SPIM_ClearRxBuffer(); // clear read buffer.
    // Send several dummy commands as suggested by Reid Harrison
    write_reg(INTAN_DUMMY,10);     
    
    // Setup Registers 0-7    
    write_reg(INTAN_REG_0_DEF,0);   // REG0: ADC Config and Fast Settle 
    write_reg(INTAN_REG_1_DEF,0);   // REG1: Supply Sensor and ADC Buffer Bias Current 
    write_reg(INTAN_REG_2_DEF,0);   // REG2: MUX Bias Current
    write_reg(INTAN_REG_3_DEF,0);   // REG3: MUX Load, Temp Sensor, Aux Dout
    write_reg(INTAN_REG_4_DEF,0);   // REG4: ADC Output Format and DSP offset Removal
    write_reg(INTAN_REG_5_DEF,0);   // REG5: Impedance Check Control
    write_reg(INTAN_REG_6_DEF,0);   // REG6: Impedance Check ADC
    write_reg(INTAN_REG_7_DEF,0);   // REG7: Impedance Amp Select

    // Setup On-Chip Amplifer Bandwidth Registers
    write_reg(INTAN_REG_8_DEF,0);   // REG8: On-Chip Amp Bandwidth Select
    write_reg(INTAN_REG_9_DEF,0);   // REG9: On-Chip Amp Bandwidth Select
    write_reg(INTAN_REG_10_DEF,0);  // REG10: On-Chip Amp Bandwidth Select
    write_reg(INTAN_REG_11_DEF,0);  // REG11: On-Chip Amp Bandwidth Select
    write_reg(INTAN_REG_12_DEF,0);  // REG12: On-Chip Amp Bandwidth Select
    write_reg(INTAN_REG_13_DEF,0);  // REG13: On-Chip Amp Bandwidth Select

    // Setup Individual Amplifier Power Registers
    write_reg(INTAN_REG_14_DEF,0);  // REG14: Individual Amp Power
    write_reg(INTAN_REG_15_DEF,0);  // REG15: Individual Amp Power
    write_reg(INTAN_REG_16_DEF,0);  // REG16: Individual Amp Power
    write_reg(INTAN_REG_17_DEF,0);  // REG17: Individual Amp Power
    
   
    // Send several dummy commands ... just because i can...
    write_reg(INTAN_DUMMY,10);

    // Let's clear the SPIM
    SPIM_ClearTxBuffer();
    SPIM_ClearRxBuffer();   
}


/*******************************************************************************
* Function Name: INTAN_Verify_Setup
********************************************************************************
*
* Summary:
*  Reads each writeable register and varifies the return value with the expected
*  defined setting.
*
* Parameters:
*  None.
*
* Return:
*  Returns bit 1 if all checks pass and bit 0 if any fail to be verified.
*
*******************************************************************************/
int INTAN_Verify_Setup(void)
{
    uint8 data i;     // loop index. Stored in data space for efficiency.
    //uint16 base=0xC000u;    // base read command
    uint16 result;          // result of read
    int flag=0;
    
    // build lookup table of defined register values
    uint16 def[18]={INTAN_REG_0_DEF, INTAN_REG_1_DEF, INTAN_REG_2_DEF, INTAN_REG_3_DEF, INTAN_REG_4_DEF,          \
                    INTAN_REG_5_DEF, INTAN_REG_6_DEF, INTAN_REG_7_DEF, INTAN_REG_8_DEF, INTAN_REG_9_DEF,        \
                    INTAN_REG_10_DEF, INTAN_REG_11_DEF, INTAN_REG_12_DEF, INTAN_REG_13_DEF, INTAN_REG_14_DEF,   \
                    INTAN_REG_15_DEF, INTAN_REG_16_DEF, INTAN_REG_17_DEF};
    
    // Send several dummy commands to clear any buffers...etc.
    write_reg(INTAN_DUMMY,10);
    SPIM_ClearRxBuffer(); // clear read buffer. Not sure if this is necessary.
    
    for(i=0;i<18;i++)
    {
        
        write_reg(get_read(def[i]),0);  // Send read command for register i
        SPIM_ReadRxData();              //read and discard result
        
        
        write_reg(INTAN_DUMMY,0);       // Send dummy command        
        SPIM_ReadRxData();              //read and discard result
        
        write_reg(INTAN_DUMMY,0);       // Send dummy command
        result=SPIM_ReadRxData();       //read result of the read command
        
        // compare result with expected defined value
        if (result == ( def[i] & 0x00FFu ))
        {
            flag=1;
        }    
        else
        {
            flag=0;
            break;
        }   
    }
    
    return flag;
}


/*******************************************************************************
* Function Name: INTAN_Calibrate_ADC
********************************************************************************
*
* Summary:
*  Calibrate INTAN ADC....
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void INTAN_Calibrate_ADC(void)
{
    
    // Send several dummy commands as suggested by Reid Harrison
    write_reg(INTAN_DUMMY,20);     
    
    // Setup Registers 0-7    
    write_reg(INTAN_CALIBRATE_ADC,20);   // REG0: ADC Config and Fast Settle 
       

//    // Let's clear the SPIM
//    SPIM_ClearTxBuffer();
//    SPIM_ClearRxBuffer();   
}

/*******************************************************************************
* Function Name: write_reg
********************************************************************************
*
* Summary:
*  Writes "word" to SPI and writes n dummy commands afterwards. Don't use 
*  write_reg for time sensitive writes becasue of the added delays.
*
* Parameters:
*  word: uint16.
*  n: number of dummy commands to send afterwards.
*
* Return:
*  None.
*
*******************************************************************************/
void write_reg(uint16 word,int8 n)
{
    uint8 data i;     // loop index. Stored in data space for efficiency.
    
    SPIM_WriteTxData(word); // Send command
    while( !(SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE)); // wait to complete
    CyDelayUs(100); // delay 100us.
    
    for(i=1;i<n;i++)
    {
        SPIM_WriteTxData(INTAN_DUMMY); // Send command
        while( !(SPIM_ReadTxStatus() & SPIM_STS_SPI_DONE)); // wait to complete
        CyDelayUs(100); // delay 100us.
    }
}


/*******************************************************************************
* Function Name: get_read
********************************************************************************
*
* Summary:
*  Converts INTAN write command to an INTAN read reg command
*
* Parameters:
*  word: uint16.
*
* Return:
*  Returns a uint16 word representing the read command relative to the input.
*
*******************************************************************************/
uint16 get_read(uint16 word)
{
    return ((word & 0xFF00u) | 0x4000u);
}