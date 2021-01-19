/*=============================================
 * Test_matrix_sub.c
 *
 *  Created on: Aug 30, 2019
 *      Author: ducan
 *///==========================================

#include "Coffee_bean.h"
#include "math.h"
#include <stdio.h>
uint32 Test_matrix_sub(uint8 IMG[ROW][COL])
{
	uint8 	IMG_txt[ROW][COL];
	uint32  check = 0;
	uint16 	i,j;
	read_IMG_Gray(IMG_txt);
	printf("Failed coordinate: \n");
	//=================================================
	for (i=0;i<ROW;i++)
	{
		for (j=0;j<COL;j++)
		{
			if( (IMG[i][j] == IMG_txt[i][j]) )
				continue;
			else
			{
				//printf(" row = %d      col = %d   \n",i,j);
				check+=1;
			}
		}
		if (check >=100) break;
	}
	printf("difference = %d \n",check);
	//=================================================
	return check;
}



