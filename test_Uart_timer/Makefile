CC=g++
CFLAGS=-g -O2 -Wall -std=c++11 -c

object = test_uart.o uart.o

all : $(object)
	$(CC) -o all $(object)


test_uart.o : 			test_uart.cpp 	uart.h
	$(CC) $(CFLAGS)  	test_uart.cpp

uart.o: 			uart.cpp 	uart.h
	$(CC) $(CFLAGS)  	uart.cpp

.PHONY : clean
clean:
	rm -rf all $(object)


