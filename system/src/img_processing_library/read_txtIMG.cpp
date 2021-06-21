/*=========================================================
* This function used to read a matrix from a txt file.
* Use 3 2D array to transfer and receive value back after
* read completely file.
* Note: This function read three files (txt) containing
* 3 channels R,G,B of a image. These channels can be written
* by Matlab into txt files
*
* Create by: Duc An Nguyen
* Last Modify: 23/2/2021
*///=======================================================
#include "img_processing.h"
#include <stdio.h>


//=============================================================== 1. READ TXT IMAGE RGB
uint8 img_pro::read_txtIMG(	Matrix &Img_re,
				Matrix &Img_gr,
				Matrix &Img_bl,
				PATH   &Path_re,
				PATH   &Path_gr,
				PATH   &Path_bl)
{
	uint16	i, j;
	dbfl	value1,value2,value3;
	FILE	*file1, *file2, *file3;
//	errno_t err1, err2, err3;     // this one is only used on Windown

	file1 = fopen(Path_re, "r");
	file2 = fopen(Path_gr, "r");
	file3 = fopen(Path_bl, "r");

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	if (file1 == (FILE*)NULL)
	{
		printf("Open file at read_txtIMG(...) fail, Path 1 is not valid, please check again!\n");
		fcloseall();

		return _ERROR_;
	}
	else if (file2 == (FILE*)NULL)
	{
		printf("Open file at read_txtIMG(...) fail, Path 2 is not valid, please check again!\n");
		fcloseall();
		return _ERROR_;
	}
	else if (file3 == (FILE*)NULL)
	{
		printf("Open file at read_txtIMG(...) fail, Path 3 is not valid, please check again!\n");
		fcloseall();
		return _ERROR_;
	}
	else
	{
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
			{
				//--------------------------//
				fscanf(file1, "%f", &value1);
				Img_re.set(i,j) = (uint8)value1;

				fscanf(file2, "%f", &value2);
				Img_gr.set(i, j) = (uint8)value2;

				fscanf(file3, "%f", &value3);
				Img_bl.set(i, j) = (uint8)value3;

				//--------------------------//
			}
		}
		fcloseall();
		return _OK_;
	}
	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}




//=============================================================== 2. READ TXT IMAGE GRAY 8 bit
uint8 img_pro::read_txtIMG(Matrix &IMG_gray, PATH &path_gray)
{
	uint16 	i, j;
	dbfl 	value;
	FILE    *file;
//	errno_t err;
	

	file = fopen(path_gray, "r");

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	if ((file == (FILE*)NULL))
	{
		printf("Open file at read_txtIMG(Matrix &IMG_gray) fail, please check again!");
		fcloseall();
		return _ERROR_;
	}
	else
	{
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
			{
				//--------------------------
				fscanf(file, "%f", &value);
				IMG_gray.set(i,j) = (uint8)value;

				//--------------------------
			}
		}
		fcloseall();
		return _OK_;
	}
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


//=============================================================== 3. READ TXT IMAGE GRAY 16 bit
uint8 img_pro::read_txtIMG(Matrix16& IMG_gray, PATH& path_gray)
{
	uint16 	i, j;
	dbfl 	value;
	FILE* file;
//	errno_t err;


	file = fopen(path_gray, "r");

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	if ((file == (FILE*)NULL))
	{
		printf("Open file at read_txtIMG(Matrix &IMG_gray) fail, please check again!");
		fcloseall();
		return _ERROR_;
	}
	else
	{
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
			{
				//--------------------------
				fscanf(file, "%f", &value);
				IMG_gray.set(i, j) = (uint16)value;

				//--------------------------
			}
		}
		fcloseall();
		return _OK_;
	}
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

