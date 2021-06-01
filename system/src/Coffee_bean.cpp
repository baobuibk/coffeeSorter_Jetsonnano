/***************************************************
 * Coffee_bean_main.cpp
 * Created on: Aug 19, 2019
 * Author: ducan
 * 
 * The result is organized as following:
 * 
 * Index    0   1     2       3
 *          x1  y1   color1   shape1
 *          x2  y2   color2   shape2
 *              ....
 *          xn  yn   colorn   shapen
 * where n = 500
 **************************************************/

//#include "Coffee_bean.h"

#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "Coffee_bean.hpp"
#include "uart.h"
#include <time.h>
#include <iostream> 

#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>



//-------------- Variable for process
const char *semName = "abc";            // Semaphore name used for synchronizing

//-------------- Variable for thread
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;	//Initialize the value for mutex



//=============================================== global
uint16    		arr_posi_obj[ROW_POSI_SINGLE][2];       // Contain positions of border pixels
uint16 			gpio = GPIO_RST_TIMER;
external_devices 	de_cfbean;			   	// declare variable for external_devices class	
uint8	volatile 	cap_flag=0;

cv::Mat  		image(ROW,COL,CV_8UC3);                 // Using to store image and exchange data bettwen 2 threads




//===================================
//     	TIMER HANDLER
//
//===================================
void timer_handler(int)
{
        static uint16   clk=0;
        clk++;
        //---------------------------
        //rst if get 50000 clk
        //---------------------------

        if (clk==50000)
        {
                clk = 0;
                de_cfbean.gpio_set_value(GPIO_RST_TIMER,0);
        }
        else    de_cfbean.gpio_set_value(GPIO_RST_TIMER,1);

        if ((clk%2500) == 0) // 0,05s->500 , 250-> 0.025 (40 frames per second)
        {
                cap_flag = 1;           //50ms
        }
}



//===================================
//	    PARENT PROCESS
//	USING TO CONTROL TIMER
//
//===================================

void parent(void)
{
	//--------------------------------------
	// 	DECLARE
	//--------------------------------------

	struct sigaction sa;

	sem_t *sem_id = sem_open(semName, O_CREAT,0600,0);
	
	if (sem_id == SEM_FAILED)
	{
		perror("Parent   : [sem_open] Failed\n"); 
		return;
	}
	printf("Parent Semaphore was opened\n");
	

	//--------------------------------------
	// 	CONFIG GPIO
	//--------------------------------------	

	de_cfbean.gpio_export(GPIO_RST_TIMER);          //enable to export gpio
        de_cfbean.gpio_set_dir(GPIO_RST_TIMER,DIR_OUT);           //set direction of gpio
	
	
	//--------------------------------------
	// 	CONFIG INTERUPT
	//--------------------------------------
	//de_cfbean.config_interrupt(paddr_int);

        sigemptyset(&sa.sa_mask);
        sa.sa_flags     = 0;
        sa.sa_handler   = &timer_handler;                 // address of handler
        sigaction (SIGALRM, &sa, NULL);

        
	
	//--------------------------------------
	// 	CONFIG TIMER
	//--------------------------------------

	de_cfbean.config_timer_us(100);                 //100us
        de_cfbean.enable_timer();

	while(1)
	{
		//--------------------------------------
		//  SEND A SEMAPHORE SIGNAL TO CAPTURE
		//--------------------------------------

		if(cap_flag ==1)
		{
			cap_flag = 0;
	//		printf("Prepare to capture!\n");
			if (sem_post(sem_id) < 0)
                		printf("Parent   : [sem_post] Failed \n");
			//std::cout<<"Send semaphore ok!"<<std::endl;
		}
	}


	//--------------------------------------
	// 	CLOSE AND UNLINK SEMAPHORE
	//--------------------------------------


	if (sem_close(sem_id) !=0)
	{
		perror("Child  : [sem_close] Failed\n"); 
		return;
	}
	
	if (sem_unlink(semName) < 0)
	{
		printf("Child  : [sem_unlink] Failed\n"); 
		return;
	}
}

