#include "maze.h"

#define LAND_TO_WALL 100
#define PASS_TO_WALL 5

void disp_map(t_data *data, int tmp_f)
{
	char **map;
	int i, j;
	map = data->map;
	if (tmp_f == 1)
		map = data->tmp;
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (map[i][j] == PLAYER)
				printf("\x1b[34mP\x1b[0m ");
			else if (map[i][j] == LAND)
				printf("  ");
			else if (map[i][j] == WALL)
				(j == WIDTH-1) ? printf("#") : printf("# ");
			else if (map[i][j] == GOAL)
				printf("\x1b[31mX\x1b[0m ");
			else if (map[i][j] == PASSED)
				printf("* ");
			else
				printf("  ");
			j++;
		}
		printf("\n");
		i++;
	}
}

void select_root(int **root)
{
	int i, j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		(*root)[i] = rand()%4;
		while (j < i)
		{
			if ((*root)[i] == (*root)[j])
			{
				i--;
				break;
			}
			j++;
		}
		i++;
	}
}	

void flood_fill(int x, int y, t_data *data)
{
	int *root;
	if (data->reach_f == 1)
		return ;
	if (data->tmp[x][y] == GOAL)
	{
		for (int k=0; k<HEIGHT; k++)
			strcpy(data->map[k], data->tmp[k]);
		data->reach_f = 1;
		return ;
	}
	data->tmp[x][y] = PASSED;
	if (PROCESS == 1)
	{
		usleep(F_ITV * 10e4);
		disp_map(data, 1);
		printf("\x1b[%d)A", HEIGHT);
	}
	root = malloc(sizeof(int) * 4);
	select_root(&root);
	for (int i=0; i<4; i++)
	{
		if (root[i] == 0 && 0 <= (x-1) && (data->tmp[x-1][y] == LAND || data->tmp[x-1][y] == GOAL))
			flood_fill(x-1, y, data);
		if (root[i] == 1 && (x+1) < HEIGHT && (data->tmp[x+1][y] == LAND || data->tmp[x+1][y] == GOAL))
			flood_fill(x+1, y, data);
		if (root[i] == 2 && 0 <= (y-1) && (data->tmp[x][y-1] == LAND || data->tmp[x][y-1] == GOAL))
			flood_fill(x, y-1, data);
		if (root[i] == 3 && (y+1) < WIDTH && (data->tmp[x][y+1] == LAND || data->tmp[x][y+1] == GOAL))
			flood_fill(x, y+1, data);
	}
	free(root);
}

void fill_wall(t_data *data)
{
	int i, j;
	i = 1;
	while (i < HEIGHT-1)
	{
		j = 1;
		while (j < WIDTH-1)
		{
			if (data->map[i][j] == LAND && (rand()%100 > (99-LAND_TO_WALL)))
				data->map[i][j] = WALL;
			if (data->map[i][j] == PASSED && (rand()%100 > (99-PASS_TO_WALL)))
				data->map[i][j] = WALL;
			if (data->map[i][j] == PASSED)
				data->map[i][j] = LAND;
			if (PROCESS == 1)
			{
				usleep(F_ITV * 10e5);
				disp_map(data, 0);
				printf("\x1b[%d)A", HEIGHT);
			}
			j++;
		}
		i++;
	}
	data->map[data->p_x][data->p_y] = PLAYER;
	data->map[data->g_x][data->g_y] = GOAL;
}

int main(void)
{
	FILE *fd;
	int i, j;
	t_data data;	

	if ((fd = fopen(OUT_F, "w")) == NULL)
	{
		fprintf(stderr, "OPEN ERROR\n");
		return (0);
	}
	srand((unsigned int)time(NULL));
	data.p_x = data.p_y = data.g_x = data.g_y = 0;
	data.reach_f = 0;

	while (data.p_x == data.g_x && data.p_y == data.g_y)
	{
		data.p_x = rand() % (WIDTH-2) + 1;
		data.p_y = rand() % (HEIGHT-2) + 1;
		data.g_x = rand() % (WIDTH-2) + 1;
		data.g_y = rand() % (HEIGHT-2) + 1;
	}
	data.map = malloc(sizeof(char *) * HEIGHT);
	data.tmp = malloc(sizeof(char *) * HEIGHT);
	for (i=0; i<HEIGHT; i++)
	{
		data.map[i] = malloc(sizeof(char) * (WIDTH+1));
		data.tmp[i] = malloc(sizeof(char) * (WIDTH+1));
		for(j=0; j<WIDTH; j++)
		{
			if (1 <= i && i < (HEIGHT-1) && 1 <= j && j < (WIDTH-1))
				data.map[i][j] = LAND;
			else
				data.map[i][j] = WALL;
		}
	}
	data.map[data.p_x][data.p_y] = PLAYER;
	data.map[data.g_x][data.g_y] = GOAL;

	system("clear");
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (data.map[i][j] == PLAYER)
			{
				for (int k=0; k<HEIGHT; k++)
					strcpy(data.tmp[k], data.map[k]);
				flood_fill(i, j, &data);
			}
			j++;
		}
		i++;
	}

	fill_wall(&data);
	disp_map(&data, 0);
	printf("\n");
	
	i = 0;
	while (i < HEIGHT)
	{
		fprintf(fd, "%s\n", data.map[i]);
		i++;
	}

	i = 0;
	while(i < HEIGHT)
	{
		free(data.map[i]);
		i++;
	}
	free(data.map);
	return (0);
}
