#include "othello.h"

typedef struct	s_data
{
	char	my_c;
	char	enemy;
	char	**field;
	int		x, y;
	int		flag;
}				t_data;

void disp_field(t_data *);
void flood_fill(int, int, t_data *, int);
int	can_place(t_data *);
int	is_finish(t_data *);

void disp_field(t_data *data)
{
	int i, j;
	printf("\n\t");
	for (i=0;i<WIDTH;i++)
		printf("%d\t", i);
	printf("\n\n\n");

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		printf("%d\t", i);
		while (j < WIDTH)
		{
			if (data->field[i][j] == NONE)
				printf("□\t");	
			else if (data->field[i][j] == WHITE)
				printf("⚪️\t");
			else if (data->field[i][j] == BLACK)
				printf("⚫️\t");
			j++;
		}
		printf("\n\n\n");
		i++;
	}
}

void flood_fill(int dx, int dy, t_data *data, int n)
{
	printf("nx = %d | ny = %d | dx = %d | dy = %d | n = %d\n", data->x, data->y, dx, dy, n);
	if (data->flag == 1)
		return ;
	data->field[data->x+(dx*n)][data->y+(dy*n)] = data->my_c;
	if (data->field[data->x+(dx*(n+1))][data->y+(dy*(n+1))] == data->my_c)
	{
		data->field[data->x][data->y] = data->my_c;
		data->flag = 1;
		return ;
	}
	if (0 <= data->x+(dx*(n+1)) && data->x+(dx*(n+1)) < HEIGHT && 0 <= data->y+(dy*(n+1)) && data->y+(dy*(n+1)) < WIDTH && data->field[data->x+(dx*(n+1))][data->y+(dy*(n+1))] == data->enemy)
		flood_fill(dx, dy, data, n+1);
	data->field[data->x+(dx*n)][data->y+(dy*n)] = data->enemy;
	return ;
}

int can_place(t_data *data)
{
	if (data->field[data->x][data->y] != NONE)
		return (0);
	for (int dx=-1; dx<=1; dx++)
		for (int dy=-1; dy<=1; dy++)
			if (data->field[data->x+dx][data->y+dy] == data->enemy)
			{
				data->flag = 0;
				flood_fill(dx, dy, data, 1);
			}
	if (data->field[data->x][data->y] == data->my_c)
		return (1);
	return (0);
}

int main(void)
{
	char p_name[2][6] = {"BLACK", "WHITE"};
	int i, j;
	t_data data;

	data.my_c = BLACK;
	data.enemy = WHITE;
	data.field = malloc(sizeof(char *) * HEIGHT);
	for (i=0; i<HEIGHT; i++)
	{
		data.field[i] = malloc(sizeof(char) * (WIDTH+1));
		for (j=0; j<WIDTH; j++)
			data.field[i][j] = NONE;
		data.field[i][j] = '\0';
	}
	data.field[3][3] = data.field[4][4] = WHITE;
	data.field[3][4] = data.field[4][3] = BLACK;
	
	while (1)
	{
		disp_field(&data);
		printf("%s | select where to place piece: ", p_name[data.my_c-49]);
		scanf("%d %d", &data.x, &data.y);
		
		if (!(can_place(&data)))
			continue;
		data.my_c = (data.my_c==WHITE) ? BLACK : WHITE;	
		data.enemy = (data.enemy==WHITE) ? BLACK : WHITE;	
	}
	
	for (i=0; i<HEIGHT; i++)
		free(data.field[i]);
	free(data.field);
	return (0);
}
