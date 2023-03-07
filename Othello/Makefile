CC=gcc
CFLAGS=-Wall

HEADER=othello.h
OBJ_NORMAL=othello_normal.o
OBJ_GUIDED=othello_guided.o

all: normal guided

normal: $(OBJ_NORMAL)
	$(CC) $(CFLAGS) -o $@ $^

guided: $(OBJ_GUIDED)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ_NORMAL) $(OBJ_GUIDED)

fclean: clean
	rm -f normal guided

%.o:%.c
	$(CC) $(CFLAGS) -c $^
