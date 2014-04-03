/*****************************************************************************
*
*  basic_wifi_application.c - CC3000 Slim Driver Implementation.
*  Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/


#include "wlan.h" 
#include "evnt_handler.h"    
#include "nvmem.h"
#include "socket.h"
#include "netapp.h"
#include "spi.h"
//#include "dispatcher.h"
#include "spi_version.h"
#include "board.h"
#include "application_version.h"
#include "host_driver_version.h"
#include <msp430.h>
#include "security.h"
#include "coms.h"


#define PALTFORM_VERSION						(1)

extern int uart_have_cmd;

#define UART_COMMAND_CC3000_SIMPLE_CONFIG_START                  (0x31)

#define UART_COMMAND_CC3000_CONNECT                              (0x32)

#define UART_COMMAND_SOCKET_OPEN                                 (0x33)

#define UART_COMMAND_SEND_DATA				  	 (0x34)

#define UART_COMMAND_RCV_DATA				  	 (0x35)

#define UART_COMMAND_BSD_BIND					 (0x36)

#define UART_COMMAND_SOCKET_CLOSE			 	 (0x37)

#define UART_COMMAND_IP_CONFIG			 	 	 (0x38)

#define UART_COMMAND_CC3000_DISCONNECT		 	         (0x39)

#define UART_COMMAND_CC3000_DEL_POLICY                           (0x61)

#define UART_COMMAND_SEND_DNS_ADVERTIZE                         (0x62)

#define CC3000_APP_BUFFER_SIZE						(5)

#define CC3000_RX_BUFFER_OVERHEAD_SIZE                          (20)

#define DISABLE                                                 (0)

#define ENABLE                                                  (1)

#define SL_VERSION_LENGTH                                       (11)

#define NETAPP_IPCONFIG_MAC_OFFSET				(20)

#define BUFFER_SIZE (128)

volatile unsigned long ulSmartConfigFinished, ulCC3000Connected,ulCC3000DHCP,
OkToDoShutDown, ulCC3000DHCP_configured;

volatile unsigned char ucStopSmartConfig;

extern volatile time_t deviceTime;

extern volatile unsigned int reading_frequency;

char digits[] = "0123456789";

volatile long ulSocket;

unsigned char printOnce = 1;

void killSocket();


/////////////////////////////////////////////////////////////////////////////////////////////////////////////      
//__no_init is used to prevent the buffer initialization in order to prevent hardware WDT expiration    ///
// before entering to 'main()'.                                                                         ///
//for every IDE, different syntax exists :          1.   __CCS__ for CCS v5                             ///
//                                                  2.  __IAR_SYSTEMS_ICC__ for IAR Embedded Workbench  ///
// *CCS does not initialize variables - therefore, __no_init is not needed.                             ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////

// Reception from the air, buffer - the max data length  + headers
#ifdef __CCS__

unsigned char pucCC3000_Rx_Buffer[CC3000_APP_BUFFER_SIZE + CC3000_RX_BUFFER_OVERHEAD_SIZE];

#elif __IAR_SYSTEMS_ICC__

__no_init unsigned char pucCC3000_Rx_Buffer[CC3000_APP_BUFFER_SIZE + CC3000_RX_BUFFER_OVERHEAD_SIZE];

#endif



//*****************************************************************************
//
//! itoa
//!
//! @param[in]  integer number to convert
//!
//! @param[in/out]  output string
//!
//! @return number of ASCII parameters
//!
//! @brief  Convert integer to ASCII in decimal base
//
//*****************************************************************************
unsigned short itoa(char cNum, char *cString)
{
	char* ptr;
	char uTemp = cNum;
	unsigned short length;
	
	// value 0 is a special case
	if (cNum == 0)
	{
		length = 1;
		*cString = '0';
		
		return length;
	}
	
	// Find out the length of the number, in decimal base
	length = 0;
	while (uTemp > 0)
	{
		uTemp /= 10;
		length++;
	}
	
	// Do the actual formatting, right to left
	uTemp = cNum;
	ptr = cString + length;
	while (uTemp > 0)
	{
		--ptr;
		*ptr = digits[uTemp % 10];
		uTemp /= 10;
	}
	
	return length;
}
//*****************************************************************************
//
//! atoc
//!
//! @param  none
//!
//! @return none
//!
//! @brief  Convert nibble to hexdecimal from ASCII
//
//*****************************************************************************
unsigned char
atoc(char data)
{
	unsigned char ucRes;

	if ((data >= 0x30) && (data <= 0x39))
	{
		ucRes = data - 0x30;
	}
	else
	{
		if (data == 'a')
		{
			ucRes = 0x0a;;
		}
		else if (data == 'b')
		{
			ucRes = 0x0b;
		}
		else if (data == 'c')
		{
			ucRes = 0x0c;
		}
		else if (data == 'd')
		{
			ucRes = 0x0d;
		}
		else if (data == 'e')
		{
			ucRes = 0x0e;
		}
		else if (data == 'f')
		{
			ucRes = 0x0f;
		}
	}


	return ucRes;
}


//*****************************************************************************
//
//! atoshort
//!
//! @param  b1 first nibble
//! @param  b2 second nibble
//!
//! @return short number
//!
//! @brief  Convert 2 nibbles in ASCII into a short number
//
//*****************************************************************************

unsigned short
atoshort(char b1, char b2)
{
	unsigned short usRes;

	usRes = (atoc(b1)) * 16 | atoc(b2);

	return usRes;
}

//*****************************************************************************
//
//! ascii_to_char
//!
//! @param  b1 first byte
//! @param  b2 second byte
//!
//! @return The converted character
//!
//! @brief  Convert 2 bytes in ASCII into one character
//
//*****************************************************************************

unsigned char
ascii_to_char(char b1, char b2)
{
	unsigned char ucRes;

	ucRes = (atoc(b1)) << 4 | (atoc(b2));

	return ucRes;
}


//*****************************************************************************
//
//! sendDriverPatch
//!
//! @param  Length   pointer to the length
//!
//! @return none
//!
//! @brief  The function returns a pointer to the driver patch: since there is  
//!				  no patch (patches are taken from the EEPROM and not from the host
//!         - it returns NULL
//
//*****************************************************************************
char *sendDriverPatch(unsigned long *Length)
{
	*Length = 0;
	return NULL;
}


//*****************************************************************************
//
//! sendBootLoaderPatch
//!
//! @param  pointer to the length
//!
//! @return none
//!
//! @brief  The function returns a pointer to the bootloader patch: since there   
//!				  is no patch (patches are taken from the EEPROM and not from the host
//!         - it returns NULL
//
//*****************************************************************************
char *sendBootLoaderPatch(unsigned long *Length)
{
	*Length = 0;
	return NULL;
}

//*****************************************************************************
//
//! sendWLFWPatch
//!
//! @param  pointer to the length
//!
//! @return none
//!
//! @brief  The function returns a pointer to the driver patch: since there is  
//!				  no patch (patches are taken from the EEPROM and not from the host
//!         - it returns NULL
//
//*****************************************************************************

char *sendWLFWPatch(unsigned long *Length)
{
	*Length = 0;
	return NULL;
}

//*****************************************************************************
//
//! CC3000_UsynchCallback
//!
//! @param  lEventType   Event type
//! @param  data   
//! @param  length   
//!
//! @return none
//!
//! @brief  The function handles asynchronous events that come from CC3000  
//!		      device and operates a LED1 to have an on-board indication
//
//*****************************************************************************

void CC3000_UsynchCallback(long lEventType, char * data, unsigned char length)
{
  
  
	if (lEventType == HCI_EVNT_WLAN_ASYNC_SIMPLE_CONFIG_DONE)
	{
		ulSmartConfigFinished = 1;
		ucStopSmartConfig     = 1;  
	}
	
	if (lEventType == HCI_EVNT_WLAN_UNSOL_CONNECT)
	{
		ulCC3000Connected = 1;
		
		// Turn on the LED7
		turnLedOn(7);
	}
	
	if (lEventType == HCI_EVNT_WLAN_UNSOL_DISCONNECT)
	{		
		ulCC3000Connected = 0;
		ulCC3000DHCP      = 0;
		ulCC3000DHCP_configured = 0;
		printOnce = 1;
		
		// Turn off the LED7
		turnLedOff(7);
		
		// Turn off LED8
		turnLedOff(8);          
	}
	
	if (lEventType == HCI_EVNT_WLAN_UNSOL_DHCP)
	{
		// Notes: 
		// 1) IP config parameters are received swapped
		// 2) IP config parameters are valid only if status is OK, i.e. ulCC3000DHCP becomes 1
		
		// only if status is OK, the flag is set to 1 and the addresses are valid
		if ( *(data + NETAPP_IPCONFIG_MAC_OFFSET) == 0)
		{
			sprintf( (char*)pucCC3000_Rx_Buffer,"IP:%d.%d.%d.%d\f\r", data[3],data[2], data[1], data[0] );

			ulCC3000DHCP = 1;

			turnLedOn(8);
		}
		else
		{
			ulCC3000DHCP = 0;

			turnLedOff(8);
		}
	}
	
	if (lEventType == HCI_EVENT_CC3000_CAN_SHUT_DOWN)
	{
		OkToDoShutDown = 1;
	}
	
}


//*****************************************************************************
//
//! initDriver
//!
//!  @param  None
//!
//!  @return none
//!
//!  @brief  The function initializes a CC3000 device and triggers it to 
//!          start operation
//
//*****************************************************************************
int
initDriver(void)
{
	
	// Init GPIO's
	pio_init();
	
	//Init Spi
	init_spi();
	
	//DispatcherUARTConfigure();
	
	// WLAN On API Implementation
	wlan_init( CC3000_UsynchCallback, sendWLFWPatch, sendDriverPatch, sendBootLoaderPatch, ReadWlanInterruptPin, WlanInterruptEnable, WlanInterruptDisable, WriteWlanPin);
	
	// Trigger a WLAN device
	wlan_start(0);
	
	// Turn on the LED 5 to indicate that we are active and initiated WLAN successfully
	turnLedOn(5);
	
	// Mask out all non-required events from CC3000
	wlan_set_event_mask(HCI_EVNT_WLAN_KEEPALIVE|HCI_EVNT_WLAN_UNSOL_INIT|HCI_EVNT_WLAN_ASYNC_PING_REPORT);
	/*
	// Generate the event to CLI: send a version string
	{
		char cc3000IP[50];
		char *ccPtr;
		unsigned short ccLen;
		
		DispatcherUartSendPacket((unsigned char*)pucUARTExampleAppString, sizeof(pucUARTExampleAppString));
		
		
		ccPtr = &cc3000IP[0];
		ccLen = itoa(PALTFORM_VERSION, ccPtr);
		ccPtr += ccLen;
		*ccPtr++ = '.';
		ccLen = itoa(APPLICATION_VERSION, ccPtr);
		ccPtr += ccLen;
		*ccPtr++ = '.';
		ccLen = itoa(SPI_VERSION_NUMBER, ccPtr);
		ccPtr += ccLen;
		*ccPtr++ = '.';
		ccLen = itoa(DRIVER_VERSION_NUMBER, ccPtr);
		ccPtr += ccLen;
		*ccPtr++ = '\f';
		*ccPtr++ = '\r';
		*ccPtr++ = '\0';
		
		DispatcherUartSendPacket((unsigned char*)cc3000IP, strlen(cc3000IP));
	}
	*/
	wakeup_timer_init();
	
	ucStopSmartConfig   = 0;
	
	return(0);
}

