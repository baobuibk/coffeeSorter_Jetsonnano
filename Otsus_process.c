#include "Coffee_bean.h"

uint8 Otsu_process(uint8 IMG[ROW][COL])
{

    dbfl   density[256];
    dbfl   P1, P2, M1, M2,MG,tem;
    dbfl   variance=0;
    uint16 i, j, ii, jj, K,TH = 0;


	//------------------------------------------------------------------------//
	for (i = 0; i <= 255; i++)
	{
		density[i] = 0;     //initialize for matrix den
	}
	//------------------------------------------------------------------------//calculate density of image
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			density[IMG[i][j]] += 1;
		}
	}

	//-------------------------------------------------------------------------//
	for (i = 0; i <= 255; i++)
	{
		density[i] /= (ROW * COL);
	}
	//-------------------------------------------------------------------------//P1 and P2
//		for (i = 0; i < 256; i++)
//		{
//			printf("%.8lf hang %d \n", den[i],i);
//		}
	for (K = 0; K <= 255; K++)                         // 255 muc xam
	{
		P1 = 0;
		P2 = 0;
		M1 = 0;
		M2 = 0;
		for (i = 0; i <= K; i++)
		{
		      P1 += density[i];
		}
		//--------------------------------//
		P2 = 1 - P1;
		if (P1 == 0) continue;
		else
		{
			//printf("%f  %f", P1, P2);
			//--------------------------------//     M1 and M2
			for (ii = 0; ii <= K; ii++)
			{
				M1 += (ii*density[ii] / P1);
			}
			for (jj = (K + 1); jj <= 255; jj++)
			{
				M2 += (jj*density[jj] / P2);
			}
			//--------------------------------//
			MG = M1*P1 + M2 *P2;
			//printf("%f ", MG);
			tem = P1*(M1 - MG)*(M1 - MG) + P2*(M2 - MG)*(M2 - MG);
			if (tem > variance)
			{
				variance = tem;
				TH = K;
			}
		}
	}
//	printf("%d   %lf", TH,variance);
	return TH;

}
