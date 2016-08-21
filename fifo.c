/*
 * fifo.c
 *
 *  Created on: Jul 31, 2016
 *      Author: daniel
 */

#include "fifo.h"

static void FifoIndexNext(fifo_p fifo, fifoIndex_t *index) {
	(*index)++;
	if ( fifo->size <= *index) {
		*index = 0;
	}
}

void FifoPut(fifoElement_t value, fifo_p fifo){
	fifo->buffer[fifo->writeIndex] = value;
	FifoIndexNext ( fifo, &(fifo->writeIndex) );
}

fifoElement_t FifoTake(fifo_p fifo) {
	fifoElement_t value = fifo->buffer[fifo->readIndex];

	FifoIndexNext ( fifo, &(fifo->readIndex) );
	return value;

}


unsigned int FifoTest(void) {
	unsigned int testResult ;

	unsigned int buffer[4] ;
	FIFO_DECLARE(testFifo, buffer, sizeof(buffer)/sizeof(unsigned int) );

	FifoPut(1, &testFifo);
	FifoPut(2, &testFifo);
	FifoPut(3, &testFifo);
	FifoPut(4, &testFifo);

	if ( 1 != FifoTake(&testFifo) ) {
		testResult = 1;
	} else if ( 2 != FifoTake(&testFifo) ) {
		testResult = 2;
	} else if ( 3 != FifoTake(&testFifo) ) {
		testResult = 3;
	} else if ( 4 != FifoTake(&testFifo) ) {
		testResult = 4;
	} else {
		testResult = 0;
	}

	return testResult;

}
