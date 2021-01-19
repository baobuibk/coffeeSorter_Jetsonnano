/*
 * check_color.c
 *`
 *  Created on: Sep 11, 2019
 *      Author: ducan
 */
#include "Coffee_bean.h"
#include "math.h"
/*
dbfl L[ROW][COL];
dbfl a[ROW][COL];
dbfl b[ROW][COL];
*/

uint8 check_color(dbfl  img_check[ROW][COL],
		  dbfl 	L[ROW][COL],
		  dbfl 	a[ROW][COL],
		  dbfl 	b[ROW][COL]
                 )
{
	uint8 	result_color;
	uint16 	i,j;
	dbfl 	sum_L = 0, Avr_L;
	dbfl 	sum_b = 0, Avr_b;
    	dbfl 	sum_Chroma = 0, Avr_Chroma;
    	uint32 	total_px = 0;
	dbfl Chroma[ROW][COL];


//    Test_matrix(img1_sgm,1);
 //   	rgb2lab(img1_sgm,img2_sgm,img3_sgm,L,a,b);
//    Test_matrix(L,3);
//    if (check_i == 2)
//    Test_matrix_sub_dbfl(L);
    //==============================================
//    Test_matrix_sub_dbfl(L);
//    Test_matrix_sub(img_check);
 //   **pstart = clock();
	for (i=0;i<ROW;i++)
	{
		for(j=0;j<COL;j++)
		{
			if (img_check[i][j] == 1)
			{
				Chroma[i][j] = fastPow(a[i][j]*a[i][j] + b[i][j]*b[i][j],0.5 );
				total_px 	+= 1;
				sum_L	 	+= L[i][j];
				sum_b    	+= b[i][j];
				sum_Chroma 	+= Chroma[i][j];
			}
		}
	}


 //   **pendtime = clock();
	//==============================================

	Avr_L 		= sum_L/total_px;
	Avr_b 		= sum_b/total_px;
	Avr_Chroma 	= sum_Chroma/total_px;

	if ((Avr_L >= L_THR) || ((Avr_b >= b_THR) && (Avr_Chroma >= Chroma_THR)))
		result_color = GOOD;
	else
		result_color = BAD;

	return result_color;

//	return 1;
	//==============================================
}