void killSocket()
{
	closesocket(ulSocket);
	ulSocket = 0xFFFFFFFF;
}

//*****************************************************************************
//
//! main
//!
//!  @param  None
//!
//!  @return none
//!
//!  @brief  The main loop is executed here
//
//*****************************************************************************
//OUR ADC10 FUNCTIONS (SET UP REQUIREMENTS, TIMER SETTINGS, ARE ALL SET UP IN THE FOLLOWING FUNCTIONS
void setPins(void) // Sets up the io pins we will be using
{
	// for SPI
	P1SEL1 |= /*BIT7 + BIT6 +*/ BIT4 + BIT5; //adc10 input channels
	//P1SEL0 &= ~(BIT6 + BIT7);
	P1SEL0 |= BIT4 + BIT5; //P1.4 and P1.5 for adc10 input
	//P2SEL1 |= BIT2;// set up for SPI incoming
	P2SEL0 &= ~(/*BIT2+*/BIT1);//SPI in
	P2SEL1 &= ~BIT1; // set 2.1 for switch output
	P2DIR |= BIT1; // bit 1 is switch output
	P2OUT = 0;
	/*//Our SPI_TALKERS
	P2DIR |= BIT3 + BIT1; // bit 3 is SPI_CS drive low to talk bit 1 is switch output
	P2OUT |= BIT3; // starts high
	P2OUT &= BIT3; // all p2 outs off accept bit 3

	P1DIR &= ~BIT3; // BIT3 is input for SPI_IRQ
	P1OUT &= ~BIT3; // set port 2 interrupt for this
	P1IE = BIT3; // interrupt on pin 1.3
    P1IES = ~BIT3; // interrupt on falling edge*/

	//SET ADC10 PINS
}
void setClocks(void)// won't clash with our UART test base as we leave the SmClock alone
{
	CSCTL0_H = 0xA5;
	CSCTL1 |= DCORSEL + DCOFSEL_0; //DCO 16 MHZ
	CSCTL2 = SELA_1 + SELM_3;// VLO on ACLK, DCO on Mclk
	CSCTL3 = DIVA_5 + DIVM_4; // f = 312 Hz on Aclk, Mclk f = 1 GHz
}
//void setSPI(void); -- will not need to use spi with UDP protocol already in place
int ST = 0;
void setTimers(void)
{
	TA0CTL |= TASSEL_1 + ID_3 + MC_1;
	//Timer A0 on 39 Hz, Count up mode to TA0CCRO, interrupt enabled
	TA0R = 0; // set count to 0;
	TA0CCR0 = 0x132;//0x426; // 1 minute
	ST = 1;
	TA0CCTL0 |= CM_1 + CCIE;
}
void setADC10(void)
{
	ADC10CTL0 |= ADC10SHT_2 + ADC10ON;
	ADC10CTL1 |= ADC10SSEL_1 + ADC10SHP;
	ADC10CTL2 |= ADC10RES;
	ADC10MCTL0 |= ADC10SREF_0 + ADC10INCH_4;
	ADC10IE |= ADC10IE0 + ADC10HIIE; // enable interrupt for ADC10
}


