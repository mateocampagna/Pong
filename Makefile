CC = gcc
CFLAGS = -Wall
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all:
	$(CC) main.c -o p $(CFLAGS) $(LIBS)