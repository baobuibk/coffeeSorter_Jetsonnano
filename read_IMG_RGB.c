#include "Coffee_bean.h"
#include "stdio.h"
//#include <QTextStream>

uint8 read_IMG_RGB(uint8 IMG_1[ROW][COL],
                   uint8 IMG_2[ROW][COL],
                   uint8 IMG_3[ROW][COL]
                   )
{
	uint16 i, j;
	dbfl value1,value2,value3;
//	dbfl IMG_1get[ROW][COL];
//	dbfl IMG_2get[ROW][COL];
//	dbfl IMG_3get[ROW][COL];

 //   qDebug( "the integer is: %d", 12345 );
//    printf("An dep zai ahihi!");
	FILE *file1, *file2, *file3;

        file1 = fopen("RGB_Red1.txt", "r");
        file2 = fopen("RGB_Green1.txt", "r");
        file3 = fopen("RGB_Blue1.txt", "r");


//	file2 = fopen("D:\\2.txt", "r");
//	file3 = fopen("D:\\3.txt", "r");

	//==================================//

	if (file1 == (FILE*)NULL)
	{
		printf("matrix 1 error!");
		return ERROR;
	}
	else if (file2 == (FILE*)NULL)
	{
		printf("matrix 2 error!");
		return ERROR;
	}
	else if (file3 == (FILE*)NULL)
	{
		printf("matrix 1 error!");
		return ERROR;
	}
	else
	{
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
			{
				//--------------------------//
				fscanf(file1, "%f", &value1);
				IMG_1[i][j] = (uint8)value1;

				fscanf(file2, "%f", &value2);
				IMG_2[i][j] = (uint8)value2;

				fscanf(file3, "%f", &value3);
				IMG_3[i][j] = (uint8)value3;

				//--------------------------//

			}
		}
		return OK_;
	}
	//==================================//
}
