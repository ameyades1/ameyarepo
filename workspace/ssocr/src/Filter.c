/*****************************************************************************
 FILE : 		Filter.c
 
 DESCRIPTION: 	Part of SSOCR. Contains general purpose image processing 
 				functions
 				 
 AUTHOR: 		Ameya Deswandikar
 
 REVSION HISTORY: 
 REV	DATE		BY						REMARKS
 1		06/05/10	Ameya Deswandikar		Original
  
 *****************************************************************************/

#include <math.h>
#include "Config.h"
#include "BMPHeader.h"
#include "Filter.h"
#include "DigitRec.h"

extern unsigned char ucTempImgArr[][MAX_HEIGHT];
extern unsigned int uiImgWidth;
extern unsigned int uiImgHeight;
extern unsigned int uiHPadding;
extern unsigned int uiVPadding;

unsigned char tempMask[MAX_WIDTH][MAX_HEIGHT];
unsigned long int hist[255];
double corr_coeff;









/*-----------------------------------------------------------------------------
 * Function:    applyFilter
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input Image Array
 * 				Rect stRectR		// Rectangle to operate on within the image array
 *				float fMaskArr[][MASK_SIZE]	// The filter mask
 *				long int lMaskWidth			// Width of the filter mask
 *				long int lMaskHeight				// Height of the filter mask
 *				float fCoeff		// A constant to be multiplied to the output 
 *	
 * Description: Generic correlation filter function
 *
 * Returns: 	Nothing      
 *-----------------------------------------------------------------------------*/
void applyFilter(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR,float fMaskArr[][MASK_SIZE],long int lMaskWidth,long int lMaskHeight,float fCoeff)
{
	long int ls;
	long int lt;
	long int lx;
	long int ly;
	float fResult;

	copyImage(ucImgArr,tempMask,stRectR.P2.x,stRectR.P2.y);
	
	for(ly = stRectR.P1.y + lMaskHeight/2; ly <= stRectR.P2.y - lMaskHeight/2; ly++)
	{
		for(lx = stRectR.P1.x + lMaskWidth/2; lx<= stRectR.P2.x -lMaskWidth/2; lx++)
		{
			fResult = 0;
			for(ls = 0; ls < lMaskHeight; ls++)					
			{
				for(lt = 0;lt < lMaskWidth; lt++)
				{
					fResult += tempMask[lx - lMaskWidth/2 + lt][ly - lMaskHeight/2 + ls] * fMaskArr[ls][lt];
				}
			}
			fResult = fResult * fCoeff;
			if(fResult > WHITE)					
			{
				fResult = WHITE;
			}
			else
			if(fResult < BLACK)					
			{
				fResult = BLACK;
			}
			ucImgArr[lx][ly] = (unsigned char)fResult;
		}
	}
}






/*-----------------------------------------------------------------------------
 * Function:    threshold
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input Image Array
 * 				unsigned char ucThrImgArr[][MAX_HEIGHT]	// Filtered output image array
 *				Rect stRectR		// Rectangle to operate on within the input image array
 *				float arr2[][MASK_SIZE]	// The filter mask
 *				unsigned char ucThr		// The threshold level
 *				unsigned char ucValAboveThr	// Output value if input is above the greater (or equal to) the thershold level
 *				unsigned char ucValBelowThr	// Output value if input is less than the thershold level
 *	
 * Description: Thresholds the input image to the desired level. Useful for generating
 * 				two tone images.
 *
 * Returns: 	Nothing      
 *-----------------------------------------------------------------------------*/
void threshold(unsigned char ucImgArr[][MAX_HEIGHT],unsigned char ucThrImgArr[][MAX_HEIGHT],Rect stRectR,unsigned char ucThr,unsigned char ucValAboveThr,unsigned char ucValBelowThr)
{
	long int li;
	long int lj;

	for(li = stRectR.P1.x; li <= stRectR.P2.x; li++)
	{
		for(lj = stRectR.P1.y; lj <= stRectR.P2.y; lj++)
		{
			if(ucImgArr[li][lj] >= ucThr)
			{
				ucThrImgArr[li][lj] = ucValAboveThr;
			}
			else
			{
				ucThrImgArr[li][lj] = ucValBelowThr;
			}
		}
	}

}






/*-----------------------------------------------------------------------------
 * Function:    combineImages
 *
 * Arguments:	unsigned char ucImgArr1[][MAX_HEIGHT]		// Input Image1 Array
 * 				unsigned char ucImgArr2[][MAX_HEIGHT]	// Input Image2 Array
 *				unsigned char ucResultImgArr[][MAX_HEIGHT]	// Result Image Array
 *				long int lImgWidth 		// Width of the images
 *				long int lImgHeight		// Height of the images
 *				
 * Description: Adds the two input images
 *
 * Returns: 	Nothing      
 *-----------------------------------------------------------------------------*/

void combineImages(unsigned char ucImgArr1[][MAX_HEIGHT],unsigned char ucImgArr2[][MAX_HEIGHT],unsigned char ucResultImgArr[][MAX_HEIGHT],long int lImgWidth,long int lImgHeight)
{
	long int li;
	long int lj;
	long int lResult;

	for(li = 0; li < lImgHeight; li++)
	{
		for(lj = 0; lj < lImgWidth; lj++)
		{
			lResult = ucImgArr1[lj][li] + ucImgArr2[lj][li];
			if(lResult > 255)
			{
				lResult = 255;
			}
			ucResultImgArr[lj][li] = (unsigned char)lResult;
		}
	}
}






/*-----------------------------------------------------------------------------
 * Function:    computeAvg
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input Image1 Array
 * 				long int lImgHeight 		// Width of the image
 *				long int lImgWidth		// Height of the image
 *				
 * Description: Computes the arithmatic mean of the given image array
 *
 * Returns: 	unsigned char      
 *-----------------------------------------------------------------------------*/

