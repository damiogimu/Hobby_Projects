#ifndef MY_HEADER_H
# define MY_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define alpha	0.8
#define gamma	0.6
#define T		0.05
#define Reward	1.0

#define DELAY	0.0 * 1.0e6
#define TRIAL	1000

#define MAP_HEIGHT		7
#define MAP_WIDTH		9
#define MAX_QUEUE_SIZE	((MAP_HEIGHT * MAP_WIDTH) + 1)

#define INIT	'0'
#define WALL	'1'
#define PATH	'2'
#define GOAL	'G'
#define PLAYER	'P'
#define OPT		'3'

typedef struct	s_info
{
	int	px, py;
	int init_px, init_py;
	int next_px, next_py;
	int gx, gy;
	int try_c;
}				t_info;

typedef struct	s_data
{
	int	x;
	int	y;
	double distance;
}				t_data;

typedef struct	s_queue
{
	int		head;
	int		tail;
	int		size;
	t_data	list[MAX_QUEUE_SIZE];
}				t_queue;

void	initQueue(t_queue *queue);
void	enqueue(char map[][MAP_WIDTH], double Qtable[][MAP_WIDTH], t_queue *queue, t_data *input);
t_data	*dequeue(t_queue *queue);
double	max(double val1, double val2);

int		setup(char map[][MAP_WIDTH], double Qtable[][MAP_WIDTH], t_info *info, t_queue *queue, t_data *data);
int		create_Qtable(double Qtable[][MAP_WIDTH], t_info *info, t_queue *queue, t_data *data);
void	update_Qtable(double Qtable[][MAP_WIDTH], t_info *info);
void	reset_map(char map[][MAP_WIDTH], t_info *info);
void	move(char map[][MAP_WIDTH], double Qtable[][MAP_WIDTH], t_info *info);

void	make_optimal_path(char map[][MAP_WIDTH], double Qtable[][MAP_WIDTH], t_info *info);
int		is_finish(char map[][MAP_WIDTH], t_info *info);
void	disp_map(char map[][MAP_WIDTH]);
void	disp_Qtable(char map[][MAP_WIDTH], double Qtable[][MAP_WIDTH], t_info *info);

#endif
