CC = gcc
CFLAGS = -Wall -O3

all:
	$(CC) $(CFLAGS) -o aes aes.c 
	$(CC) $(CFLAGS) -o decifra decifra.c