CC = gcc
CFLAGS = -Wall

all:
	$(CC) $(CFLAGS) -o aes aes.c 
	$(CC) $(CFLAGS) -o decifra decifra.c