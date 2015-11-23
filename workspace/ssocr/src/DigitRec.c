/*****************************************************************************
 FILE : 		DigitRec.c
 
 DESCRIPTION: 	Part of SSOCR. Contains functions for seven segment digit 
 				recognition
 				 
 AUTHOR: 		Ameya Deswandikar
 
 REVSION HISTORY: 
 REV	DATE		BY						REMARKS
 1		30/06/10	Ameya Deswandikar		Original
  
 *****************************************************************************/

#include <math.h>
#include "Config.h"
#include "BMPHeader.h"
#include "Filter.h"
#include "DigitRec.h"
#include "FilterConst.h"


unsigned char ucTestImgArr[MAX_WIDTH][MAX_HEIGHT];	// Main Image Buffer
unsigned char ucTempImgArr[MAX_WIDTH][MAX_HEIGHT];	// Temporary Image Buffer

unsigned char ucNoOfDigits = 0;				// Number of digits detected
unsigned char ucSegmentThickness;
unsigned char ucDigitsArr[MAX_NO_DIGITS];	// Array of the detected digits

unsigned int uiImgHeight;	// Image Height
unsigned int uiImgWidth;	// Image Width

unsigned int uiHPadding;	// Image Horizontal Padding
unsigned int uiVPadding;	// Image Vertical Padding

Rect stRectDigitRect[MAX_NO_DIGITS];	// The digit rectangles

#define DEBUG_RECT_ON





/*-----------------------------------------------------------------------------
 * Function:    isValidRect
 *
 * Arguments:	Rect stRectR		// Input rectangle
 *
 * Description: Checks if the input rectangle 'stRectR'is within the boudaries of the 
 *				image. Returns 0 if rectangle is invalid, else returns 1      
 *
 * Returns: 	unsigned char      
 *-----------------------------------------------------------------------------*/

unsigned char isValidRect(Rect stRectR)
{
	unsigned char ucIsValid = 0;

	if(stRectR.width > MAX_WIDTH || stRectR.height > MAX_HEIGHT)
	{	
		ucIsValid = 0;
	}
	if(stRectR.P1.x < 0 || stRectR.P2.x < 0 || stRectR.P1.x >= MAX_WIDTH || stRectR.P2.x >= MAX_WIDTH)
	{
		ucIsValid = 0;
	}
	if(stRectR.P1.y < 0 || stRectR.P2.y < 0 || stRectR.P1.y >= MAX_HEIGHT || stRectR.P2.y >= MAX_HEIGHT)
	{
		ucIsValid = 0;
	}
	else
	{	
		ucIsValid = 1;
	}
	return ucIsValid;
}












/*-----------------------------------------------------------------------------
 * Function:    getSegmentWidth
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input image array
 *				Rect stRectR	// Rectangle to operate on within the image array
 *	
 * Description: Returns a horizontal line segment of maximum length.        
 *
 * Returns: 	Segment	// The structure includes start point, end point and length      
 *-----------------------------------------------------------------------------*/
Segment getSegmentWidth(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR)
{
	long int li;
	long int lj;
	long int lLength = 0;
	long int lMaxLength = 0;	// Maximum segment length

	Point stPointP1 = {0,0};
	Point stPointP2 = {0,0};
	Segment stSegS;

	stSegS.length = 0;
	stSegS.P1.x = 0;
	stSegS.P1.y = 0;
	stSegS.P2.x = 0;
	stSegS.P2.y = 0;

	for(li = stRectR.P1.y; li <= stRectR.P2.y; li++)
	{
		stPointP1.y = li;
		stPointP2.y = li;
		lj = stRectR.P1.x;
		
		while(lj <= stRectR.P2.x)
		{
			if(ucImgArr[lj][li] !=WHITE && ucImgArr[lj][li] != BLACK)
			{
				break;			// Return if the pixel is neither black nor white
			}
			while(lj <= stRectR.P2.x && ucImgArr[lj][li] == WHITE)
			{
				lj++;	// Scan till one black pixel is found
			}
			if(lj == 0)
			{	
				stPointP1.x = 0;
			}
			else
			{	
				stPointP1.x = lj - 1;
			}

			while(lj <= stRectR.P2.x && ucImgArr[lj][li] == BLACK)
			{
				lj++;	// Scan till a white pixel is found. i.e. continue till there are black pixels
			}
			if(lj==0)
			{
				stPointP2.x = 0;
			}
			else
			{
				stPointP2.x = lj - 1;
			}
			lLength = stPointP2.x - stPointP1.x;

			if(lLength > lMaxLength)
			{
				lMaxLength = lLength;		// Find the maximum segment length
				stSegS.P1 = stPointP1;
				stSegS.P2 = stPointP2;
				stSegS.length = stSegS.P2.x - stSegS.P1.x;
			}
		}
	}
	return stSegS;
}






/*-----------------------------------------------------------------------------
 * Function:    getSegmentHeight
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input image array
 *				Rect stRectR	// Rectangle to operate on within the image array
 *	
 * Description: Returns a vertical line segment of maximum length.        
 *
 * Returns: 	Segment	// The structure includes start point,end point and length      
 *-----------------------------------------------------------------------------*/

Segment getSegmentHeight(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR)
{
	long int li;
	long int lj;
	long int lLength = 0;
	long int lMaxLength = 0;	// Maximum Segment length

	Point stPointP1 = {0,0};
	Point stPointP2 = {0,0};
	Segment stSegS;
	
	stSegS.length = 0;
	stSegS.P1.x = 0;
	stSegS.P1.y = 0;
	stSegS.P2.x = 0;
	stSegS.P2.y = 0;

	for(li = stRectR.P1.x; li <= stRectR.P2.x; li++)
	{
		stPointP1.x = li;
		stPointP2.x = li;
		lj = stRectR.P1.y;
		
		while(lj <= stRectR.P2.y)
		{
			if(ucImgArr[li][lj] !=WHITE && ucImgArr[li][lj] != BLACK)
			{
				break;		// Return if the pixel is neither black nor white
			}
			while(lj <= stRectR.P2.y && ucImgArr[li][lj] == WHITE)
			{
				lj++;		// Scan till one black pixel is found
			}
			stPointP1.y = lj - 1;
			
			while(lj <= stRectR.P2.y && ucImgArr[li][lj] == BLACK)
			{
				lj++;		// Scan till a white pixel is found. i.e. continue till there are black pixels
			}

			stPointP2.y = lj - 1;
			lLength = stPointP2.y - stPointP1.y;

			if(lLength > lMaxLength)
			{
				lMaxLength = lLength;		// Find the maximum segment length
				stSegS.P1 = stPointP1;
				stSegS.P2 = stPointP2;
				stSegS.length = lLength;
			}
		}
	}
	return stSegS;
}






