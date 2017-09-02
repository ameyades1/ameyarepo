/*r
 * testexec.cpp
 *
 *  Created on: 2013-03-08
 *      Author: root
 */



#include <cstdio>
#include <iostream>
#include <cstring>

#include "predictor.h"

#include "testgen.h"
//#include "tread.h"
//#include "cbp_inst.h"




using namespace std;
//using namespace cbp;



int main(int argc, char* argv[])
{

	PREDICTOR pred;
	branch_record_c br_rec;
	FILE* fp;

	if(argc != 3)
	{
		printf("Usage: testexec <input test file> <output test file>");
		return 1;
	}

	fp = fopen(argv[1],"r");
	if(!fp)
	{
		printf("Error opening input file!");
		return 1;
	}
	FILE* fp2 = fopen(argv[2],"w");
	if(!fp2)
    {
    	printf("Error creating output file!");
    	return 1;
	}

	uint32 address = 0;
	char outcome[10] = "X";
	char type[100] = "X";
	char buf[100];
	uint tadd = 0;


	bool actual = false;
	uint8 read_chars = 0;
	while (!feof(fp))
	{
		address = 0;
		strcpy(outcome,"X");
		strcpy(type, "X");

		buf[0] = '\n';
		//fgets(&buf[0],100,fp);
		fscanf(fp,"%d %s %s \n",&address,&outcome[0],&type[0]);

		if(0 == address || 0 == strcmp(outcome,"X") || 0 == strcmp(type,"X"))
			break;

		if(0 == strcmp(outcome,"NOT_TAKEN"))
		{
			actual = false;
		}
		else
		{
			actual = true;
		}

		//printf("%s\n",outcome);

		br_rec.instruction_addr = address;
		br_rec.instruction_next_addr = address + 0x04;
		br_rec.is_call = false;
		uint8 iscond = 0;
		if((iscond = strcmp(type,"CONDITIONAL")) == 0)
			br_rec.is_conditional = true;
		else
			br_rec.is_conditional = false;

		bool result = pred.get_prediction(&br_rec,NULL,&tadd);
		pred.update_predictor(&br_rec,NULL,actual,0x00);
		if(result == actual)
		{
			fprintf(fp2,"%d %s %s SUCCESS\n",address, outcome, type);
		}
		else
		{
			fprintf(fp2,"%d %s %s FAIL\n",address, outcome, type);
		}

	}
	printf("Output file created...\n");
	fclose(fp);
	return 0;
}

