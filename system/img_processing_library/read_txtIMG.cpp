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
#include "stdio.h"


//=============================================================== 1. READ TXT IMAGE RGB
uint8 img_pro::read_txtIMG(	Matrix &Img_re,
							Matrix &Img_gr,
							Matrix &Img_bl,
							PATH   &Path_re,
							PATH   &Path_gr,
							PATH   &Path_bl
						    )
{
	uint16	i, j;
	dbfl	value1,value2,value3;
	FILE	*file1, *file2, *file3;
	errno_t err1, err2, err3;

	err1 = fopen_s(&file1, Path_re, "r");
	err2 = fopen_s(&file2, Path_gr, "r");
	err3 = fopen_s(&file3, Path_bl, "r");

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	if ((file1 == (FILE*)NULL) || err1 != 0)
	{
		printf("Open file at read_txtIMG(uint8 IMG_1[ROW][COL], ...) fail, Path 1 is not valid, please check again!");
		_fcloseall();
		return _ERROR_;
	}
	else if (file2 == (FILE*)NULL || err2 != 0)
	{
		printf("Open file at read_txtIMG(uint8 IMG_1[ROW][COL], ...) fail, Path 2 is not valid, please check again!");
		_fcloseall();
		return _ERROR_;
	}
	else if (file3 == (FILE*)NULL || err3 != 0)
	{
		printf("Open file at read_txtIMG(uint8 IMG_1[ROW][COL], ...) fail, Path 3 is not valid, please check again!!");
		_fcloseall();
		return _ERROR_;
	}
	else
	{
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
			{
				//--------------------------//
				fscanf_s(file1, "%f", &value1);
				Img_re.set(i,j) = (uint8)value1;

				fscanf_s(file2, "%f", &value2);
				Img_gr.set(i, j) = (uint8)value2;

				fscanf_s(file3, "%f", &value3);
				Img_bl.set(i, j) = (uint8)value3;

				//--------------------------//
			}
		}
		_fcloseall();
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
	errno_t err;
	

	err = fopen_s(&file, path_gray, "r");

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	if ((file == (FILE*)NULL) || err != 0)
	{
		printf("Open file at read_txtIMG(Matrix &IMG_gray) fail, please check again!");
		_fcloseall();
		return _ERROR_;
	}
	else
	{
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
			{
				//--------------------------
				fscanf_s(file, "%f", &value);
				IMG_gray.set(i,j) = (uint8)value;

				//--------------------------
			}
		}
		_fcloseall();
		return _OK_;
	}
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}


//=============================================================== 2. READ TXT IMAGE GRAY 16 bit
uint8 img_pro::read_txtIMG(Matrix16& IMG_gray, PATH& path_gray)
{
	uint16 	i, j;
	dbfl 	value;
	FILE* file;
	errno_t err;


	err = fopen_s(&file, path_gray, "r");

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	if ((file == (FILE*)NULL) || err != 0)
	{
		printf("Open file at read_txtIMG(Matrix &IMG_gray) fail, please check again!");
		_fcloseall();
		return _ERROR_;
	}
	else
	{
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
			{
				//--------------------------
				fscanf_s(file, "%f", &value);
				IMG_gray.set(i, j) = (uint16)value;

				//--------------------------
			}
		}
		_fcloseall();
		return _OK_;
	}
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
}

//=============================================================== 3. READ TXT IMAGE DOUBLE FLOAT
uint8 img_pro::read_txtIMG(dbfl IMG[ROW][COL])
{
	uint16 	i, j;
	dbfl 	value;

	FILE* file1;
	errno_t err;

	err = fopen_s(&file1, "D:/B. WORK/LAB/COFFEE _BEAN IMAGE PROCESSING/Text_value/Gray.txt", "r");

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	if (file1 == (FILE*)NULL)
	{
		printf("matrix gray error!");
		_fcloseall();
		return _ERROR_;
	}
	else
	{
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
			{
				//--------------------------
				fscanf_s(file1, "%f", &value);
				IMG[i][j] = value;

				//--------------------------
			}
		}
		_fcloseall();
		return _OK_;
	}
}
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=