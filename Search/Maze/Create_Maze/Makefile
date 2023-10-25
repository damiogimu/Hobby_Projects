CC=gcc
CFLAGS=-Wall
NAME=create
MAP=map.txt

HEADER=maze.h
CREATE_OBJ=create_map.o

$(NAME): $(CREATE_OBJ)
	$(CC) -o $@ $^

clean:
	rm -f $(CREATE_OBJ)

fclean: clean
	rm -f $(NAME) $(MAP)

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -c $<
