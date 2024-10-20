CC = gcc
CFLAGS = -Wall -O3
ARQS = aes.c 

all:
	$(CC) $(CFLAGS) -o aes $(ARQS)