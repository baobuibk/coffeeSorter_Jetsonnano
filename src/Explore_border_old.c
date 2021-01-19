//=========================================================
// This funtion find border of each object in image and return
// bordered image and position of them
// posi_single: single position of object
// The single position is orginized as following:
//      131313  size of object 1
//         xn1    yn1
//         xn2    yn2
//            ...
//      131313  size of object 2
//         xm1    ym1
//         xm2    ym2
//            ...
//         xmm    ymm
// out_border: border image
// out_pst_pxl : pixel position
// num_object  : number of good object
// er_find_line: check error when find border (ON=1, OFF=0)
//=========================================================
#include "Coffee_bean.h"
#include "stdio.h"


uint8 	Explore_border(	uint8 	IMGBi[ROW][COL],
			uint8 	*pnb_object,
			uint16 	*psize_sum_lsp,
			uint16  posi_single[ROW_POSI_SINGLE][2],
			uint8  	IMG_Bdlc[ROW][COL])

{
	uint16 	i,j;
	uint16  ERP_x_cur,ERP_y_cur;
	int8    ii,jj;
	uint8 	TB_sum_neighbor,ERP_sum_neighbor;
	uint8 	si_flag;
//	uint8   img_border_si[ROW][COL];
//	uint16  posi_single[ROW_POSI_SINGLE][2];
//	uint8  	IMG_Bdlc[ROW][COL];                           // Image border local


//	Test_matrix_sub(IMGBi);
	//========================================================= INITIALIZING VALUE
/*
	for(i=0;i<ROW;i++)
	{
		for (j=0;j<COL;j++)
		{
			IMG_Bdlc[i][j] 	= 	1;
		}
	}
*/
	//========================================================= THINING BORDER
	for (i=0;i<ROW;i++)
	{
		for (j=0;j<COL;j++)
		{
			//-------------------------------------------
			if (((i<5) | (i>= ROW-5)) & ((j<5) | (j >= COL-5)))
			{
				IMG_Bdlc[i][j] = BLACK;
				IMG_Bi[i][j]   = BLACK;
				continue;
			}
			else
			{
				TB_sum_neighbor = 0;
				for (ii=-1;ii<=1;ii++)
				{
					for (jj=-1;jj<=1;jj++) 	
					{
						TB_sum_neighbor +=	IMGBi[i+ii][j+jj];
					} 
				}

				if((IMGBi[i][j] == WHITE) && (TB_sum_neighbor <= 8))
					IMG_Bdlc[i][j] = WHITE;
				else 	IMG_Bdlc[i][j] = BLACK;
			}
			//-------------------------------------------
		}
	}

//	Test_matrix_sub(IMG_Bdlc);
	Thinning_process(IMG_Bdlc);

	//========================================================= ELIMINATING RESIDUAL PIXELS
	for (i=5;i<ROW-5;i++)
	{
		for (j=5;j<COL-5;j++)
		{
			//------------------------------------------------
			if(IMG_Bdlc[i][j] == WHITE)
			{
                //------------ check sum neighbors
				ERP_sum_neighbor = 0;
				for (ii=-1;ii<=1;ii++)
				{
					for (jj=-1;jj<=1;jj++) ERP_sum_neighbor += IMG_Bdlc[i+ii][j+jj];
				}

                //------------ if existing one point noise
				if (ERP_sum_neighbor == 1) IMG_Bdlc[i][j] = BLACK;

                //------------ if the line is broken
				else if (ERP_sum_neighbor == 2)
				{
					ERP_x_cur 	= i;
					ERP_y_cur 	= j;
					eliminate_noise_line(ERP_x_cur,ERP_y_cur,IMG_Bdlc);
				}

                //------------------------------------ if the line is divided two brand
				else if (ERP_sum_neighbor > 3)
				{
					ERP_x_cur                      = i;
					ERP_y_cur                      = j;
					IMG_Bdlc[ERP_x_cur][ERP_y_cur] = BLACK;
                    //------------------
					for (ii=-1;ii<=1;ii++)
					{
						for (jj=-1;jj<=1;jj++)
						{
							if(IMG_Bdlc[ERP_x_cur+ii][ERP_y_cur+jj] == WHITE)
								eliminate_noise_line(ERP_x_cur+ii,ERP_y_cur+jj,IMG_Bdlc);
						}
					}
                    //------------------
				}
				else continue;
                //------------------------------------
			}
			else continue;
			//-------------------------------------------------
		}
	}
//Test_matrix_sub(IMG_Bdlc);
//	Test_matrix_sub(IMG_Bdlc);
	//========================================================= FIND BORDER LINE
	for (i=5;i<ROW-5;i++)
	{
		for (j=5;j<COL-5;j++)
		{
    //-----------------------------------------------
			if (IMG_Bdlc[i][j] == WHITE)
			{
				si_flag = Explore_border_single(posi_single,IMG_Bdlc,&psize_sum_lsp,i,j);
				if (si_flag == OFF)  *pnb_object += 1;
			}
    //-----------------------------------------------
		}
	}
    return OK;
}