//Globals for ADC10routine, its outputs and ISRs FOUND IN dispatcher.c
int STATE = 0;
unsigned int ADC10_READING = 0;
unsigned int battLow = 0;

void ADC10routine(void)
{
	 WDTCTL = WDTPW + WDTHOLD;	// Stop watchdog timer
	    _bis_SR_register(GIE); //enable maskable global interrupts
		//setPins();
		setClocks();
		//setSPI();
		setTimers();
		setADC10();
		//setADC10();

		while(STATE != 2)
		{
			if(STATE == 1) // timer expired Take ADC10 readings
			{
				ADC10CTL0 |= ADC10ENC + ADC10SC;// Take sensor reading
				while((ADC10CTL1 & ADC10BUSY) == ADC10BUSY);
				ADC10_READING = ADC10MEM0; // save sensor reading
				ADC10MCTL0 &= ~ADC10INCH_4; // turn off channel 4
				ADC10MCTL0 |= ADC10INCH_5; //select ch 5 for battery reading
				P2OUT |= BIT1;
				_delay_cycles(40000);//let switch settle

				ADC10CTL0 |= ADC10ENC + ADC10SC;// Take battery reading
				while((ADC10CTL1 & ADC10BUSY) == ADC10BUSY);
				ADC10MCTL0 &= ~ ADC10INCH_5;//CLOSE CHANNEL 5
				ADC10MCTL0 |= ADC10INCH_4; //BACK TO CHANNEL 4
				P2OUT &= ~BIT1; // turn switch off


				STATE = 2;


			}

		}
		STATE = 0;// restore to timer set off for next round
		initClk();
}