unsigned char computeAvg(unsigned char ucImgArr[][MAX_HEIGHT], long int lImgHeight,long int lImgWidth)
{
	long int li;
	long int lj;
	long int lSum = 0;
	unsigned char ucAvg = 0;

	for(li = 0;li < lImgHeight; li++)
	{
		for(lj = 0;lj < lImgWidth; lj++)
		{
			lSum += ucImgArr[lj][li];
		}
	}
	ucAvg = (unsigned char) (lSum/(lImgHeight*lImgWidth) );
	return ucAvg;
}






/*-----------------------------------------------------------------------------
 * Function:    computeCorr
 *
 * Arguments:	unsigned char ucImgArr1[][MAX_HEIGHT]		// Input Image1 Array
 * 				long int lImgWidth1 	// Width of the image 1
 *				long int lImgArrHeight1		// Height of the image 1
 *				unsigned char ucImgArr2[][MAX_HEIGHT]		// Input Image2 Array
 				long int lImgWidth2 	// Width of the image 2
 *				long int lImgArrHeight2		// Height of the image 2
 *				
 * Description: Computes the normalized cross correlation of image 1 with image 2
 *
 * Returns: 	Point	// Returns the co-ordinates of the Point of the heighest 
 * 							correlation      
 *-----------------------------------------------------------------------------*/
Point computeCorr(unsigned char ucImgArr1[][MAX_HEIGHT], long int lImgWidth1,long int lImgArrHeight1,unsigned char ucImgArr2[][MAX_HEIGHT],long int lImgWidth2,long int lImgArrHeight2)
{
	unsigned char ucTempMaskAvg;
	unsigned char ucTempImgArrAvg;
	long int ls;
	long int lt;
	long int lx;
	long int ly;
	double dCorrCoeff = 0.0;
	double dMaxCorrCoeff = 0.0;
	double dMaskDev;
	double dImgDev;
	double dMaskDevSqr;
	double dImgDevSqr;
	Point stPointP = {0,0};
	
	ucTempImgArrAvg = computeAvg(ucImgArr2,lImgArrHeight2,lImgWidth2);
	
	for(ly = lImgArrHeight2 / 2; ly <= lImgArrHeight1 - lImgArrHeight2 / 2 - 1; ly++)
	{
		for(lx = lImgWidth2 / 2; lx <= lImgWidth1 - lImgWidth2 / 2 - 1; lx++)
		{
			for(ls = 0;ls < lImgArrHeight2; ls++)					// Fill the temp mask with img pixels
			{
				for(lt = 0;lt < lImgWidth2; lt++)
				{
					tempMask[lt][ls] = ucImgArr1[lx - lImgWidth2 / 2 + lt][ly - lImgArrHeight2 / 2 + ls];		
				}
			}

			ucTempMaskAvg = computeAvg(tempMask,lImgArrHeight2,lImgWidth2);

			dMaskDev = 0;
			dImgDev = 0;
			dMaskDevSqr = 0;
			dImgDevSqr = 0;

			for(ls = 0;ls < lImgArrHeight2; ls++)					//calculate term 1 and 3 of eqn i.e. mask deviation
			{									// and square mask deviation
				for(lt = 0;lt < lImgWidth2; lt++)
				{
					dMaskDev += (ucImgArr2[lt][ls] - ucTempImgArrAvg);
					dMaskDevSqr += ( (ucImgArr2[lt][ls] - ucTempImgArrAvg) * (ucImgArr2[lt][ls] - ucTempImgArrAvg) );
				}
			}
			
			for(ls = 0;ls < lImgArrHeight2; ls++)					// calculate term 2 and 4 of eqn i.e img deviation 
			{									// and square img deviation
				for(lt = 0;lt < lImgWidth2; lt++)
				{
					dImgDev += (tempMask[lt][ls] - ucTempMaskAvg);
					dImgDevSqr += ((tempMask[lt][ls] - ucTempMaskAvg) * (tempMask[lt][ls] - ucTempMaskAvg) ) ;
				}
			}
			
			dCorrCoeff = (double) (dMaskDev * dImgDev) / sqrt((dMaskDevSqr * dImgDevSqr)) ;

			if(dCorrCoeff > dMaxCorrCoeff)
			{
				dMaxCorrCoeff = dCorrCoeff;
				stPointP.x = lx;
				stPointP.y = ly;
			}

		}
	}
	return stPointP;
}




 
/*-----------------------------------------------------------------------------
 * Function:    createMaskFromTemplateImg
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input Image1 Array
 * 				long int lImgWidth 	// Width of the image 
 *				long int lImgArrHeight		// Height of the image 
 *				int iMaskArr[][MAX_HEIGHT]	// The Mask to be generated
 *				
 *				
 * Description: Generates a mask from an image (useful for correlation)
 *
 * Returns: 	Nothing	
 *-----------------------------------------------------------------------------*/
void createMaskFromTemplateImg(unsigned char ucImgArr[][MAX_HEIGHT],int iMaskArr[][MAX_HEIGHT],long int lImgWidth,long int lImgHeight)
{
	long int li;
	long int lj;
	int iCoeff;

	iCoeff = lImgWidth * lImgHeight;
	
	for(li = 0;li < lImgHeight; li++)
	{
		for(lj = 0;lj < lImgWidth; lj++)
		{
			if(ucImgArr[lj][li] == BLACK)
				iMaskArr[lj][li] = iCoeff;
			else
				iMaskArr[lj][li] = -1;
		}
	}
}






