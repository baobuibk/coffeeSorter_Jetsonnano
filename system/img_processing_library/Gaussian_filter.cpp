#include "img_processing.h"


void  img_pro::Gaussian_filter(Matrix& img, uint8 size_kernel, dbfl sigma)
{
	uint16 i, j;
	dbfl   center_pxl;
	if (size_kernel == 7)
	{
		if (sigma == 1.5)
		{
			for (i = 3; i < ROW - 3; i++)
			{
				for (j = 3; j < COL - 3; j++)
				{
					center_pxl = Gauss_7_15_1[img.at(i - 3, j - 3) + img.at(i - 3, j + 3) + img.at(i + 3, j - 3) + img.at(i + 3, j + 3)] +
								 Gauss_7_15_2[img.at(i - 3, j - 2) + img.at(i - 3, j + 2) + img.at(i - 2, j - 3) + img.at(i - 2, j + 3) +
											  img.at(i + 2, j - 3) + img.at(i + 2, j + 3) + img.at(i + 3, j - 2) + img.at(i + 3, j + 2)] +
								 Gauss_7_15_3[img.at(i - 3, j - 1) + img.at(i - 3, j + 1) + img.at(i - 1, j - 3) + img.at(i - 1, j + 3) +
											  img.at(i + 1, j - 3) + img.at(i + 1, j + 3) + img.at(i + 3, j - 1) + img.at(i + 3, j + 1)] +
								 Gauss_7_15_4[img.at(i - 3, j	 ) + img.at(i    , j - 3) + img.at(i    , j + 3) + img.at(i + 3, j	  )] +
								 Gauss_7_15_5[img.at(i - 2, j - 2) + img.at(i - 2, j + 2) + img.at(i + 2, j - 2) + img.at(i + 2, j + 2)] +
								 Gauss_7_15_6[img.at(i - 2, j - 1) + img.at(i - 2, j + 1) + img.at(i - 1, j - 2) + img.at(i - 1, j + 2) +
											  img.at(i + 1, j - 2) + img.at(i + 1, j + 2) + img.at(i + 2, j - 1) + img.at(i + 2, j + 1)] +
								 Gauss_7_15_7[img.at(i - 2, j	 ) + img.at(i    , j - 2) + img.at(i    , j + 2) + img.at(i + 2, j	  )] +
								 Gauss_7_15_8[img.at(i - 1, j - 1) + img.at(i - 1, j + 1) + img.at(i + 1, j - 1) + img.at(i + 1, j + 1)] +
								 Gauss_7_15_9[img.at(i - 1, j	 ) + img.at(i    , j - 1) + img.at(i    , j + 1) + img.at(i + 1, j	  )] +
								 Gauss_7_15_10[img.at(i   , j)];
					img.set(i,j) = (uint8)round(center_pxl);
				}
			}
		}
	}
//	else if (size_kernel == 5) {}
//	else if (size_kernel == 3) {}
}