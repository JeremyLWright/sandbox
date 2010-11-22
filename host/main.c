#define USE_AND_OR
#include "p24fxxxx.h"
#include "gpio.h"
#include "uart.h"
#include "PPS.h"
/*************** COFIGURATION **************************************
*	Watchdog Timer Disabled
*	Oscillator Selection: Fast RC (8MHz)
********************************************************************/
_CONFIG1(GCP_OFF & GWRP_OFF & FWDTEN_OFF & ICS_PGx1)
_CONFIG2(FNOSC_FRC)


unsigned char Rxdata[10];
unsigned char DataAvailable=0;
unsigned char Txdata[] = "RingRing";

typedef enum {
    HOST_INIT,
    HOST_WAIT_FOR_CALL,
    HOST_SEND_MESSAGE,
    HOST_CHECK_FOR_RESPONSE
} host_ringer_state_t; 
//********************************************************************************************** 
int main(void)
{	

//********************** Assign UART 2 signals onto pins using PPS ***********************************
	static unsigned int i = 0;
    host_ringer_state_t host_ringer_state = HOST_INIT;
    unsigned char rx_data = 0;


/*********************** UART 2 Configuration ****************************************************
*
*		1200 baudrate
*		Low baud rate
*		8 bit transmission/reception
*		No parity bit
*		1 stop bit
************************************************************************************************/	
    /*Enable UART intruupts*/	    
     /*wait till data is transmitted and received*/    
    while(1)
	{
        switch(host_ringer_state)
        {
            case HOST_INIT:
	            iPPSInput(IN_FN_PPS_U2RX,IN_PIN_PPS_RP5);		//Assing U2RX to pin RP2
            	iPPSOutput(OUT_PIN_PPS_RP3,OUT_FN_PPS_U2TX);	//Assing U2TX to pin RP3
                ConfigIntUART2(UART_RX_INT_DIS | UART_TX_INT_DIS);
                OpenUART2(UART_EN, UART_TX_ENABLE, 25);			//configure UART and enable it
                init_io();
                i = 0;
				host_ringer_state = HOST_WAIT_FOR_CALL;
                break;
            case HOST_WAIT_FOR_CALL:
                if(check_for_call()  == 1)
                {
                    host_ringer_state = HOST_SEND_MESSAGE;
					RINGER_LED=1;
                }
                else
                {
					RINGER_LED=0;
                    host_ringer_state = HOST_WAIT_FOR_CALL;
                }
                break;
            case HOST_SEND_MESSAGE:
                if(Txdata[i] != '\0')
                {
                    if(!BusyUART2())
                    {
                        WriteUART2(Txdata[i++]);
                    }
                }
                else
                {
                    i = 0;
					host_ringer_state = HOST_CHECK_FOR_RESPONSE;
                }
                break;
            case HOST_CHECK_FOR_RESPONSE:
                //Start Timer here.
                rx_data = U2RXREG;
                if(rx_data != 0)
                    host_ringer_state = HOST_INIT;
                else /* This should be a timeout */
                    host_ringer_state = HOST_SEND_MESSAGE;
                break;
            default:
                host_ringer_state = HOST_INIT;
        }
	}
        

    CloseUART2();									//disable UART2
	
	while(1);										//end of program
	
} 