/*-----------------------------------------------------------------------------
 * Function:    findRect
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input image array
 *				Rect stRectR	// Rectangle to operate on within the image array
 *	
 * Description: Returns a smaller rectangle which closely encloses the the stRectR 
 *				in the image,within the given input rectangle stRectR by 
 *				removing any padding      
 *
 * Returns: 	Rect	// The structure includes diagonal points, height and
 * 							width of the rectangle      
 *-----------------------------------------------------------------------------*/

Rect findRect(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR)
{
	unsigned char ucBlackPixelFound = 0;
	long int li;
	long int lj;
	Rect stRectResult;

	for(li = stRectR.P2.x; li >= stRectR.P1.x; li --)	//scan the whole image R->L 
	{
		ucBlackPixelFound = 0;
		for(lj = stRectR.P1.y ; lj <= stRectR.P2.y ; lj++)
		{
			if(ucImgArr[li][lj] == BLACK)
			{	
				ucBlackPixelFound = 1;	// Stop if a black pixel is found
				break;
			}
		}
		if(ucBlackPixelFound == 1)
			break;
	}
	stRectResult.P2.x = li;
	
	for(li = stRectR.P2.y ; li >= stRectR.P1.y; li --)	//scan the whole image Down to Up 
	{
		ucBlackPixelFound = 0;
		for(lj = stRectR.P1.x  ;lj <= stRectR.P2.x ; lj++)
		{
			if(ucImgArr[lj][li] == BLACK)
			{	
				ucBlackPixelFound = 1;	// Stop if a black pixel is found
				break;
			}
		}
		if(ucBlackPixelFound == 1)
			break;
	}
	stRectResult.P2.y = li;

	for(li = stRectR.P1.x ; li <= stRectR.P2.x ; li ++)		//scan the whole image L->R
	{
		ucBlackPixelFound = 0;
		for(lj = stRectR.P1.y ;lj <= stRectR.P2.y  ;lj++)
		{
			if(ucImgArr[li][lj] == BLACK)
			{	
				ucBlackPixelFound = 1;	// Stop if a black pixel is found
				break;
			}
		}
		if(ucBlackPixelFound == 1)
			break;
	}
	stRectResult.P1.x = li;

	for(li = stRectR.P1.y ; li <= stRectR.P2.y ; li++)						//scan the whole image Up to Down 
	{
		ucBlackPixelFound = 0;
		for(lj = stRectR.P1.x  ;lj <= stRectR.P2.x ;lj++)
		{
			if(ucImgArr[lj][li] == BLACK)
			{	
				ucBlackPixelFound = 1;	// Stop if a black pixel is found
				break;
			}
		}
		if(ucBlackPixelFound == 1)
			break;
	}
	stRectResult.P1.y = li;
	
	if(stRectResult.P1.x < stRectR.P1.x)		// Do the boundary checks
		stRectResult.P1.x = stRectR.P1.x;

	if(stRectResult.P1.y < stRectR.P1.y)
		stRectResult.P1.y = stRectR.P1.y;

	if(stRectResult.P2.x >= stRectR.P2.x)
		stRectResult.P2.x = stRectR.P2.x;

	if(stRectResult.P2.y >= stRectR.P2.y)
		stRectResult.P2.y = stRectR.P2.y;

	calcHeightWidth(&stRectResult);
	return stRectResult;
}






/*------------------------------------------------------------------------------------------------------
 * Function:    getNextRect
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input image array
 *				Rect stRectBoundaryRect	// Rectangle to operate on within the image array
 *				Rect stRectLastRect	// Reference rectangle from which the next one is to be
 * 									// searched
 *				int iMaxVSegLength	// Maximum vertical line segment length within stRectBoundaryRect
 *				int iMaxHSegLength	// Maximum horizontal line segment length within stRectBoundaryRect
 *	
 * Description: Returns a rectangle which contains one digit located to the left of the 
 *				current digit rectangle stRectLastRect , within the larger rectangle stRectBoundaryRect       
 *
 * Returns: 	Rect	// The structure includes diagonal points, height and
 * 						// width of the rectangle      
 *------------------------------------------------------------------------------------------------------*/

