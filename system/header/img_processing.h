/*
* This header contains 2 class: img_pro and Matrix
* img_pro consists of image processing algorithms
* and Matrix is a class for array that used heap memory
* instead of stack.
* 
*/
#ifndef IMAGE_HEADER
#define IMAGE_HEADER



#include "Matrix.h"
#include "type.h"
//#include "Gaussian_table.h"
#include <iostream>
#include <stdlib.h> 
#include <opencv2/opencv.hpp>
using cv::Mat;
using cv::Vec3b;




#define ROW			240	//480
#define COL			320	//640

#define _ERROR_			1
#define _OK_			0

#define _SAME_			0
#define _DIFF_			1

//#define _FLOAT_    		0
//#define _NEGATIVE_FLOAT_ 	1

#define BLACK			0
#define WHITE			1

#define _ON_			1
#define _OFF_			0

#define _GOOD_			1
#define _BAD_			0

#define NO_OBJECT       	0
#define OVER_FL_OBJ		500 

#define MAX_REAL_OBJ    	100



#define ROW_POSI_SINGLE 10000

#define E_B_S_First_point 				2
#define E_B_S_OVERFLOW_SIZE_POS_SINGLE_LOCAL 		3              //E_B_S_OVERFLOW_SIZE_POS_SINGLE_LOCAL
#define E_B_S_NOISE_OBJECT				4

#define OV_LB			501



extern uint8 		M[ROW][COL];

//========================================== Matrix CLASS 
class Matrix
{
private:
	uint8* array;
	uint16 col;
	uint16 r,c;
public:
	
	//---------------------------- Constructor
	Matrix()
	{
		r = 0;
		c = 0;
		col = COL;            // number of colum of defaut image
		array = new(std::nothrow) uint8[ROW * COL];
		if (!array)
		{
			std::cout << "Array allocation failed!\n";
			exit(0);
		}
		
		//-----------------initialize for matrix
		for (r = 0; r < ROW; r++)
		{
			for (c = 0; c < COL; c++)
			{
				this->set(r, c) = 0;
			}
		}
		//-----------------
	};

	//---------------------------- Deconstructor
	~Matrix() { delete[] array; }

	//----------------------------   Use to get value of Matrix
	inline uint8 at(int pos_row, int pos_col)
	{
		return array[index(pos_row, pos_col)];
	}
	//---------------------------- Be used to set value for Matrix
	inline uint8 &set(int pos_row, int pos_col)
	{
		return array[index(pos_row, pos_col)];
	}

protected:
	inline uint32 index(int pos_row, int pos_col)
	{
		return pos_col + col * pos_row;
	}
};

//========================================== Matrix CLASS 
class Matrix16
{
private:
	uint16* array;
	uint16 col;

public:

	//---------------------------- Constructor
	Matrix16()
	{
		col = COL;            // number of colum of defaut image
		array = new(std::nothrow) uint16[ROW * COL];
		if (!array)
		{
			std::cout << "Array allocation failed!\n";
			exit(0);
		}
	};

	//---------------------------- Deconstructor
	~Matrix16() { delete[] array; }

	//----------------------------   Use to get value of Matrix
	uint16 at(int pos_row, int pos_col)
	{
		return array[index(pos_row, pos_col)];
	}
	//---------------------------- Be used to set value for Matrix
	uint16& set(int pos_row, int pos_col)
	{
		return array[index(pos_row, pos_col)];
	}

protected:
	uint32 index(int pos_row, int pos_col)
	{
		return pos_col + col * pos_row;
	}
};




//==========================================
class Matrix_dbfl
{
private:
	dbfl* array;
	uint16 col;

public:

	//---------------------------- Constructor
	Matrix_dbfl()
	{
		col = COL;            // number of colum of defaut image
		array = new(std::nothrow) dbfl[ROW * COL];
		if (!array)
		{
			std::cout << "Array allocation failed!\n";
			exit(0);
		}
	};

	//---------------------------- Deconstructor
	~Matrix_dbfl() { delete[] array; }

