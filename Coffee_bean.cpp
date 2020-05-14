/*
 * Coffee_bean_main.c
 *
 *  Created on: Aug 19, 2019
 *      Author: ducan
 */
#include "Coffee_bean.h"
#include <stdio.h>
#include <time.h>
#include "opencv2/opencv.hpp"


//using namespace cv;
//=============================================== global

dbfl 	 result[NUM_LIMIT_OBJ][4];
uint16   posi_single[ROW_POSI_SINGLE][2];			 // contain pixels position
uint16   DUPLI_POS_MT[MAX_MT_POS][3];
uint8 	 IMG_1[ROW][COL];
uint8 	 IMG_2[ROW][COL];
uint8 	 IMG_3[ROW][COL];
uint8    IMGBi[ROW][COL];							 // Segmentation and binary image

//This global value is used in "check_shape_color" function
uint8   img1_sgm[ROW][COL];			// use for determining color
uint8   img2_sgm[ROW][COL];
uint8   img3_sgm[ROW][COL];
uint8   img_check[ROW][COL];		// use for checking color
uint8  	IMG_Bdlc[ROW][COL];                           // Image border local

int   check=1;

//===============================================

int main(int argc, char *argv[])
{

	   //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= declare
	uint16 	size_sum_lsp    = 0;               // size of sum of single positions ( include starting flag)
	uint8 	nb_object       = 0;
	uint8	result_gb       = 0;			   // Returned value to check result is bad or good
	uint8   check_err_Seg   = 0;
	uint8   f_read_IMG      = OK_;
	clock_t start_time,end_time;

	cv::Mat  frame(ROW_CAM, COL_CAM, CV_8UC3);
	cv::Mat  image(ROW,COL,CV_8UC3);
	cv::Vec3b *ptr;
//	uint8 B[ROW_CAM][COL_CAM],G[ROW_CAM][COL_CAM],R[ROW_CAM][COL_CAM];
	uint8 B[ROW][COL],G[ROW][COL],R[ROW][COL];

	uint32 r,c;

	cv::VideoCapture cap(0);
	cap.set(cv::CAP_PROP_FRAME_WIDTH, COL_CAM);	// Column = 640
	cap.set(cv::CAP_PROP_FRAME_HEIGHT,ROW_CAM); 	// Row = 480
//	cap.set(cv::CAP_PROP_FPS,30);
	
	if (cap.isOpened()== true)  //check if we succeeded
		printf("Camera was opened. Please wait ...\n");
	else
		printf("Get error when open camera\n");
	cv::waitKey(2000);
//	uint16 loop = 0;
//	while(1)
//	{
//	if (loop++ == 1000)
//		break;

//	cap.read(frame);

	while(1)
	{
	cap.read(frame);					//get image from camera directly
	cv::resize(frame,image,image.size(),0.5,0.5,cv::INTER_AREA);	//resize the image size 

//	p = frame.data;
//	ptr = frame.ptr<cv::Vec3b>(0);

//	cv::Size sz = frame.size();
/*
	imshow("Camera",frame);
		if(cv::waitKey(30) == 's')
		{
			cv::Mat frame2;
			frame2 = frame.clone();
			imshow("capture image",frame2);
		}
		if(cv::waitKey(30) == 'd')
			break;
			
	}

*/


	for (r=0;r<ROW;r++)
	{
		ptr = image.ptr<cv::Vec3b>(r);
		for(c=0;c<COL;c++)
		{
			IMG1[r][c] = ptr[c][2];
			IMG2[r][c] = ptr[c][1];
			IMG3[r][c] = ptr[c][0];
		//	B[r][c] = ptr[c][0];
		//	G[r][c] = ptr[c][1];
		//	R[r][c] = ptr[c][2];
		}
	}


/*
	for (index=0;index<ROW*COL;index++)
	{
		r = index / (COL);
		c = index % (COL);
	//	c *= 3;

		B[r][c]   = ptr[index][0];
		G[r][c+1] = ptr[index][1];
		R[r][c+2] = ptr[index][2];
	}

	write_img2txt(R,RED_);
	write_img2txt(G,GREEN_);
	write_img2txt(B,BLUE_);
	printf("success when writting\n");	
	*/
//	printf("value:",frame[0][0]);
//	setvbuf(stdout, NULL, _IONBF, 0);
//	setvbuf(stderr, NULL, _IONBF, 0);

//	double a=fastPow(3.444,0.33);
	//uint16 i,j;

	start_time = clock();
	//-------------------------------------------- read and segmentation image
//	f_read_IMG = read_IMG_RGB(IMG_1,IMG_2,IMG_3);
//	Test_matrix(IMG_3,1);

//	Test_matrix(IMG_3,1);
//	Test_matrix_sub(IMG_3);
//	Test_matrix(IMG_2);
//	Test_matrix(IMG_3);
	if (f_read_IMG == OK_)
	{
		printf("read IMG OK_! \n");
		check_err_Seg = Segmentation_RGB(IMG_1,IMG_2,IMG_3,IMGBi);
	//	printf("Seg = %d \n ",check_err_Seg);
	//	Test_matrix(IMGBi,1);
	//	Test_matrix_sub(IMGBi);
	    //---------------------- Check shape and color
		if (check_err_Seg == OK_)
		{
			Explore_border(IMGBi, &nb_object,&size_sum_lsp, 
					posi_single,IMG_Bdlc);
			printf("objects = %d \n",nb_object);

			if (nb_object !=0)
			{
				result_gb = check_shape_color(IMG_1,IMG_2,IMG_3,
							      posi_single,&nb_object,
							      result,img1_sgm,img2_sgm,
							      img3_sgm,img_check);
			printf("result = good \n");
			}
		else
		{
			result_gb = 0;
			printf("result = bad \n");
*	
	            for (uint8 i=0;i< MAX_MT_POS; i++){
	                DUPLI_POS_MT[i][0] = 0;
	                DUPLI_POS_MT[i][1] = 0;
	                DUPLI_POS_MT[i][2] = 0;
	            }
	           
		}
		}
	}
	else printf("Error when read IMG");
	end_time = clock();
	float seconds = (float)(end_time - start_time)/CLOCKS_PER_SEC; 		
	printf("time = %4f \n",seconds);
	printf("%d \n",result_gb);

//	for (uint8 k=0;k<=result[0][0];k++)
//	{
//		printf("%.2f     %.2f     %.2f    %.2f \n",result[k][0],result[k][1],result[k][2],result[k][3]);
//	}

	}
	return 0;

}
