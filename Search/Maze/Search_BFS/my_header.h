#ifndef MY_HEADER_H
# define MY_HEADER_H

#include <stdio.h>
#include <stdlib.h>

#define MAP_HEIGHT		8
#define MAP_WIDTH		8
#define MAX_QUEUE_SIZE	((MAX_HEIGHT * MAX_WIDTH) + 1)

typedef struct	s_info
{
	int px, py;
	int gx, gy;
}				t_info;

typedef struct	s_data
{
	int x;
	int y;
}				t_data;

typedef struct	s_queue
{
	int head;
	int tail;
	int size;
	t_pos list[MAX_QUEUE_SIZE];
}				t_queue;

#endif
