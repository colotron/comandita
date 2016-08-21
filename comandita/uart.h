/*
 * uart.h
 *
 *  Created on: Jul 31, 2016
 *      Author: daniel
 */

#ifndef UART_H_
#define UART_H_

void UartSetup(void) ;

unsigned int UartCharacterArrived(void) ;
char UartRead(void) ;
void UartWrite(char tx) ;


#endif /* UART_H_ */
