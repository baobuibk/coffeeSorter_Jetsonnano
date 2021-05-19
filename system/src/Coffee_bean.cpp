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
//=============================================== global
uint16    		arr_posi_obj[ROW_POSI_SINGLE][2];       // Contain positions of border pixels
uint16 			gpio = GPIO_RST_TIMER;
external_devices 	de_cfbean;			   	// declare variable for external_devices class	
uint8	volatile 	cap_flag=0;
//uint16 			clk = 0;

//===============================================
// 	This function is used for timer interupt
//
// ==============================================

void timer_handler(int)
{
	static uint16	clk=0;
	clk++;
	//---------------------------
	//rst if get 50000 clk
	//---------------------------
	
	if (clk==50000)
	{
		clk = 0;
 		de_cfbean.gpio_set_value(gpio,0);
	}
	else	de_cfbean.gpio_set_value(gpio,1);

	if ((clk%10000) == 0) // 0,05s->500 , 
	{
		cap_flag = 1; 		//50ms
//		printf("clk: %d\n",clk);
	}	
//	printf("%d\n",clk);
}



//===============================================
//		MAIN FUNCTION
//
//===============================================

int main()
{
	
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
	Mat             re_bgr2(ROW, COL, CV_8UC1);
	Mat             gr_bgr2(ROW, COL, CV_8UC1);
	Mat             bl_bgr2(ROW, COL, CV_8UC1);
*/

	clock_t start_time=0,end_time=0;
	uint8 	loop=0;
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= Declare
    	//------------------------ 
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
	uint16 		nb_object = 0;                      // Store the number of entire objects, using to send all data to kit
	uint16          nb_obj_eva = 0;                     // Store the number of meaningfull objects that is not broken or so on...
 
	img_pro 	img_pro_cfbean;                     // Object for class imagpe processing library
	Algorithm_Cfbean    alg_cfbean;                     // Object is used for Algorithm class (Algorithm, Open_Camera, Hardware class)
	cv::VideoCapture    cap;	
 	struct sigaction sa;
	Uart 		cf_Uart;
	uint16 		time_test=0;

	//========================Using for openCV
	cv::Mat  frame(ROW_CAM, COL_CAM, CV_8UC3);
	cv::Mat  image(ROW,COL,CV_8UC3);
//	cv::Mat  Lab_img;
	cv::Vec3b *ptr;
//	cv::Vec3b *pLab;

	uint16 r,c;

     	
    	PATH		    path_re =	"src/img_processing_library/Sample_txt/RGB_Red1.txt";
    	PATH		    path_gr =	"src/img_processing_library/Sample_txt/RGB_Green1.txt";
    	PATH		    path_bl =	"src/img_processing_library/Sample_txt/RGB_Blue1.txt";

    	//------------------------ Background
    	PATH            path_re_bgr = "src/img_processing_library/Sample_txt/background_red.txt";
    	PATH            path_gr_bgr = "src/img_processing_library/Sample_txt/background_green.txt";
    	PATH            path_bl_bgr = "src/img_processing_library/Sample_txt/background_blue.txt";

	
	if (img_pro_cfbean.read_txtIMG(re_bgr, gr_bgr, bl_bgr, path_re_bgr, path_gr_bgr, path_bl_bgr) == _OK_)  
        	printf("Reading background successfull\n");
    	else
    	{
        	printf("Reading background failed, please check again! Thanks\n");
        	exit(0);
    	}
	
	
	
	
	
	//--------------------------
	//set up camera
	//--------------------------
    	de_cfbean.open_camera(cap);	
	
	//--------------------------
	//set up gpio
	//--------------------------
	de_cfbean.gpio_export(gpio);			//enable to export gpio
	de_cfbean.gpio_set_dir(gpio,DIR_OUT);		//set direction of gpio
	
	//--------------------------
	//config interupt
	//--------------------------
//	de_cfbean.config_interrupt(paddr_int);	
				   	
	sigemptyset(&sa.sa_mask);
        sa.sa_flags 	= 0;
        sa.sa_handler 	= &timer_handler;                 // address of handler
        sigaction (SIGALRM, &sa, NULL);

	//--------------------------
	//config timer
	//--------------------------
	de_cfbean.config_timer_us(100); 		//100us
	de_cfbean.enable_timer();		
	
//	cf_Uart.Uart2kit(1000,11);


	while(1)
	{

		
//		start_time = 0;
//		end_time   = 0;
		if(cap_flag == 1)
		{
		//	start_time = clock();
			cap_flag=0;
/*			cap.read(frame);		//get image from camera directly
			cv::resize(frame,image,image.size(),0.5,0.5,cv::INTER_AREA);	//resize the image size 
			
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
*/			
			
	
//		start_time = 0;
//		end_time   = 0;

		/*
			if(img_pro_cfbean.read_txtIMG(img_re, img_gr, img_bl, path_re, path_gr, path_bl) == _OK_)
			{	
			
			img_pro_cfbean.Sub_image(img_re, img_gr, img_bl, re_bgr, gr_bgr, bl_bgr, 40);	
			
			alg_cfbean.Coffee_Segmentation(img_re, img_gr, img_bl, Img_Bi, img_pro_cfbean, Img_label_rm_smobj);
 			
			img_pro_cfbean.pre_evaluation(Img_Bi, Img_label, nb_object, nb_obj_eva, order_label, Border_img, arr_posi_obj, center_pxl);
        	*/
			//
		//	end_time = clock();

//			alg_cfbean.features_evaluation(img_re, Img_label, nb_object, order_label, result, arr_posi_obj, alg_cfbean);
		
			printf("here  %d\n",loop++);
			//std::cout<<nb_object<<"here"<<std::endl;	
		//	}
			/*	
			for (uint8 i = 0; i < nb_object; i++)
			{ 
	//			printf("%d \n", order_label[i]);
				printf("%d  %d\n", center_pxl[i][0], center_pxl[i][1]);
			}
			

		//	}	

		*/	
		/*
			float seconds = (float)(end_time - start_time)/CLOCKS_PER_SEC; 		
			printf("time = %4f \n",seconds);
			if (loop++ == 20) break;
		*/
			//=========================Using to transfer to Uart
			/*
			//de_cfbean.calculate_2kit(center_pxl,time_send,channel_send);
			for (uint16 ii=0;ii<nb_object;ii++)
			{
				cf_Uart.Uart2kit(time_send[ii],channel_send[ii]);   //row 0 contains time, row 1 store channel
				
			}*/
				
		}
		//pause();
	
	}

	return 0;

}
