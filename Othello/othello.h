#ifndef OTHELLO_H
# define OTHELLO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NONE	'0'
#define BLACK	'1'
#define WHITE	'2'
#define CAN		'3'

#define HEIGHT	8
#define WIDTH	8

typedef struct	s_data
{
	char	my_c;
	char	enemy;
	char	**field;
	char	**tmp;
	int		x, y;
	int		flag;
}				t_data;

#endif
