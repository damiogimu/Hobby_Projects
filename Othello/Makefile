CC=gcc
CFLAGS=-Wall

HEADER=othello.h
OBJ_NORMAL=othello_normal.o
OBJ_GUIDED=othello_guided.o
OBJ_PvE=othello_PvE.o
OBJ_EvE=othello_EvE.o

all: normal guided pve eve

normal: $(OBJ_NORMAL)
	$(CC) $(CFLAGS) -o $@ $^

guided: $(OBJ_GUIDED)
	$(CC) $(CFLAGS) -o $@ $^

pve: $(OBJ_PvE)
	$(CC) $(CFLAGS) -o $@ $^

eve: $(OBJ_EvE)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ_NORMAL) $(OBJ_GUIDED) $(OBJ_PvE) $(OBJ_EvE)

fclean: clean
	rm -f normal guided pve eve

%.o:%.c
	$(CC) $(CFLAGS) -c $^
