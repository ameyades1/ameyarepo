/*
 * testgen.h
 *
 *  Created on: 2013-03-08
 *      Author: root
 */

#ifndef TESTGEN_H_
#define TESTGEN_H_

#ifndef __cplusplus
	typedef unsigned char bool;
#endif
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int 	uint32;


typedef enum _br_type
{
	BR_CONDITIONAL,
	BR_UNCONDITIONAL,
	BR_JUMP
}BR_TYPE;

typedef enum _outcome
{
	BR_TAKEN = 0,
	BR_NOT_TAKEN
}BR_OUTCOME;

typedef struct _trace
{
	uint32 	address;
	BR_OUTCOME	outcome;
	BR_TYPE br_type;
	uint32 	repeat;

}TRACE;

#endif /* TESTGEN_H_ */
