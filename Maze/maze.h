#ifndef MAZE_H
# define MAZE_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PLAYER	'0'
#define LAND	'1'
#define WALL	'2'
#define PASSED	'3'
#define GOAL	'4'
#define NOW		'5'

#define WIDTH 30
#define HEIGHT 30

#define OUT_F "map.txt"
#define F_ITV 0.02

#endif