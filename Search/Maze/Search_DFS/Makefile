CC=gcc
CFLAGS=-Wall
NAME=search

HEADER=maze.h
SEARCH_OBJ=search_map.o

$(NAME): $(SEARCH_OBJ)
	$(CC) -o $@ $^

clean:
	rm -f $(SEARCH_OBJ)

fclean: clean
	rm -f $(NAME)

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -c $<
