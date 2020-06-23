/*==============================================
This funtion eliminates residual pixels at angle
pixels

//=============================================*/
#include "Coffee_bean.h"


void 	Thin_step2_cd2(uint8 IMG[ROW][COL])
{
	uint16 	i, j;
	uint8	k;
    int8 	ii, jj;
	uint8 	M[ROW][COL];
	uint8 	xnei[8], ynei[8];
	uint8 	checkI, checknei, count1, count2;


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
			if (IMG[i][j] == 0) continue;
			else
			{
				//==========================
				for (ii = -1; ii <= 1; ii++)
				{
					for (jj = -1; jj <= 1; jj++)
					{
						if ((IMG[i + ii][j + jj] == 1) && ((ii != 0) || (jj != 0)))
						{
							xnei[checkI] = i + ii;
							ynei[checkI] = j + jj;
							checkI++;
						}
					}
				}
				//==========================
				if (checkI == 3)
				{
					for (k = 0; k < 3; k++)
					{
						checknei = 0;
						//==========================
						for (ii = -1; ii <= 1; ii++)
						{
							for (jj = -1; jj <= 1; jj++)
							{
								if ((IMG[xnei[k] + ii][ynei[k] + jj] == 1) && ((ii != 0) || (jj != 0)))
									checknei++;
							}
						}
						//==========================
						if (checknei == 3) count1++;
						else if (checknei == 4) count2++;
					}
					if (count1 == 2 && count2 == 1) M[i][j] = 0;
				}
				//==========================
			}
		}
	}
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			IMG[i][j] *= M[i][j];
		}
	}
	//==========================================================================
}
