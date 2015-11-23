#pragma once
#pragma once
#include <stdio.h>
#include "Config.h"
#include "BMPHeader.h"
#include "Filter.h"
#include "IconStatus.h"

unsigned char iconImgArr[MAX_WIDTH][MAX_HEIGHT];



unsigned char getIconStatus(unsigned char arr[][MAX_HEIGHT],Rect r)
{
	unsigned long int h[256];
	unsigned char c,iconStat = OFF;
	float onRatio;
	c = calcGlobalThreshold(arr,r);
	threshold(arr,arr, r, c,  WHITE,  BLACK);
	findHistogram(arr,r,h);	
	onRatio = (float)h[WHITE] / ((float)h[BLACK]+ (float)h[WHITE]);
	if(onRatio >= ICON_ON_COEFF)
	{
		iconStat = ON;
	}
	else
	{
		iconStat = OFF;
	}
	return iconStat;
}