/*-----------------------------------------------------------------------------
 * Function:    computeCorr2
 *
 * Arguments:	unsigned char ucImgArr1[][MAX_HEIGHT]		// Input Image1 Array
 * 				long int lImgWidth1 		// Width of the image 1
 *				long int lImgHeight1		// Height of the image 1
 *				unsigned char ucImgArr2[][MAX_HIEGHT]		// Input Image2 Array
 *				long int lImgWidth2 	// Width of the image 2
 *				long int lImgHeight2		// Height of the image 2
 *				
 * Description: Computes the cross correlation of image 1 with image 2 
 * 				(does not use normalized correlation)
 *
 * Returns: 	Point	// Returns the co-ordinates of the Point of the heighest 
 * 							correlation      
 *-----------------------------------------------------------------------------*/
Point computeCorr2(unsigned char ucImgArr1[][MAX_HEIGHT],long int lImgWidth1,long int lImgHeight1,int ucImgArr2[][MAX_HEIGHT],long int lImgWidth2,long int lImgHeight2)
{
	long int ls;
	long int lt;
	long int lx;
	long int ly;
	float fCorrCoeff = 0;
	float fMaxCorrCoeff = 0;
	Point stPointP = {0,0};

	for(ly = lImgHeight2 / 2; ly < lImgHeight1 - lImgHeight2 / 2; ly++)
	{
		for(lx = lImgWidth2 / 2; lx < lImgWidth1 - lImgWidth2 / 2; lx++)
		{
			fCorrCoeff = 0;
			for(ls = 0; ls < lImgHeight2; ls++)					
			{
				for(lt = 0; lt < lImgWidth2; lt++)
				{
					fCorrCoeff += ucImgArr1[lx - lImgWidth2/2 + lt][ly - lImgHeight2/2 + ls] * ucImgArr2[lt][ls];
				}
			}
			if(fCorrCoeff > fMaxCorrCoeff)					
			{
				fMaxCorrCoeff = fCorrCoeff;
				stPointP.x = lx;
				stPointP.y = ly;
			}
		}
	}
	return stPointP;
}












/*-----------------------------------------------------------------------------
 * Function:    negative
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input Image1 Array
 * 				Rect stRectR	// Rectangle to operate on within the input image array
 *				
 * Description: Computes the negative of image
 *
 * Returns: 	Nothing    
 *-----------------------------------------------------------------------------*/
void negative(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR)
{
	unsigned char ucTemp;
	long int li;
	long int lj;
	
	for(li = stRectR.P1.y; li <= stRectR.P2.y; li++)
	{
		for(lj = stRectR.P1.x; lj <= stRectR.P2.x; lj++)
		{
			ucTemp = 255 - ucImgArr[lj][li];
			ucImgArr[lj][li] = ucTemp;
		}
	}
}






/*-----------------------------------------------------------------------------
 * Function:    calcHeightWidth
 *
 * Arguments:	Rect *spRectR		// Pointer to input rectangle
 *				
 * Description: Computes the height and width of the input rectangle
 *
 * Returns: 	Nothing    
 *-----------------------------------------------------------------------------*/
void calcHeightWidth(Rect *spRectR)
{
	spRectR->height = spRectR->P2.y - spRectR->P1.y + 1 ;
	spRectR->width = spRectR->P2.x - spRectR->P1.x + 1;
}






/*-----------------------------------------------------------------------------
 * Function:    copyImage
 *
 * Arguments:	unsigned char ucSrcImgArr[][MAX_HEIGHT]		// Source image array
 *				unsigned char ucDestImgArr[][MAX_HEIGHT]	// Copy image array	
 *				long int ucImgWidth			// Width of the image
 *				long int ucImgHeight		// Height of the image
 *				
 * Description: Copies the soucrce image to the destination image
 *
 * Returns: 	Nothing    
 *-----------------------------------------------------------------------------*/
void copyImage(unsigned char ucSrcImgArr[][MAX_HEIGHT],unsigned char ucDestImgArr[][MAX_HEIGHT],long int ucImgWidth,long int ucImgHeight)
{
	long int li;
	long int lj;
	for(li = 0; li < ucImgHeight; li++)
	{
		for(lj = 0; lj < ucImgWidth; lj++)
			ucDestImgArr[lj][li] = ucSrcImgArr[lj][li];
	}
}






/*-----------------------------------------------------------------------------
 * Function:    morph
 *
 * Arguments:	unsigned char ucImgArr1[][MAX_HEIGHT]		// Source image array
 *				Rect spRectR	 // Rectangle to operate on within the input image array
 *				float fMaskArr[][MASK_SIZE]	// Filter mask
 *				long int lMaskWidth		// Width of the image
 *				long int lMaskHeight		// Height of the image
 *				unsigned char ucOperation // ucOperation = EROSION or DIALATION
 *				
 * Description: Applies morphological processing like erosion and dialation to the 
 *				input image array
 *
 * Returns: 	Nothing
 *-----------------------------------------------------------------------------*/
void morph(unsigned char ucImgArr1[][MAX_HEIGHT],Rect spRectR,float fMaskArr[][MASK_SIZE],long int lMaskWidth,long int lMaskHeight,unsigned char ucOperation)
{
	unsigned char ucPixelBuffer[MASK_SIZE * MASK_SIZE];
	long int ls;
	long int lt;
	long int lx;
	long int ly;
	long int lElementCount;
		
	copyImage(ucImgArr1,ucTempImgArr,spRectR.P2.x,spRectR.P2.y);
	
	for(ly = spRectR.P1.y + lMaskHeight / 2; ly < spRectR.P2.y - lMaskHeight / 2; ly++)
	{
		for(lx = spRectR.P1.x + lMaskWidth / 2; lx< spRectR.P2.x - lMaskWidth / 2; lx++)
		{
			lElementCount = 0;
			for(ls = 0; ls < lMaskHeight; ls++)					
			{
				for(lt = 0; lt < lMaskWidth; lt++)
				{
					//tempMask[lt][ls] = ucTempImgArr[lx - lMaskWidth/2 + lt][ly - lMaskHeight/2 + ls] * (unsigned char)fMaskArr[ls][lt];
					if(fMaskArr[ls][lt] == 1)
						ucPixelBuffer[lElementCount++] = ucTempImgArr[lx - lMaskWidth/2 + lt][ly - lMaskHeight/2 + ls] * (unsigned char)fMaskArr[ls][lt];
				}
			}
			if(lElementCount != 0)
			{
				if(ucOperation == EROSION)
				{
					ucImgArr1[lx][ly] = findMax(ucPixelBuffer,lElementCount);
				}
				if(ucOperation == DILATION)
				{
					ucImgArr1[lx][ly] = findMin(ucPixelBuffer,lElementCount);
				}
			}
		}
	}
}






