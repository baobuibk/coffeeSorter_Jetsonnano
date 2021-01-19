#include <stdio.h>
#include "Coffee_bean.h"

#define INTEGER  		1
#define FLOAT    		2
#define NEGATIVE_FLOAT 	3

void 	Test_matrix(uint8 IMG[ROW][COL],
					uint8 type)			// 1: integer, 2: float 3: negetive float value
{
	uint16 i, j;

	//================================================================//
	if (type == INTEGER){
	for (j=1;j<=COL;j++)
	{
//			if (j<10) 			printf("%d        ",j);         // double float
//			else if (j<100)		printf("%d       ",j);
//			else                printf("%d      ",j);

			if (j<10) 			printf("%d   ",j);                // integer
			else if (j<100)		printf("%d  ",j);
			else                printf("%d ",j);

	}
	printf("\n");
	//================================================================//

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			//--------------------------------------------------------//
				if (IMG[i][j] < 10)			    printf("%d   ", (uint8)IMG[i][j]);
				else if (IMG[i][j] < 100)		printf("%d  ", (uint8)IMG[i][j]);
				else							printf("%d ", (uint8)IMG[i][j]);
//				if (IMG[i][j] < 10)			    printf("%.4f   ", IMG[i][j]);
//				else if (IMG[i][j] < 100)		printf("%.4f  ", IMG[i][j]);
//				else							printf("%.4f ", IMG[i][j]);

			//--------------------------------------------------------//
		}
		printf (" // hang %d\n",i+1);
	}
	}
	else if (type ==FLOAT)
	{
		for (j=1;j<=COL;j++)
		{
				if (j<10) 			printf("%d        ",j);         // double float
				else if (j<100)		printf("%d       ",j);
				else                printf("%d      ",j);


		}
		printf("\n");
		//================================================================//

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
			printf (" // hang %d\n",i+1);
		}
	}
	else if (type == NEGATIVE_FLOAT)
	{
		for (j=1;j<=COL;j++)
		{
				if (j<10) 			printf("%d         ",j);         // double float
				else if (j<100)		printf("%d        ",j);
				else                printf("%d       ",j);


		}
		//================================================================//

		printf("\n");
		for (i=0;i<ROW;i++)
		{
			for (j=0;j<COL;j++)
			{
				//--------------------------------------------------------//
					if ((IMG[i][j] < 0) && (IMG[i][j] > -10))			printf("%.4f   ", (dbfl)IMG[i][j]);
					else if ((IMG[i][j] < 0) && (IMG[i][j] > -100))		printf("%.4f  ", (dbfl)IMG[i][j]);
					else if ((IMG[i][j] < 0) && (IMG[i][j] > -1000))	printf("%.4f ", (dbfl)IMG[i][j]);
					else if ((IMG[i][j] < 10)&&(IMG[i][j] >= 0))		printf("%.4f    ", (dbfl)IMG[i][j]);
					else if ((IMG[i][j] < 100)&&(IMG[i][j] >= 0))		printf("%.4f   ", (dbfl)IMG[i][j]);
					else												printf("%.4f  ", (dbfl)IMG[i][j]);

				//--------------------------------------------------------//
			}
			printf (" // hang %d\n",i+1);
		}
	}
	else printf("PLease enter type what want to print!!!");
}


