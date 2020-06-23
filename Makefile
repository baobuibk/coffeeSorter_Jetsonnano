CC=g++
CFLAGS=-g -O2 -Wall -std=c++11 -c

OPENCV = `pkg-config opencv4 --cflags --libs`
#OPENCV = -L/opt/opencv_3.2.0/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio\
	-I/opt/opencv_3.2.0/include/
#	-I/opt/opencv_3.2.0/include/opencv4
LIBS   = $(OPENCV)


objects = Coffee_bean.o          read_IMG_RGB.o           Segmentation_RGB.o \
	  Otsus_process.o        Gaussian_filter.o        Cc_label.o \
	  Explore_border.o       Thinning_process.o       Thin_step1.o \
	  Thin_step2.o           Thin_step2_cd1.o         Thin_step2_cd2.o \
	  eliminate_noise_line.o Explore_border_single.o  check_shape_color.o \
	  check_single_shape.o   explore_single_img.o     check_color.o \
	  rgb2lab.o              gauss5x5_table.o         rgb2lab_table.o \
          Test_matrix.o          Test_matrix_sub.o        read_IMG_Gray.o \
	  write_img2txt.o


all : $(objects)
	$(CC)	-o all $(objects) $(LIBS)

#capturev4l2.o:	capturev4l2.c 
#	$(CC) $(CFLAGS) $(LIBS) capturev4l2.c 	

Coffee_bean.o :          Coffee_bean.cpp Coffee_bean.h
	$(CC) $(CFLAGS) $(LIBS)  Coffee_bean.cpp 

read_IMG_RGB.o :         read_IMG_RGB.c Coffee_bean.h
	$(CC) $(CFLAGS)  read_IMG_RGB.c	

Segmentation_RGB.o :         Segmentation_RGB.c Coffee_bean.h
	$(CC) $(CFLAGS)  Segmentation_RGB.c

Otsus_process.o :         Otsus_process.c Coffee_bean.h
	$(CC) $(CFLAGS)  Otsus_process.c

Gaussian_filter.o :      Gaussian_filter.c Coffee_bean.h gauss5x5_table.h 
	$(CC) $(CFLAGS)  Gaussian_filter.c

gauss5x5_table.o:        gauss5x5_table.c gauss5x5_table.h
	$(CC) $(CFLAGS)  gauss5x5_table.c

Cc_label.o :              Cc_label.c Coffee_bean.h
	$(CC) $(CFLAGS)  Cc_label.c

Explore_border.o :       Explore_border.c Coffee_bean.h
	$(CC) $(CFLAGS)  Explore_border.c
       	
Thinning_process.o :     Thinning_process.c Coffee_bean.h
	$(CC) $(CFLAGS)  Thinning_process.c

Thin_step1.o :           Thin_step1.c Coffee_bean.h
	$(CC) $(CFLAGS)  Thin_step1.c

Thin_step2.o :           Thin_step2.c Coffee_bean.h
	$(CC) $(CFLAGS)  Thin_step2.c

Thin_step2_cd1.o :       Thin_step2_cd1.c Coffee_bean.h
	$(CC) $(CFLAGS)  Thin_step2_cd1.c

Thin_step2_cd2.o :       Thin_step2_cd2.c Coffee_bean.h
	$(CC) $(CFLAGS)  Thin_step2_cd2.c

eliminate_noise_line.o : eliminate_noise_line.c Coffee_bean.h
	$(CC) $(CFLAGS)  eliminate_noise_line.c

Explore_border_single.o :Explore_border_single.c Coffee_bean.h
	$(CC) $(CFLAGS)  Explore_border_single.c

check_shape_color.o :    check_shape_color.c Coffee_bean.h
	$(CC) $(CFLAGS)  check_shape_color.c

check_single_shape.o :   check_single_shape.c Coffee_bean.h
	$(CC) $(CFLAGS)  check_single_shape.c

explore_single_img.o :   explore_single_img.c Coffee_bean.h
	$(CC) $(CFLAGS)  explore_single_img.c

check_color.o :          check_color.c Coffee_bean.h
	$(CC) $(CFLAGS)  check_color.c

rgb2lab_table.o :        rgb2lab_table.c rgb2lab_table.h
	$(CC) $(CFLAGS)  rgb2lab_table.c
	
rgb2lab.o :              rgb2lab.c Coffee_bean.h rgb2lab_table.h
	$(CC) $(CFLAGS)  rgb2lab.c

Test_matrix.o :          Test_matrix.c Coffee_bean.h
	$(CC) $(CFLAGS)  Test_matrix.c

Test_matrix_sub.o :      Test_matrix_sub.c Coffee_bean.h
	$(CC) $(CFLAGS)  Test_matrix_sub.c

read_IMG_Gray.o :        read_IMG_Gray.c Coffee_bean.h
	$(CC) $(CFLAGS)  read_IMG_Gray.c

write_img2txt.o:  	 write_img2txt.c Coffee_bean.h
	$(CC) $(CFLAGS)	 write_img2txt.c

.PHONY : clean
clean:
	rm -rf all $(objects)

