#include "Coffee_bean.h"
#include "stdio.h"


uint8 write_img2txt(uint8 IMG[ROW][COL],uint8 channel)
{
	uint16 r,c;
	FILE *file;
	
	if (channel == RED_)
		file = fopen("R.txt","w");
	else if (channel == GREEN_)
		file = fopen("G.txt","w");
	else 
		file = fopen("B.txt","w");
	//=====================================
	if (file == (FILE*)NULL)
	{
		printf("get matrix error");
		return ERROR;
	}
	else
	{
		for (r=0;r<ROW;r++)
		{
			for(c=0;c<COL;c++)
			{
				if (IMG[r][c] < 10)
					fprintf(file,"%d    ",IMG[r][c]);
				else if (IMG[r][c] <100)
					fprintf(file,"%d   ",IMG[r][c]);
				else
					fprintf(file,"%d  ",IMG[r][c]);
			}
			fprintf(file,"\n");	
		}
		fclose(file);
		return OK_;
	}	
}
