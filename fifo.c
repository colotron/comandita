/*
 * fifo.c
 *
 *  Created on: Jul 31, 2016
 *      Author: daniel
 */

#include "myAssert.h"
#include "fifo.h"

static void FifoIndexNext(fifo_p fifo, fifoIndex_t *index) {
	(*index)++;
	if ( fifo->size <= *index) {
		*index = 0;
	}
}

void FifoPut(fifoElement_t value, fifo_p fifo){
	ASSERT(fifo->count < fifo->size);

	fifo->buffer[fifo->writeIndex] = value;
	FifoIndexNext ( fifo, &(fifo->writeIndex) );
	fifo->count++;
}

fifoElement_t FifoTake(fifo_p fifo) {
	ASSERT(fifo->count > 0);
	fifoElement_t value = fifo->buffer[fifo->readIndex];
	FifoIndexNext ( fifo, &(fifo->readIndex) );
	fifo->count--;
	return value;
}

fifoIndex_t FifoCount(fifo_p fifo) {
	return fifo->count;
}

void FifoReset(fifo_p fifo) {
	fifo->readIndex = 0;
	fifo->writeIndex = 0;
	fifo->count = 0;
}

unsigned int FifoSize(fifo_p fifo) {
	return fifo->size;
}

//---------------------------------------------------------------------

static void FifoTestPut1(fifo_p fifo) {
	unsigned int value = 10;
	unsigned int previousCount = FifoCount(fifo);

	ASSERT( FifoSize(fifo) > FifoCount(fifo) );	//test pre-condition
	FifoPut(value, fifo);

	ASSERT(FifoCount(fifo) == (previousCount + 1 ) ); //evaluate test result
}

static void FifoTestTake1(fifo_p fifo) {
	unsigned int previousCount = FifoCount(fifo);

	ASSERT(FifoCount(fifo) > 0);	//verify test pre-conditions

	FifoTake(fifo);	//call function to test

	ASSERT(FifoCount(fifo) == (previousCount - 1 ) ); //examine test results
}

static void FifoTestPut1Take1(fifo_p fifo) {
	const unsigned oldFifoCount = FifoCount(fifo);
	const unsigned int fifoValue = 5;

	ASSERT(FifoCount(fifo) <= FifoSize(fifo) -1 ) ;
	FifoPut(fifoValue, fifo);
	ASSERT( fifoValue == FifoTake(fifo) );
	ASSERT(oldFifoCount == FifoCount(fifo));
}

static void FifoTestRollOver(fifo_p fifo) {
	unsigned int i;

	FifoReset(fifo);

	//Fill fifo
	for(i = 0; i< FifoSize(fifo); i++) {
		FifoPut(i, fifo);
	}

	FifoTake(fifo);

	ASSERT( FifoSize(fifo) -1 == FifoCount(fifo) );

	FifoPut(i, fifo);

	ASSERT( FifoSize(fifo) == FifoCount(fifo) );

	for(i = 1; i<FifoSize(fifo)+1; i++) {
		ASSERT( FifoTake(fifo) == i);
	}

	ASSERT( 0 == FifoCount(fifo));
}

void FifoTest(void) {
	unsigned int buffer[4] ;
	FIFO_DECLARE(testFifo, buffer, sizeof(buffer)/sizeof(unsigned int) );

	FifoTestPut1(&testFifo);
	FifoTestTake1(&testFifo);
	FifoTestPut1Take1(&testFifo);
	FifoTestRollOver(&testFifo);
}
