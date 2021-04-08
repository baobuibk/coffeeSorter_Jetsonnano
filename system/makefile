CC=g++
CFLAGS=-g -O2 -Wall -std=c++11 -c

#SRCDIR := src
#OBJDIR := bin

OPENCV = `pkg-config opencv4 --cflags --libs`
#OPENCV = -L/opt/opencv_3.2.0/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio\
#	-I/opt/opencv_3.2.0/include/
#	-I/opt/opencv_3.2.0/include/opencv4
LIBS   = $(OPENCV)

VPATH  = img_processing_library                                    #use vpath when using a specific file inside another directory



objects = 	Coffee_bean.o	timer.o \
	   	gpio.o 		open_camera.o	




all : $(objects)
	$(CC)	-o all $(objects) $(LIBS)


Coffee_bean.o :  	Coffee_bean.cpp Coffee_bean.hpp img_processing.hpp
	$(CC) $(CFLAGS) $(LIBS) Coffee_bean.cpp 

#external_devices.o :     external_devices.cpp external_devices.hpp
#	$(CC) $(CFLAGS) $(LIBS) external_devices.cpp	


timer.o: 		timer.cpp external_devices.hpp
	$(CC) $(CFLAGS) $(LIB) 	timer.cpp

gpio.o: 		gpio.cpp external_devices.hpp
	$(CC) $(CFLAGS) $(LIB)	gpio.cpp

open_camera.o: 		open_camera.cpp external_devices.hpp
	$(CC) $(CFLAGS) $(LIB)	open_camera.cpp









PHONY : clean
clean:
	rm -rf all $(objects)

