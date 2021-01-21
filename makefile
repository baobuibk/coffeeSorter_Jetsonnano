#.SUFFIXES:
#.SUFFIXES: .cpp .o

CC=g++
CFLAGS=-g -O2 -Wall -std=c++11 -c

#SRCDIR := src
OBJDIR = obj

OPENCV = `pkg-config opencv4 --cflags --libs`
#OPENCV = -L/opt/opencv_3.2.0/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio\
#	-I/opt/opencv_3.2.0/include/
#	-I/opt/opencv_3.2.0/include/opencv4
LIBS   = $(OPENCV)

vpath %.cpp src
vpath %.h src
vpath %.c src

objects = $(addprefix $(OBJDIR)/, Coffee_bean.o 	read_IMG_RGB.o           Segmentation_RGB.o \
	  			  Otsus_process.o        Gaussian_filter.o        Cc_label.o \
	  			Explore_border.o       Thinning_process.o       Thin_step1.o \
	  			Thin_step2.o           Thin_step2_cd1.o         Thin_step2_cd2.o \
	  			eliminate_noise_line.o Explore_border_single.o  check_shape_color.o \
	  			check_single_shape.o   explore_single_img.o     check_color.o \
	  			rgb2lab.o              gauss5x5_table.o         rgb2lab_table.o \
          			Test_matrix.o          Test_matrix_sub.o        read_IMG_Gray.o \
	  			write_img2txt.o	 	timer_handler.o)


all : $(objects)
	$(CC)	$(CFLAGS) -o all $(objects) $(LIBS)

#capturev4l2.o:	capturev4l2.c 
#	$(CC) $(CFLAGS) $(LIBS) capturev4l2.c 	
obj/Coffee_bean.o: src/Coffee_bean.cpp src/Coffee_bean.h
	$(CC) $(CFLAGS) $(LIBS) -c Coffee_bean.cpp

obj/%.o: %.c
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@


.PHONY : clean
clean:
	rm -rf all $(objects)

