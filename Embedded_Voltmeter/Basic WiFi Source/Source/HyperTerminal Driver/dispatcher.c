/*****************************************************************************
*
*  dispatcher.c  - CC3000 Host Driver Implementation.
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

//*****************************************************************************
//
//! \addtogroup dispatcher_api
//! @{
//
//*****************************************************************************

#include "dispatcher.h"


#include <msp430.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////                     
//__no_init is used to prevent varible's initialize.                                                    ///
//for every IDE, exist different syntax:          1.   __CCS__ for CCS v5                               ///
//                                                2.  __IAR_SYSTEMS_ICC__ for IAR Embedded Workbench    ///
// *CCS does not initialize variables - therefore, __no_init is not needed.                             ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __CCS__

unsigned char g_ucUARTBuffer[UART_IF_BUFFER];
unsigned char g_ucLength;

#elif __IAR_SYSTEMS_ICC__

__no_init unsigned char g_ucUARTBuffer[UART_IF_BUFFER];
__no_init unsigned char g_ucLength;

#endif

int uart_have_cmd = 0;

//*****************************************************************************
//
//! UARTIntHandler
//!
//!  \param  buffer
//!
//!  \return none
//!
//!  \brief  Handles RX and TX interrupts
//
//*****************************************************************************
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
	switch(__even_in_range(UCA0IV,0x08))
	{
		case 0:break;                             // Vector 0 - no interrupt
		case 2:                                   // Vector 2 - RXIFG
			g_ucUARTBuffer[g_ucLength] = UCA0RXBUF;                  
			if (g_ucUARTBuffer[g_ucLength] == 0x0D)
			{
				g_ucLength = 0;
				uart_have_cmd = 1;
				__bic_SR_register_on_exit(LPM3_bits);
				__no_operation();
			}
			else
			{
				g_ucLength ++;
			}
		break;
		case 4:break;                             // Vector 4 - TXIFG
		default: break;  
  }
}


//*****************************************************************************
//
//! DispatcherUartSendPacket
//!
//!  \param  inBuff    pointer to the UART input buffer
//!  \param  usLength  buffer length
//!
//!  \return none
//!
//!  \brief  The function sends to UART a buffer of given length 
//
//*****************************************************************************
void
DispatcherUartSendPacket(unsigned char *inBuff, unsigned short usLength)
{
	while (usLength)
	{
		while (!(UCA0IFG&UCTXIFG));
		UCA0TXBUF = *inBuff;
		usLength--;
		inBuff++;
	}
}


//*****************************************************************************
//
//! Cofigure the UART
//!
//!  @param  none
//!
//!  @return none
//!
//!  @brief  Cofigure the UART
//
//*****************************************************************************
void
DispatcherUARTConfigure(void)
{
	// Configure UART pins P2.0 & P2.1
	P2SEL1 |= BIT0 + BIT1;
	P2SEL0 &= ~(BIT0 + BIT1);
	
	UCA0CTL1 |= UCSWRST; 
	UCA0CTL1 = UCSSEL_2;                      // Set SMCLK as UCLk 
	UCA0BRW = 0x9C4;                              // 9600 baud
	// 8000000/(9600*16) - INT(8000000/(9600*16))=0.083
	//UCA0BR1 = 0; 
	// UCBRFx = 1, UCBRSx = 0x49, UCOS16 = 1 (Refer User Guide)
	UCA0MCTLW = 0;//0x4911 ;                      
	                                        
	UCA0CTL1 &= ~UCSWRST;                     // release from reset
	UCA0IE   |= UCRXIE;

	g_ucLength = 0;
}


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