//===================================
//	    CAPTURE THREAD
//	USING TO CAPTURE IMAGE
//
//===================================

void *capture_img_thread(void* arg)
{
	//--------------------------------------
	// 		DECLARE
	//--------------------------------------

	cv::VideoCapture    	cap;					// Using for capturing img
	cv::Mat  		frame(ROW_CAM, COL_CAM, CV_8UC3);	// Using to store the image after captured
	clock_t start_time = 0,  end_time = 0;
	static uint16 count_frame = 0;


	//--------------------------------------
	// 	OPEN AND SET UP CAMERA
	//--------------------------------------
	
	printf("Camera will open soon... \n");
	cap.open(0 + cv::CAP_V4L2);
	cap.set(cv::CAP_PROP_FOURCC,cv::VideoWriter::fourcc('M','J','P','G'));

	cap.set(cv::CAP_PROP_FRAME_WIDTH, COL_CAM);	// set the resolution for camera. In this case, Column = 640
	cap.set(cv::CAP_PROP_FRAME_HEIGHT,ROW_CAM); 	// Row = 480
	
	printf("Open camera ok!!!\n");



	if (cap.isOpened()== true)  //check if we succeeded
		printf("Camera was opened. Please wait ...\n");
	else
		printf("Get error when open camera\n");
	
	printf("loading...\n");
	cv::waitKey(2000);				// waiting to open whole camera
	printf("Ready to capture!");	

	//--------------------------------------
	// 	      OPEN SEMAPHORE
	//
	//--------------------------------------

	sem_t *sem_id = sem_open(semName, O_CREAT,0600,0);
	
	if (sem_id == SEM_FAILED)
	{
		perror("Child   : [sem_open] Failed\n"); 
		pthread_exit(0);
	}
	
//	printf("Child Semaphore was opened ok!\n");



	//--------------------------------------
	// 	  LOOP FUNCTION TO GET IMAGE
	//
	//--------------------------------------

	while(true)
        {
		//--------------------------------------
		// Wait and block untill recieving 
		// the unlock signal from parent process
		//
		//--------------------------------------

		if (sem_wait(sem_id) < 0)
        		printf("Child   : [sem_wait] Failed \n");
		
		//--------------------------------------
		// Using mutex during reading, storing 
		// and resizing image into image
		// -------------------------------------
		
		
//		start_time = clock();

		pthread_mutex_lock(&mtx);	

		cap.read(frame);	
		cv::resize(frame,image,image.size(),0.5,0.5,cv::INTER_AREA);	//resize the image size 
		count_frame = (count_frame >= 50000)?0:count_frame+1;
                pthread_mutex_unlock(&mtx);

		printf("%d \n",count_frame);

		// Measure timer
//		end_time = clock();

//		float seconds = (float)(end_time - start_time)/CLOCKS_PER_SEC;
//		printf("time = %4f \n",seconds);

        }
 	pthread_exit(0);
}


		
//===================================
//	   IMG_PROCESSING THREAD
//   USING TO PROCESS THE IMG AFTER CAPTURED
//
//===================================

