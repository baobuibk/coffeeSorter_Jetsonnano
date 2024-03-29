#include "img_processing.h"
#include <stdio.h>



//============================================================================== Using own Matrix
void img_pro::Sub_image(	Matrix& Img_re, Matrix& Img_gr, Matrix& Img_bl,
							Matrix& re_bgr, Matrix& gr_bgr, Matrix& bl_bgr, uint8 ADJUST)
{
	uint16	i, j;
	int16  tem_re, tem_gr, tem_bl;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			tem_re = (Img_re.at(i, j) + ADJUST) - re_bgr.at(i, j);
			tem_gr = (Img_gr.at(i, j) + ADJUST) - gr_bgr.at(i, j);
			tem_bl = (Img_bl.at(i, j) + ADJUST) - bl_bgr.at(i, j);

			if (tem_re > 255)		Img_re.set(i, j) = 255;
			else if (tem_re < 0)	Img_re.set(i, j) = 0;
			else					Img_re.set(i, j) = (uint8)tem_re;

			if (tem_gr > 255)		Img_gr.set(i, j) = 255;
			else if (tem_gr < 0)	Img_gr.set(i, j) = 0;
			else					Img_gr.set(i, j) = (uint8)tem_gr;
			
			if (tem_bl > 255)		Img_bl.set(i, j) = 255;
			else if (tem_bl < 0)	Img_bl.set(i, j) = 0;
			else					Img_bl.set(i, j) = (uint8)tem_bl;
		}
	}
}

//============================================================================== Using own _Matrix_
void img_pro::Sub_image(_Matrix_& Img_re, _Matrix_& Img_gr, _Matrix_& Img_bl,
						_Matrix_& re_bgr, _Matrix_& gr_bgr, _Matrix_& bl_bgr, uint8 ADJUST)
{
	uint16	i, j;
	int16  tem_re, tem_gr, tem_bl;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			tem_re = (Img_re.val[i][j] + ADJUST) - re_bgr.val[i][j];
			tem_gr = (Img_gr.val[i][j] + ADJUST) - gr_bgr.val[i][j];
			tem_bl = (Img_bl.val[i][j] + ADJUST) - bl_bgr.val[i][j];

			if (tem_re > 255)		Img_re.val[i][j] = 255;
			else if (tem_re < 0)	Img_re.val[i][j] = 0;
			else					Img_re.val[i][j] = (uint8)tem_re;

			if (tem_gr > 255)		Img_gr.val[i][j] = 255;
			else if (tem_gr < 0)	Img_gr.val[i][j] = 0;
			else					Img_gr.val[i][j] = (uint8)tem_gr;

			if (tem_bl > 255)		Img_bl.val[i][j] = 255;
			else if (tem_bl < 0)	Img_bl.val[i][j] = 0;
			else					Img_bl.val[i][j] = (uint8)tem_bl;
		}
	}
}

//============================================================================== Using Mat openCV
void img_pro::Sub_image(Mat& img_re, Mat& img_gr, Mat& img_bl,
						Mat& re_bgr, Mat& gr_bgr, Mat& bl_bgr, uint8 ADJUST)
{

	uint16	i, j;
	int16  tem_re, tem_gr, tem_bl;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			tem_re = (img_re.at<uchar>(i, j) + ADJUST) - re_bgr.at<uchar>(i, j);
			tem_gr = (img_gr.at<uchar>(i, j) + ADJUST) - gr_bgr.at<uchar>(i, j);
			tem_bl = (img_bl.at<uchar>(i, j) + ADJUST) - bl_bgr.at<uchar>(i, j);

			if (tem_re > 255)		img_re.at<uchar>(i, j) = 255;
			else if (tem_re < 0)	img_re.at<uchar>(i, j) = 0;
			else					img_re.at<uchar>(i, j) = (uint8)tem_re;

			if (tem_gr > 255)		img_gr.at<uchar>(i, j) = 255;
			else if (tem_gr < 0)	img_gr.at<uchar>(i, j) = 0;
			else					img_gr.at<uchar>(i, j) = (uint8)tem_gr;

			if (tem_bl > 255)		img_bl.at<uchar>(i, j) = 255;
			else if (tem_bl < 0)	img_bl.at<uchar>(i, j) = 0;
			else					img_bl.at<uchar>(i, j) = (uint8)tem_bl;
		}
	}
}



//============================================================================== Need test
void img_pro::Sub_image(Matrix& Img_re, Matrix& Img_gr, Matrix& Img_bl,
						Matrix& re_bgr, Matrix& gr_bgr, Matrix& bl_bgr,
						Matrix& out_re, Matrix& out_gr, Matrix& out_bl, uint8 ADJUST)
{
	uint16 i, j;
	int16  tem_re, tem_gr, tem_bl;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			tem_re = (Img_re.at(i, j) + ADJUST) - re_bgr.at(i, j);
			tem_gr = (Img_gr.at(i, j) + ADJUST) - gr_bgr.at(i, j);
			tem_bl = (Img_bl.at(i, j) + ADJUST) - bl_bgr.at(i, j);

			if (tem_re > 255)		out_re.set(i, j) = 255;
			else if (tem_re < 0)	out_re.set(i, j) = 0;
			else					out_re.set(i, j) = (uint8)tem_re;

			if (tem_gr > 255)		out_gr.set(i, j) = 255;
			else if (tem_gr < 0)	out_gr.set(i, j) = 0;
			else					out_gr.set(i, j) = (uint8)tem_gr;

			if (tem_bl > 255)		out_bl.set(i, j) = 255;
			else if (tem_bl < 0)	out_bl.set(i, j) = 0;
			else					out_bl.set(i, j) = (uint8)tem_bl;
		}
	}
}


//============================================================================== Need test
void img_pro::Sub_image(Matrix& Img_re, Matrix& Img_gr, Matrix& Img_bl,
						Matrix& re_bgr, Matrix& gr_bgr, Matrix& bl_bgr,
						Matrix& out_re, Matrix& out_gr, Matrix& out_bl)
{
	uint16 i, j;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			out_re.set(i, j) = Img_re.at(i, j)  - re_bgr.at(i, j);
			out_gr.set(i, j) = Img_gr.at(i, j)  - gr_bgr.at(i, j);
			out_bl.set(i, j) = Img_bl.at(i, j)  - bl_bgr.at(i, j);
		}
	}
}