/*-----------------------------------------------------------------------------
 * Function:    findMin
 *
 * Arguments:	unsigned char* ucArr		// Source array
 *				long int lCount	// Number elements in the array
 *				
 * Description: Returns the minimum value of the array
 *
 * Returns: 	unsigned char
 *-----------------------------------------------------------------------------*/
unsigned char findMin(unsigned char *ucArr,long int lCount)
{
	long int li;
	unsigned char ucMin = 255;
	for(li = 0; li< lCount; li++)
	{
		if(ucArr[li] < ucMin)
			ucMin = ucArr[li];
	}
	return ucMin;
}






/*-----------------------------------------------------------------------------
 * Function:    findMax
 *
 * Arguments:	unsigned char* ucArr		// Source array
 *				long int lCount	// Number elements in the array
 *				
 * Description: Returns the maximum value of the array
 *
 * Returns: 	unsigned char
 *-----------------------------------------------------------------------------*/
unsigned char findMax(unsigned char *ucArr,long int lCount)
{
	long int li;
	unsigned char ucMax = 0;
	for(li = 0 ;li < lCount; li++)
	{
		if(ucArr[li] > ucMax)
			ucMax = ucArr[li];
	}
	return ucMax;
}






/*-----------------------------------------------------------------------------
 * Function:    applyFilterMedian
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Source image array
 *				Rect stRectR	 // Rectangle to operate on within the input image array
 *				float mask[][MASK_SIZE]	// Filter mask
 *				long int lMaskWidth		// Width of the filter
 *				long int lMaskHeight		// Height of the filter
 *				
 * Description: Applies median filter of size lMaskWidth x lMaskHeight to the input image array
 *
 * Returns: 	Nothing
 *-----------------------------------------------------------------------------*/
void applyFilterMedian(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR,long int lMaskWidth,long int lMaskHeight)
{
	unsigned char ucMedianValue;
	long int ls;
	long int lt;
	long int lx;
	long int ly;
	
	copyImage(ucImgArr,ucTempImgArr,stRectR.P2.x,stRectR.P2.y);

	for(ly = stRectR.P1.y + lMaskHeight / 2; ly < stRectR.P2.y - lMaskHeight / 2; ly++)
	{
		for(lx = stRectR.P1.x + lMaskWidth / 2; lx< stRectR.P2.x - lMaskWidth / 2; lx++)
		{
			for(ls = 0; ls < lMaskHeight; ls++)					
			{
				for(lt = 0;lt < lMaskWidth; lt++)
				{
					tempMask[lt][ls] = ucTempImgArr[lx - lMaskWidth / 2 + lt][ly - lMaskHeight / 2 + ls];
				}
			}
			ucMedianValue = getMedianValue(tempMask,lMaskWidth,lMaskHeight);
			ucImgArr[lx][ly] = ucMedianValue;
		}
	}
}






/*-----------------------------------------------------------------------------
 * Function:    getMedianValue
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Source image array
 *				long int lMaskWidth		// Width of the filter
 *				long int lMaskHeight		// Height of the filter
 *				
 * Description: Returns the median value of the array
 *
 * Returns: 	unsigned char
 *-----------------------------------------------------------------------------*/
unsigned char getMedianValue(unsigned char ucImgArr[][MAX_HEIGHT],long int lMaskWidth,long int lMaskHeight)
{
	unsigned char ucTempArr[MAX_MASK_SIZE*MAX_MASK_SIZE];
	unsigned char ucTemp;
	long int li;
	long int lj;
	long int lCount = 0;
	
	for(li = 0; li < lMaskWidth; li++)
	{
		for(lj = 0; lj < lMaskHeight; lj++)
		{
			ucTempArr[lCount++] = ucImgArr[li][lj]; 
		}
	}
	for(li = 0;li < lCount; li++)
	{
		for(lj = li;lj < lCount; lj++)
		{
			if(ucTempArr[li] > ucTempArr[lj])
			{
				ucTemp = ucTempArr[li];
				ucTempArr[li] = ucTempArr[lj];
				ucTempArr[lj] = ucTemp; 
			}
		}
	}
	return ucTempArr[lCount/2];
}






/*-----------------------------------------------------------------------------
 * Function:    rotateImg
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Source image array
 *				long int lImgWidth		// Width of the image
 *				long int lImgHeight		// Height of the image
 *				float fAngle		// Angle in radian
 *
 * Description: Rotates the image by the specified angle
 *
 * Returns: 	Nothing
 *-----------------------------------------------------------------------------*/