Rect getNextRect(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectLastRect,int iMaxVSegLength,int iMaxHSegLength,Rect stRectBoundaryRect)
{
	unsigned char ucVSegFound = 0;
	int ii;
	Segment stSegS;
	Rect stRectNextRect = stRectLastRect;

	stRectNextRect.P1.x = stRectLastRect.P1.x - 2;	// stRectNextRect is a rectangle strip of width = thickness of a segment
	stRectNextRect.P1.y = stRectBoundaryRect.P1.y;
	
	if(stRectNextRect.P1.x < stRectBoundaryRect.P1.x)
	{	
		stRectNextRect.P1.x = stRectBoundaryRect.P1.x;	// Boundary check
	}

	stRectNextRect.P2.y = stRectBoundaryRect.P2.y;
	stRectNextRect.P2.x = stRectLastRect.P1.x ;

	stRectNextRect.P1.x --;
	stRectNextRect.P2.x --;
	calcHeightWidth(&stRectNextRect);

	if(stRectNextRect.P1.x >= stRectBoundaryRect.P1.x)		// Continue only if the boundary rectangle is not crossed
	{
		for(ii = stRectLastRect.P1.x; ii > stRectBoundaryRect.P1.x; ii --)			// Scan the image from P1 of input rectangle 
		{																			// From Right to left  
			stSegS = getSegmentHeight(ucImgArr,stRectNextRect);
			if(stSegS.length >= VSEG_DEV * iMaxVSegLength)
			{
				ucVSegFound = 1;			// if a vertical segment is found, set the flag 
				break;						// and exit the loop
			}
			stRectNextRect.P1.x --;			// Boundary Checks

			if(stRectNextRect.P1.x <= 0)
				stRectNextRect.P1.x = 0;
		
			stRectNextRect.P2.x --;			

			if(stRectNextRect.P2.x <= 0)	// Boundary Checks
				stRectNextRect.P2.x = 0;
			calcHeightWidth(&stRectNextRect);

			if(stRectNextRect.P1.x <= stRectBoundaryRect.P1.x)	// Boundary Checks
			{
				stRectNextRect.P1.x = stRectBoundaryRect.P1.x;	
				calcHeightWidth(&stRectNextRect);
				break;
			}
		
		}
	}
	if(ucVSegFound == 1)			// Mark a rectangle once a vertical segment is found
	{
		if(stRectNextRect.P2.x >= stRectBoundaryRect.P2.x)
		{
			stRectNextRect.P2.x = stRectBoundaryRect.P2.x - 1;
		}
		stRectNextRect.P1.x = stRectNextRect.P2.x - iMaxHSegLength * RECT_WIDTH_MULTIPLIER;
		if(stRectNextRect.P1.x <= 0)
		{
			stRectNextRect.P1.x = 0;	// Boundary Checks
		}
		calcHeightWidth(&stRectNextRect);
	
		if(stRectNextRect.P1.x <= stRectBoundaryRect.P1.x)	// Boundary Checks
		{
			stRectNextRect.P1.x = stRectBoundaryRect.P1.x;
		}
		if(stRectNextRect.P1.y >= stRectBoundaryRect.P1.y)
		{
			stRectNextRect.P1.y = stRectBoundaryRect.P1.y;
		}
		calcHeightWidth(&stRectNextRect);
	}
	else
	{
		stRectNextRect.P1.x = 0;		// Return 0 rectangle if no digit is found
		stRectNextRect.P1.y = 0;
		stRectNextRect.P2.x = 0;
		stRectNextRect.P2.y = 0;
		calcHeightWidth(&stRectNextRect);
	}
	return stRectNextRect;
}






/*---------------------------------------------------------------------------------------
 * Function:    adjustDigitRectWidth
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input image array
 *				Rect stRectR	// Rectangle whose width is to be adjusted	
 *				int iMaxHSegLength // Maximum acceptable length of a Horizontal segment
 *	
 * Description: Reduces or increases the digit rectangle width to fit exactly around the 
 *				digit.
 *
 * Returns: 	Rect	// The structure includes diagonal points, height and
 * 						// width of the rectangle      
 *---------------------------------------------------------------------------------------*/

Rect adjustDigitRectWidth(unsigned char ucImgArr[][MAX_HEIGHT], Rect stRectR,int iMaxHSegLength,int iMaxVSegLength,Rect stRectBoundary)
{
	int ij;
	float fSegRatio;
	float fWidthRatio;
	Segment stSegHSeg;
	Segment stSegS;
	Segment LastSeg;	// The leftmost segment in the rectangle stRectR
	Rect stRectAdjR;	// The adjusted rectangle 
	Rect stRectScanRect;	

	stRectAdjR = findRect(ucImgArr,stRectR);	// Trim the rectangle to eliminate white borders

	stSegHSeg = getSegmentWidth(ucImgArr,stRectAdjR);	// Find maximum Horizontal segment

	LastSeg = stSegHSeg;
	

/*----- REDUCE THE RECTANGLE WIDTH TO THE LEFTMOST HORIZONTAL SEGMENT -----*/

	stRectScanRect.P1.x = stRectAdjR.P1.x;
	stRectScanRect.P2.x = stRectAdjR.P2.x;
	for(ij = stRectAdjR.P1.y ; ij < stRectAdjR.P2.y; ij++)
	{
		stRectScanRect.P1.y = ij;				
		stRectScanRect.P2.y = ij;
		calcHeightWidth(&stRectScanRect);
		stSegS = getSegmentWidth(ucImgArr,stRectScanRect);
		if(stSegS.P1.x < LastSeg.P1.x && stSegS.length >= iMaxHSegLength * HSEG_DEV)
		{
			LastSeg = stSegS;		// Find the left most horizontal segment
		}
	}
	stRectAdjR.P1.x = LastSeg.P1.x;

	if(stRectAdjR.P1.x < stRectBoundary.P1.x)	// Boundary Check
	{
		stRectAdjR.P1.x = stRectAdjR.P1.x;
	}
	calcHeightWidth(&stRectAdjR);

	stRectAdjR = findRect(ucImgArr,stRectAdjR);

/*----------------------------------------------------------------------*/

/*----- INCREASE THE RECTANGLE WIDTH TO ACCOMODATE THE LEFTMOST VERTICAL SEGMENT -----*/
	stRectScanRect.P1 = stRectAdjR.P1;
	stRectScanRect.P2.x = stRectAdjR.P1.x;
	stRectScanRect.P2.y = stRectAdjR.P2.y;
	calcHeightWidth(&stRectScanRect);
	
	stSegS = getSegmentHeight(ucImgArr,stRectScanRect);
	fSegRatio = (float)(stRectAdjR.width) / (float)(stRectAdjR.height / 2);

	while( stSegS.length > stRectAdjR.height * HEIGHT_THRESHOLD_COEFF)
	{
		stRectScanRect.P1.x--;			// Increase the rectangle width till a vertical segment 
		stRectScanRect.P2.x--;			// exists at the edge of the rectangle.  
										// This is required for sheared as seven segments digits are sheared
		if(stRectScanRect.P1.x < stRectBoundary.P1.x)
		{	
			stRectScanRect.P1.x++;		// Boundary Check
			stRectScanRect.P2.x++;
			calcHeightWidth(&stRectScanRect);
			break;
		}

		calcHeightWidth(&stRectScanRect);
		stRectAdjR.P1 = stRectScanRect.P1;
		calcHeightWidth(&stRectAdjR);
			
		stSegS = getSegmentHeight(ucImgArr,stRectScanRect);
	}
/*------------------------------------------------------------------------------------*/

	stRectAdjR = findRect(ucImgArr,stRectAdjR);		// Eliminate any offset white pixels

	fSegRatio = (float)(stRectAdjR.width) / (float)(stRectAdjR.height / 2);
	fWidthRatio = (float)(stRectAdjR.width) / (float)(iMaxHSegLength);

	if(fSegRatio < (float)MIN_SEGMENT_RATIO || fWidthRatio < MIN_RECT_WIDTH_COEFF)
	{
		stSegS = getSegmentWidth(ucImgArr,stRectAdjR);		// Adjust the rectangle width in case of a '1'
		stRectAdjR.P1.x = stRectAdjR.P2.x - (iMaxHSegLength);
		
		if(stRectAdjR.P1.x < stRectBoundary.P1.x)
		{
			stRectAdjR.P1.x = stRectBoundary.P1.x;	// Boundary Check
		}
		calcHeightWidth(&stRectAdjR);
	}
	calcHeightWidth(&stRectAdjR);
	return stRectAdjR;
}






