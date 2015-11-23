/*****************************************************************************
 FILE : 		Config.h
 
 DESCRIPTION: 	Contains Configuration Parameters of the SSOCR
 				 
 AUTHOR: 		Ameya Deswandikar
 
 REVSION HISTORY: 
 REV	DATE		BY						REMARKS
 1		13/05/10	Ameya Deswandikar		Original
  
 *****************************************************************************/

#define MAX_MASK_SIZE			20		// Maximum mask size
#define MASK_SIZE				 3

#define MAX_WIDTH				1280	// Maximum width of the image
#define MAX_HEIGHT				1280	// Maximum height of the image

#define BLACK					0				
#define WHITE					255

#define SEGMENT_COLOUR			WHITE	// Colour of the illuminated segment. Select BLACK for using printer paper images

#define VOFFSET					2		// Vertical Offset of the peripheral rectangle of a digit

#define WIDTH_THRESHOLD_COEFF	0.5		// Minimum ratio of (horizontal line / width of rectangle) for positive segment detection
#define HEIGHT_THRESHOLD_COEFF	0.33	// Minimum ratio of (vertical line / height of rectangle) for positive segment detection

#define BRIGHT_COEFF_SEGMENT	1.25	// Brightness cofficient for threseholding of segment of a digit

#define MIN_SEGMENT_RATIO		0.6		// Minimum Aspect Ratio ( = MIN_SEGMENT_RATIO / 2)
#define RECT_WIDTH_MULTIPLIER	1.2		// Width mulitipler to accomodate shear, tilt and other distortions
#define MIN_RECT_WIDTH_COEFF	0.6		// Min Ratio of Digit Rect width / Max Horizontal Segment

#define MAX_VSEG_COEFF			0.5		// Maximum ratio of (vertical line / height of rectangle)
#define VSEG_DEV				0.7		// Maximum deviation of longest vertical segment	
#define HSEG_DEV				0.7		// Maximum deviation of longest horizontal segment

#define MAX_NO_DIGITS			12

#define EROSION					0
#define DILATION				1

#define PI						3.141916
#define SHEAR_ANGLE				5		// Shear angle of a seven segment display in degrees

#define ON						1
#define OFF						0
#define ICON_ON_COEFF			0.05	// Ratio of White pixels / Black Pixels for ON indication
