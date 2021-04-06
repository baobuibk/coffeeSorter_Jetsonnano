#include <stdio.h>
#include "img_processing.h"



//================================================================ PRINT TYPE OF INTEGER
void img_pro::print_matrix(uint8 IMG[ROW][COL])			// 1: integer, 2: float 3: negetive float value
{
	uint16 i, j;
	uint16 jj;

	for (i = 0; i < ROW; i++)
	{
		//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
		for (jj = 1; jj <= 40; jj++)
		{
			if (jj < 10) 			printf("%d   ", jj);                // integer
			else if (jj < 100)		printf("%d  ", jj);
			else					printf("%d ", jj);
		}
		printf("\n");
		//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

		for (j = 0; j < COL; j++)
		{
			//--------------------------------------------------------//
			if (IMG[i][j] < 10)			    printf("%d   ", (uint8)IMG[i][j]);
			else if (IMG[i][j] < 100)		printf("%d  ", (uint8)IMG[i][j]);
			else							printf("%d ", (uint8)IMG[i][j]);

			//--------------------------------------------------------//
		}
		printf(" // hang %d\n", i + 1);
	}
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

}

//================================================================ PRINT TYPE OF MATRIX
void img_pro::print_matrix(Matrix &img)			// object_img_pro.Print_matrix(object_matrix)
{
	uint16 num_row, num_col;
	uint16 num_col_div;
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

	for (num_row = 0; num_row < ROW; num_row++)
	{
		//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
		for (num_col_div = 1; num_col_div <= 40; num_col_div++)
		{
			if (num_col_div < 10) 			printf("%d   ", num_col_div);                // integer
			else if (num_col_div < 100)		printf("%d  ", num_col_div);
			else							printf("%d ", num_col_div);
		}
		printf("\n");

		//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
		for (num_col = 0; num_col < COL; num_col++)
		{
			//--------------------------------------------------------//
			if (img.at(num_row, num_col) < 10)			    printf("%d   ", (uint8)img.at(num_row, num_col));
			else if (img.at(num_row, num_col) < 100)		printf("%d  ",  (uint8)img.at(num_row, num_col));
			else								printf("%d ",   (uint8)img.at(num_row, num_col));

			if ((num_col +1) % 40 == 0) printf("      ...%d\n", (uint8)((num_col + 1) / 40));
			//--------------------------------------------------------//
		}
		printf(" // hang %d\n", num_row + 1);
		printf("\n");

	}
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

}


//================================================================ PRINT TYPE OF DOUBLE FLOAT
void img_pro::print_matrix(dbfl IMG[ROW][COL])
{
	uint16 i, j;

	for (j = 1; j <= COL; j++)
	{
		if (j < 10) 			printf("%d         ", j);         // double float
		else if (j < 100)		printf("%d        ", j);
		else                printf("%d       ", j);
	}
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

	printf("\n");
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			//--------------------------------------------------------//
			if ((IMG[i][j] < 0) && (IMG[i][j] > -10))			printf("%.4f   ", (dbfl)IMG[i][j]);
			else if ((IMG[i][j] < 0) && (IMG[i][j] > -100))		printf("%.4f  ", (dbfl)IMG[i][j]);
			else if ((IMG[i][j] < 0) && (IMG[i][j] > -1000))	printf("%.4f ", (dbfl)IMG[i][j]);
			else if ((IMG[i][j] < 10) && (IMG[i][j] >= 0))		printf("%.4f    ", (dbfl)IMG[i][j]);
			else if ((IMG[i][j] < 100) && (IMG[i][j] >= 0))		printf("%.4f   ", (dbfl)IMG[i][j]);
			else												printf("%.4f  ", (dbfl)IMG[i][j]);

			//--------------------------------------------------------//
		}
		printf(" // hang %d\n", i + 1);
	}
}
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
	/*
	for (j=1;j<=COL;j++)
	{
		if (j<10) 			printf("%d        ",j);         // double float
		else if (j<100)		printf("%d       ",j);
		else                printf("%d      ",j);
	}
		printf("\n");
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			//--------------------------------------------------------//
			if (IMG[i][j] < 10)			    printf("%.4f   ", (dbfl)IMG[i][j]);
			else if (IMG[i][j] < 100)		printf("%.4f  ", (dbfl)IMG[i][j]);
			else							printf("%.4f ", (dbfl)IMG[i][j]);
			//--------------------------------------------------------//
		}
		printf(" // hang %d\n", i + 1);
		}
	}
	*/
		
