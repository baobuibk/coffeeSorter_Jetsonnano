#include "Coffee_bean.h"

void invert_image(uint8 IMG[ROW][COL])
{
	uint16 i, j;
	//==================================
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			IMG[i][j] = 1 - IMG[i][j];
		}
	}
	//==================================

}
