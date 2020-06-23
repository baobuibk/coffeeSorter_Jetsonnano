#include "Coffee_bean.h"
#include <stdio.h>

void    Test_kernel(double IMG[ROW_KERNEL][COL_KERNEL])
{
	uint16 i,j;

	for (i=0;i<ROW_KERNEL;i++)
	{
		for (j=0;j<COL_KERNEL;j++)
		{
			printf("%.2lf   ",IMG[i][j]);
//			fflush(stdout);
		}
		printf(" \n");
	}

}
