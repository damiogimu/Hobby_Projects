CC=gcc
CFLAGS=-Wall

HEADER=othello.h
OBJ_NORMAL=othello_normal.o
OBJ_GUIDED=othello_guided.o
OBJ_CPU=othello_cpu.o

all: normal guided cpu

normal: $(OBJ_NORMAL)
	$(CC) $(CFLAGS) -o $@ $^

guided: $(OBJ_GUIDED)
	$(CC) $(CFLAGS) -o $@ $^

cpu: $(OBJ_CPU)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ_NORMAL) $(OBJ_GUIDED) $(OBJ_CPU)

fclean: clean
	rm -f normal guided cpu

%.o:%.c
	$(CC) $(CFLAGS) -c $^
