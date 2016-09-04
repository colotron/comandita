/*
 * common.h
 *
 *  Created on: Sep 4, 2016
 *      Author: daniel
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <msp430.h>

#define ISR(interruptVectorAddress) __attribute__ ((interrupt(interruptVectorAddress)))

inline void EnableInterrupts(void) {	__enable_interrupt();	}
inline void DisableInterrupts(void) {	__disable_interrupt();	}

inline void Delay(unsigned long int cycles) { __delay_cycles(cycles); }
inline void Nop(void) {	__nop(); }

#endif /* COMMON_H_ */
