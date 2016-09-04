/*
 * myAssert.c
 *
 *  Created on: Aug 21, 2016
 *      Author: daniel
 */


#include "common.h"
#include "led.h"

void AssertFailure(void) {
	volatile unsigned int continueBlocking = 1;

	DisableInterrupts();
	while (continueBlocking) {
		LedToggle();
		Delay(100000);
		Nop();
	}
	EnableInterrupts();
}


