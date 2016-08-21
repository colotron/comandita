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
	if(fifo->count < fifo->size) {
		fifo->buffer[fifo->writeIndex] = value;
		FifoIndexNext ( fifo, &(fifo->writeIndex) );
		fifo->count++;
	}
}

fifoElement_t FifoTake(fifo_p fifo) {
	if(fifo->count > 0) {
		fifoElement_t value = fifo->buffer[fifo->readIndex];
		FifoIndexNext ( fifo, &(fifo->readIndex) );
		fifo->count--;
		return value;
	} else {
		return 0;
	}

}

void FifoReset(fifo_p fifo) {
	fifo->writeIndex = 0;
	fifo->readIndex = 0;
	fifo->count = 0;
}

fifoIndex_t FifoCount(fifo_p fifo) {
	return fifo->count;
}

//-----------------------------------------------------------------------------------
unsigned int FifoTestPut1Take1(fifo_p fifoP) {
	unsigned int value = 10;

	FifoPut(value, fifoP);


	if ( FifoTake(fifoP) == value ) {
		return 0;
	} else {
		return 10;
	}
}

unsigned int FifoTestRollover(fifo_p fifoP) {
	unsigned int putTakeCount;

	for(putTakeCount = fifoP->size + 1; putTakeCount != 0; putTakeCount--) {
		if (FifoTestPut1Take1(fifoP) ) {
			break;
		}
	}

	return putTakeCount;
}

unsigned int FifoTestPut1MoreThanSize(fifo_p fifoP) {
	unsigned int i = fifoP->size + 1;

	FifoReset(fifoP);

	for(;i>0; i--) {
		FifoPut(i, fifoP);
	}

	for(i = fifoP->size + 1; i > 1; i--) {
		if( i !=  FifoTake(fifoP) )
			break;
	}

	return (i-1);
}

unsigned int FifoTestTake1MoreThanCount(fifo_p fifoP){
	unsigned int i = fifoP->size + 1;

	FifoReset(fifoP);
	for(;i>0; i--) {
		FifoPut(i, fifoP);
	}

	for(i = fifoP->size + 1; i > 0; i--) {
		FifoTake(fifoP) ;
	}

	return FifoTake(fifoP);
}

unsigned int FifoTest(void) {
	unsigned int testResult ;

	unsigned int buffer[4] ;
	FIFO_DECLARE(testFifo, buffer, sizeof(buffer)/sizeof(unsigned int) );

	if ( FifoTestPut1Take1(&testFifo) ) {
		testResult = 1;
	} else if ( FifoTestRollover(&testFifo) ) {
		testResult = 2;
	} else if ( FifoTestPut1MoreThanSize(&testFifo) ) {
		testResult = 3;
	} else if ( FifoTestTake1MoreThanCount(&testFifo) ) {
		testResult = 4;
	} else {
		testResult = 0;
	}

	return testResult;

}
