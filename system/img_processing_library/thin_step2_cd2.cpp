/*=================================================
*	This funtion eliminates residual pixels at angle
*	pixels that aims to get one one pixel width at angle
*	A pixel is removed if it has three neighbors 
*	in which two of out these three have three 
*	neighbors, the rested one has 4 neighbors
*
*=================================================*/
#include "img_processing.h"

//uint8 	M[ROW][COL];
void 	img_pro::thin_step2_cd2(Matrix &img)
{
	uint16 	i, j;
	uint8	k;
    int8 	ii, jj;
	
	uint16 	xnei[8], ynei[8];               // if using V1.0, please notice to adjust type of xnei.
	uint8 	checkI, checknei, count1, count2;

//	Compare_2matrix(img);
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			M[i][j] = 1;
		}
	}
	
	//=======================================================================================//
	for (i = 1; i < ROW - 1; i++)
	{
		for (j = 1; j < COL - 1; j++)
		{
			checkI = 0;
			count1 = 0;
			count2 = 0;
			if (img.at(i,j) == BLACK) continue;
			else
			{
				//==========================  Get the whole coordinate of neighbors white pixels
				for (ii = -1; ii <= 1; ii++)
				{
					for (jj = -1; jj <= 1; jj++)
					{
						if ((img.at(i + ii,j + jj) == WHITE) && ((ii != 0) || (jj != 0)))
						{
							xnei[checkI] = i + ii;
							ynei[checkI] = j + jj;
							checkI++;
						}
					}
				}
				//========================== Checking the neighboor of three above neighbor
				if (checkI == 3)
				{
					if (i == 400 && j == 80)
						uint8 a = 0;
					for (k = 0; k < 3; k++)
					{
						checknei = 0;
						//==========================
						for (ii = -1; ii <= 1; ii++)
						{
							for (jj = -1; jj <= 1; jj++)
							{
								if ((img.at(xnei[k] + ii,ynei[k] + jj) == WHITE) && ((ii != 0) || (jj != 0)))
									checknei++;
							}
						}
						//==========================
						if (checknei == 3) count1++;                
						else if (checknei == 4) count2++;
						else continue;
					}
					if ((count1 == 2) && (count2 == 1)) M[i][j] = 0;
				}
				//==========================
			}
		}
	}
	//==========================
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			img.set(i,j) *= M[i][j];
		}
	}
	//==========================================================================
}
