/*
 * Test_matrix_sub_dbfl.c
 *
 *  Created on: Sep 16, 2019
 *      Author: ducan
 */
#include "Coffee_bean.h"


dbfl 	IMG_txt[ROW][COL];
uint32  Test_matrix_sub_dbfl(dbfl IMG[ROW][COL])
{

	int32  		check = 0;
	uint16 		i,j;
//	int32       check_IMG,check_IMGtxt;

	read_IMG_Gray_dbfl(IMG_txt);
/*
	for (i=0;i<ROW;i++)
	{
		for (j=0;j<COL;j++)
		{
			IMG[i][j] -= IMG_txt[i][j];
		}
	}
*/
//	Test_matrix(IMG,3);
	//=================================================
	for (i=0;i<ROW;i++)
	{
		for (j=0;j<COL;j++)
		{
//			check_IMG 		= round_float(IMG[i][j],4);
//			check_IMGtxt 	= round_float(IMG_txt[i][j],4);
			double a = IMG[i][j] - IMG_txt[i][j];
			a = (a<0)?-a:a;
			if( a <= 0.0001)
				continue;
			else
				check+=1;
		}
	}

	//=================================================
	return check;




}
