CC=g++
CFLAGS=-g -O2 -Wall -std=c++11 -c

#SRCDIR := src
#OBJDIR := bin

OPENCV = `pkg-config opencv4 --cflags --libs`
#OPENCV = -L/opt/opencv_3.2.0/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio\
#	-I/opt/opencv_3.2.0/include/
#	-I/opt/opencv_3.2.0/include/opencv4
LIBS   = $(OPENCV)


objects = 	Coffee_bean.o          external_devices.o     







all : $(objects)
	$(CC)	-o all $(objects) $(LIBS)

#capturev4l2.o:	capturev4l2.c 
#	$(CC) $(CFLAGS) $(LIBS) capturev4l2.c 	

Coffee_bean.o :          Coffee_bean.cpp Coffee_bean.hpp
	$(CC) $(CFLAGS) $(LIBS)  Coffee_bean.cpp 

external_devices.o :     external_devices.cpp external_devices.hpp
	$(CC) $(CFLAGS)  external_devices.cpp	



PHONY : clean
clean:
	rm -rf all $(objects)

