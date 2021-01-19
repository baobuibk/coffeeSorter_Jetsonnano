/*
 * rgb2lab.c
 *
 *  Created on: Sep 16, 2019
 *      Author: ducan
 */
#include "Coffee_bean.h"
#include "math.h"
#include "rgb2lab_table.h"
//dbfl  RED[ROW][COL];
//dbfl  GREEN[ROW][COL];
//dbfl  BLUE[ROW][COL];

//dbfl  XXn[ROW][COL];
//dbfl  YYn[ROW][COL];
//dbfl  YYn_ori[ROW][COL];
//dbfl  ZZn[ROW][COL];

void rgb2lab(	uint8   img1_sgm[ROW][COL],
		uint8   img2_sgm[ROW][COL],
		uint8   img3_sgm[ROW][COL],
		dbfl	L[ROW][COL],
		dbfl	a[ROW][COL],
                dbfl	b[ROW][COL]
                )
{
	dbfl  red, green, blue;
	dbfl  X_Xn_THR,Y_Yn_THR,Z_Zn_THR;
	dbfl  RED,GREEN,BLUE;
	dbfl  Xn,Yn,Zn;
	dbfl  XXn,YYn,ZZn;
	int16 i,j;

//	uint8 check;
//=============================================== RGB2XYZ: Normalize data and Inverse sRGB to linear

	for (i=0;i<ROW;i++)
	{
		for (j=0;j<COL;j++)
		{
			red   = ((dbfl)(img1_sgm[i][j])/255);      //USE TABLE
			green = ((dbfl)(img2_sgm[i][j])/255);
			blue  = ((dbfl)(img3_sgm[i][j])/255);

			RED 	= (red > THRCIE_sRGB2XYZ_ISC)?	 	rgb2xyz_table1[img1_sgm[i][j]]:
									rgb2xyz_table2[img1_sgm[i][j]];
			GREEN	= (green > THRCIE_sRGB2XYZ_ISC)?	rgb2xyz_table1[img2_sgm[i][j]]:
									rgb2xyz_table2[img2_sgm[i][j]];
			BLUE 	= (blue > THRCIE_sRGB2XYZ_ISC)?		rgb2xyz_table1[img3_sgm[i][j]]:
									rgb2xyz_table2[img3_sgm[i][j]];


			//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			Xn = 0.41239079926596*RED + 0.35758433938388*GREEN + 0.18048078840183*BLUE;
			Yn = 0.21263900587151*RED + 0.71516867876776*GREEN + 0.07219231536073*BLUE;
			Zn = 0.01933081871559*RED + 0.11919477979463*GREEN + 0.95053215224966*BLUE;

			//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=- Normalize XYZ2Lab
			X_Xn_THR = Xn * 1.0521265582;   // X/Xn  	X_Xn_THR = XXn[i][j] / 0.950456;
			Y_Yn_THR = Yn;		   			// Y/Yn		Y_Yn_THR = YYn[i][j] / 1;
			Z_Zn_THR = Zn * 0.91848112613;	// Z/Zn		Z_Zn_THR = ZZn[i][j] / 1.088754;
					//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=- Calculate L*a*b*
			XXn = (X_Xn_THR > THRCIE_XYZ2Lab_T)?fastPow(X_Xn_THR,0.33333333333):7.787 *X_Xn_THR + 0.13793103448;
			YYn = (Y_Yn_THR > THRCIE_XYZ2Lab_T)?fastPow(Y_Yn_THR,0.33333333333):7.787 *Y_Yn_THR + 0.13793103448;
			ZZn = (Z_Zn_THR > THRCIE_XYZ2Lab_T)?fastPow(Z_Zn_THR,0.33333333333):7.787 *Z_Zn_THR + 0.13793103448;

			L[i][j] = (Y_Yn_THR > THRCIE_XYZ2Lab_T)?116*YYn - 16:903.3*Yn;
			a[i][j] = 500*(XXn - YYn);
			b[i][j] = 200*(YYn - ZZn);
		}
	}

//	Test_matrix(YYn);
//	check = Test_matrix_sub_dbfl(ZZn);
//=============================================== XYZ2Lab (D65 white point)
 ///   ***pstart = clock();

/// ***pendtime = clock();
//	Test_matrix(b,2);

//	Test_matrix(L,2);
//	Test_matrix_sub_dbfl(L);






}

