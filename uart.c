/*
 * uart.c
 *
 *  Created on: Jul 31, 2016
 *      Author: daniel
 */

#include <msp430.h>
#include "fifo.h"

#define UART_INPUT_BUFFER_SIZE	80U

static fifoElement_t uartInputBuffer[UART_INPUT_BUFFER_SIZE];

FIFO_DECLARE(uartFifo, uartInputBuffer, UART_INPUT_BUFFER_SIZE);

void UartSetup(void) {
	P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2 ;                    // P1.1 = RXD, P1.2=TXD

	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 = 104;                            // 1MHz 9600
	UCA0BR1 = 0;                              // 1MHz 9600
	UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
}

unsigned int UartCharacterArrived(void) {
	return (IFG2 & UCA0RXIFG);
}

char UartRead(void) {
	return UCA0RXBUF;
}

void UartWrite(char tx){
	while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
	UCA0TXBUF = tx;
}


void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR (void) {
	while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
	UCA0TXBUF = UCA0RXBUF;                    // TX -> RXed character
}

