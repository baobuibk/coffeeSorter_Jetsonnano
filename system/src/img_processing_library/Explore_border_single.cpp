//=====================================%
// This funtion explores single border of object and returns single border
// if seeing noise (1), si_flag = 1
// if the line attracts with limited image border, si_flag = 1
//
//	Matrix  &IMG_Bdlc,							//Input: image border local
//	uint32& ixd_arr_psobj						// Input: Contain the current pointer of arr_posi_obj, if starting, it will be 0
//	uint16  x_cur,								// the current x position 	
//	uint16  y_cur,								// the current y position 
//	uint16  order_label[100],					// Input: Contain the label order
//	uint16  arr_posi_obj[ROW_POSI_SINGLE][2])	// Output: using to store position of pxls
// Notice: arr_posi_obj is organized as following:
//		1313	nb_obj
//		x1		y1
//		x2		y2
//			...
// 
// In the case of nb_obj=1, the next x,y coordinate will contain the object center coordinate
//=====================================%

#include "img_processing.h"
#include "stdio.h"


uint8 img_pro::Explore_border_single( 	Matrix  &IMG_Bdlc,							//Input: image border local
										uint32  &ixd_arr_psobj,						// Input: Contain the current pointer of arr_posi_obj
										uint16  x_cur,								// Input:the current x position 	
										uint16  y_cur,								// Input: the current y position 
										uint16  arr_posi_obj[ROW_POSI_SINGLE][2],	// Output: using to store position of pxls)		
								//		uint16	center_pxl[100][2],					// Output: contain the center pixel of each obj organized in place of order_label
										uint32  &center_row,						// Output: contain the temporary row center
										uint32	&center_col)						// Output: contain the temporary col center		
{
	//=============================================================%
	uint16  size_lsp = 1;										// size of local single position, index 0 stores the starting point
	uint16  arr_posi_local[ROW_POSI_SINGLE/10][2];				// contain the local single position, if ok will copy to arr_posi_obj
	uint16 	pos33[3][2];										// Store the first point of input argument and two their neighbors(left and right).
	int8  	ii, jj;												// index for windowns size 3x3
	uint8 	size_pos33 = 0;										// Using to check size of pos33

	uint16  i;
	
	uint8 	flag_el;											// flag of exploring line
	
	uint16 	x_next,y_next, original_x, original_y;
	uint8   ERR_FLAG = _OFF_;									// using to control error of algorithm
	


	//----------------------------------------------------------
//	arr_posi_obj[ixd_arr_psobj++][0] = 1313;			// Starting position of current obj in arr_posi_obj


	arr_posi_local[0][0] 	= x_cur;					// First point
	arr_posi_local[0][1] 	= y_cur;

	IMG_Bdlc.set(x_cur,y_cur) = BLACK;					// Eliminate starting pixel

	//============================================================= Searching two neighbors of first point
	for(ii=-1;ii<=1;ii++)								//	Notice: on the line only exists two neighbors at each point, because						
	{													//	thinning algorithm removed residual pixels		
		for (jj=-1;jj<=1;jj++)
		{
			if((ii!=0 || jj!=0) && (IMG_Bdlc.at( x_cur + ii, y_cur + jj) == 1))
			{
				pos33[size_pos33  ][0]  = x_cur + ii;
				pos33[size_pos33++][1]	= y_cur + jj;
			}
			if (size_pos33 == 3) break;
		}
		if (size_pos33 == 3) break;
	}
	//-------------------------------------
	if (size_pos33 == 3) 	ERR_FLAG = E_B_S_First_point;
	else
	{
		//---------------------------------				// Get the original point and next point that used for seaching border pxls
		if (pos33[0][1] > pos33[1][1])					// Choose the right point is the next point
		{												// The left point will be considered as an original point
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

		//---------------------------------------------------------- Exploring border
		flag_el = _ON_;
		while(flag_el == _ON_)
		{
			x_cur = x_next;
			y_cur = y_next;

			arr_posi_local[size_lsp	  ][0] 	= x_cur;
			arr_posi_local[size_lsp++ ][1] 	= y_cur;

			if (size_lsp >= ROW_POSI_SINGLE/10)       //if size of single position is overflow
			{
				ERR_FLAG 	= E_B_S_OVERFLOW_SIZE_POS_SINGLE_LOCAL;
				flag_el 	= _OFF_;
			}
			else
			{
				IMG_Bdlc.set(x_cur,y_cur) 	= BLACK;
				//--------------------------------- Searching next point
				for (ii=-1;ii<=1;ii++)
				{
					for (jj=-1;jj<=1;jj++)
					{
						if (IMG_Bdlc.at(x_cur+ii,y_cur+jj) == WHITE)
						{
							x_next 	= x_cur + ii;
							y_next	= y_cur + jj;
						}
					}
				}

				//-------------------------------- Save local single positions

				if ((x_next == original_x) && (y_next == original_y))
				{
					flag_el = _OFF_;
					arr_posi_local[size_lsp 	][0] 		= x_next;
					arr_posi_local[size_lsp++ 	][1] 		= y_next;
					IMG_Bdlc.set(x_next,y_next) 			= BLACK;
				}
			}
		}
	}

	//=====================================
//	pre_size_sum_lsp = **size_sum_lsp;
	if (ERR_FLAG == _OFF_)
	{
		arr_posi_obj[ixd_arr_psobj	][0]  = 1313;
		arr_posi_obj[ixd_arr_psobj++][1]  = size_lsp;

		for (i=0;i<size_lsp;i++)
		{
			arr_posi_obj[ixd_arr_psobj	][0] = arr_posi_local[i][0];
			arr_posi_obj[ixd_arr_psobj++][1] = arr_posi_local[i][1];
			center_row	+= arr_posi_local[i][0];
			center_col	+= arr_posi_local[i][1];
		}

		center_row /= size_lsp;
		center_col /= size_lsp;

		if (ixd_arr_psobj >= ROW_POSI_SINGLE)
		{
			ERR_FLAG = E_B_S_OVERFLOW_SIZE_POS_SINGLE_LOCAL;
			printf("single poisition is overflow!\n");
		}
	}

//	Test_matrix_sub(IMG_Bdlc);

	return ERR_FLAG;

}