void rotateImg(unsigned char ucImgArr[][MAX_HEIGHT],long int lImgWidth,long int lImgHeight, float fAngle)
{
	long int lx;
	long int ly;

	long int lxT;
	long int lyT;

	long int lv;
	long int lu;

	long int lvT;
	long int luT;
	
	if(fAngle == 0)
		return;

	copyImage(ucImgArr,ucTempImgArr,lImgWidth,lImgHeight);
	clearImg(ucImgArr,lImgWidth,lImgHeight,BLACK);

	for(ly = -lImgHeight / 2 ; ly < lImgHeight / 2 ; ly++)
	{
		for(lx = - lImgWidth / 2 ; lx < lImgWidth / 2 ; lx++)
		{
			luT = (long int) ( (float)(lx) * cos(fAngle) - (float)(ly) * sin(fAngle) );
			lvT = (long int) ( (float)(lx) * sin(fAngle) + (float)(ly) * cos(fAngle) );
			
			lu = luT + lImgWidth / 2;
			lv = lvT + lImgHeight / 2;

			lxT = lx + lImgWidth / 2;
			lyT = ly + lImgHeight / 2;
			
			if(lu < 0)
				lu = 0;
			if(lu >= MAX_WIDTH)
				lu = MAX_WIDTH - 1;
			
			if(lv < 0)
				lv = 0;
			if(lv >= MAX_HEIGHT)
				lv = MAX_HEIGHT - 1;

			if(lxT < 0)
				lxT = 0;
			if(lxT >= MAX_WIDTH)
				lxT = MAX_WIDTH - 1;

			if(lyT < 0)
				lyT = 0;
			if(lyT >= MAX_HEIGHT)
				lyT = MAX_HEIGHT - 1;

			ucImgArr[lu][lv] = ucTempImgArr[lxT][lyT];
		}
	}
}






/*-----------------------------------------------------------------------------
 * Function:    clearImg
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Source image array
 *				long int lImgWidth		// Width of the image
 *				long int lImgHeight		// Height of the image
 *				unsigned char ucColor	// Intensity value  
 *
 * Description: Fills the image array with one colour
 *
 * Returns: 	Nothing
 *-----------------------------------------------------------------------------*/

void clearImg(unsigned char ucImgArr[][MAX_HEIGHT],long int lImgWidth,long int lImgHeight,unsigned char ucColor)
{
	long int li;
	long int lj;

	for(li = 0; li < lImgWidth; li++)
	{
		for(lj = 0; lj < lImgHeight; lj++)
		{
			ucImgArr[li][lj] = ucColor;
		}
	}
}






/*-----------------------------------------------------------------------------
 * Function:    drawRect
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Source image array
 *				Rect stRectR	// Rectangle to be drawn  
 *
 * Description: Draws the rectangle r in the image array of border 1 pixel thick
 * 				of black colour. Useful for debugging purposes.
 *
 * Returns: 	Nothing
 *-----------------------------------------------------------------------------*/
void drawRect(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR)
{
	long int li;
	long int lj;

	lj = stRectR.P1.y;
	for(li = stRectR.P1.x; li <= stRectR.P2.x; li++)
		ucImgArr[li][lj] = BLACK;
	
	lj = stRectR.P2.y;
	for(li = stRectR.P1.x; li <= stRectR.P2.x; li++)
		ucImgArr[li][lj] = BLACK;

	li = stRectR.P1.x;
	for(lj = stRectR.P1.y; lj <= stRectR.P2.y; lj++)
		ucImgArr[li][lj] = BLACK;

	li = stRectR.P2.x;
	for(lj = stRectR.P1.y; lj <= stRectR.P2.y; lj++)
		ucImgArr[li][lj] = BLACK;
}






/*-----------------------------------------------------------------------------
 * Function:    findHistogram
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Source image array
 *				Rect stRectR	 // Rectangle to operate on within the input image array  
 *				unsigned long int ulHist[] // The histogram array
 *
 * Description: Finds the histogram of the image within the rectangle stRectR
 *
 * Returns: 	Nothing
 *-----------------------------------------------------------------------------*/
void findHistogram(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR,unsigned long int ulHist[])
{
	long int li;
	long int lj;
	
	for(li = 0;li < 256; li++)
		ulHist[li] = 0;

	for(li = stRectR.P1.x; li < stRectR.P2.x; li++)
	{
		for(lj = stRectR.P1.y; lj < stRectR.P2.y; lj++)
		{
			ulHist[ucImgArr[li][lj]]++;
		}
	}
}






/*-----------------------------------------------------------------------------
 * Function:    findBrightness
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Source image array
 *				Rect stRectR	 // Rectangle to operate on within the input image array  
 *
 * Description: Computes and returns the brightness (average value of the pixels) 
 *				of the rectangle stRectR within the image array
 *
 * Returns: 	unsigned char
 *-----------------------------------------------------------------------------*/
unsigned char findBrightness(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR)
{
	unsigned char ucBrightness;
	long int lSum = 0;
	long int li;
	long int lj;
	for(li = stRectR.P1.x; li <= stRectR.P2.x; li++)
	{
		for(lj = stRectR.P1.y; lj <= stRectR.P2.y; lj++)
		{
			lSum += ucImgArr[li][lj];
		}
	}
	ucBrightness = (unsigned char) (lSum /(stRectR.width * stRectR.height));
	return ucBrightness;
}






/*-----------------------------------------------------------------------------
 * Function:    findContrast
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Source image array
 *				Rect stRectR	 // Rectangle to operate on within the input image array  
 *
 * Description: Computes and returns the contrast of the rectangle stRectR within 
 * 				the image array
 *
 * Returns: 	float
 *-----------------------------------------------------------------------------*/
float findContrast(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR)
{
	unsigned char ucMaxPixelValue = 0;
	unsigned char ucMinPixelValue = 255;
	long int li;
	long int lj;
	float fContrast;
		
	for(li = stRectR.P1.x;li < stRectR.P2.x;li++)
	{
		for(lj = stRectR.P1.y;lj <stRectR.P2.y;lj++)
		{
			if( ucImgArr[li][lj] >= ucMaxPixelValue)
				ucMaxPixelValue = ucImgArr[li][lj];
			
			if( ucImgArr[li][lj] <= ucMinPixelValue)
				ucMinPixelValue = ucImgArr[li][lj];
		}
	}
	
	fContrast = (float)((ucMaxPixelValue - ucMinPixelValue)/(ucMaxPixelValue + ucMinPixelValue) );
	return fContrast;
}






