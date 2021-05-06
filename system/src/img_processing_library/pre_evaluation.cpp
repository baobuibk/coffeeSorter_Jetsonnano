//=========================================================
// This funtion find border of each object in a BINARY image and return
// bordered image and position of them
// posi_single: single position of object
// The single position is organized as following:
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

#include "img_processing.h"
#include "stdio.h"


uint8 	img_pro::pre_evaluation(	Matrix  &img_bi,							// input binary image with background 0 and foreground 1
									Matrix16&Img_label,							// Using for store img_label
									uint16 	&nb_object,							// number of objects
									uint16	&nb_obj_eva,						// number of meaningful objects
									uint16  order_label[100],					// contain the order of obj after the process
									Matrix  &Border_img,						// img_border
									uint16  arr_posi_obj[ROW_POSI_SINGLE][2],	// contain position of pixels on object border )						
									uint16  center_pxl[100][2])
{
	uint32  row_coor_noise;     // store the center pixel of redundant object that will be deleted
	uint32  col_coor_noise;     // store the center pixel of redundant object that will be deleted
	uint16 	i=0,j=0;            // index
	uint32  ixd_arr_psobj=0;	// index of arr_posi_obj
	uint16  idx_odlb = 0;		// index of order_label
	uint16	cur_label = 0;		// the label of residual object needing to be removed or label of processing object
	int8    ii=0,jj=0;			// index
	uint8 	TB_sum_neighbor=0,ERP_sum_neighbor=0; // Containing the sum of neighbor pixels
	uint8	si_flag;			// flag that used for checking explore_border_single
	uint32  center_row;			// contain the temporary row center
	uint32	center_col;			// contain the temporary col center
	
	nb_object = Cc_label(img_bi, Img_label,5);              
	nb_obj_eva = nb_object;
//	printf("%d  %d", img_bi.at(79, 71), img_bi.at(104, 47));
	//========================================================= THINNING BORDER
	for (i=0;i<ROW;i++)
	{
		for (j=0;j<COL;j++)
		{
			if ((i < 5) | (i >= ROW - 5) | (j < 5) | (j >= COL - 5))
				Border_img.set(i, j) = BLACK;
			//-------------------------------------------
			else
			{
				if (img_bi.at(i, j) == WHITE)
				{
					TB_sum_neighbor = 0;
					for (ii = -1; ii <= 1; ii++)
					{
						for (jj = -1; jj <= 1; jj++)
						{
							TB_sum_neighbor += img_bi.at(i + ii, j + jj);
						}
					}
					Border_img.set(i, j) = (TB_sum_neighbor <= 8) ? WHITE : BLACK;
				}
				else Border_img.set(i, j) = BLACK;
			}
			
			//-------------------------------------------
		}
	}
	
	thining_algorithm(Border_img);
	//========================================================= ELIMINATING RESIDUAL PIXELS
	for (i=5;i<ROW-5;i++)
	{
		for (j=5;j<COL-5;j++)
		{
			//------------------------------------------------
			if(Border_img.at(i, j) == WHITE)
			{
                //------------ check sum neighbors
				ERP_sum_neighbor = 0;
				for (ii=-1;ii<=1;ii++)
					for (jj=-1;jj<=1;jj++) ERP_sum_neighbor += Border_img.at(i+ii,j+jj);

                //------------ if existing one point noise
				if (ERP_sum_neighbor == 1) Border_img.set(i,j) = BLACK;

                //------------ if the line was broken
				else if ((ERP_sum_neighbor == 2) || (ERP_sum_neighbor > 3))
				{
					cur_label = Img_label.at(i, j);                              // get the removed label that contains in img_bi 
					eliminate_noise_line(cur_label, Border_img, Img_label, row_coor_noise, col_coor_noise);
					arr_posi_obj[ixd_arr_psobj	][0]		= 1313;
					arr_posi_obj[ixd_arr_psobj++][1]		= 1;
					arr_posi_obj[ixd_arr_psobj	][0]		= row_coor_noise;
					arr_posi_obj[ixd_arr_psobj++][1]		= col_coor_noise;
					//-------------------------
					center_pxl[idx_odlb][0]					= row_coor_noise;   //center point of broken lines are saved 
					center_pxl[idx_odlb][1]					= col_coor_noise;	//center point of broken lines are saved 
					order_label[idx_odlb++]					= cur_label;		// label order of broken lines are saved 
					nb_obj_eva--;
					//-------------------------
				}
				else continue;
                //------------------------------------
			}
			else continue;
			//-------------------------------------------------
		}
	} 
	
//Test_matrix_sub(IMG_Bdlc);

	//========================================================= FIND BORDER LINE
	for (i=5;i<ROW-5;i++)
	{
		for (j=5;j<COL-5;j++)
		{
			//-----------------------------------------------
			if (Border_img.at(i,j) == WHITE)
			{
				cur_label	= Img_label.at(i, j);
				center_row	= 0;
				center_col	= 0;
				si_flag		= Explore_border_single(Border_img, ixd_arr_psobj,i,j, arr_posi_obj, center_pxl, center_row, center_col);
				if (si_flag == _OFF_)  
				{ 
					center_pxl[idx_odlb][0] = center_row;
					center_pxl[idx_odlb][1] = center_col;
					order_label[idx_odlb++] = cur_label;
				}
			}
			//-----------------------------------------------
		}
	}
    return _OK_;
}