/*-----------------------------------------------------------------------------
 * Function:    findDigitRects
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input image array
 *				Rect stRectBoundaryRect	// Rectangle to operate on within the image array				
 *	
 * Description: Finds the number of ucDigitsArr, and the rectangles in which these 
 * 				ucDigitsArr are present, within the larger rectangle stRectBoundaryRect
 *
 * Returns: 	Nothing // Fills the global array Rect stRectDigitRect[] which contains the
 * 				digit rectangles, and global variable ucNoOfDigits
 *-----------------------------------------------------------------------------*/

void findDigitRects(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectBoundaryRect)
{
	unsigned char ucVSegFound = 0;
	int ii;
	float fSegmentRatio;
	Segment stSegMaxHSeg;
	Segment stSegMaxVSeg;
	Segment stSegS;
	Rect stRectFirstDigit;
	Rect stRectTemp;

	stSegMaxHSeg = getSegmentWidth(ucImgArr,stRectBoundaryRect);	// Find the largest Horizontal and vertical line segment in
	stSegMaxVSeg = getSegmentHeight(ucImgArr,stRectBoundaryRect);	// the entire panel to find length of one LED-segment
	
	if( stSegMaxVSeg.length > MAX_VSEG_COEFF * (stRectBoundaryRect.height) ) //If the 2 vertical segments appear joint i.e as 1 segment  
		stSegMaxVSeg.length = MAX_VSEG_COEFF * (stSegMaxVSeg.length) ;	// then limit the max vertical segment to the threshold
	
	
	fSegmentRatio = ((float)stSegMaxHSeg.length / (float)stSegMaxVSeg.length);

	if(fSegmentRatio <= MIN_SEGMENT_RATIO)
	{
		stSegMaxHSeg.length = stSegMaxVSeg.length;		// Make the Aspect Ratio = 1 E.g. All 1's Case
	}
		
	stRectFirstDigit.P2 = stRectBoundaryRect.P2;	//stRectFirstDigit is a rectangle for scanning the whole image Right->Left
	stRectFirstDigit.P2.x;
	stRectFirstDigit.P1.y = stRectBoundaryRect.P1.y; //stRectFirstDigit is strip of width = thickess of a segment
	stRectFirstDigit.P1.x = stRectBoundaryRect.P2.x - 2 ;		
	calcHeightWidth(&stRectFirstDigit);				

	for(ii = stRectFirstDigit.P2.x; ii >= stRectBoundaryRect.P1.x; ii -= 2)	 // Scan the whole image stRectBoundaryRect->L to find the 
	{																		// First vertical segment
		stSegS = getSegmentHeight(ucImgArr,stRectFirstDigit);
		if(stSegS.length >= VSEG_DEV * stSegMaxVSeg.length)
		{
			ucVSegFound = 1;		// Set flag when a segment is found and exit the loop
			break;
		}
		stRectFirstDigit.P1.x -= 2;
		stRectFirstDigit.P2.x -= 2;
		calcHeightWidth(&stRectFirstDigit);
	}
	calcHeightWidth(&stRectFirstDigit);

	if(ucVSegFound == 0)	// If no vertical segment is found then Number of digits = 0
	{					
		ucNoOfDigits = 0;
	}
	else				// If atleast 1 vertical segment is found, mark a rectangle around it 
	{
		stRectFirstDigit.P2.x = (stSegS.P2.x);		// Mark the 1st peripheral rectangle from the 1st segment found above
		if(stRectFirstDigit.P2.x >= stRectBoundaryRect.P2.x)								
		{
			stRectFirstDigit.P2.x = stRectBoundaryRect.P2.x - 1;	// Boundary check
		}
		
		stRectFirstDigit.P1.x = stRectFirstDigit.P2.x - (stSegMaxHSeg.length * RECT_WIDTH_MULTIPLIER); // Width of the rectangle to accomodate shear etc.
		
		if(stRectFirstDigit.P1.x <= stRectBoundaryRect.P1.x)
		{
			stRectFirstDigit.P1.x = stRectBoundaryRect.P1.x;	// Boundary check
		}

		calcHeightWidth(&stRectFirstDigit);
		
		stRectFirstDigit = adjustDigitRectWidth(ucImgArr,stRectFirstDigit,stSegMaxHSeg.length,stSegMaxVSeg.length,stRectBoundaryRect); // Adjust the rectangle width

		stRectDigitRect[ucNoOfDigits++] = stRectFirstDigit;	
		stRectTemp = stRectFirstDigit;				// Store the rectangle
		
		while((stRectTemp.P1.x - stRectBoundaryRect.P1.x) >= stSegMaxHSeg.length * HSEG_DEV)	//Try searching for more digits till you reach the end of the area
		{												
			stRectTemp = getNextRect(ucImgArr,stRectDigitRect[ucNoOfDigits-1],stSegMaxVSeg.length,stSegMaxHSeg.length,stRectBoundaryRect); // Find the next rectangle			
			if(stRectTemp.width > 1)
			{
				stRectTemp = adjustDigitRectWidth(ucImgArr,stRectTemp,stSegMaxHSeg.length,stSegMaxVSeg.length,stRectBoundaryRect);
				stRectDigitRect[ucNoOfDigits++] = stRectTemp;
			}
		}
	}
}






