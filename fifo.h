/*
 * fifo.h
 *
 *  Created on: Jul 31, 2016
 *      Author: daniel
 */

#ifndef FIFO_H_
#define FIFO_H_

typedef char fifoElement_t;
typedef unsigned int fifoIndex_t;

typedef struct fifo_s {
	fifoElement_t *buffer;
	fifoIndex_t readIndex, writeIndex, count;
	const unsigned int size;
} fifo_t;

typedef fifo_t *fifo_p;

#define FIFO_DECLARE(FIFO_NAME, BUFFER_NAME, FIFO_SIZE) \
	fifo_t FIFO_NAME = { \
			.buffer = BUFFER_NAME, \
			.readIndex = 0,\
			.writeIndex = 0, \
			.size = FIFO_SIZE, \
			.count = 0, \
	};

extern void FifoPut ( fifoElement_t value, fifo_p fifo ) ;

extern fifoElement_t FifoTake(fifo_p fifo) ;

extern unsigned int FifoSize(fifo_p fifo) ;
extern void FifoReset(fifo_p fifo) ;
extern fifoIndex_t FifoCount(fifo_p fifo) ;

extern void FifoTest(void) ;

#endif /* FIFO_H_ */
