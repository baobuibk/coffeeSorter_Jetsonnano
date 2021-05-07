/*
 * Create by: Duc An Nguyen
 * Date on: 5/4/2021 
 *
 *
 * This function is used for communicating with external devices
 * It consist of three parts: open camera, Uart and timer. 
 */


#ifndef EXTERNAL_HEADER
#define EXTERNAL_HEADER

#include "type.h"
#include <opencv2/opencv.hpp>
#include <signal.h>
#include <sys/time.h>

//==================================
//INCLUDE FOR GPIO
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

#include<unistd.h>
//==================================
//DEFINE FOR GPIO

#define COL_CAM 640			//size of the global camera
#define ROW_CAM 480

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define POLL_TIMEOUT (3 * 1000) 	/* 3 seconds */
#define MAX_BUF 64

#define GPIO_RST_TIMER 168              //PIN 32 onboard
#define GPIO_38         38              //PIN 33 onboard
//... so on, defind again GPIO and UART pin for header.

#define DIR_OUT         1
#define DIR_IN          0



class external_devices
{
	public:
		//---------------------
		//Camera functions
		uint8 open_camera(cv::VideoCapture &cap);
		

		//---------------------
		//GPIO functions
		int gpio_export(unsigned int gpio);
		int gpio_unexport(unsigned int gpio);
		int gpio_set_dir(unsigned int gpio, unsigned int out_flag);
		int gpio_set_value(unsigned int gpio, unsigned int value);
		int gpio_get_value(unsigned int gpio, unsigned int *value);
		int gpio_set_edge(unsigned int gpio, char *edge);
		int gpio_fd_open(unsigned int gpio);
		int gpio_fd_close(int fd);

		//---------------------
		//Timer functions
		int config_timer_us(uint16 value);
		int enable_timer();
		int disable_timer();
	
		//---------------------
		//Determine position and time to send to Jetson
		uint8 calculate_2kit(	uint16 center_pxl[100][2],
                                      	uint16 time_send[100],
                                      	uint8 channel_send[100]);


		//---------------------
		//Interrupt functions
		
//		int config_interrupt(void *paddr);

	private:
		struct itimerval timer;			//using for timer
//		struct sigaction sa;			// using for interupt	

};



#endif