void *img_processing_thread(void* arg)
{
     	cv::Vec3b *ptr;
	
/*	
	_Matrix_    img_re1(ROW,COL);
    	_Matrix_    img_gr1(ROW, COL);
    	_Matrix_    img_bl1(ROW, COL);
	_Matrix_    re_bgr1(ROW, COL);
    	_Matrix_    gr_bgr1(ROW, COL);
    	_Matrix_    bl_bgr1(ROW, COL);

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= Declare for OpenCV
	Mat             img_re2(ROW, COL, CV_8UC1);
	Mat             img_gr2(ROW, COL, CV_8UC1);
	Mat             img_bl2(ROW, COL, CV_8UC1);
	*/
	Mat             re_bgr_cv(ROW_CAM, COL_CAM, CV_8UC1);
	Mat             gr_bgr_cv(ROW_CAM, COL_CAM, CV_8UC1);
	Mat             bl_bgr_cv(ROW_CAM, COL_CAM, CV_8UC1);
	
	Mat             re_bgr_cv_rs(ROW, COL, CV_8UC1);
	Mat             gr_bgr_cv_rs(ROW, COL, CV_8UC1);
	Mat             bl_bgr_cv_rs(ROW, COL, CV_8UC1);

     	//--------------------------------------
	//      	DECLARE
	//
	//--------------------------------------
	uint16   	r,c;				    // row and col variable	
	uint16          center_pxl[100][2];                 // contain the center of pxl
//	uint16          result[500][4];                     // store results after processing
//	uint16 		time_send[100];
//	uint8		channel_send[100];

	Matrix          re_bgr;                             // red background
	Matrix          gr_bgr;                             // green background
	Matrix          bl_bgr;                             // blue background

	Matrix		img_re;                             // Red channel
	Matrix	    	img_gr;                             // Green channel
 	Matrix	    	img_bl;                             // Blue channel

	Matrix          Img_Bi;                             // Be used to store Binary image
 	Matrix          Border_img;                         // Be used to store Border pixels

	Matrix16        Img_label;
	Matrix16        Img_label_rm_smobj;

 	uint16          order_label[200];                   // Contain the order of obj after the processing
	uint16 		nb_object = 0;                      	// Store the number of entire objects, using to send all data to kit
	uint16          nb_obj_eva = 0;                     // Store the number of meaningfull objects that is not broken or so on...

	img_pro 	img_pro_cfbean;                     	// Object for class imagpe processing library
	Algorithm_Cfbean    alg_cfbean;                     // Object is used for Algorithm class (Algorithm, Open_Camera, Hardware class)

	Uart 		cf_Uart;
	uint16 		time_test=0;
  
	
	
	//--------------------------------------
	//    PATH OF BACKGROUND AND TXT IMG
	//
	//--------------------------------------


	PATH		    path_re =	"src/img_processing_library/Sample_txt/RGB_Red1.txt";
    	PATH		    path_gr =	"src/img_processing_library/Sample_txt/RGB_Green1.txt";
    	PATH		    path_bl =	"src/img_processing_library/Sample_txt/RGB_Blue1.txt";

    	//------------------------ Background
    	PATH            path_re_bgr = "src/img_processing_library/Sample_txt/background_red.txt";
    	PATH            path_gr_bgr = "src/img_processing_library/Sample_txt/background_green.txt";
    	PATH            path_bl_bgr = "src/img_processing_library/Sample_txt/background_blue.txt";

	
	if (img_pro_cfbean.read_txtIMG(re_bgr_cv, gr_bgr_cv, bl_bgr_cv, path_re_bgr, path_gr_bgr, path_bl_bgr) == _OK_)  
	{
		cv::resize(re_bgr_cv,re_bgr_cv_rs,re_bgr_cv_rs.size(),0.5,0.5,cv::INTER_AREA);    //resize the image size
		cv::resize(gr_bgr_cv,gr_bgr_cv_rs,re_bgr_cv_rs.size(),0.5,0.5,cv::INTER_AREA);    //resize the image size
		cv::resize(bl_bgr_cv,bl_bgr_cv_rs,re_bgr_cv_rs.size(),0.5,0.5,cv::INTER_AREA);    //resize the image size
		
		for (r=0; r<ROW; r++)
		{
			for (c=0;c<COL;c++)
			{
				re_bgr.set(r,c) = re_bgr_cv_rs.at<uchar>(r,c);
				gr_bgr.set(r,c) = gr_bgr_cv_rs.at<uchar>(r,c);
				bl_bgr.set(r,c) = bl_bgr_cv_rs.at<uchar>(r,c);

			}
		}


		printf("Reading background successfull\n");

	}
    	else
    	{
        	printf("Reading background failed, please check again! Thanks\n");
        	exit(0);
    	}
	
     
	//--------------------------------------
	// 	   PROCESSING ALGORITHM
	//
	//--------------------------------------
	while (true)
        {

		//--------------------------------------
		// 	Get data from general buffer   
		//
		//--------------------------------------
                pthread_mutex_lock(&mtx);	//block 
	        
		for (r=0;r<ROW;r++)
		{
			ptr = image.ptr<cv::Vec3b>(r);
			for(c=0;c<COL;c++)
			{
				img_re.set(r,c) = ptr[c][2];
				img_gr.set(r,c) = ptr[c][1];
				img_bl.set(r,c) = ptr[c][0];
			}
		}
		
		pthread_mutex_unlock(&mtx);	// unblock


		//--------------------------------------
		// 	Main algorithm   
		//
		//--------------------------------------
		//--------------Sub image
		img_pro_cfbean.Sub_image(img_re, img_gr, img_bl, re_bgr, gr_bgr, bl_bgr, 40);		
		
		//--------------Segmentation 
		alg_cfbean.Coffee_Segmentation(img_re, img_gr, img_bl, Img_Bi, img_pro_cfbean, Img_label_rm_smobj);
 		
		//--------------Pre-evaluation
		img_pro_cfbean.pre_evaluation(Img_Bi, Img_label, nb_object, nb_obj_eva, order_label, Border_img, arr_posi_obj, center_pxl);
		
		//--------------Evaluation image
//		alg_cfbean.features_evaluation(img_re, Img_label, nb_object, order_label, result, arr_posi_obj, alg_cfbean);


		//-------------- Printf center point
		for (uint8 i = 0; i < nb_object; i++)
		{
//			printf("%d \n", order_label[i]);
			printf("%d  %d\n", center_pxl[i][0], center_pxl[i][1]);
		}

		/*
		float seconds = (float)(end_time - start_time)/CLOCKS_PER_SEC;
		printf("time = %4f \n",seconds);
		*/
		//---------------Using to transfer to Uart
		/*
		//de_cfbean.calculate_2kit(center_pxl,time_send,channel_send);
		for (uint16 ii=0;ii<nb_object;ii++)
		{
			cf_Uart.Uart2kit(time_send[ii],channel_send[ii]);   //row 0 contains time, row 1 store channel

		}
		*/
                
        }
        pthread_exit(0);
}


