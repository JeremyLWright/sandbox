/**********************************************************************
* 2009 Microchip Technology Inc.
*
* FileName:        	uart.c
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       	PIC24F
* Compiler:        	MPLAB C30 v3.11 or higher
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all 
* ownership and intellectual property rights in the code accompanying
* this message and in all derivatives hereto.  You may use this code,
* and any derivatives created by any person or entity by or on your 
* behalf, exclusively with Microchip's proprietary products.  Your 
* acceptance and/or use of this code constitutes agreement to the 
* terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS". NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT 
* NOT LIMITED TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, 
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS 
* CODE, ITS INTERACTION WITH MICROCHIP'S PRODUCTS, COMBINATION WITH 
* ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE 
* LIABLE, WHETHER IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR
* BREACH OF STATUTORY DUTY), STRICT LIABILITY, INDEMNITY, 
* CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
* EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR 
* EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER 
* CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE
* DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWABLE BY LAW, 
* MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS
* CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP 
* SPECIFICALLY TO HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and 
* determining its suitability.  Microchip has no obligation to modify,
* test, certify, or support the code.
*
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author        	Date      	Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Jyoti Shrinivas	04/04/09	First version of source file - v1
* Harsha.J.M			Modifications with library - version v1.1
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
* Code uses the PERIPHERAL LIBRARY support available with MPLAB C30 Compiler
* Code Tested on:
* EXPLORER 16 demo board with PIC24FJ256GB110 controller
* The Processor starts with the External Crystal (8 Mhz).
*
* Uses Tx pin for transmission and Rx pin for reception.
* Assings U2RX to pin RP10 using PPS feature
* Assings U2CTS to pin RP32 using PPS feature
* Assings U2TX to pin RP17 using PPS feature
* Assings U2RTS to pin RP31 using PPS feature
* Baud rate of 9600 is configred at 8MHz oscillator fequency
**********************************************************************/
#define USE_AND_OR
#include "p24fxxxx.h"
#include "uart.h"
#include "PPS.h"

/*************** COFIGURATION **************************************
*	Watchdog Timer Disabled
*	Oscillator Selection: Low Power Rc (500kHz)
********************************************************************/
_CONFIG1(GCP_OFF & GWRP_OFF & FWDTEN_OFF & ICS_PGx1)
_CONFIG2(FNOSC_FRC)


unsigned char Rxdata[10];
unsigned char DataAvailable=0;
unsigned char Txdata[] = "RingRing";

//*************** Interrupt Service routine for UART2 Transmission *************************************
void __attribute__ ((interrupt,no_auto_psv)) _U2TXInterrupt(void)
{	
  static unsigned int i=0;
  U2TX_Clear_Intr_Status_Bit;  						//clear the interrupt status of UART2 TX
  if(Txdata[i]!='\0')								//check for end of string
  {
   while(BusyUART2());								//wait till the UART is busy
   WriteUART2((unsigned int)Txdata[i++]);			//Transmit the data to hyper terminal of computer
  } 
  else
  DisableIntU2TX; 								//disable the UART TX interrupt after end of complete transmission
 
}

//*************** Interrupt Service routine for UART2 reception *************************************
void __attribute__ ((interrupt,no_auto_psv)) _U2RXInterrupt(void)
{
 static unsigned int j=0; 
 U2RX_Clear_Intr_Status_Bit;  						//clear the interrupt status of UART2 RX     
    
   while(!DataRdyUART2());							//wait for data reception on RX
   Rxdata[j++] = ReadUART2();						//Read the data from UART buffer
   if(j == 10)
   DataAvailable=1;									//Set the DataAvailability flag after complete reception		  
 }

 
//********************************************************************************************** 
int main(void)
{	

//********************** Assign UART 2 signals onto pins using PPS ***********************************
	iPPSInput(IN_FN_PPS_U2RX,IN_PIN_PPS_RP2);		//Assing U2RX to pin RP10
	iPPSInput(IN_FN_PPS_U2CTS,IN_PIN_PPS_RP4);	//Assing U2CTS to pin RP32
	iPPSOutput(OUT_PIN_PPS_RP3,OUT_FN_PPS_U2TX);	//Assing U2TX to pin RP17
	iPPSOutput(OUT_PIN_PPS_RP5,OUT_FN_PPS_U2RTS);	//Assing U2RTS to pin RP31
	static unsigned int i = 0;

   //: CloseUART2();  									//dsiable UART if enabled previously        

/*********************** UART 2 Configuration ****************************************************
*
*		9600 baudrate
*		Low baud rate
*		8 bit transmission/reception
*		No parity bit
*		1 stop bit
************************************************************************************************/	
    /*Enable UART intruupts*/	    
    ConfigIntUART2(UART_RX_INT_DIS | UART_TX_INT_DIS);
    OpenUART2(UART_EN, UART_TX_ENABLE, 207);			//configure UART and enable it
   init_io();
     /*wait till data is transmitted and received*/    
    while(1)
	{
		 if(Txdata[i]!='\0')								//check for end of string
  		{
   			while(BusyUART2());								//wait till the UART is busy
   				WriteUART2(Txdata[i++]);			//Transmit the data to hyper terminal of computer
		/*	if(DataRdyUART2())
			{
				i = ReadUART2();
			}*/
  		}
		else
			i = 0; 
        gpio_task();
	}
        

    CloseUART2();									//disable UART2
	
	while(1);										//end of program
	
} 