//=============================================================== 4. READ TXT IMAGE DOUBLE FLOAT
uint8 img_pro::read_txtIMG(dbfl IMG[ROW][COL])
{
	uint16 	i, j;
	dbfl 	value;

	FILE* file1;
//	errno_t err;

	file1 = fopen("D:/B. WORK/LAB/COFFEE _BEAN IMAGE PROCESSING/Text_value/Gray.txt", "r");

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	if (file1 == (FILE*)NULL)
	{
		printf("matrix gray error!");
		fcloseall();
		return _ERROR_;
	}
	else
	{
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
			{
				//--------------------------
				fscanf(file1, "%f", &value);
				IMG[i][j] = value;

				//--------------------------
			}
		}
		fcloseall();
		return _OK_;
	}
}
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//=============================================================== 5. READ TXT IMAGE RGB INTO OPENCV IMG
uint8 img_pro::read_txtIMG(	Mat& img_re,
							Mat& img_gr,
							Mat& img_bl,
							PATH& Path_re,
							PATH& Path_gr,
							PATH& Path_bl)
{
	uint16	i, j;
	dbfl	value1, value2, value3;
	FILE	*file1, *file2, *file3;
//	errno_t err1, err2, err3;     // this one is only used on Windown

	file1 = fopen(Path_re, "r");
	file2 = fopen(Path_gr, "r");
	file3 = fopen(Path_bl, "r");
	

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	if ((file1 == (FILE*)NULL))
	{
		printf("Open file at read_txtIMG(uint8 IMG_1[ROW][COL], ...) fail, Path 1 is not valid, please check again!");
		fcloseall();
		return _ERROR_;
	}
	else if (file2 == (FILE*)NULL)
	{
		printf("Open file at read_txtIMG(uint8 IMG_1[ROW][COL], ...) fail, Path 2 is not valid, please check again!");
		fcloseall();
		return _ERROR_;
	}
	else if (file3 == (FILE*)NULL)
	{
		printf("Open file at read_txtIMG(uint8 IMG_1[ROW][COL], ...) fail, Path 3 is not valid, please check again!!");
		fcloseall();
		return _ERROR_;
	}
	else
	{
		for (i = 0; i < ROW_CAM; i++)
		{
			for (j = 0; j < COL_CAM; j++)
			{
				//--------------------------//
				fscanf(file1, "%f", &value1);
				img_re.at<uchar>(i, j) = (uint8)value1;

				fscanf(file2, "%f", &value2);
				img_gr.at<uchar>(i, j) = (uint8)value2;

				fscanf(file3, "%f", &value3);
				img_bl.at<uchar>(i, j) = (uint8)value3;

				//--------------------------//
			}
		}
//		printf("%d ", img_re_bgr.at<uchar>(0,0));
		fcloseall();
		return _OK_;
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

//=============================================================== 6. READ TXT IMAGE RGB USING CLASS OF MALLOC
uint8 img_pro::read_txtIMG(	_Matrix_& Img_re,
							_Matrix_& Img_gr,
							_Matrix_& Img_bl,
							PATH& Path_re,
							PATH& Path_gr,
							PATH& Path_bl)
{
	uint16	i, j;
	dbfl	value1, value2, value3;
	FILE* file1, * file2, * file3;
//	errno_t err1, err2, err3;

	file1 = fopen(Path_re, "r");
	file2 = fopen(Path_gr, "r");
	file3 = fopen(Path_bl, "r");

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	if ((file1 == (FILE*)NULL))
	{
		printf("Open file at read_txtIMG(uint8 IMG_1[ROW][COL], ...) fail, Path 1 is not valid, please check again!");
		fcloseall();
		return _ERROR_;
	}
	else if (file2 == (FILE*)NULL)
	{
		printf("Open file at read_txtIMG(uint8 IMG_1[ROW][COL], ...) fail, Path 2 is not valid, please check again!");
		fcloseall();
		return _ERROR_;
	}
	else if (file3 == (FILE*)NULL)
	{
		printf("Open file at read_txtIMG(uint8 IMG_1[ROW][COL], ...) fail, Path 3 is not valid, please check again!!");
		fcloseall();
		return _ERROR_;
	}
	else
	{
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
			{
				//--------------------------//
				fscanf(file1, "%f", &value1);
				Img_re.val[i][j] = (uint8)value1;

				fscanf(file2, "%f", &value2);
				Img_gr.val[i][j] = (uint8)value2;

				fscanf(file3, "%f", &value3);
				Img_bl.val[i][j] = (uint8)value3;

				//--------------------------//
			}
		}
		fcloseall();
		return _OK_;
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}