main(void)
{
	//FakeList();
	ulCC3000DHCP = 0;
	ulCC3000Connected = 0;
	ulSocket = 0xFFFFFFFF;
	ulSmartConfigFinished=0;
	char outBuffer[BUFFER_SIZE];
	char inBuffer[BUFFER_SIZE];


	WDTCTL = WDTPW + WDTHOLD;

	//  Board Initialization start
	initDriver();
	setPins();
	setClocks();
	//setTimers(); Do this each time in the AD10routine

	ConnectToAP();
	turnLedOn(1);
	//wakeup_timer_disable();

	// Loop forever waiting  for commands from PC...
	while (1)
	{
		__bis_SR_register(LPM2_bits + GIE);
		__no_operation();

		/*if(ulSocket == 0xFFFFFFFF)
		{
			ConnectToServer();
		}*/

		if((printOnce == 1) && (ulCC3000DHCP == 1) && (ulCC3000Connected == 1)) {
			turnLedOn(6); // we have a dhcp address
			printOnce = 0;
		}

		if(deviceTime % reading_frequency == 0) {//(ulCC3000DHCP == 1) && (ulCC3000Connected == 1)) {

			if(ConnectToServer()) {
				int bytesToSend = 0;
				int bytesSent;
				memset(outBuffer, 0, BUFFER_SIZE);
				memset(inBuffer, 0, BUFFER_SIZE);
				bytesToSend = CreateReadingsRaw(outBuffer, 128);
				bytesToSend = bytesToSend*8+6;
				bytesSent = send(ulSocket, (char *) &outBuffer, bytesToSend, 0);
				if(bytesSent < 0 || bytesSent != bytesToSend) {
					turnLedOn(1);
					break;
				}

				int temp = recv(ulSocket, (char *) &inBuffer, BUFFER_SIZE, 0);
				if(temp != -1)
					ProcessConfirmRaw(inBuffer, temp);

				killSocket();
			}
		}

		if((deviceTime != 0) && (deviceTime % reading_frequency == 0)) {
			ADC10routine();
			AddReading(deviceTime, ADC10_READING);
		}

		SleepOneSecond();
	}
}


#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer__Off()
{
	//clear interrupt flags
	TA0CTL &= ~TAIFG;
	TA0CCR0 =  0x132;//0x462;
	if(ST==1)
	{
		STATE = 1;
		ST = 0;
	}
	TA0CTL |= MC_0; // stop timer
}

#pragma vector = ADC10_VECTOR
__interrupt void ADC10_read_In()
{
	__bic_SR_register_on_exit(CPUOFF);
	ADC10IFG &= ~(ADC10IFG0 + ADC10INIFG); // lower flag
	ADC10CTL0 &= ~(ADC10ENC + ADC10SC);
	if(ADC10MCTL0 & ADC10INCH_5)
	{
		if(ADC10MEM0 < 681)
		{
			battLow = 1;
		}
		else
		{
			battLow = 0;
		}


	}

}


