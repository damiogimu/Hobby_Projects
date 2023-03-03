CC=gcc
CFLAGS=-Wall

HEADER=maze.h
CREATE_OBJ=create_map.o
SEARCH_OBJ=search_map.o

create: $(CREATE_OBJ)
	$(CC) -o $@ $^

search: $(SEARCH_OBJ)
	$(CC) -o $@ $^

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -c $<