/*-----------------------------------------------------------------------------
 * Function:    calcThreshold
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Source image array
 *				Rect stRectR	 // Rectangle to operate on within the input image array  
 *
 * Description: Computes and returns the threshold value required for extracting 
 *				the illuminated segments in the rectangle stRectR within the image 
 * 				array
 *
 * Returns: 	unsigned char
 *-----------------------------------------------------------------------------*/
unsigned char calcThreshold(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR)
{
	unsigned int uiThreshold;
	unsigned char ucBrightness;
	unsigned char ucGlobalThreshold;
	ucBrightness = findBrightness(ucImgArr,stRectR);
	uiThreshold = (unsigned int)(BRIGHT_COEFF_SEGMENT * ucBrightness);
	if(uiThreshold > 255) 
		uiThreshold = 255;

	ucGlobalThreshold = calcGlobalThreshold(ucImgArr,stRectR);
	return ( (unsigned char)ucGlobalThreshold );
}






/*-----------------------------------------------------------------------------
 * Function:    shearImg
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Source image array
 *				long int lImgWidth	// Width of the image
 *				long int lImgHeight	// Height of the image
 * 				float fShearV	// Amount of vertical shear
 *				float fShearH	// Amount of horizontal shear
 *
 * Description: Shears the image array
 *
 * Returns: 	Nothing
 *-----------------------------------------------------------------------------*/
void shearImg(unsigned char ucImgArr[][MAX_HEIGHT],long int lImgWidth,long int lImgHeight, float fShearV,float fShearH)
{
	long int lx;
	long int ly;
	long int lv;
	long int lu;
	
	copyImage(ucImgArr,ucTempImgArr,lImgWidth,lImgHeight);
	clearImg(ucImgArr,lImgWidth,lImgHeight,BLACK);

	for(ly = -lImgHeight/2; ly < lImgHeight / 2; ly++)	// Image origin is shifted to the center of the rectangle
	{
		for(lx = -lImgWidth/2; lx < lImgWidth / 2; lx++)
		{
			lu = (long int) ( lx + fShearV * ly );
			lv = (long int) ( lx * fShearH + ly );
			
			lu += lImgWidth / 2;
			lv += lImgHeight / 2;

			if( lu < 0 )
			{	
				lu = 0;
			}
			else
			{
				if( lu >= lImgWidth)
					lu = lImgWidth - 1;
			}
			if( lv < 0 )
			{
				lv = 0;
			}
			else
			{
				if(lv >= lImgHeight)
					lv = lImgHeight - 1;
			}
			ucImgArr[lu][lv] = ucTempImgArr[lx + lImgWidth/2][ly + lImgHeight/2];
		}
	}
}






/*-----------------------------------------------------------------------------
 * Function:    histogramEqu
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Source image array
 *				Rect stRectR	 // Rectangle to operate on within the input image array 
 *
 * Description: Applies the histogram equalization to the rectangle stRectR within the
 *				image array.
 *
 * Returns: 	Nothing
 *-----------------------------------------------------------------------------*/
void histogramEqu(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR)
{
	long int lHistogram[256];
	long int lCDF[256];
	long int li;
	long int lj;
	double dResult;
	double dCoeff;
	
	dCoeff = 255;
	dCoeff = dCoeff / ( stRectR.height * stRectR.width );

	findHistogram(ucImgArr,stRectR,lHistogram);
	lCDF[0] = lHistogram[0];

	for(li = 1; li < 256; li++)
	{
		lCDF[li] = lCDF[li - 1] + lHistogram[li];	// Find the CDF (Cumulative distribution function (Cumulative PDF))
	}

	for(li = stRectR.P1.x; li < stRectR.P2.x; li++)
	{
		for(lj = stRectR.P1.y; lj < stRectR.P2.y; lj++)
		{
			dResult = floor( dCoeff * lCDF[ ucImgArr[li][lj] ]);
			ucImgArr[li][lj] = (unsigned char) dResult;
		}
	}
}






/*-----------------------------------------------------------------------------
 * Function:    _gamma
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Source image array
 *				Rect stRectR	 // Rectangle to operate on within the input image array 
 *				unsigned char ucCoeff	// constant to be multipled
 *				float fExponent		// the exponent
 *
 * Description: Applies the gamma transform to the rectangle r within the
 *				image array. (output = c * input ^ g)
 *
 * Returns: 	Nothing
 *-----------------------------------------------------------------------------*/
void _gamma(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR,unsigned char ucCoeff,float fExponent)
{
	int iResult;
	long int li;
	long int lj;
	
	for(li = stRectR.P1.x; li <= stRectR.P2.x; li++)
	{
		for(lj = stRectR.P1.y; lj <= stRectR.P2.y; lj++)
		{
			iResult = ucCoeff * pow(ucImgArr[li][lj],fExponent);
			if(iResult > 255)
			{
				iResult = 255;
			}
			if(iResult < 0)
			{
				iResult = 0;
			}
			ucImgArr[li][lj] = (unsigned char)iResult; 
		}
	}
}






/*-----------------------------------------------------------------------------
 * Function:    logTrans
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Source image array
 *				Rect stRectR	 // Rectangle to operate on within the input image array 
 *				unsigned char ucCoeff	// constant to be multipled
 *
 * Description: Applies the log transform to the rectangle stRectR within the
 *				image array. (output = c * log10(1 + input)
 *
 * Returns: 	Nothing
 *-----------------------------------------------------------------------------*/
void logTrans(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR,unsigned char ucCoeff)
{
	int iResult;
	long int li;
	long int lj;
	
	for(li = stRectR.P1.x; li <= stRectR.P2.x; li++)
	{
		for(lj = stRectR.P1.y; lj <= stRectR.P2.y; lj++)
		{
			iResult = log10(1 + ucImgArr[li][lj]);
			iResult = iResult * ucCoeff;
			if(iResult > 255)
			{
				iResult = 255;
			}
			if(iResult < 0)
			{
				iResult = 0;
			}
			ucImgArr[li][lj] = (unsigned char)iResult; 
		}
	}
}






