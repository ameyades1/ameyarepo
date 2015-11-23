/*****************************************************************************
 FILE : 		DigitRec.h
 
 DESCRIPTION: 	Part of SSOCR. Contains functions for seven segment digit 
 				recognition
 				 
 AUTHOR: 		Ameya Deswandikar
 
 REVSION HISTORY: 
 REV	DATE		BY						REMARKS
 1		30/06/10	Ameya Deswandikar		Original
  
 *****************************************************************************/

#ifndef DigitRec_H
#define DigitRec_H


Segment getSegmentWidth(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR);

Segment getSegmentHeight(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR);

Rect findRect(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR);

void findDigitRects(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectBoundaryRect);

Rect adjustDigitRectWidth(unsigned char ucImgArr[][MAX_HEIGHT], Rect stRectR,int iMaxHSegLength, int iMaxVSegLength, Rect stRectBoundary);

Rect getNextRect(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectLastRect,int iMaxVSegLength,int iMaxHSegLength,Rect stRectBoundaryRect);

unsigned int identifyDigit(unsigned char ucImgArr[][MAX_HEIGHT], Rect stRectR);

unsigned char matchPattern(unsigned char ucDigitPattern[]);

unsigned char findAvgSegmentThickness(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR);

unsigned short int processPanel(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectBoundaryRect);

unsigned char matchRegRect(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR1,Rect stRectR2);

unsigned char getSignDigit(unsigned char ucImgArr[][MAX_HEIGHT], Rect stRectBoundaryRect);

unsigned char identifySignDigit(unsigned char ucImgArr[][MAX_HEIGHT], Rect stRectR);

Rect getCorrectRect(Rect stRectR);

unsigned char isValidRect(Rect stRectR);

unsigned short int getNumberFromDigits(unsigned char *ucDigitsArr, unsigned char ucDigits);

void setCameraOrientation(unsigned char ucImgArr[][MAX_HEIGHT],float fAngle);

Rect applyCorrection(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR,Rect stRectBoundaryRect);

#endif