/*-----------------------------------------------------------------------------
 * Function:    matchPattern
 *
 * Arguments:	unsigned char ucDigitPattern[]		// Input seven segment pattern				
 *	
 * Description: Returns the digit(0 to 9) for the given seven segment pattern
 * 				Returns 10 if the pattern does not match with predefined 
 *				patterns (error condition)
 *
 * Returns: 	unsigned char
 *-----------------------------------------------------------------------------*/

unsigned char matchPattern(unsigned char ucDigitPattern[])
{
	unsigned char uci;
	unsigned char ucj;
	unsigned char ucSegmentMatch; // Segment match flag

	for(uci = 0; uci <= 9; uci++)
	{
		ucSegmentMatch = 0;
		for(ucj = 0; ucj < 7; ucj++)
		{
			if(ucDigitPattern[ucj] == ucDigitSegPattern[uci][ucj])
			{
				ucSegmentMatch = 1;
			}
			else
			{
				ucSegmentMatch = 0;
				break;
			}
		}
		if(ucSegmentMatch == 1) // If flag stays 1 after the exiting inner loop, then pattern the is found
			break;
	}
	return uci;
}






/*-----------------------------------------------------------------------------
 * Function:    identifyDigit
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input image array
 *				Rect stRectR		// Rectangle which contains the digit				
 *	
 * Description: Identifies and returns the digit (0 to 9) in the given rectangle.
 * 				Returns 10 if the pattern does not match with predefined 
 *				patterns (error condition)
 *
 * Returns: 	unsigned int
 *-----------------------------------------------------------------------------*/
unsigned int identifyDigit(unsigned char ucImgArr[][MAX_HEIGHT], Rect stRectR)
{
	unsigned char ucHSegPresent[3];	// Array for indicating presence of horizontal segment
	unsigned char ucVSegPresent[4];	// Array for indicating presence of vertical segment 
	unsigned char ucInd;		
	unsigned char ucSegmentPattern[7];	// The segment pattern formed by horizontal and vertical segments
	unsigned char ucDigit;	// The digit 

	Segment stSegHSeg[3];	// The horizontal segments of the digit
	Segment stSegVSeg[4];	// The vertical segments of the digit

	Rect stRectR1;	// The rectangles used for detecting each segment
	Rect stRectR2;
	Rect stRectR3;
	Rect stRectR4;
	
/*---------- MARK RECTANGLES FOR DETECTING HORIZONTAL SEGMENTS ----------*/
	stRectR1.P1 = stRectR.P1;
 	stRectR1.P2.x = stRectR.P2.x;
	stRectR1.P2.y = stRectR.P1.y + stRectR.height/3;
  	calcHeightWidth(&stRectR1);

	stRectR2.P1.x = stRectR.P1.x;
	stRectR2.P1.y = stRectR.P1.y + stRectR.height/3;		// Divide the digit rectangle  
	stRectR2.P2.x = stRectR.P2.x;							// in 3 equal parts by 2 horizontal lines
	stRectR2.P2.y = stRectR.P1.y + 2*stRectR.height/3;
	calcHeightWidth(&stRectR2);

	stRectR3.P1.x = stRectR.P1.x;
	stRectR3.P1.y = stRectR.P1.y + 2*stRectR.height/3;
	stRectR3.P2 = stRectR.P2;
	calcHeightWidth(&stRectR3);
	
	stSegHSeg[0] = getSegmentWidth(ucImgArr,stRectR1);
	stSegHSeg[1] = getSegmentWidth(ucImgArr,stRectR2);
	stSegHSeg[2] = getSegmentWidth(ucImgArr,stRectR3);
/*---------------------------------------------*/

/*---------- MARK RECTANGLES FOR DETECTING VERTICAL SEGMENTS ----------*/
	stRectR1.P1 = stRectR.P1;
	stRectR1.P2.x = stRectR.P1.x + (stRectR.width / 2);
	stRectR1.P2.y = stRectR.P1.y + stRectR.height / 2;
	calcHeightWidth(&stRectR1);

	stRectR2.P1.x = stRectR.P1.x + (stRectR.width / 2);
	stRectR2.P1.y = stRectR.P1.y;
	stRectR2.P2.x = stRectR.P2.x;
	stRectR2.P2.y = stRectR.P1.y + stRectR.height / 2;
	calcHeightWidth(&stRectR2);							// Divide the rectangle in 4 equal parts
														// by 1 vertical line and 1 horizontal line
	stRectR3.P1.x = stRectR.P1.x;		
	stRectR3.P1.y = stRectR.P1.y + stRectR.height / 2;
	stRectR3.P2.x = stRectR.P1.x + (stRectR.width / 2);
	stRectR3.P2.y = stRectR.P2.y;
	calcHeightWidth(&stRectR3);
	
	stRectR4.P1.x = stRectR.P1.x + (stRectR.width / 2);
	stRectR4.P1.y = stRectR.P1.y + stRectR.height/2;
	stRectR4.P2 = stRectR.P2;
	calcHeightWidth(&stRectR4);
	
	stSegVSeg[0] = getSegmentHeight(ucImgArr,stRectR1);
	stSegVSeg[1] = getSegmentHeight(ucImgArr,stRectR2);
	stSegVSeg[2] = getSegmentHeight(ucImgArr,stRectR3);
	stSegVSeg[3] = getSegmentHeight(ucImgArr,stRectR4);
/*---------------------------------------------*/

/*---------- THRESHOLD THE SEGMENTS ----------*/
	for(ucInd = 0; ucInd < 3; ucInd++)
	{
		if(stSegHSeg[ucInd].length < WIDTH_THRESHOLD_COEFF * stRectR.width)
			ucHSegPresent[ucInd] = 0;
		else
			ucHSegPresent[ucInd] = 1;
	}
	for(ucInd = 0; ucInd < 4; ucInd++)
	{
		if(stSegVSeg[ucInd].length < HEIGHT_THRESHOLD_COEFF * stRectR.height)
			ucVSegPresent[ucInd] = 0;
		else
			ucVSegPresent[ucInd] = 1;
	}
/*---------------------------------------------*/
	
	ucSegmentPattern[0] = ucHSegPresent[0];		// Generate the segment pattern
	ucSegmentPattern[1] = ucVSegPresent[1];
	ucSegmentPattern[2] = ucVSegPresent[3];
	ucSegmentPattern[3] = ucHSegPresent[2];
	ucSegmentPattern[4] = ucVSegPresent[2];
	ucSegmentPattern[5] = ucVSegPresent[0];
	ucSegmentPattern[6] = ucHSegPresent[1];
	
	ucDigit = matchPattern(ucSegmentPattern);	// Identify the digit
	return ucDigit;
}







