/*
 * explore_single_img.c
 *
 *  Created on: Sep 9, 2019
 *      Author: ducan
 */
#include "Coffee_bean.h"
void explore_single_img(uint16  posi_single[ROW_POSI_SINGLE][2],
			uint8 	IMG_1[ROW][COL],
			uint8 	IMG_2[ROW][COL],
			uint8 	IMG_3[ROW][COL],
//			dbfl   img1_sgm[ROW][COL],			// use for determining color
//			dbfl   img2_sgm[ROW][COL],
//			dbfl   img3_sgm[ROW][COL],
			uint8   img_check[ROW][COL],		// use for checking color
			int16 	pnt_st,
                        int16	pnt_end,
			dbfl    L[ROW][COL],
			dbfl 	a[ROW][COL],
			dbfl 	b[ROW][COL]
//						uint16  check_ii
                        )
{
//===================================================
	uint16 	min_row=2000,min_col=2000,max_row=0,max_col=0;
	uint16 	i;
	uint16  ii,jj;
	uint16 	sum_lbcur	  = 0;	    // sum of current label
	uint16 	sum_lbnxt;				// sum of next label
	uint8	num_obj;
    	uint8  	obj,sa_obj=0;             // object and satified object

	for (ii=0;ii<ROW;ii++)
		for(jj=0;jj<COL;jj++)
			img_check[ii][jj] = BLACK;
//	Test_matrix(IMG_1,1);
//========================================================
	for (i=pnt_st;i<=pnt_end;i++)
	{
		if (posi_single[i][0] < min_row) min_row = posi_single[i][0];
		if (posi_single[i][1] < min_col) min_col = posi_single[i][1];
		if (posi_single[i][0] > max_row) max_row = posi_single[i][0];
		if (posi_single[i][1] > max_col) max_col = posi_single[i][1];
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-
	for (ii=min_row;ii<=max_row;ii++)
		for(jj=min_col;jj<=max_col;jj++)
			img_check[ii][jj] = IMG_1[ii][jj];

//	Test_matrix(img_check,1);
	num_obj = Cc_label(img_check);
//	Test_matrix(img_check,1);

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-	EXPLORE OBJECT
	for(obj=1;obj<=num_obj;obj++)
	{
		sum_lbnxt  = 0;
		//----------------------------
		for (ii=0;ii<ROW;ii++)
		{
			for(jj=0;jj<COL;jj++)
			{
				if (img_check[ii][jj] == obj)	sum_lbnxt +=1;
			}
		}
		//----------------------------explore max object
		if (sum_lbnxt > sum_lbcur)
		{
			sum_lbcur = sum_lbnxt;
			sa_obj    = obj;
		}
		//----------------------------
	}
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=- FOUND OBJECT
	for(ii=0;ii<ROW;ii++)
	{
		for (jj=0;jj<COL;jj++)
		{
			if (img_check[ii][jj] == sa_obj)
				img_check[ii][jj] = 1;
			else
				img_check[ii][jj] = 0;

			//----------------------------
		//	img1_sgm[ii][jj]  =	IMG_1[ii][jj] * img_check[ii][jj];
		//	img2_sgm[ii][jj]  =	IMG_2[ii][jj] * img_check[ii][jj];
		//	img3_sgm[ii][jj]  =	IMG_3[ii][jj] * img_check[ii][jj];
//			img1_sgm[ii][jj]  =	L[ii][jj] * (dbfl)img_check[ii][jj];
//			img2_sgm[ii][jj]  =	a[ii][jj] * (dbfl)img_check[ii][jj];
//			img3_sgm[ii][jj]  =	b[ii][jj] * (dbfl)img_check[ii][jj];

			//----------------------------
		}
	}
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-
//	Test_matrix(img1_sgm,1);
//	uint8 b=0;

}
