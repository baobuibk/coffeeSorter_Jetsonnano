//=====================================%
// This funtion explores single border of object and returns single border
// if see noise (1), si_flag = 1
// if the line attract with limited image border, si_flag = 1
//
//=====================================%

#include "Coffee_bean.h"
#include "stdio.h"


uint8 Explore_border_single( 	uint16  posi_single[ROW_POSI_SINGLE][2],
				uint8   IMG_Bdlc[ROW][COL],			// image border local
                             	uint16  **ppsize_sum_lsp,                      	// size of sum local single position
				uint16  x_cur,
				uint16  y_cur)

{
	//=============================================================%
	uint16  i;
	int8  	ii,jj;
	uint8 	size_pos33 = 0;
	uint16 	pos33[3][2];
	uint8 	flag_el;										// flag of exploring line
	uint8 	check_border = 0;
	uint16  size_lsp = 1;                                   // size of local single position
	uint16  pos_lsp[ROW_POSI_SINGLE][2];                    // local single position
	uint16 	x_next,y_next, original_x, original_y;
	uint8   ERR_FLAG = OFF;
	uint16  pre_size_sum_lsp = **ppsize_sum_lsp;


 	pos_lsp[0][0] 	= x_cur;							//initializing si_posi
	pos_lsp[0][1] 	= y_cur;

	IMG_Bdlc[x_cur][y_cur] = BLACK;							//eliminate starting pixel

	//==============================================================% searching the first point
	for(ii=-1;ii<=1;ii++)
	{
		for (jj=-1;jj<=1;jj++)
		{
			if((ii!=0 || jj!=0) && (IMG_Bdlc[ x_cur + ii][y_cur + jj] == 1))
			{
				pos33[size_pos33  ][0]  = x_cur + ii;
				pos33[size_pos33++][1]	= y_cur + jj;
			}
			if (size_pos33 == 3) break;
		}
		if (size_pos33 == 3) break;
	}
	//=====================================
	if (size_pos33 == 3) 	ERR_FLAG = E_B_S_First_point;
	else
	{
		//---------------------------------
		if (pos33[0][1] > pos33[1][1])
		{
			x_next 		= pos33[0][0];
			y_next 		= pos33[0][1];
			original_x 	= pos33[1][0];
			original_y 	= pos33[1][1];
		}
		else
		{
			x_next 		= pos33[1][0];
			y_next 		= pos33[1][1];
			original_x 	= pos33[0][0];
			original_y 	= pos33[0][1];
		}

		//--------------------------------- Exploring border
		flag_el = ON;
		while(flag_el == ON)
		{
			x_cur = x_next;
			y_cur = y_next;

			pos_lsp[size_lsp   ][0] 	= x_cur;
			pos_lsp[size_lsp++ ][1] 	= y_cur;

			if (size_lsp >= ROW_POSI_SINGLE)       //if size of single position is overflow
			{
				ERR_FLAG 	= E_B_S_OVERFLOW_SIZE_POS_SINGLE_LOCAL;
				flag_el 	= OFF;
			}
			else
			{
				//--------------------------------- if object stand by image border
				if ((x_cur == 5) || (x_cur == ROW-6) || (y_cur == 5) || (y_cur == COL - 6))
					check_border +=1;

				IMG_Bdlc[x_cur][y_cur] 	= BLACK;
				//---------------------------------


				//--------------------------------- Searching next point
				for (ii=-1;ii<=1;ii++)
				{
					for (jj=-1;jj<=1;jj++)
					{
						if (IMG_Bdlc[x_cur+ii][y_cur+jj] == WHITE)
						{
							x_next 	= x_cur + ii;
							y_next	= y_cur + jj;
						}
					}
				}

				//-------------------------------- Save local single positions

				if ((x_next == original_x) && (y_next == original_y))
				{
					flag_el = OFF;
					pos_lsp[size_lsp 	][0] 		= x_next;
					pos_lsp[size_lsp++ 	][1] 		= y_next;
					IMG_Bdlc[x_next][y_next] 		= BLACK;

					if ((size_lsp <=100) || (check_border >=15))  ERR_FLAG = E_B_S_NOISE_OBJECT;
				}
			}
		}
	}

	//=====================================
//	pre_size_sum_lsp = **size_sum_lsp;
	if (ERR_FLAG == OFF)
	{
		posi_single[ **ppsize_sum_lsp  ][0]  = 13131;
		posi_single[(**ppsize_sum_lsp)++][1] = size_lsp;

		for (i=0;i<size_lsp;i++)
		{
			posi_single[**ppsize_sum_lsp+i][0] = pos_lsp[i][0];
			posi_single[**ppsize_sum_lsp+i][1] = pos_lsp[i][1];
		}
		**ppsize_sum_lsp += size_lsp;
		if (**ppsize_sum_lsp >= ROW_POSI_SINGLE)
		{
			**ppsize_sum_lsp 	= pre_size_sum_lsp;
			ERR_FLAG 		= E_B_S_OVERFLOW_SIZE_POS_SINGLE_LOCAL;
		}
	}

//	Test_matrix_sub(IMG_Bdlc);

	return ERR_FLAG;

}
