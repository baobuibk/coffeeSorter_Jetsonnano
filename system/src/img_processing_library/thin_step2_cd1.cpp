/*
 * Thin_step2_cd1.c
 *
 *  Created on: Aug 29, 2019
 *      Author: ducan
 */

#include "img_processing.h"

//uint8 	M[ROW][COL];
void img_pro::thin_step2_cd1(Matrix &img)
{

	uint16 	i, j;
	uint8 	P, P2, P3, P4, P5, P6,P8;  //P1, P7
	uint8   condition2;
	
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
			{
				M[i][j] = 1;
			}
		}
		//=======================================================================================// Calculate condition 1
		for (i = 1; i < ROW - 1; i++)
		{
			for (j = 1; j < COL - 1; j++)
			{
				P = img.at(i,j);
				if (P == 0)   continue;
				else
				{
				/*	P1 = IMG[i - 1][j - 1];*/		P2 = img.at(i - 1,j    );   P3 = img.at(i - 1,j + 1);
					P4 = img.at(i    ,j + 1);	  	P5 = img.at(i + 1,j + 1);   P6 = img.at(i + 1,j    );
				/*	P7 = IMG[i + 1][j - 1];*/		P8 = img.at(i    ,j - 1);
					//--------------------------------------------------------------------------//

				//	condition1 = P1 + P2 + P3 + P4 + P5 + P6 + P7 + P8;
					condition2 = (~P4) & P8 & ((P2 & (~P5) & (~P6)) | ((~P2) & (~P3) & P6));
					if (condition2 == 1)  M[i][j] = 0;

				}
			}
		}
		//=======================================================================================//

		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
			{
				img.set(i,j) *= M[i][j];
			}
		}


}
