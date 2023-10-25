CC=gcc
CFLAGS=-Wall
NAME=calc

H_FILE=my_header.h
O_FILES=main.o utils.o

$(NAME):$(O_FILES)
	$(CC) -o $@ $^ -lm
	
clean:
	rm -f $(O_FILES)

fclean: clean
	rm -f $(NAME)

%.o:%.c $(H_FILE)
	$(CC) $(CFLAGS) -c $< 
