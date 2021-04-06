/*
 * Coffee_bean_main.c
 *
 *  Created on: Aug 19, 2019
 *      Author: ducan
 *  Last modify by: ducan
 *  Date: April 6, 2021
 */
#include "Coffee_bean.hpp"
#include <stdio.h>
//#include <time.h>
#include <opencv2/opencv.hpp>
#include <signal.h>
#include <sys/time.h>

//using namespace cv;
//=============================================== global

/*
dbfl 	 result[NUM_LIMIT_OBJ][4];
uint16   posi_single[ROW_POSI_SINGLE][2];		        // contain pixels position
//uint16   DUPLI_POS_MT[MAX_MT_POS][3];
uint8 	 IMG_1[ROW][COL];
uint8 	 IMG_2[ROW][COL];
uint8 	 IMG_3[ROW][COL];
uint8    IMGBi[ROW][COL];					// Segmentation and binary image

//This global value is used in "check_shape_color" function
//dbfl   img1_sgm[ROW][COL];					// use for determining color
//dbfl   img2_sgm[ROW][COL];
//dbfl   img3_sgm[ROW][COL];
uint8   img_check[ROW][COL];					// use for checking color
uint8  	IMG_Bdlc[ROW][COL];                           		// Image border local
dbfl    L[ROW][COL];
dbfl	a[ROW][COL];
dbfl   	b[ROW][COL];

uint8	flag_timer = 0;

int   check=1;

*/

//===============================================

