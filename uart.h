/*
 * uart.h
 *
 *  Created on: Jul 31, 2016
 *      Author: daniel
 */

#ifndef UART_H_
#define UART_H_

extern void UartSetup(void) ;

extern unsigned int UartPendingInput(void) ;
extern char UartRead(void) ;
extern void UartWrite(char tx) ;
extern void UartTxStart(void) ;


#endif /* UART_H_ */
