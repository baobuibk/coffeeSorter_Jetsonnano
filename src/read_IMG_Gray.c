/*
 * read_IMG_Gray.c
 *
 *  Created on: Aug 30, 2019
 *      Author: ducan
 */

#include "Coffee_bean.h"
#include "stdio.h"



uint8 read_IMG_Gray(uint8 IMG[ROW][COL])
{
	uint16 	i, j;
	dbfl 	value;

		FILE *file1;
		file1 = fopen("Gray.txt", "r");

		//==================================//

		if (file1 == (FILE*)NULL)
		{
			printf("matrix gray error!");
			return ERROR;
		}
		else
		{
			for (i = 0; i < ROW; i++)
			{
				for (j = 0; j < COL; j++)
				{
					//--------------------------//
					fscanf(file1, "%f", &value);
					IMG[i][j] = (uint8)value;

					//--------------------------//
				}
			}
			return OK_;
		}
		//==================================//
		fclose(file1);

}
