
CC:=g++
CPPLAGS:=-g -O2 -Wall -std=c++11 -c

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
vpath %.hpp header
vpath %.h   header

CPPLAGS += -Iheader	# I stand for include header

#--------------------------------------
#	STORE THE OBJECT FILE
#--------------------------------------
OBJDIR 	:=bin
OBJS	:= $(addprefix $(OBJDIR)/,Coffee_bean.o timer.o gpio.o open_camera.o)



#--------------------------------------
#		RULE
#--------------------------------------
all: $(OBJS)
	$(CC) -o all $(LIBS) $(OBJS)


$(OBJDIR)/%.o: %.cpp
	$(CC) $(CPPLAGS) $(LIBS) $< -o $@


#--------------------------------------
#	make clean 
# Using to clean all *.o file
# -------------------------------------

.PHONY : clean
clean:
	rm -rf all $(OBJS)

