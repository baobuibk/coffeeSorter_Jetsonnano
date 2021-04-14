
CC=g++
CFLAGS=-g -O2 -Wall -std=c++11 -c


#--------------------------------------
#	IMPORT OPENCV LIBRARY
#--------------------------------------

OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS   = $(OPENCV)



#****************************************************************************************************
#OPENCV = -L/opt/opencv_3.2.0/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio\
#	-I/opt/opencv_3.2.0/include/
#	-I/opt/opencv_3.2.0/include/opencv4
#****************************************************************************************************



#--------------------------------------
#	LET MAKEFILE KNOW THE DIRECTORY
#--------------------------------------
#VPATH = src:src/img_processing_library:src/external_devices

vpath %.cpp src:src/img_processing_library:src/external_devices
vpath %.c   src/external_devices
vpath %.hpp header
vpath %.h   header

CFLAGS += -Iheader	# I stands for include header
#CFLAGS += -ILIBS
#--------------------------------------
#	STORE THE OBJECT FILE
#--------------------------------------
OBJDIR 	:= bin
OBJS	:= $(addprefix $(OBJDIR)/,Coffee_bean.o timer.o gpio.o open_camera.o \
				  afproto.o 	crc16.o	uart.o)



#--------------------------------------
#		RULE
#--------------------------------------
all: $(OBJS)
	$(CC) -o all $(OBJS) $(LIBS)	#remember to place $(LIBS) behind $(OBJS)


$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(LIBS) $< -o $@


#--------------------------------------
#	make clean 
# Using to clean all *.o file
# -------------------------------------

.PHONY : clean
clean:
	rm -rf all $(OBJS)