/*-----------------------------------------------------------------------------
 * Function:    findAvgSegmentThickness
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input image array
 *				Rect stRectR		// Rectangle to operate on within the image array				
 *	
 * Description: Finds and returns the average thickness of a segment in
 *				the given rectangle.
 *
 * Returns: 	unsigned char
 *-----------------------------------------------------------------------------*/

unsigned char findAvgSegmentThickness(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR)
{
	unsigned char ucAvgThickness;
	int iSegLenArr[MAX_HEIGHT];
	long int li,lCount =0;
	float fTotalLength = 0;
	Segment stSegS;
	Rect stRectR1;

	stRectR1.P1.x = stRectR.P1.x;
	stRectR1.P1.y = stRectR.P1.y;
	stRectR1.P2.x = stRectR.P2.x;
	stRectR1.P2.y = stRectR.P1.y + 1;
	calcHeightWidth(&stRectR1);

	for(li = stRectR.P1.y; li < stRectR.P2.y - 1; li++)
	{
		stSegS = getSegmentWidth(ucImgArr,stRectR1);
		if(stSegS.length > 0)
		{
			iSegLenArr[lCount++] = stSegS.length;
			fTotalLength += stSegS.length;
		}
		stRectR1.P1.y = li;
		stRectR1.P2.y = li + 1;
		calcHeightWidth(&stRectR1);
	}
	ucAvgThickness = fTotalLength / lCount;
	return ucAvgThickness;
}	



/*-------------------------------------------------------------------------------------------------
 * Function:    processPanel
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input image array
 *				Rect stRectBoundaryRect		// Rectangle to operate on within the image array				
 *	
 * Description: Finds all the seven segment ucDigitsArr in the given rectangle stRectBoundaryRect
 *				Fills the global variables ucNoOfDigits (Number of Digits), 
 * 				stRectDigitRect[] (digit rectangles),and ucDigitsArr[] (the ucDigitsArr)
 *
 * Returns: 	unsigned short int // Returns 0xFFFF if there is an error in detection of any digit
 *-------------------------------------------------------------------------------------------------*/

unsigned short int processPanel(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectBoundaryRect)
{
	unsigned char ucSegmentOnThreshold;
	unsigned short int usDigitValue = 0;
	int iInd;
	Rect stRectR;
	Rect stRectTemp;
	
	ucNoOfDigits = 0;
	if(isValidRect(stRectBoundaryRect) == 0)
		return 0xFFFF;
/*----------------------FILTERING OPERATIONS -------------------------------------------*/	
	if(SEGMENT_COLOUR == BLACK)
	{
		negative(ucImgArr,stRectBoundaryRect);	// Take the image neagetive if segment colour is black
	}
	ucSegmentOnThreshold = calcThreshold(ucImgArr,stRectBoundaryRect); // Calculate the threshold 
	threshold(ucImgArr,ucImgArr, stRectBoundaryRect, ucSegmentOnThreshold,  WHITE,  BLACK);
	applyFilterMedian(ucImgArr,stRectBoundaryRect,3,3);		// Remove salt and pepper noise
	negative(ucImgArr,stRectBoundaryRect);
/*--------------------------------------------------------------------------------------*/	

/*----------------------FIND THE RECTANGLULAR SUBIMAGE WHERE ALL DIGITS MAY BE LOCATED--------------*/	
	stRectR = stRectBoundaryRect;
	stRectTemp = findRect(ucImgArr,stRectBoundaryRect);	// Eliminate any white borders surrounding the 
	stRectR.P1.y = stRectTemp.P1.y;						// digits	
	stRectR.P2.y = stRectTemp.P2.y;
	calcHeightWidth(&stRectR);
/*---------------------------------------------------------------------------------------------------*/
	
	
/*-------------FIND RECTANGLES OF ALL INDIVIDUAL DIGITS IN THE SUBIMAGE---------------------------*/	
	findDigitRects(ucImgArr,stRectR);		// Find all digit rectangles 
	for(iInd = 0; iInd < ucNoOfDigits; iInd++)
	{
		stRectTemp = findRect(ucImgArr,stRectDigitRect[iInd]);	// Remove vertical white borders only
		stRectDigitRect[iInd].P1.y = stRectTemp.P1.y;		
		stRectDigitRect[iInd].P2.y = stRectTemp.P2.y;
		calcHeightWidth(&stRectDigitRect[iInd]);
	}
	//drawRect(ucImgArr,stRectR);
/*-----------------------------------------------------------------------------------------------*/
	if(ucNoOfDigits != 0)
	{
		for(iInd = 0; iInd<ucNoOfDigits; iInd++)
		{
			ucDigitsArr[iInd] = identifyDigit(ucImgArr,stRectDigitRect[iInd]);	//Identify the digit in each rectangle
			if(ucDigitsArr[iInd] == 10 || ucDigitsArr[iInd] == 8)
			{
				stRectDigitRect[iInd] = applyCorrection(ucImgArr,stRectDigitRect[iInd],stRectBoundaryRect);
				ucDigitsArr[iInd] = identifyDigit(ucImgArr,stRectDigitRect[iInd]);
				if(ucDigitsArr[iInd] == 10)
				{
					usDigitValue = 0xFFFF;
				}
			}
		}
		#ifdef DEBUG_RECT_ON
			for(iInd = 0; iInd < ucNoOfDigits; iInd++)
			{
				drawRect(ucImgArr,stRectDigitRect[iInd]);
			}
			drawRect(ucImgArr,stRectR);
		#endif
		if(usDigitValue != 0xFFFF)
			usDigitValue = getNumberFromDigits(ucDigitsArr,ucNoOfDigits);
		
	}
	else
	{
		usDigitValue = 0xFFFF;
	}
	
	return usDigitValue;
}