/*-----------------------------------------------------------------------------
 * Function:    computeCorrHist
 *
 * Arguments:	unsigned long *ucHist1	// Histogram 1
 *				unsigned long *ucHist2	// Histogram 1
 *
 * Description: Computes and returns the normalized correlation of the 
 *				two histograms
 *
 * Returns: 	float
 *-----------------------------------------------------------------------------*/
float computeCorrHist(unsigned char *ucHist1,unsigned char *ucHist2)
{
	unsigned long int uli;
	unsigned long int ulSum1 = 0;
	unsigned long int ulSum2 = 0; 
	float fHistAvg1;
	float fHistAvg2;
	float fHistSqrDev1 = 0;
	float fHistSqrDev2 = 0;
	float fCorrCoeff = 0;
	
	for(uli = 0; uli < 256; uli++)
	{
		ulSum1 += ucHist1[uli];
		ulSum2 += ucHist2[uli];
	}
	fHistAvg1 = (float)ulSum1 / (float)256;
	fHistAvg2 = (float)ulSum2 / (float)256;
	
	for(uli = 0; uli < 256; uli++)
	{
		fHistSqrDev1 += (ucHist1[uli] - fHistAvg1) * (ucHist1[uli] - fHistAvg1);
		fHistSqrDev2 += (ucHist2[uli] - fHistAvg2) * (ucHist2[uli] - fHistAvg2);
		fCorrCoeff += (ucHist1[uli] - fHistAvg1) * (ucHist2[uli] - fHistAvg2);
	}

	fCorrCoeff = fCorrCoeff / sqrt(fHistSqrDev1 * fHistSqrDev2);
	return fCorrCoeff;
}






/*-----------------------------------------------------------------------------
 * Function:    computeCorr3
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Source image array
 *				Rect stRectR1		// Rectangular region 1
 *				Rect stRectR2		// Rectangular region 2
 *
 * Description: Computes and returns the normalized correlation [-1 1] of the 
 *				two rectangle areas within the source image array
 *
 * Returns: 	double
 *-----------------------------------------------------------------------------*/
double computeCorr3(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR1,Rect stRectR2)
{
	unsigned long int uli;
	unsigned long int ulj;
	unsigned long int ulh;
	unsigned long int ulw;
	double dRectAvgR1;
	double dRectAvgR2;
	double dRectSqrDevR1 = 0;
	double dRectSqrDevR2 = 0;
	double dSum1 = 0;
	double dSum2 = 0;
	double dCorrCoeff = 0;
	
	if(stRectR1.height >= stRectR2.height)
	{
		ulh = stRectR2.height;
	}
	else
	{
		ulh = stRectR1.height;
	}

	if(stRectR1.width >= stRectR2.width)
	{
		ulw = stRectR2.width;
	}
	else
	{
		ulw = stRectR1.width;
	}
	
	for(uli = 0; uli < ulw; uli++)
	{
		for(ulj = 0; ulj < ulh; ulj++)
		{
			dSum1 += ucImgArr[stRectR1.P1.x + uli][stRectR1.P1.y + ulj];
			dSum2 += ucImgArr[stRectR2.P1.x + uli][stRectR2.P1.y + ulj];
		}
	}

	dRectAvgR1 = dSum1 / (ulh * ulw);
	dRectAvgR2 = dSum2 / (ulh * ulw);

	for(uli = 0; uli < ulw; uli++)
	{
		for(ulj = 0; ulj < ulh; ulj++)
		{
			dCorrCoeff += ( (ucImgArr[stRectR1.P1.x + uli][stRectR1.P1.y + ulj] - dRectAvgR1) * (ucImgArr[stRectR2.P1.x + uli][stRectR2.P1.y + ulj] - dRectAvgR2) );
			dRectSqrDevR1 += ( (ucImgArr[stRectR1.P1.x + uli][stRectR1.P1.y + ulj] - dRectAvgR1) * (ucImgArr[stRectR1.P1.x + uli][stRectR1.P1.y + ulj] - dRectAvgR1) );
			dRectSqrDevR2 += ( (ucImgArr[stRectR2.P1.x + uli][stRectR2.P1.y + ulj] - dRectAvgR2) * (ucImgArr[stRectR2.P1.x + uli][stRectR2.P1.y + ulj] - dRectAvgR2) );
		}
	}

	dCorrCoeff = dCorrCoeff / sqrt(dRectSqrDevR1 * dRectSqrDevR2);
	return dCorrCoeff;
	
}





/*-----------------------------------------------------------------------------
 * Function:    getAvgPixels
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Source image array
 *				Rect stRectR		// Rectangle to Operate on
 *				unsigned char ucUpperLimit	// Upper Pixel Intensity Limit  
 *				unsigned char ucLowerLimit	// Lower Pixel Intensity Limit
 *
 * Description: Computes and returns the average pixel value between ucUpperLimit and
 *				ucLowerLimit. Used as a part of calcGlobalThreshold()
 *
 * Returns: 	unsigned char
 *-----------------------------------------------------------------------------*/
unsigned char getAvgPixels(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR, unsigned char ucUpperLimit,unsigned char ucLowerLimit)
{
	unsigned char ucAvg;
	int ii;
	int ij;
	long int lCount = 0;
	float fSum = 0;
	
	for(ii = stRectR.P1.x; ii <= stRectR.P2.x; ii++)
	{
		for(ij = stRectR.P1.y; ij <= stRectR.P2.y; ij++)
		{
			if(ucImgArr[ii][ij] >= ucLowerLimit && ucImgArr[ii][ij] <= ucUpperLimit)
			{	
				fSum += ucImgArr[ii][ij];
				lCount++;
			}
		}
	}

	ucAvg = (unsigned char) (fSum / lCount);
	return ucAvg;
}





