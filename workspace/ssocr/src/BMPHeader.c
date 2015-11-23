/*****************************************************************************
 FILE : 		BMPHeader.c
 
 DESCRIPTION: 	BMP Header for 8 bit grayscale images and some commonly 
 				used structures in image processing.
 				 
 AUTHOR: 		Ameya Deswandikar
 
 REVSION HISTORY: 
 REV	DATE		BY						REMARKS
 1		13/05/10	Ameya Deswandikar		Original
  
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "Config.h"
#include "BMPHeader.h"




/*-----------------------------------------------------------------------------
 * Function:    saveArrToBMP
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Input Image Array
 * 				Image* spImg		// Image Structure Pointer
 *	
 * Description: Saves an image array (raw pixel data) in to a BMP File
 *
 * Returns: 	Nothing      
 *-----------------------------------------------------------------------------*/
void saveArrToBMP(unsigned char ucArr[][MAX_HEIGHT],Image* spImg)
{
	unsigned char ch = 0;
	long int li;
	long int lj;
	long int lk;
	long int ll;
	
	lk = spImg->header.width % 4;
	lk = 4 - lk;
	fseek(spImg->fptr,spImg->header.data_offset,SEEK_SET);
	
	for(li = spImg->header.height-1; li >= 0; li--)
	{
		for(lj = 0; lj < spImg->header.width; lj++)
		{
			fwrite(&ucArr[lj][li],sizeof(unsigned char),1,spImg->fptr);
		}
		if(lk != 4)
		{
			for(ll = 0; ll < lk; ll++)
			{
				fwrite(&ch,sizeof(unsigned char),1,spImg->fptr);
			}
		}
	}
}





/*-----------------------------------------------------------------------------
 * Function:    fillArray2
 *
 * Arguments:	unsigned char ucImgArr[][MAX_HEIGHT]		// Output Image Array
 * 				Image *spImageImg 		// Image Structure Pointer
 *								
 * Description: Fills the array from a BMP file whose details are in spImageImg
 * 				(does not use normalized correlation)
 *
 * Returns: 	Nothing	
 *-----------------------------------------------------------------------------*/
void fillArray2(Image *spImageImg,unsigned char ucImgArr[][MAX_HEIGHT])
{
	unsigned char ucTempBuff;
	long int li;
	long int lj;
	long int lk;
	long int ll;
	
	fseek(spImageImg->fptr,spImageImg->header.data_offset,SEEK_SET);
	lk = spImageImg->header.width % 4;
	if(lk != 0)
	{
		lk = 4 - lk;
	}
	
	for(li = spImageImg->header.height - 1; li >= 0; li--)
	{
		for(lj = 0; lj < spImageImg->header.width; lj++)
		{
			fread(&ucTempBuff,sizeof(unsigned char),1,spImageImg->fptr);
			ucImgArr[lj][li] = ucTempBuff;
		}
		for(ll = 0; ll < lk; ll++)
		{
			fread(&ucTempBuff,sizeof(unsigned char),1,spImageImg->fptr);
		}
	}
}



void InitBMPHeader(BMPHeader *bmpHead,int width,int height)
{
	int data_offset = 1078,i,j=0;
	
	//bmpHead->magic[0] = 'B';						/* The BMP Magic Number */
	//bmpHead->magic[1] = 'M';
	bmpHead->size = height * width + data_offset;
	bmpHead->tp1 = 0;
	bmpHead->tp2 = 0;
	bmpHead->data_offset = data_offset;
	bmpHead->no_bytes_in_header_from_here = 40;
	bmpHead->width = width;
	bmpHead->height = height;
	bmpHead->no_colour_planes = 1;
	bmpHead->bits_per_pixel = 8;
	bmpHead->compression = 0;
	bmpHead->size_of_raw_BMP_after_header = 0;
	bmpHead->hrzntl_resltn = 3780;				/* Resolution in pixels per meter */
	bmpHead->vrtcl_resltn = 3780;
	bmpHead->no_of_colors_in_pallete = 256;
	bmpHead->no_of_important_colors = 256;
	 
	for(i = 0; i <= 4*256 - 1; i += 4,j++)			/* Generate the palette */
	{
		bmpHead->pallete[i] = j;
		bmpHead->pallete[i + 1] = j; 
		bmpHead->pallete[i + 2] = j;
		bmpHead->pallete[i + 3] = 0xFF;
	}
}
