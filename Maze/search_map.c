#include "maze.h" 

typedef struct	s_data
{
	char	**map;
	char	**tmp;
	int		goal_f;
}				t_data;

void	all_free(char ***str);
void	flood_fill(int x, int y, t_data *data);
void	disp_map(t_data *data);
int		check_input(int *fd, int argc, char **argv);
void	disp_tmp(t_data *data);
void	disp_map(t_data *data);

void all_free(char ***str)
{
	int i;
	i = 0;
	while (i < HEIGHT)
	{
		free((*str)[i]);
		i++;
	}
	free(*str);
}

int	check_input(int *fd, int argc, char **argv)
{
	if (argc == 1 && (*fd = open(OUT_F, O_RDONLY)) == -1)
	{
		fprintf(stderr, "OPEN ERROR\n");
		return (-1);
	}
	else if (argc == 2)
	{
		if ((*fd = open(argv[1], O_RDONLY)) == -1)
		{
			fprintf(stderr, "OPEN ERROR\n");
			return (-1);
		}
	}
	else if (argc > 2)
	{
		fprintf(stderr, "Too many Commandline Arguments\n");
		return (-1);
	}
	return (0);
}

void flood_fill(int x, int y, t_data *data)
{
	if (data->goal_f == 1)
		return ;
	if (data->tmp[x][y] == GOAL)
	{
		data->goal_f = 1;
		for (int k=0; k<HEIGHT; k++)
			strcpy(data->map[k], data->tmp[k]);
		return ;
	}
	data->tmp[x][y] = NOW;
//
	usleep(F_ITV * 10e5);
	system("clear");
	disp_tmp(data);
//
	if (0 <= (x-1) && (data->tmp[x-1][y] == LAND || data->tmp[x-1][y] == GOAL))
	{
		data->tmp[x][y] = 'u';
		flood_fill(x-1, y, data);
		data->tmp[x][y] = PASSED;
	}
	if ((x+1) < HEIGHT && (data->tmp[x+1][y] == LAND || data->tmp[x+1][y] == GOAL))
	{
		data->tmp[x][y] = 'd';
		flood_fill(x+1, y, data);
		data->tmp[x][y] = PASSED;
	}
	if (0 <= (y-1) && (data->tmp[x][y-1] == LAND || data->tmp[x][y-1] == GOAL))
	{
		data->tmp[x][y] = 'l';
		flood_fill(x, y-1, data);
		data->tmp[x][y] = PASSED;
	}
	if ((y+1) < WIDTH && (data->tmp[x][y+1] == LAND || data->tmp[x][y+1] == GOAL))
	{
		data->tmp[x][y] = 'r';
		flood_fill(x, y+1, data);
		data->tmp[x][y] = PASSED;
	}
	data->tmp[x][y] = PASSED;
}

void disp_tmp(t_data *data)
{
	int i, j;
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (data->tmp[i][j] == PLAYER || data->tmp[i][j] == NOW)
				printf("\x1b[34mP\x1b[0m ");
			else if (data->tmp[i][j] == LAND)
				printf("  ");
			else if (data->tmp[i][j] == WALL)
				(j==(WIDTH-1)) ? printf("#") : printf("# ");
			else if (data->tmp[i][j] == GOAL)
				printf("\x1b[31mX\x1b[0m ");
			else if (data->tmp[i][j] == 'u')
				printf("\x1b[33m▲ \x1b[0m");
			else if (data->tmp[i][j] == 'd')
				printf("\x1b[33m▼ \x1b[0m");
			else if (data->tmp[i][j] == 'l')
				printf("\x1b[33m◀︎ \x1b[0m");
			else if (data->tmp[i][j] == 'r')
				printf("\x1b[33m▶︎ \x1b[0m");
			else if (data->tmp[i][j] == LAND || data->tmp[i][j] == PASSED)
				printf("  ");
			j++;
		}
		printf("\n");
		i++;
	}
}

void disp_map(t_data *data)
{
	int i, j;
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (data->map[i][j] == PLAYER || data->map[i][j] == NOW)
				printf("\x1b[34mP\x1b[0m ");
			else if (data->map[i][j] == LAND || data->map[i][j] == NOW)
				printf("  ");
			else if (data->map[i][j] == WALL)
				(j==(WIDTH-1)) ? printf("#") : printf("# ");
			else if (data->map[i][j] == GOAL)
				printf("\x1b[31mX\x1b[0m ");
			else if (data->map[i][j] == 'u')
				printf("\x1b[33m▲ \x1b[0m");
			else if (data->map[i][j] == 'd')
				printf("\x1b[33m▼ \x1b[0m");
			else if (data->map[i][j] == 'l')
				printf("\x1b[33m◀︎ \x1b[0m");
			else if (data->map[i][j] == 'r')
				printf("\x1b[33m▶︎ \x1b[0m");
			else if (data->map[i][j] == LAND || data->map[i][j] == PASSED)
				printf("  ");
			j++;
		}
		printf("\n");
		i++;
	}
}

int main(int argc, char **argv)
{
	int i, j;
	int p_x, p_y;
	int fd = -1;
	t_data data;
	data.goal_f = 0;
	data.map = malloc(sizeof(char *) * HEIGHT);
	data.tmp = malloc(sizeof(char *) * HEIGHT);
	i = 0;
	while(i < HEIGHT)
	{
		data.map[i] = malloc(sizeof(char) * (WIDTH+1));
		data.tmp[i] = malloc(sizeof(char) * (WIDTH+1));
		i++;
	}
	if (check_input(&fd, argc, argv) == -1)	
		return (0);
	i = 0;
	while (i < HEIGHT)
	{
		read(fd, data.map[i], sizeof(char)*(WIDTH+1));
		data.map[i][WIDTH] = '\0';
		i++;
	}

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			for (int k=0; k<HEIGHT; k++)
				strcpy(data.tmp[k], data.map[k]);
			if (data.tmp[i][j] == PLAYER)
			{
				p_x = i;
				p_y = j;
				flood_fill(i, j, &data);
			}
			j++;
		}
		i++;
	}
	data.map[p_x][p_y] = PLAYER;
	system("clear");

	if (data.goal_f == 0)
	{
		disp_tmp(&data);
		printf("Can't reach the GOAL\n");
	}
	else
	{
		disp_map(&data);
	}
	printf("\n");

	all_free(&data.map);
	all_free(&data.tmp);
	return (0);
}
