CC=g++
CFLAGS=-g -O2 -Wall -std=c++11 -c

object = test_uart.o uart.o crc16.o afproto.o

all : $(object)
	$(CC) -o all $(object)


test_uart.o : 			test_uart.cpp 	uart.h
	$(CC) $(CFLAGS)  	test_uart.cpp

uart.o: 			uart.cpp 	uart.h
	$(CC) $(CFLAGS)  	uart.cpp
crc16.o:			crc16.c		crc16.h	
	$(CC) $(CFLAGS) 	crc16.c		
afproto.c:			afproto.c	afproto.h	crc16.h
	$(CC) $(CFLAGS) 	afproto.c


.PHONY : clean
clean:
	rm -rf all $(object)


