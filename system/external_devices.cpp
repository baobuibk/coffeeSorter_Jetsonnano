#include "external_devices"
#include <stdio.h>





uint8 external_devices::open_camera(cv::VideoCapture &cap)
{
	uint8 flag_error;
	printf("Camera will open soon! Please wait... \n");


	//	cv::VideoCapture cap;  				// initialize for camera
	cap.open(0 + cv::CAP_V4L2);
	cap.set(cv::CAP_PROP_FOURCC,cv::VideoWriter::fourcc('M','J','P','G'));

	cap.set(cv::CAP_PROP_FRAME_WIDTH, COL_CAM);	// Set the resolution for camera. In this case, Column = 640
	cap.set(cv::CAP_PROP_FRAME_HEIGHT,ROW_CAM); 	// and Row = 480
	//cap.set(cv::CAP_PROP_FPS,120);
	printf("Get camera ok!!!\n");
	
	//---------------Open camera here
	if (cap.isOpened()== true)  //check if we succeeded
	{
		printf("Camera was opened. Please wait ...\n");
		printf("Loading...\n");
		cv::waitKey(2000);				// waiting to open whole camera
		printf("Ready to capture!");
		return true;
	}
	else
	{
		printf("Get error when open camera\n");
		return false;
	}

}


