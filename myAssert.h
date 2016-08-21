/*
 * myAssert.h
 *
 *  Created on: Aug 21, 2016
 *      Author: daniel
 */

#ifndef MYASSERT_H_
#define MYASSERT_H_

extern void AssertFailure(void) ;

#define ASSERT(conditionThatShouldBeTrue) if ( !(conditionThatShouldBeTrue) ) AssertFailure();

#endif /* MYASSERT_H_ */