	//----------------------------   Use to get value of Matrix
	dbfl at(int pos_row, int pos_col)
	{
		return array[index(pos_row, pos_col)];
	}
	//---------------------------- Be used to set value for Matrix
	dbfl& set(int pos_row, int pos_col)
	{
		return array[index(pos_row, pos_col)];
	}

protected:
	uint32 index(int pos_row, int pos_col)
	{
		return pos_col + col * pos_row;
	}
};
//========================================== img_pro CLASS
class img_pro
{
private:
	void thin_step1(Matrix& img);
	void thin_step2(Matrix& img);
	void thin_step2_cd1(Matrix& img);
	void thin_step2_cd2(Matrix& img);
	void thin_step3(uint8 IMG[ROW][COL]);

public:

		
	uint8	read_txtIMG(Matrix& Img_re, Matrix& Img_gr, Matrix& Img_bl, PATH& Path_re, PATH& Path_gr, PATH& Path_bl);
	uint8	read_txtIMG(Matrix &IMG_gray, PATH &path_gray);
	uint8   read_txtIMG(Matrix16& IMG_gray, PATH& path_gray);
	uint8	read_txtIMG(dbfl IMG[ROW][COL]);
	uint8	read_txtIMG(Mat& img_re,
						Mat& img_gr,
						Mat& img_bl,
						PATH& Path_re,
						PATH& Path_gr,
						PATH& Path_bl);
						
	uint8	read_txtIMG(_Matrix_& Img_re,
						_Matrix_& Img_gr,
						_Matrix_& Img_bl,
						PATH& Path_re,
						PATH& Path_gr,
						PATH& Path_bl);

	uint32	compare_2matrix(Matrix& img_ori);
	uint32  compare_2matrix(Matrix16& img_ori);
	uint32  compare_2matrix(uint8 img_ori[ROW][COL]);
	uint32	compare_2matrix(uint8 IMG1[ROW][COL], uint8 IMG2[ROW][COL]);

	void	print_matrix(uint8 IMG[ROW][COL]);
	void	print_matrix(dbfl IMG[ROW][COL]);
	void	print_matrix(Matrix &img);

	void Sub_image(	Matrix& Img_re, Matrix& Img_gr, Matrix& Img_bl,
					Matrix& re_bgr, Matrix& gr_bgr, Matrix& bl_bgr, uint8 ADJUST);
				
	void Sub_image(	Mat& img_re, Mat& img_gr, Mat& img_bl,
					Mat& re_bgr, Mat& gr_bgr, Mat& bl_bgr, uint8 ADJUST);
					
	void Sub_image(	Matrix& Img_re, Matrix& Img_gr, Matrix& Img_bl,
					Matrix& re_bgr, Matrix& gr_bgr, Matrix& bl_bgr,
					Matrix& out_re, Matrix& out_gr, Matrix& out_bl, uint8 ADJUST);
	void Sub_image(	Matrix& Img_re, Matrix& Img_gr, Matrix& Img_bl,
					Matrix& re_bgr, Matrix& gr_bgr, Matrix& bl_bgr,
					Matrix& out_re, Matrix& out_gr, Matrix& out_bl);
					
	void Sub_image(	_Matrix_& Img_re, _Matrix_& Img_gr, _Matrix_& Img_bl,
					_Matrix_& re_bgr, _Matrix_& gr_bgr, _Matrix_& bl_bgr, uint8 ADJUST);

	uint8 erosion_square2x2(Matrix& img);
	uint8 remove_sm_obj(Matrix& img, Matrix16& Img_lbl,uint16 Thr,uint8 cut_bd);

	uint8 get_automatic_thres_Otsu(Matrix& img);
	void  Gaussian_filter(Matrix& img, uint8 size_kernel, dbfl sigma);
	uint16 Cc_label(Matrix& img, Matrix16& Img_label, uint8 cut_bd);
	uint8 pre_evaluation(	Matrix	&img_bi,								//input binary image with background 0 and foreground 1
							Matrix16 &Img_label,
							uint16	&nb_object,							// number of objects
							uint16	&nb_obj_eva,							// number of meaningful objects
							uint16  order_lable[100],					// contain the order of obj after the process
							Matrix	&Border_img,							// img_border);
							uint16  arr_posi_obj[ROW_POSI_SINGLE][2],
							uint16  center_pxl[100][2]);
							
	void thining_algorithm(Matrix& img);
	void eliminate_noise_line(	uint16		del_val,
								Matrix		&img_border,
								Matrix16	&img_label,
								uint32		&x_coor_noise,
								uint32		&y_coor_noise);

	uint8 Explore_border_single(Matrix& IMG_Bdlc,							//Input: image border local
								uint32& ixd_arr_psobj,						// Input: Contain the current pointer of arr_posi_obj
								uint16  x_cur,								// Input:the current x position 	
								uint16  y_cur,								// Input: the current y position 
								uint16  arr_posi_obj[ROW_POSI_SINGLE][2],	// Output: using to store position of pxls)	
								//uint16	center_pxl[100][2],					// Output: contain the position of center pixel
								uint32& center_row,						// Output: contain the temporary row center
								uint32& center_col);			
	
	void invert_binary_img(Matrix& img);
	uint8 rm_border_obj(Matrix& ImgBi, Matrix16 &Img_lbl);
	
};


#endif // PHYSICS_H
