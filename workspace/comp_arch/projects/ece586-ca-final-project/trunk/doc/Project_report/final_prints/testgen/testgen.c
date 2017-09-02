/*
 * testgen.c
 *
 *  Created on: 2013-03-08
 *      Author: root
 */

#include <stdio.h>
#include "testgen.h"

#define ADDRESS_1	(0x0000ABCDUL)
#define ADDRESS_2	(0x0000ABABUL)



static const char outcome_str[][20] = {
		"TAKEN",
		"NOT_TAKEN"
};

static const char br_type_str[][20] = {
		"CONDITIONAL",
		"UNCONDITIONAL",
		"JUMP"
};

static const TRACE trace_array[] =
{
		{ADDRESS_1,	BR_TAKEN,		BR_CONDITIONAL,	1},
		{ADDRESS_1,	BR_NOT_TAKEN,	BR_CONDITIONAL,	9},
#if 1
		{ADDRESS_1,	BR_TAKEN,		BR_CONDITIONAL,	1},
		{ADDRESS_1,	BR_NOT_TAKEN,	BR_CONDITIONAL,	9},

		{ADDRESS_1,	BR_TAKEN,		BR_CONDITIONAL,	1},
		{ADDRESS_1,	BR_NOT_TAKEN,	BR_CONDITIONAL,	9},

		{ADDRESS_1,	BR_TAKEN,		BR_CONDITIONAL,	1},
		{ADDRESS_1,	BR_NOT_TAKEN,	BR_CONDITIONAL,	9},

		{ADDRESS_1,	BR_TAKEN,		BR_CONDITIONAL,	1},
		{ADDRESS_1,	BR_NOT_TAKEN,	BR_CONDITIONAL,	9},

		{ADDRESS_1,	BR_TAKEN,		BR_CONDITIONAL,	1},
		{ADDRESS_1,	BR_NOT_TAKEN,	BR_CONDITIONAL,	9},

		{ADDRESS_1,	BR_TAKEN,		BR_CONDITIONAL,	1},
		{ADDRESS_1,	BR_NOT_TAKEN,	BR_CONDITIONAL,	9},

		{ADDRESS_1,	BR_TAKEN,		BR_CONDITIONAL,	1},
		{ADDRESS_1,	BR_NOT_TAKEN,	BR_CONDITIONAL,	9},

		{ADDRESS_1,	BR_TAKEN,		BR_CONDITIONAL,	1},
		{ADDRESS_1,	BR_NOT_TAKEN,	BR_CONDITIONAL,	9},

		{ADDRESS_1,	BR_TAKEN,		BR_CONDITIONAL,	1},
		{ADDRESS_1,	BR_NOT_TAKEN,	BR_CONDITIONAL,	9},

		{ADDRESS_1,	BR_TAKEN,		BR_CONDITIONAL,	1},
		{ADDRESS_1,	BR_NOT_TAKEN,	BR_CONDITIONAL,	9}
#endif
};

static const uint32 num_elements = sizeof(trace_array) / sizeof(trace_array[0]);

int main(int argc, char* argv[])
{

	FILE* fp;

	if(argc != 2)
	{
		printf("Usage: testgen <filename>");
		return 1;
	}

	fp = fopen(argv[1],"w+");
	if(!fp)
	{
		printf("Error creating file!");
		return 1;
	}
	uint32 i;
	for(i = 0; i < num_elements; i++)
	{
		uint32 j;
		for(j = 0; j < trace_array[i].repeat; j++)
		{

			fprintf(fp,"%d %s %s \n",trace_array[i].address, outcome_str[trace_array[i].outcome], br_type_str[trace_array[i].br_type]);
		}
	}
	printf("Test file created...\n");
	fclose(fp);
	return 0;
}