//===================================
//		CHILD
//	USING TO PROCESS IMAGE
//       (CAPTURE AND PROCESS)
//===================================

void child(void)
{

	pthread_t CAP_THREAD,IMG_PRO_THREAD;		// Using to create 2 threads


	//--------------------------------------
	// 	Creating 2 threads
	//
	//--------------------------------------
	
	if ( pthread_create(&CAP_THREAD,NULL,capture_img_thread,NULL) != 0)
		printf("pthread_create at CAP_THREAD fail!!");

	if ( pthread_create(&IMG_PRO_THREAD,NULL,img_processing_thread,NULL) != 0)
		printf("pthread_create at IMG_PRO_THREAD fail!!");

	if (pthread_join(CAP_THREAD, NULL) != 0)
		printf("Escape capture thread was failed!!!");

	if (pthread_join(IMG_PRO_THREAD, NULL) != 0)
		printf("Escape image processin thread was failed!!");

	exit(EXIT_SUCCESS);

}



//===============================================
//		MAIN FUNCTION
//
//===============================================

int main()
{
	pid_t pid;

	pid = fork();

	if(pid == -1)
	{
		printf("Get error when creating a new process");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)	//child
	{
		child();		
	}

	else			//parent
	{
		int status;
		parent();
		wait(&status);		
	}
	return 0;

}


