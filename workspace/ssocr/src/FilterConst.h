/*****************************************************************************
 FILE : 		FilterConst.h
 
 DESCRIPTION: 	Part of SSOCR. Contains frequently used filter coefficients in 
 				image processing.
 				 
 AUTHOR: 		Ameya Deswandikar
 
 REVSION HISTORY: 
 REV	DATE		BY						REMARKS
 1		----		Ameya Deswandikar		Original
  
 *****************************************************************************/

#ifndef FilterConst_H
#define FilterConst_H

/*--------- DIGIT PATTERN FOR SEVEN SEGMENTS ---------*/
/* 1 = Segment Present 	*/
/* 0 = Segment Absent	*/
/* Order in clockwise direction	*/

static unsigned char ucDigitSegPattern[][7] = { 1, 1, 1, 1, 1, 1, 0,	// 0	
												0, 1, 1, 0, 0, 0, 0,	// 1	   
												1, 1, 0, 1, 1, 0, 1,	// 2	    
												1, 1, 1, 1, 0, 0, 1,	// 3	
												0, 1, 1, 0, 0, 1, 1,	// 4
												1, 0, 1, 1, 0, 1, 1,	// 5
												1, 0, 1, 1, 1, 1, 1,	// 6
												1, 1, 1, 0, 0, 0, 0,	// 7
												1, 1, 1, 1, 1, 1, 1,	// 8				
												1, 1, 1, 1, 0, 1, 1};	// 9

/*----------------------------------------------------*/



/*--------- EDGE DETECTION FILTERS ---------*/

static float fMaskSobelH [][3] = {	 1, 2, 1,
									 0,	 0,	 0,			// Sobel Operator Horizontal
									-1, -2, -1	};


static float fMaskSobelV[][3] = {	1, 0, -1,
									2, 0, -2,			// Sobel Operator Vertical
									1, 0, -1	};


static float fMaskPrewittH[][3] = {	-1,	-1,	-1,
									0,	0,	0,			// Prewitt Operator Horizontal
									1,	1,	1	};


static float fMaskPrewittV[][3] = {-1,	0,	1,
									-1,	0,	1,			// Prewitt Operator Vertical
									-1,	0,	1	};

/*------------------------------------------*/


/*--------- SPATIAL FILTERS ---------*/

static float fMaskHPF[][3] = {	-1, -1, -1,
								-1,	 8, -1,				// High Pass Filter
								-1, -1, -1	};

static float fMaskHPF2[][3] = { 0 -1, 0,
								-1,	 4, -1,				// High Pass Filter (Laplacian)
								0, -1, 0	};

static float fMaskMean[][3] = {	1,	1,	1,
								1,	1,	1,				// Mean Filter (Averaging)
								1,	1,	1};

static float fMaskUnit[][3] = {	0,	0,	0,
								0,	1,	0,
								0,	0,	0}	;
 
static float fMaskMorphH[][3] = {	1,	1,	1,		
									1,	1,	1,	
									1,	1,	1};

/*------------------------------------------*/



/*--------- MORPHOLOGICAL FILTERS ---------*/

static float fMaskMorphH2[][3] = {	1,	1,	1,		
									0,	0,	0,	
									0,	0,	0};

static float fMaskMorphV[][3] = {	1,	1,	0,
									1,	1,	0,
									1,	1,	0};

static float fMaskMorphV1[][3] = {	1,	1,	1,
									1,	1,	1,
									1,	1,	1};


static float fMaskMorphV2[][3] = {	1,	0,	0,
									1,	0,	0,
									1,	0,	0};

/*------------------------------------------*/
#endif