/*=============================================
 * Compare_2matrix.cpp
 *
 *  Created on: Feb 23, 2021
 *      Author: Duc An Nguyen
 * 
 * This function is used for comparing two matrixs.
 * Two inputs are two matrixs that are the same size.
 * When the function finished, it will return the number 
 * of different positions in two matrixs. If return 0, no difference
 * is detected, this means two object is the same. 
 *
 *///==========================================

#include "img_processing.h"
#include "math.h"
#include <stdio.h>


 //======================================================================== COMPARE IMG and another in txt file
uint32 img_pro::compare_2matrix(Matrix &img_ori)
{
	Matrix 	IMG_txt;
	img_pro readtxt;
	uint32  num_diff = 0;
	uint16 	i,j;
//	img_pro *readtxt = new img_pro;
	PATH	path_gray = "img_processing_library/Sample_txt/Gray.txt";

	if (readtxt.read_txtIMG(IMG_txt, path_gray) == _ERROR_)
	{
		printf("Opening image txt was failed \n");
		exit(0);
	}

//	readtxt.Print_matrix(IMG_txt);
	//-------------------------------------------------
	for (i=0;i<ROW;i++)
	{
		for (j=0;j<COL;j++)
		{
			if(img_ori.at(i,j) != IMG_txt.at(i,j))
			{ 
//				printf("The difference at: %d  %d and the value is: %d", i, j, img_ori.at(i, j));
//				printf("The difference at: %d  %d and the value is: %d", i, j, IMG_txt.at(i, j));
				num_diff +=1;
			}
		}
	}
	//-------------------------------------------------
//	delete readtxt;
	printf("The difference is: %ld\n", num_diff);
	return num_diff;
}


//======================================================================== COMPARE IMG and another in txt file
uint32 img_pro::compare_2matrix(Matrix16& img_ori)
{
	Matrix16  IMG_txt;
	img_pro readtxt;
	uint32  num_diff = 0;
	uint16 	i, j;
	//	img_pro *readtxt = new img_pro;
	PATH	path_gray = "img_processing_library/Sample_txt/Gray.txt";

	if (readtxt.read_txtIMG(IMG_txt, path_gray) == _ERROR_)
	{
		printf("Opening image txt was failed \n");
		exit(0);
	}

	//	readtxt.Print_matrix(IMG_txt);
		//-------------------------------------------------
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (img_ori.at(i, j) != IMG_txt.at(i, j))
			{
				//				printf("The difference at: %d  %d and the value is: %d", i, j, img_ori.at(i, j));
				//				printf("The difference at: %d  %d and the value is: %d", i, j, IMG_txt.at(i, j));
				num_diff += 1;
			}
		}
	}
	//-------------------------------------------------
//	delete readtxt;
	printf("The difference is: %ld\n", num_diff);
	return num_diff;
}


//======================================================================== 
uint32 img_pro::compare_2matrix(uint8 img_ori[ROW][COL])
{
	Matrix 	IMG_txt;
	img_pro readtxt;
	uint32  num_diff = 0;
	uint16 	i, j;
	//	img_pro *readtxt = new img_pro;
	PATH	path_gray = "img_processing_library/Sample_txt/Gray.txt";

	if (readtxt.read_txtIMG(IMG_txt, path_gray) == _ERROR_)
	{
		printf("Opening image txt was failed \n");
		exit(0);
	}

	//	readtxt.Print_matrix(IMG_txt);
		//-------------------------------------------------
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (img_ori[i][j] != IMG_txt.at(i, j))
			{
//				printf("The difference at: %d  %d and the value is: %d\n", i, j, img_ori[i][j]);
//				printf("The difference at: %d  %d and the value is: %d\n", i, j, IMG_txt.at(i, j));
				num_diff += 1;
			}
		}
	}
	//-------------------------------------------------
//	delete readtxt;
	printf("The difference is: %ld\n", num_diff);
	return num_diff;
}


//======================================================================== COMPARE 2 arguments IMG
uint32 img_pro::compare_2matrix(uint8 IMG1[ROW][COL], uint8 IMG2[ROW][COL])
{
	uint32  num_diff = 0;
	uint16 	i, j;

	//-------------------------------------------------
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if ((IMG1[i][j] == IMG2[i][j]))
				continue;
			else
			{
				//printf(" row = %d      col = %d   \n",i,j);
				num_diff += 1;
			}
		}
		//		if (check >=100) break;
	}
	printf("difference = %d \n", num_diff);
	//-------------------------------------------------
	return num_diff;
}




