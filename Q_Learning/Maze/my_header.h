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
#define TRIAL	100

#define MAP_HEIGHT	10
#define MAP_WIDTH	10

#define PATH	'0'
#define WALL	'1'
#define GOAL	'G'
#define PLAYER	'P'
#define OPT		'2'

typedef struct	s_info
{
	int	px, py;
	int init_px, init_py;
	int next_px, next_py;
	int gx, gy;
	int try_c;
}				t_info;

int		setup(char map[][MAP_WIDTH], double Qtable[][MAP_WIDTH], t_info *info);
void	move(char map[][MAP_WIDTH], double Qtable[][MAP_WIDTH], t_info *info);
void	update_Qtable(double Qtable[][MAP_WIDTH], t_info *info);
void	reset_map(char map[][MAP_WIDTH], t_info *info);
int		is_finish(char map[][MAP_WIDTH], t_info *info);
void	make_optimal_path(char map[][MAP_WIDTH], double Qtable[][MAP_WIDTH], t_info *info);

void	disp_phase(t_info *info);
void	disp_map(char map[][MAP_WIDTH]);
void	disp_Qtable(char map[][MAP_WIDTH], double Qtable[][MAP_WIDTH], t_info *info);
double	max(double val1, double val2);

#endif
