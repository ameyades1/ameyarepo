/*****************************************************************************
 FILE : 		Filter.h
 
 DESCRIPTION: 	Part of SSOCR. Contains general purpose image processing 
 				functions
 				 
 AUTHOR: 		Ameya Deswandikar
 
 REVSION HISTORY: 
 REV	DATE		BY						REMARKS
 1		06/05/10	Ameya Deswandikar		Original
  
 *****************************************************************************/
#ifndef Filter_H
#define Filter_H



void combineImages(unsigned char ucImgArr1[][MAX_HEIGHT],unsigned char ucImgArr2[][MAX_HEIGHT],unsigned char ucResultImgArr[][MAX_HEIGHT],long int lImgWidth,long int lImgHeight);
void copyImage(unsigned char ucSrcImgArr[][MAX_HEIGHT],unsigned char ucDestImgArr[][MAX_HEIGHT],long int ucImgWidth,long int ucImgHeight);
void rotateImg(unsigned char ucImgArr[][MAX_HEIGHT],long int lImgWidth,long int lImgHeight, float fAngle);
void clearImg(unsigned char ucImgArr[][MAX_HEIGHT],long int lImgWidth,long int lImgHeight,unsigned char ucColor);
void createMaskFromTemplateImg(unsigned char ucImgArr[][MAX_HEIGHT],int iMaskArr[][MAX_HEIGHT],long int lImgWidth,long int lImgHeight);
void drawRect(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR);
void calcHeightWidth(Rect *spRectR);
unsigned char findMin(unsigned char *ucArr,long int lCount);
unsigned char findMax(unsigned char *ucArr,long int lCount);

void applyFilter(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR,float fMaskArr[][MASK_SIZE],long int lMaskWidth,long int lMaskHeight,float fCoeff);

void threshold(unsigned char ucImgArr[][MAX_HEIGHT],unsigned char ucThrImgArr[][MAX_HEIGHT],Rect stRectR,unsigned char ucThr,unsigned char ucValAboveThr,unsigned char ucValBelowThr);

unsigned char computeAvg(unsigned char ucImgArr[][MAX_HEIGHT], long int lImgHeight,long int lImgWidth);
Point computeCorr(unsigned char ucImgArr1[][MAX_HEIGHT], long int lImgWidth1,long int lImgArrHeight1,unsigned char ucImgArr2[][MAX_HEIGHT],long int lImgWidth2,long int lImgArrHeight2);
Point computeCorr2(unsigned char ucImgArr1[][MAX_HEIGHT],long int lImgWidth1,long int lImgHeight1,int ucImgArr2[][MAX_HEIGHT],long int lImgWidth2,long int lImgHeight2);
float computeCorrHist(unsigned char *ucHist1,unsigned char *ucHist2);
double computeCorr3(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR1,Rect stRectR2);
void negative(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR);

void morph(unsigned char ucImgArr1[][MAX_HEIGHT],Rect spRectR,float fMaskArr[][MASK_SIZE],long int lMaskWidth,long int lMaskHeight,unsigned char ucOperation);

void applyFilterMedian(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR,long int lMaskWidth,long int lMaskHeight);

unsigned char getMedianValue(unsigned char ucImgArr[][MAX_HEIGHT],long int lMaskWidth,long int lMaskHeight);

unsigned char findBrightness(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR);

void findHistogram(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR,unsigned long int ulHist[]);

float findContrast(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR);

unsigned char calcThreshold(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR);
void shearImg(unsigned char ucImgArr[][MAX_HEIGHT],long int lImgWidth,long int lImgHeight, float fShearV,float fShearH);
void histogramEqu(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR);
void _gamma(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR,unsigned char ucCoeff,float fExponent);
void logTrans(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR,unsigned char ucCoeff);

unsigned char calcGlobalThreshold(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR);
unsigned char getAvgPixels(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR, unsigned char ucUpperLimit,unsigned char ucLowerLimit);
void addPaddingImg(unsigned char ucImgArr[][MAX_HEIGHT] , unsigned int uiHPadd, unsigned int uiVPadd);
void addOffsetRect(Rect *spRectR,unsigned int uiHOffset,unsigned int uiVOffset);
void removePaddingImg(unsigned char ucImgArr[][MAX_HEIGHT] , unsigned int uiImgWidth, unsigned int uiImgHeight);
void rotateRect(Rect * spRectR,float fAngle);
#endif
