/*****************************************************************************
 FILE : 		BMPHeader.h
 
 DESCRIPTION: 	BMP Header for 8 bit grayscale images and some commonly 
 				used structures in image processing.
 				 
 AUTHOR: 		Ameya Deswandikar
 
 REVSION HISTORY: 
 REV	DATE		BY						REMARKS
 1		13/05/10	Ameya Deswandikar		Original
  
 *****************************************************************************/

#ifndef BMPHeader_H
#define BMPHeader_H

#include <stdio.h>

/*----------THE BMP HEADER(FIRST TWO BYTES) ----------*/
typedef struct bmp_magic
{
	char type[2];
}BMPMagic;

/*----------THE BMP HEADER ----------*/
typedef struct bmp_header 
{
	//unsigned char magic[2];
	long int size;
	short int tp1,tp2;
	long int data_offset;
	long int no_bytes_in_header_from_here;
	long int width,height;
	short int no_colour_planes;
	short int bits_per_pixel;
	long int compression;
	long int size_of_raw_BMP_after_header;
	long int hrzntl_resltn,vrtcl_resltn;
	long int no_of_colors_in_pallete,no_of_important_colors;
	unsigned char pallete[4*256];
}BMPHeader;
/*-----------------------------------*/


/*-------- THE RGB PIXEL --------*/
typedef struct RGBpixel_data
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
}RGBpixelData;
/*-------------------------------*/

/*-------- THE IMAGE --------*/
typedef struct Img
{
	BMPHeader header;
	char * fname;
	FILE* fptr;
}Image;
/*-------------------------------*/

/*-------- THE POINT --------*/
typedef struct point
{
	long int x;
	long int y;
}Point;
/*---------------------------*/

/*-------- THE LINE SEGMENT --------*/
typedef struct segment
{
	Point P1;
	Point P2;
	long int length;
}Segment;
/*----------------------------------*/

/*-------- THE RECTANGLE --------*/
typedef struct rect
{
	Point P1;
	Point P2;
	long int height,width;
}Rect;
/*-------------------------------*/

void saveArrToBMP(unsigned char ucArr[][MAX_HEIGHT],Image*);

void fillArray2(Image *spImageImg,unsigned char ucImgArr[][MAX_HEIGHT]);

void InitBMPHeader(BMPHeader *bmpHead,int width,int height);
#endif