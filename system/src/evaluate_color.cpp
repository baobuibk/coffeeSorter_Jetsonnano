//==================================================================
/*
* This function is used to inspect the color of objects
* by using historgram of red color channel.
* If the number of pixel '0' in histogram is greater 
* than a specific parameter, it will consider as a bad bean.
* By constrast, it will be classified into the good beans group.
* result_color->0,1: position center, 2:color:,3:shape
*/
//==================================================================

#include "Coffee_bean.hpp"
uint8 Algorithm_Cfbean::evaluate_color(	Matrix&		Img_seg,
										Matrix16&	img_label,
										uint16		nb_object,
										uint16		result_color[500][4])
{
	//--------------------------------------------------------------------
	uint32	num_pxl[500];				// store number of pixels of each object
	uint16	his_color[500];				// contain number of pixels that is greater than a particular parameter 	
	uint16	i, j;
	uint16	ii;
	dbfl	tem_result;

	for (ii = 0; ii < 500; ii++)
	{
		his_color[ii]	= 0;
		num_pxl[ii]		= 0;
	}
	//--------------------------------------------------------------------
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (img_label.at(i, j) != 0)
			{
				num_pxl[img_label.at(i, j) - 1] += 1;
				if (Img_seg.at(i, j) <= THR_PXL)
					his_color[img_label.at(i, j) - 1] += 1;
				else continue;
			}
		}
	}
	//--------------------------------------------------------------------
	for (ii = 0; ii < nb_object; ii++)
	{
		tem_result = (dbfl)his_color[ii] / (dbfl)num_pxl[ii];

//		printf("%f   %d  %d\n", tem_result, tem_result <= THR_PERCENTAGE,ii+1);
		if (tem_result >= THR_PERCENTAGE)
			result_color[ii][2] = _BAD_;
		else
			result_color[ii][2] = _GOOD_;
//		printf("%f \n", tem_result);
	}
//	for (i = 0; i < nb_object; i++)
//		printf("%d  \n", result_color[i][2]);
	return 0;
}


