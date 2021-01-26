CC=g++
CFLAGS=-g -O2 -Wall -std=c++11 -c

object = test_timer.o	GPIOnew.o

all : $(object)
	$(CC) -o all $(object)


test_timer.o : 			test_timer.cpp 	GPIOnew.h
	$(CC) $(CFLAGS)  	test_timer.cpp

GPIOnew.o: 			GPIOnew.c 	GPIOnew.h
	$(CC) $(CFLAGS)  	GPIOnew.c


.PHONY : clean
clean:
	rm -rf all $(object)


