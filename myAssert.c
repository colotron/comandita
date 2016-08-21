/*
 * myAssert.c
 *
 *  Created on: Aug 21, 2016
 *      Author: daniel
 */

#include "led.h"

void AssertFailure(void) {
	volatile unsigned int continueBlocking = 1;

	while (continueBlocking) {
		LedToggle();
		__delay_cycles(100000);
		__nop();
	}
}


