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
 * 	Recibir cadena de texto por puerto serie uart <---
 * 		Recibir caracter por puerto uart [hecho]
 * 			Configurar modulo uart	[hecho]
 * 			Configuramos reloj sistema/watchdog [hecho]
 * 			Recibimos caracteres en forma secuencial [hecho]
 * 			Recibir caracteres a traves de interrupción uart rx [hecho]
 *
 */

#include "common.h"
#include "uart.h"
#include "fifo.h"
#include "myAssert.h"
#include "led.h"

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
void Test(void) ;

int main(void) {
	Setup();

	LedOff() ;
	Test();

	__enable_interrupt();

	while(1) {
		if ( UartPendingInput() ) {
			UartRead();
			UartWrite( 'H' );
			UartWrite( 'o' );
			UartWrite( 'l' );
			UartWrite( 'a' );
			UartWrite( '\r' );
			UartWrite( '\n' );
			UartTxStart();
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

void Test(void) {
	FifoTest();
}

///----------------------------------------------------------------------
void WatchdogSetup(void) {
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
}

void ClockSetup(void) {
	if (CALBC1_1MHZ==0xFF) {				// If calibration constant erased
		while(1);                               // do not load, trap CPU!!
	}

	DCOCTL = 0;                               // Select lowest DCOx and MODx settings
	BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
	DCOCTL = CALDCO_1MHZ;
}

