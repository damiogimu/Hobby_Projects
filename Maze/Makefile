CC=gcc
CFLAGS=-Wall

HEADER=maze.h
CREATE_OBJ=create_map.o
SEARCH_OBJ=search_map.o

all:create search

create: $(CREATE_OBJ)
	$(CC) -o $@ $^

search: $(SEARCH_OBJ)
	$(CC) -o $@ $^

clean:
	rm -f $(CREATE_OBJ) $(SEARCH_OBJ)

fclean: clean
	rm -f create search map.txt 

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -c $<
