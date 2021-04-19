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



//=============================================== global
uint16    		arr_posi_obj[ROW_POSI_SINGLE][2];       // Contain positions of border pixels
uint16 			gpio = GPIO_RST_TIMER;
external_devices 	de_cfbean;			   	// declare variable for external_devices class	
uint8	volatile 	cap_flag=0;
uint16 			clk = 0;

//===============================================
// 	This function is used for timer interupt
//
// ==============================================

void timer_handler(int)
{
//	static uint16	clk=0;
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

	if ((clk%50) == 0) //500
	{
		cap_flag = 1; 		//50ms
		printf("clk: %d\n",clk);
	}	
//	printf("%d\n",clk);
}



//===============================================
//		MAIN FUNCTION
//
//===============================================

int main()
{

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= Declare
    	//------------------------ 
	uint16          result[500][4];                     // store results after processing 
	Matrix          re_bgr;                             // red background
	Matrix          gr_bgr;                             // green background
	Matrix          bl_bgr;                             // blue background

	Matrix		Img_re;                             // Red channel
	Matrix	    	Img_gr;                             // Green channel
 	Matrix	    	Img_bl;                             // Blue channel

	Matrix          Img_Bi;                             // Be used to store Binary image    
 	Matrix          Border_img;                         // Be used to store Border pixels

	Matrix16        Img_label;
    
    
 	uint16          order_label[100];                   // Contain the order of obj after the processing 
	uint16 	    	nb_object = 0;                      // Store the number of meaningful object
 
	img_pro 	img_pro_cfbean;                     // Object for class imagpe processing library
	Algorithm_Cfbean    alg_cfbean;                     // Object is used for Algorithm class (Algorithm, Open_Camera, Hardware class)
	cv::VideoCapture    cap;	
 	struct sigaction sa;
	Uart 		cf_Uart;
	uint16 		time_test=0;

 /*    	
    	PATH		    path_re =	"img_processing_library/Sample_txt/RGB_Red1.txt";
    	PATH		    path_gr =	"img_processing_library/Sample_txt/RGB_Green1.txt";
    	PATH		    path_bl =	"img_processing_library/Sample_txt/RGB_Blue1.txt";

    	//------------------------ Background
    	PATH            path_re_bgr = "img_processing_library/Sample_txt/background_red.txt";
    	PATH            path_gr_bgr = "img_processing_library/Sample_txt/background_green.txt";
    	PATH            path_bl_bgr = "img_processing_library/Sample_txt/background_blue.txt";
*/
	
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
	de_cfbean.config_timer_us(10000); 		//100us
	de_cfbean.enable_timer();		
	
//	cf_Uart.Uart2kit(1000,11);


	while(1)
	{
		if(cap_flag == 1)
		{
			cf_Uart.Uart2kit(clk+(time_test++),5);
			cap_flag = 0;
		
		}
		
	
	}

	return 0;

}
