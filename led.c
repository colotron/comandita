/*
 * led.c

 *
 *  Created on: Aug 21, 2016
 *      Author: daniel
 */

#include <msp430.h>

void LedSetup(void) {
	P1DIR |= BIT0;
}

void LedToggle(void) {
	P1OUT ^= BIT0;
}

void LedOff(void) {
	P1OUT |= BIT0;
}

void LedOn(void) {
	P1OUT &= ~BIT0;
}


