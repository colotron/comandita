/*
 * main.c
 *
 *  Created on: Jul 3, 2014
 *      Author: daniel
 */

/*
 * Interfaz de comandos en modo textual
 *
 * led on -> enciende el led
 * led off-> apaga el led
 * mem read 0x1234: leer posición de memoria 0x1234
 * mem write 0x1234 100: escribir posición de memoria 0x1234 con el valor 100
 *
 * 	Recibir cadena de texto por puerto serie uart
 * 		Recibir caracter por puerto uart <---
 * 			Configurar modulo uart	[hecho]
 * 			Configuramos reloj sistema/watchdog [hecho]
 * 			Recibimos caracteres en forma secuencial [hecho]
 * 			Recibir caracteres a traves de interrupción uart rx <---
 *
 */

#include <msp430.h>
#include "uart.h"
#include "fifo.h"

/*
 *
@startuml
activate main
main -> Interrupt: RxUart
deactivate main
activate Interrupt
note over Interrupt: doSomething()
Interrupt -> main: return
deactivate Interrupt
activate main
note over main: continue

@enduml
 *
 *
 */

void appRun(void) ;
void Setup(void) ;
unsigned int Test(void) ;

void LedToggle(void) ;
void LedOn(void) ;
void LedOff(void) ;


int main(void) {
	Setup();

	LedOff() ;
	if ( 0 != Test() ) {
		while(1) {
			LedToggle();
			__delay_cycles(100000);
			__nop();
		}
	}

	while(1) {
		if ( UartCharacterArrived() ) {
			UartWrite( UartRead() );	//echo
			LedToggle();
		}

		//Resto de aplicación, ejemplo
		//Monitorerar temperatura. Si temperatura > 30C encender led naranja
		appRun();
	}
}

void WatchdogSetup(void) ;
void LedSetup(void) ;
void ClockSetup(void) ;

void Setup(void) {
	WatchdogSetup();
	ClockSetup();
	LedSetup();
	UartSetup();
}


void appRun(void) {
	__nop();
}

unsigned int Test(void) {
	return FifoTest();
}

///----------------------------------------------------------------------
void WatchdogSetup(void) {
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
}

void LedSetup(void) {
	P1DIR |= BIT0;
}

void LedToggle(void) {
	P1OUT ^= BIT0;
}

void LedOn(void) {
	P1OUT |= BIT0;
}

void LedOff(void) {
	P1OUT &= ~BIT0;
}


void ClockSetup(void) {
	if (CALBC1_1MHZ==0xFF) {				// If calibration constant erased
		while(1);                               // do not load, trap CPU!!
	}

	DCOCTL = 0;                               // Select lowest DCOx and MODx settings
	BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
	DCOCTL = CALDCO_1MHZ;
}

