CC=gcc
CFLAGS=-Wall
NAME=calc
HEADER=my_header.h

OBJS=main.o utils.o

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -c $<