/*-----------------------------------------------------------------------------
 * Function:    calcGlobalThreshold
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Source image array
 *				Rect stRectR		// Rectangle to Operate on
 *
 * Description: Computes and returns the threshold level using the global thresholding
 *				Method. This is histogram based thresholding
 *
 * Returns: 	unsigned char
 *-----------------------------------------------------------------------------*/
unsigned char calcGlobalThreshold(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR)
{
	unsigned char ucBrightness;
	unsigned char ucThreshold1;
	unsigned char ucThreshold2;
	unsigned char ucDelT;
	unsigned char ucMinDelT = 2;
	unsigned char ucAvgThreshold1;
	unsigned char ucAvgThreshold2;

	ucBrightness = findBrightness(ucImgArr,stRectR);
	ucThreshold1 = ucBrightness;
	
	do
	{
		ucAvgThreshold1 = getAvgPixels(ucImgArr,stRectR,255,ucThreshold1);
		ucAvgThreshold2 = getAvgPixels(ucImgArr,stRectR, ucThreshold1,0);
		ucThreshold2 = (ucAvgThreshold1 + ucAvgThreshold2)/2;
		ucDelT = abs(ucThreshold1 - ucThreshold2);
		ucThreshold1 = ucThreshold2;
	}while(ucDelT > ucMinDelT);
	return ucThreshold1;
}






void addPaddingImg(unsigned char ucImgArr[][MAX_HEIGHT] , unsigned int uiHPadd, unsigned int uiVPadd)
{
	unsigned int ii;
	unsigned int ij;

	clearImg(ucTempImgArr,MAX_WIDTH,MAX_HEIGHT,BLACK);

	for(ii = 0; ii < uiImgWidth; ii++)
	{
		for(ij = 0; ij < uiImgHeight; ij++)
		{
			ucTempImgArr[ii + uiHPadd][ij + uiVPadd] = ucImgArr[ii][ij];
		}
	}
	
	copyImage(ucTempImgArr,ucImgArr,MAX_WIDTH,MAX_HEIGHT);
}

void removePaddingImg(unsigned char ucImgArr[][MAX_HEIGHT] , unsigned int uiImgWidth, unsigned int uiImgHeight)
{
	unsigned int ii;
	unsigned int ij;
	unsigned int uiHPadd;
	unsigned int uiVPadd;

	uiHPadd = (MAX_WIDTH - uiImgWidth) / 2;
	uiVPadd = (MAX_HEIGHT - uiImgHeight) / 2;

	clearImg(ucTempImgArr,MAX_WIDTH,MAX_HEIGHT,WHITE);

	for(ii = 0; ii < uiImgWidth; ii++)
	{
		for(ij = 0; ij < uiImgHeight; ij++)
		{
			ucTempImgArr[ii][ij] = ucImgArr[ii + uiHPadd][ij + uiVPadd];
		}
	}
	clearImg(ucImgArr,MAX_WIDTH,MAX_HEIGHT,WHITE);
	copyImage(ucTempImgArr,ucImgArr,MAX_WIDTH,MAX_HEIGHT);
}

void addOffsetRect(Rect *spRectR,unsigned int uiHOffset,unsigned int uiVOffset)
{
	spRectR->P1.x += uiHOffset;
	spRectR->P2.x += uiHOffset;

	spRectR->P1.y += uiVOffset;
	spRectR->P2.y += uiVOffset;
	
	if(spRectR->P1.x >= MAX_WIDTH)
	{
		spRectR->P1.x = MAX_WIDTH;		// Boundary check
	}
	if(spRectR->P1.y >= MAX_HEIGHT)
	{
		spRectR->P1.y = MAX_HEIGHT;		// Boundary check
	}

	if(spRectR->P2.x >= MAX_WIDTH)
	{
		spRectR->P2.x = MAX_WIDTH;		// Boundary check
	}
	if(spRectR->P2.y >= MAX_HEIGHT)
	{
		spRectR->P2.y = MAX_HEIGHT;		// Boundary check
	}
	calcHeightWidth(spRectR);
}

void rotateRect(Rect * spRectR,float fAngle)
{
	Point stPointOrigin;
	Rect stRectTemp;
	
	fAngle = (fAngle * PI) / 180;

	*spRectR = getCorrectRect(*spRectR);
	
	stPointOrigin.x = (MAX_WIDTH - 1) / 2;
	stPointOrigin.y = (MAX_HEIGHT - 1) / 2;

	spRectR->P1.x -= stPointOrigin.x;	// Shift the origin to the center of the image
	spRectR->P1.y -= stPointOrigin.y;

	spRectR->P2.x -= stPointOrigin.x;
	spRectR->P2.y -= stPointOrigin.y;
	calcHeightWidth(spRectR);

	stRectTemp.P1.x = (long int) ( (float)(spRectR->P1.x) * cos(fAngle) - (float)(spRectR->P1.y) * sin(fAngle) );
	stRectTemp.P1.y = (long int) ( (float)(spRectR->P1.x) * sin(fAngle) + (float)(spRectR->P1.y) * cos(fAngle) );
	
	stRectTemp.P2.x = (long int) ( (float)(spRectR->P2.x) * cos(fAngle) - (float)(spRectR->P2.y) * sin(fAngle) );
	stRectTemp.P2.y = (long int) ( (float)(spRectR->P2.x) * sin(fAngle) + (float)(spRectR->P2.y) * cos(fAngle) );
	
	stRectTemp.P1.x += stPointOrigin.x;
	stRectTemp.P1.y += stPointOrigin.y;
	
	stRectTemp.P2.x += stPointOrigin.x;	// Shift the origin back  to top left corner
	stRectTemp.P2.y += stPointOrigin.y;
	
	stRectTemp = getCorrectRect(stRectTemp);
	calcHeightWidth(&stRectTemp);

	(*spRectR) = stRectTemp;
}
