#include "maze.h"

#define LAND_TO_WALL 80	// %
#define PASS_TO_WALL 20 // %

typedef struct	s_data
{
	char **map;
	char **tmp;
	int width, height;
	int p_x, p_y;
	int g_x, g_y;
	int reach_f;
}				t_data;

/*
void check_input(t_data *data)
{
	while (1)
	{
		scanf("%d %d", &data->height, &data->width);
		if (data->height <= 2 || data->width <= 2 || \
			   	MAX_HEIGHT < data->height || MAX_WIDTH < data->width)
			fprintf(stderr, "Invalid val (range 4 ~ 100): ");
		else
			break;
	}
}
*/
void disp_map(t_data *data)
{
	int i, j;
	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (data->map[i][j] == PLAYER)
				printf("\x1b[34mP\x1b[0m ");
			else if (data->map[i][j] == LAND)
				printf("  ");
			else if (data->map[i][j] == WALL)
				(j == data->width-1) ? printf("#") : printf("# ");
			else if (data->map[i][j] == GOAL)
				printf("\x1b[31mX\x1b[0m ");
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
	if (data->reach_f == 1)
		return ;
	if (data->tmp[x][y] == GOAL)
	{
		for (int k=0; k<data->height; k++)
			strcpy(data->map[k], data->tmp[k]);
		data->reach_f = 1;
		return ;
	}
	int *root;
	root = malloc(sizeof(int) * 4);
	select_root(&root);
	data->tmp[x][y] = PASSED;
	for (int i=0; i<4; i++)
	{
		switch(root[i])
		{
			case 0:
				if (0 <= (x-1) && (data->tmp[x-1][y] == LAND || data->tmp[x-1][y] == GOAL))
					flood_fill(x-1, y, data);
			case 1:
				if ((x+1) < data->height && (data->tmp[x+1][y] == LAND || data->tmp[x+1][y] == GOAL))
					flood_fill(x+1, y, data);
			case 2:
				if (0 <= (y-1) && (data->tmp[x][y-1] == LAND || data->tmp[x][y-1] == GOAL))
					flood_fill(x, y-1, data);
			case 3:
				if ((y+1) < data->width && (data->tmp[x][y+1] == LAND || data->tmp[x][y+1] == GOAL))
					flood_fill(x, y+1, data);
		}
	}
	free(root);
}

void fill_wall(t_data *data)
{
	int i, j;
	i = 1;
	while (i < data->height-1)
	{
		j = 1;
		while (j < data->width-1)
		{
			if (data->map[i][j] == LAND && (rand()%100 >= (100-LAND_TO_WALL)))
				data->map[i][j] = WALL;
			if (data->map[i][j] == PASSED && (rand()%100 >= (100-PASS_TO_WALL)))
				data->map[i][j] = WALL;
			if (data->map[i][j] == PASSED)
				data->map[i][j] = LAND;
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

//	check_input(&data);
	data.height = HEIGHT;
	data.width = WIDTH;

	while (data.p_x == data.g_x && data.p_y == data.g_y)
	{
		data.p_x = rand() % (data.width-2) + 1;
		data.p_y = rand() % (data.height-2) + 1;
		data.g_x = rand() % (data.width-2) + 1;
		data.g_y = rand() % (data.height-2) + 1;
	}
	data.map = malloc(sizeof(char *) * data.height);
	data.tmp = malloc(sizeof(char *) * data.height);
	for (i=0; i<data.height; i++)
	{
		data.map[i] = malloc(sizeof(char) * (data.width+1));
		data.tmp[i] = malloc(sizeof(char) * (data.width+1));
		for(j=0; j<data.width; j++)
		{
			if (1 <= i && i < (data.height-1) && 1 <= j && j < (data.width-1))
				data.map[i][j] = LAND;
			else
				data.map[i][j] = WALL;
		}
	}
	data.map[data.p_x][data.p_y] = PLAYER;
	data.map[data.g_x][data.g_y] = GOAL;

	i = 0;
	while (i < data.height)
	{
		j = 0;
		while (j < data.width)
		{
			if (data.map[i][j] == PLAYER)
			{
				for (int k=0; k<data.height; k++)
					strcpy(data.tmp[k], data.map[k]);
				flood_fill(i, j, &data);
			}
			j++;
		}
		i++;
	}

	fill_wall(&data);
	system("clear");
	disp_map(&data);

	i = 0;
	while (i < data.height)
	{
		fprintf(fd, "%s\n", data.map[i]);
		i++;
	}

	i = 0;
	while(i < data.height)
	{
		free(data.map[i]);
		i++;
	}
	free(data.map);
	return (0);
}