/*--------------------------------------------------------------------------------------------
 * Function:    matchRegRect
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input image array
 *				Rect stRectR1		// Rectangle 1	.
 *				Rect stRectR2		// Rectangle 2
 *	
 * Description: Computes the normalized correlation between rectangles stRectR1 and stRectR2,
 *				within the given image array.If the correlateion exceeds the set 
 *				threshold for matching, it returns 1 else returns 0.
 *
 * Returns: 	unsigned char 
 *-------------------------------------------------------------------------------------------*/

unsigned char matchRegRect(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR1,Rect stRectR2)
{
	unsigned char ucIsMatch = 0;
	unsigned long int ulHist1[256];
	unsigned long int ulHist2[256]; 
	double dCorrCoeff = 0;
		
	findHistogram(ucImgArr,stRectR1,ulHist1);
	findHistogram(ucImgArr,stRectR2,ulHist2);
	
	dCorrCoeff = computeCorr3(ucImgArr,stRectR1,stRectR2);

	if(dCorrCoeff >= 0.85)
		ucIsMatch = 1;
	return ucIsMatch;
}






/*-----------------------------------------------------------------------------
 * Function:    identifySignDigit
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input image array
 *				Rect stRectR		// Rectangle to operate on within the image array				
 *	
 * Description: Returns the sign digit in the given rectangle (S, I or -).
 * 				Called from getSignDigit()
 *
 * Returns: 	unsigned char
 *-----------------------------------------------------------------------------*/

unsigned char identifySignDigit(unsigned char ucImgArr[][MAX_HEIGHT], Rect stRectR)
{
	unsigned char ucHSegPresent[3];
	unsigned char ucInd;
	unsigned char ucSign;
	Segment stSegHSeg[3];
	Rect stRectR1;
	Rect stRectR2;
	Rect stRectR3;
/*---------- DETECT HORIZONTAL SEGMENTS ----------*/
	stRectR1.P1 = stRectR.P1;
 	stRectR1.P2.x = stRectR.P2.x;
	stRectR1.P2.y = stRectR.P1.y + stRectR.height / 3;
  	calcHeightWidth(&stRectR1);

	stRectR2.P1.x = stRectR.P1.x;
	stRectR2.P1.y = stRectR.P1.y + stRectR.height / 3;
	stRectR2.P2.x = stRectR.P2.x;
	stRectR2.P2.y = stRectR.P1.y + 2 * stRectR.height / 3;
	calcHeightWidth(&stRectR2);

	stRectR3.P1.x = stRectR.P1.x;
	stRectR3.P1.y = stRectR.P1.y + 2 * stRectR.height / 3;
	stRectR3.P2 = stRectR.P2;
	calcHeightWidth(&stRectR3);
	
	stSegHSeg[0] = getSegmentWidth(ucImgArr,stRectR1);
	stSegHSeg[1] = getSegmentWidth(ucImgArr,stRectR2);
	stSegHSeg[2] = getSegmentWidth(ucImgArr,stRectR3);
/*---------------------------------------------*/

/*---------- THRESHOLD THE SEGMENTS ----------*/
	for(ucInd = 0; ucInd < 3; ucInd++)
	{
		if(stSegHSeg[ucInd].length < WIDTH_THRESHOLD_COEFF * stRectR.width)
			ucHSegPresent[ucInd] = 0;
		else
			ucHSegPresent[ucInd] = 1;
	}
	
/*---------------------------------------------*/

	if(ucHSegPresent[1] == 1)
		ucSign = '-';
	else
		ucSign = 'X';
	return ucSign;
}






/*--------------------------------------------------------------------------------------------
 * Function:    getSignDigit
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input image array
 *				Rect stRectBoundaryRect		// Rectangle to operate on within the image array				
 *	
 * Description: Returns the sign digit in the given rectangle (S, I or -). 
 *				Includes pre processing of the rectangle and a call to
 *				identifySignDigit
 *
 * Returns: 	unsigned char
 *-------------------------------------------------------------------------------------------*/

unsigned char getSignDigit(unsigned char ucImgArr[][MAX_HEIGHT], Rect stRectBoundaryRect)
{
	unsigned char ucSignDigit = 0;
	unsigned char ucSegmentOnThreshold;
	Rect stRectR;
	Rect stRectTemp;
	
/*----------------------FILTERING OPERATIONS ---------------------------------------------------*/	
	
	ucSegmentOnThreshold = calcThreshold(ucImgArr,stRectBoundaryRect); //Calculate the threshold 
	threshold(ucImgArr,ucImgArr, stRectBoundaryRect, ucSegmentOnThreshold,  WHITE,  BLACK);
	applyFilterMedian(ucImgArr,stRectBoundaryRect,3,3);
	//applyFilter(ucImgArr,stRectBoundaryRect,fMaskHPF,3,3,1);
	negative(ucImgArr,stRectBoundaryRect);
/*----------------------FIND THE RECTANGLULAR SUBIMAGE WHERE ALL DIGITS MAY BE LOCATED--------------*/	
	stRectR = findRect(ucImgArr,stRectBoundaryRect);
	ucSegmentThickness = findAvgSegmentThickness(ucImgArr,stRectR);
/*---------------------------------------------------------------------------------------------------*/
	
	
/*---------------------------------------------------------------------------------------------*/
	
/*-------------FIND RECTANGLES OF ALL INDIVIDUAL DIGITS IN THE SUBIMAGE---------------------------*/	
	findDigitRects(ucImgArr,stRectR);

	stRectTemp = findRect(ucImgArr,stRectDigitRect[0]);
	stRectDigitRect[0].P1.y = stRectTemp.P1.y;
	stRectDigitRect[0].P2.y = stRectTemp.P2.y;
	calcHeightWidth(&stRectDigitRect[0]);
	//drawRect(ucImgArr,stRectR);
/*-----------------------------------------------------------------------------------------------*/
	//if(ucNoOfDigits == 1)
	ucDigitsArr[0] = identifyDigit(ucImgArr,stRectDigitRect[0]);	//Identify the digit in rectangle
	//drawRect(ucImgArr,stRectDigitRect[0]);
	if(ucDigitsArr[0] == 5 || ucDigitsArr[0] == 1)
	{
		if(ucDigitsArr[0] == 5)
		{
			ucSignDigit = 'S';
		}
		else
		if(ucDigitsArr[0] == 1)
		{
			ucSignDigit = 'I';
		}
	}
	else
	{
		ucDigitsArr[0] = identifySignDigit(ucImgArr,stRectDigitRect[0]);
		if(ucDigitsArr[0] == '-')
		{
			ucDigitsArr[0] = identifySignDigit(ucImgArr,stRectDigitRect[0]);
			if(ucDigitsArr[0] == '-')
			{
				ucSignDigit = '-';
			}
			else 
				ucSignDigit = 'X';
		}
		else 
			ucSignDigit = 'X';
	}
	return ucSignDigit;
}