int main(int argc, char *argv[])
{
/************ Check version for openCV
	std::cout << "OpenCV version : " << CV_VERSION << std::endl;
        std::cout << "Major version : " << CV_MAJOR_VERSION << std::endl;
        std::cout << "Minor version : " << CV_MINOR_VERSION << std::endl;
        std::cout << "Subminor version : " << CV_SUBMINOR_VERSION << std::endl;
*************/

	printf("camera will open soon... \n");

/*
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= Declare
	uint16 		size_sum_lsp    = 0;             	  // size of sum of single positions ( include starting flag)
	uint8 		nb_object       = 0;
	uint8		result_gb       = 0;			  // Returned value to check result is bad or good
	uint8   	check_err_Seg   = 0;
	clock_t 	start_time=0,end_time=0;
	uint32 		r,c;
	uint8 		B[ROW][COL],G[ROW][COL],R[ROW][COL];
	

//	uint16 		ploop = 0;
	dbfl  		ptimer =0;
	dbfl    	sumtimer= 0;
	uint16  	loop1 = 0;
	dbfl  		max = 0;

	uint8	  	count=0;

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= Get camera
	cv::Mat  	frame(ROW_CAM, COL_CAM, CV_8UC3);
	cv::Mat  	image(ROW,COL,CV_8UC3);
	cv::Mat  	Lab_img;
	cv::Vec3b 	*ptr;
	cv::Vec3b 	*pLab;
*/	
	//---------------Set up parameters for camera 
	printf("Camera is about to open... \n");
	printf("Please wait...\n");
	cv::VideoCapture cap;  				// initialize for camera	
	cap.open(0 + cv::CAP_V4L2);
	cap.set(cv::CAP_PROP_FOURCC,cv::VideoWriter::fourcc('M','J','P','G'));

	cap.set(cv::CAP_PROP_FRAME_WIDTH, COL_CAM);	// Set the resolution for camera. In this case, Column = 640
	cap.set(cv::CAP_PROP_FRAME_HEIGHT,ROW_CAM); 	// and Row = 480
	//cap.set(cv::CAP_PROP_FPS,120);
	printf("Get camera ok!!!\n");

	//---------------Open camera here
	if (cap.isOpened()== true)  //check if we succeeded
		printf("Camera was opened. Please wait ...\n");
	else
		printf("Get error when open camera\n");
	
	printf("Loading...\n");
	cv::waitKey(2000);				// waiting to open whole camera
	printf("Ready to capture!");
	

	//---------------Open and test camera for the first time
	cap.read(frame);
	cv::resize(frame,image,image.size(),0.5,0.5,cv::INTER_AREA);	
	ptr = frame.ptr<cv::Vec3b>(0);
	
	for (r=0;r<ROW;r++)
	{
		ptr = image.ptr<cv::Vec3b>(r);
		for(c=0;c<COL;c++)
		{
			B[r][c] = ptr[c][0];
			G[r][c] = ptr[c][1];
			R[r][c] = ptr[c][2];
		}
	}


	write_img2txt(R,RED_);
	write_img2txt(G,GREEN_);
	write_img2txt(B,BLUE_);
	printf("Success when writting\n");	
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= SET UP TIMER and HANDLER
	//------------------------Install timer_handler as the signal handler for SIGNTALRM
	struct sigaction sa;
	memset(&sa,0,sizeof(sa));
	sa.sa_handler = &timer_handler;
	sigaction(SIGALRM, &sa, NULL);
	
	//------------------------Config timer.... detail can reference at "https://www.informit.com/articles/article.aspx?p=23618&seqNum=14"
	struct itimerval timer;
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 60000;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 60000;
	setitimer(ITIMER_REAL, &timer, NULL);

	//=============================================MAIN FUNCTION
	while(1)
	{
		if (flag_timer == ENABLE)
		{
			//------------------------ DISABLE flag of timer_handler
			flag_timer = DISABLE;
		 	printf("Value timer at %d\n",++count);
	
			//------------------------ initializing for timer to count algorithm processing time
//			start_time = 0;
//			end_time   = 0;

//			start_time = clock();

			//------------------------ read frame from camera directly
			cap.read(frame);	
			cv::resize(frame,image,image.size(),0.5,0.5,cv::INTER_AREA);	//resize the image size 
			cv::cvtColor(frame,Lab_img,cv::COLOR_BGR2Lab);			//converting RGB to CIE color space 	
	
			for (r=0;r<ROW;r++)						//take image into array
			{
				ptr = image.ptr<cv::Vec3b>(r);
				pLab= Lab_img.ptr<cv::Vec3b>(r);
				for(c=0;c<COL;c++)
				{
					IMG_1[r][c] = ptr[c][2];
					IMG_2[r][c] = ptr[c][1];
					IMG_3[r][c] = ptr[c][0];
					L[r][c]     = pLab[c][0];
					a[r][c]     = pLab[c][1];
					b[r][c]	    = pLab[c][2];
				}
			}
			//------------------------ Segmentate for image
			check_err_Seg = Segmentation_RGB(IMG_1,IMG_2,IMG_3,IMGBi);
 				
			//------------------------ Check shape and color
			if (check_err_Seg == OK_)
			{
				Explore_border(IMGBi, &nb_object,&size_sum_lsp, 
					posi_single,IMG_Bdlc);

				if (nb_object !=0)
				{
					ptimer = 0;
					result_gb = check_shape_color(IMG_1,IMG_2,IMG_3,
							      posi_single,&nb_object,
							      result,img_check,&ptimer,
							      L,a,b);
				}	
				else
				{	
					result_gb = 0;
//			printf("result = bad \n");

/*
//	            	for (uint8 i=0;i< MAX_MT_POS; i++){
//	                	DUPLI_POS_MT[i][0] = 0;
//	                	DUPLI_POS_MT[i][1] = 0;
//	                	DUPLI_POS_MT[i][2] = 0;
//	            	}
//
*/	         
				}	
			}
			else continue;
/*
//			end_time = clock();
//			float seconds = (float)(end_time - start_time)/CLOCKS_PER_SEC; 		
//			printf("time = %4f \n",seconds);
//			if (++loop1 >150)
//				break;
//			else
//			{
				(seconds>max)?max=seconds:max=max;
			 	sumtimer += seconds;
			}
*/	
		}
		printf("end here\n");
		if (count == 40) break;
	}

	cap.release();
	
	return result_gb;

}
