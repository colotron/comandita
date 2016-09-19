/*
 * uart.c
 *
 *  Created on: Jul 31, 2016
 *      Author: daniel
 */

#include "common.h"
#include "fifo.h"
#include "myAssert.h"

#define UART_INPUT_BUFFER_SIZE	80U
#define UART_OUTPUT_BUFFER_SIZE	UART_INPUT_BUFFER_SIZE

static fifoElement_t uartInputBuffer[UART_INPUT_BUFFER_SIZE];
FIFO_DECLARE(uartFifoRx, uartInputBuffer, UART_INPUT_BUFFER_SIZE);

static fifoElement_t uartOutputBuffer[UART_OUTPUT_BUFFER_SIZE];
FIFO_DECLARE(uartFifoTx, uartOutputBuffer, UART_OUTPUT_BUFFER_SIZE);

unsigned int UartPendingInput(void) {
	return FifoCount(&uartFifoRx);
}

char UartRead(void) {
	return FifoTake(&uartFifoRx);
}

void UartWrite(char tx){
	FifoPut(tx, &uartFifoTx);
}

void UartWriteString(char *stringToSend) {
	while( *stringToSend != '\0' ) {
		UartWrite(*stringToSend);
		stringToSend++;
	}
}

char * UartReadString(void) {
	FifoPut('\0', &uartFifoRx);
	FifoReset(&uartFifoRx);
	return uartFifoRx.buffer;
}

static unsigned int UartTxInterruptEnabled(void) ;
static void UartEnableTxInterrupt(void) ;
void UartSendByte(char c) ;

void UartTxStart(void){
	if ( 0 == UartTxInterruptEnabled() ) {
		if ( 0 != FifoCount(&uartFifoTx) ) {
			UartSendByte( FifoTake(&uartFifoTx) );
			UartEnableTxInterrupt();
		}
	}
}

//----------------------------------------
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

void UartSendByte(char c) {
	UCA0TXBUF = c;
}

char UartReadReceivedByte(void) {
	return UCA0RXBUF;
}

static unsigned int UartTxInterruptEnabled(void) {
	return (IE2 & UCA0TXIE);
}

static void UartEnableTxInterrupt(void) {
	IE2 |= UCA0TXIE;         // Enable USCI_A0 TX interrupt
}


static void UartDisableTxInterrupt(void) {
	 IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
}

ISR(USCIAB0RX_VECTOR) void UartCharReceivedInterrupt (void) ;

//void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) UartRxCharInterrupt (void) {
void UartCharReceivedInterrupt (void) {
	FifoPut(UartReadReceivedByte(), &uartFifoRx);
}

ISR(USCIAB0TX_VECTOR) void UartReadyToTransmitInterrupt (void) ;

//void __attribute__ ((interrupt(USCIAB0TX_VECTOR))) USCI0TX_ISR (void) {
void UartReadyToTransmitInterrupt (void) {
	if( FifoCount(&uartFifoTx) ) {
		UartSendByte (FifoTake(&uartFifoTx) );
	} else {
		UartDisableTxInterrupt();
	}
}