/*-----------------------------------------------------------------------------
 * Function:    getCorrectRect
 *
 * Arguments:	Rect stRectR	// The input rectangle
 *	
 * Description: Returns a rectangle in the standard form where points P1 and P2 
 *				of the rectangle are top left and bottom right corners respectively.
 *				Used for correcting the rectangle co-ordinates received from the 
 *				Host Application during calibration.
 *
 * Returns: 	Rect // The corrected rectangle
 *-----------------------------------------------------------------------------*/

Rect getCorrectRect(Rect stRectR)
{
	Rect stRectCorrRect;
	
	if(stRectR.P1.x < stRectR.P2.x && stRectR.P1.y < stRectR.P2.y)
	{
		stRectCorrRect = stRectR;
	}
	else
	if(stRectR.P1.x > stRectR.P2.x && stRectR.P1.y > stRectR.P2.y)
	{
		stRectCorrRect.P1 = stRectR.P2;
		stRectCorrRect.P2 = stRectR.P1;
	}
	else
	if(stRectR.P1.x < stRectR.P2.x && stRectR.P1.y > stRectR.P2.y)
	{
		stRectCorrRect.P1.x = stRectR.P1.x;
		stRectCorrRect.P1.y = stRectR.P2.y;
		stRectCorrRect.P2.x = stRectR.P2.x;
		stRectCorrRect.P2.y = stRectR.P1.y;
	}
	else
	if(stRectR.P1.x > stRectR.P2.x && stRectR.P1.y < stRectR.P2.y)
	{
		stRectCorrRect.P1.x = stRectR.P2.x;
		stRectCorrRect.P1.y = stRectR.P1.y;
		stRectCorrRect.P2.x = stRectR.P1.x;
		stRectCorrRect.P2.y = stRectR.P2.y;
	}
	calcHeightWidth(&stRectCorrRect);
	return stRectCorrRect;
}





/*-----------------------------------------------------------------------------
 * Function:    getNumberFromDigits
 *
 * Arguments:	unsigned char *ucDigitsArr	// The input ucDigitsArr array
 *				unsigned char ucDigits	// Number of ucDigitsArr
 *	
 * Description: Returns the number from the individual ucDigitsArr in the array
 *
 * Returns: 	unsigned short int // The number
 *-----------------------------------------------------------------------------*/

unsigned short int getNumberFromDigits(unsigned char *ucDigitsArr, unsigned char ucDigits)
{
	unsigned short int usNumber = 0;
	short int siInd;
	float fMultiplier = 1;
	
	for(siInd = 0; siInd < ucDigits; siInd++)
	{
		usNumber += ucDigitsArr[siInd] * fMultiplier;
		fMultiplier = fMultiplier * 10;
	}
	return usNumber;
}


void setCameraOrientation(unsigned char ucImgArr[][MAX_HEIGHT],float fAngle)
{
	float fAngleRad;
	unsigned int uiTemp;
	int uiImgWidthR;
	int uiImgHeightR;

	fAngleRad = fAngle * PI / 180;

	rotateImg(ucImgArr,MAX_WIDTH,MAX_HEIGHT,-fAngleRad);
	
	uiImgWidthR = (long int) ( uiImgWidth * cos(fAngle) - uiImgHeight * sin(fAngle) );
	uiImgHeightR = (long int) ( uiImgWidth * sin(fAngle) + uiImgHeight * cos(fAngle) );
	
	uiImgWidth = uiImgWidthR;
	uiImgHeight = uiImgHeightR;
}


Rect applyCorrection(unsigned char ucImgArr[][MAX_HEIGHT],Rect stRectR,Rect stRectBoundaryRect)
{
	unsigned char ucDigit = 10; 
	unsigned int ui;
	unsigned int uiMaxDigitWidth = 0;
	Rect stRectCorrectedRect;
	
	stRectCorrectedRect = stRectR;

	if(ucNoOfDigits == 1)
	{
		uiMaxDigitWidth = stRectR.height;
		stRectCorrectedRect.P1.x = stRectCorrectedRect.P2.x - uiMaxDigitWidth;

		if(stRectCorrectedRect.P1.x < stRectBoundaryRect.P1.x)
		{
			stRectCorrectedRect.P1.x = stRectBoundaryRect.P1.x;
		}
		calcHeightWidth(&stRectCorrectedRect);
	}
	else
	{
		for(ui = 0; ui < ucNoOfDigits; ui++)
		{
			if(stRectDigitRect[ui].width > uiMaxDigitWidth)
			{
				uiMaxDigitWidth = stRectDigitRect[ui].width;
			}
		}
		do
		{
			stRectCorrectedRect.P1.x--;
			calcHeightWidth(&stRectCorrectedRect);
			if(stRectCorrectedRect.P1.x <= stRectBoundaryRect.P1.x || stRectCorrectedRect.width > uiMaxDigitWidth)
			{
				stRectCorrectedRect.P1.x++;
				calcHeightWidth(&stRectCorrectedRect);
				break;
			}
			else
			{
				ucDigit = identifyDigit(ucImgArr,stRectCorrectedRect); 
			}
		}while(ucDigit == 10);
	}

	return stRectCorrectedRect;
}