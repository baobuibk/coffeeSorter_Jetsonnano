#include "img_processing.h"


//===================================
//      WRITE ALL 3 CHANNELS
//
//===================================

uint8 img_pro::write_img2txt(Matrix& img_re, Matrix& img_gr, Matrix& img_bl, PATH &path_re, PATH& path_gr, PATH& path_bl)
{
	uint16 r, c;
	FILE* file_re;
	FILE* file_gr;
	FILE* file_bl;
//	errno_t err_re, err_gr, err_bl;
	//--------------------------------------
	//      OPEN TXT FILE
	//--------------------------------------
	//------------------
	//Using for Linux
	//------------------

	file_re = fopen(path_re, "w");
	file_gr = fopen(path_gr, "w");
	file_bl = fopen(path_bl, "w");


	//------------------
	//Using for windown
	//------------------
/*		
	err_re = fopen_s(&file_re, path_re, "w");
	err_gr = fopen_s(&file_gr, path_gr, "w");
	err_bl = fopen_s(&file_bl, path_bl, "w");
*/
	//--------------------------------------
	//      CHECK ERROR AND WRITE IMG TO TXT
	//--------------------------------------
	if ((file_re == (FILE*)NULL) || (file_gr == (FILE*)NULL) || (file_bl == (FILE*)NULL))
	{
		printf("get matrix error at function write_img2txt");
		return _ERROR_;
	}
	else
	{
		for (r = 0; r < ROW; r++)
		{
			for (c = 0; c < COL; c++)
			{
				//--------------------------------------
				//		Write into red channel
				// -------------------------------------
				if (img_re.at(r,c) < 10)
					fprintf(file_re, "%d    ", img_re.at(r, c));
				else if (img_re.at(r, c) < 100)
					fprintf(file_re, "%d   ", img_re.at(r, c));
				else
					fprintf(file_re, "%d  ", img_re.at(r, c));

				//--------------------------------------
				//		Write into green channel
				// -------------------------------------
				if (img_gr.at(r, c) < 10)
					fprintf(file_gr, "%d    ", img_gr.at(r, c));
				else if (img_gr.at(r, c) < 100)
					fprintf(file_gr, "%d   ", img_gr.at(r, c));
				else
					fprintf(file_gr, "%d  ", img_gr.at(r, c));

				//--------------------------------------
				//		Write into blue channel
				// -------------------------------------
				if (img_bl.at(r, c) < 10)
					fprintf(file_bl, "%d    ", img_bl.at(r, c));
				else if (img_bl.at(r, c) < 100)
					fprintf(file_bl, "%d   ", img_bl.at(r, c));
				else
					fprintf(file_bl, "%d  ", img_bl.at(r, c));

			}
			fprintf(file_re, "\n");
			fprintf(file_gr, "\n");
			fprintf(file_bl, "\n");

		}
		//_fcloseall();
		fcloseall();
		return _OK_;

	}
}


//===================================
//      WRITE GRAY IMAGE
//
//===================================

uint8 img_pro::write_img2txt(Matrix & img_gray, PATH & path_gray)
{
	uint16 r, c;
	FILE* file_gray;
//	errno_t err_gray;
	//--------------------------------------
	//			OPEN TXT FILE
	//--------------------------------------
	file_gray = fopen(path_gray, "w");
//	err_gray = fopen_s(&file_gray, path_gray, "w");

	//--------------------------------------
	//  CHECK ERROR AND WRITE INTO TXT FILE
	//--------------------------------------
	if (file_gray == (FILE*)NULL)
	{
		printf("get matrix error at function write_img2txt");
		return _ERROR_;
	}
	else
	{
		for (r = 0; r < ROW; r++)
		{
			for (c = 0; c < COL; c++)
			{
				
				//--------------------------------------
				//		Write into red channel
				// -------------------------------------

				if (img_gray.at(r, c) < 10)
					fprintf(file_gray, "%d    ", img_gray.at(r, c));
				else if (img_gray.at(r, c) < 100)
					fprintf(file_gray, "%d   ", img_gray.at(r, c));
				else
					fprintf(file_gray, "%d  ", img_gray.at(r, c));

			}
			fprintf(file_gray, "\n");
		}
		fclose(file_gray);
		return _OK_;
	}
}


//===================================
//      WRITE GRAY IMAGE USING ARRAY
//
//===================================

uint8 img_pro::write_img2txt(uint8 img_gray[3600][320], PATH& path_gray)
{
	uint16 r, c;
	FILE* file_gray;
//	errno_t err_gray;
	//--------------------------------------
	//			OPEN TXT FILE
	//--------------------------------------
	file_gray = fopen(path_gray, "w");
//	err_gray = fopen_s(&file_gray, path_gray, "w");

	//--------------------------------------
	//  CHECK ERROR AND WRITE INTO TXT FILE
	//--------------------------------------
	if (file_gray == (FILE*)NULL)
	{
		printf("get matrix error at function write_img2txt");
		return _ERROR_;
	}
	else
	{
		for (r = 0; r < 3600; r++)
		{
			for (c = 0; c < 320; c++)
			{

				//--------------------------------------
				//		Write into red channel
				// -------------------------------------

				if (img_gray[r][c] < 10)
					fprintf(file_gray, "%d    ", img_gray[r][c]);
				else if (img_gray[r][c] < 100)
					fprintf(file_gray, "%d   ", img_gray[r][c]);
				else
					fprintf(file_gray, "%d  ", img_gray[r][c]);

			}
			fprintf(file_gray, "\n");
		}
		fclose(file_gray);
		return _OK_;
	}
}
