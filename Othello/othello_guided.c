#include "othello.h"

void disp_field(t_data *, int);
void flood_fill(int, int, t_data *, int);
int	can_place(t_data *);
int	check_field(t_data *);

void disp_field(t_data *data, int tmp_f)
{
	int i, j;
	char **map;
	map = ((tmp_f==1) ? data->tmp : data->field);
	printf("\n\t");

	for (i=0;i<WIDTH;i++)
		printf("%d\t", i);
	printf("\n\n\n");
	for (i=0; i<HEIGHT; i++)
	{
		printf("%d\t", i);
		for (j=0; j<WIDTH; j++)
		{
			if (map[i][j] == NONE)
				printf("□\t");	
			else if (map[i][j] == WHITE)
				printf("⚪️\t");
			else if (map[i][j] == BLACK)
				printf("⚫️\t");
			else if (map[i][j] == CAN)
				printf("\x1b[34mX\x1b[0m\t");
		}
		printf("\n\n\n");
	}
}

void flood_fill(int dx, int dy, t_data *data, int n)
{
	if (data->flag == 1)
		return ;
	data->tmp[data->x+(dx*n)][data->y+(dy*n)] = data->my_c;
	if (data->tmp[data->x+(dx*(n+1))][data->y+(dy*(n+1))] == data->my_c)
	{
		data->tmp[data->x][data->y] = data->my_c;
		data->flag = 1;
		return ;
	}
	if (0 <= data->x+(dx*(n+1)) && data->x+(dx*(n+1)) < HEIGHT && 0 <= data->y+(dy*(n+1)) && data->y+(dy*(n+1)) < WIDTH && data->tmp[data->x+(dx*(n+1))][data->y+(dy*(n+1))] == data->enemy)
		flood_fill(dx, dy, data, n+1);
	data->tmp[data->x+(dx*n)][data->y+(dy*n)] = data->enemy;
	return ;
}

int can_place(t_data *data)
{
	if (data->field[data->x][data->y] == BLACK || data->field[data->x][data->y] == WHITE)
		return (0);
	for (int dx=-1; dx<=1; dx++)
		for (int dy=-1; dy<=1; dy++)
			if (0 <= data->x+dx && data->x+dx < HEIGHT && 0 <= data->y+dy && data->y+dy < WIDTH && data->field[data->x+dx][data->y+dy] == data->enemy)
			{
				data->flag = 0;
				flood_fill(dx, dy, data, 1);
			}
	if (data->tmp[data->x][data->y] == data->my_c)
		return (1);
	return (0);
}

int	check_field(t_data *data)
{
	int i, j;
	for (i=0; i<HEIGHT; i++)
	{
		for (j=0; j<WIDTH; j++)
		{
			data->x = i;
			data->y = j;
			if (data->tmp[i][j] == CAN)
				data->tmp[i][j] = NONE;
			if (can_place(data))
				data->tmp[i][j] = CAN;
		}
	}
	return (1);
}

int main(void)
{
	char p_name[2][6] = {"BLACK", "WHITE"};
	int i, j;
	t_data data;

	data.my_c = BLACK;
	data.enemy = WHITE;
	data.field = malloc(sizeof(char *) * HEIGHT);
	data.tmp = malloc(sizeof(char *) * HEIGHT);
	for (i=0; i<HEIGHT; i++)
	{
		data.field[i] = malloc(sizeof(char) * (WIDTH+1));
		data.tmp[i] = malloc(sizeof(char) * (WIDTH+1));
		for (j=0; j<WIDTH; j++)
			data.field[i][j] = NONE;
		data.field[i][j] = '\0';
	}
	data.field[3][3] = data.field[4][4] = WHITE;
	data.field[3][4] = data.field[4][3] = BLACK;
	for (i=0; i<HEIGHT; i++)
		strcpy(data.tmp[i], data.field[i]);

	while (check_field(&data))
	{
		for (i=0; i<HEIGHT; i++)
			strcpy(data.tmp[i], data.field[i]);
		disp_field(&data, 0);
		printf("%s | select where to place piece: ", p_name[data.my_c-49]);
		scanf("%d %d", &data.x, &data.y);

		if (!(can_place(&data)))
		{
			printf("You can't put this place\n");
			continue;
		}
		for (i=0; i<HEIGHT; i++)
			strcpy(data.field[i], data.tmp[i]);
		data.my_c = (data.my_c==WHITE) ? BLACK : WHITE;	
		data.enemy = (data.enemy==WHITE) ? BLACK : WHITE;	
	}
	
	for (i=0; i<HEIGHT; i++)
		free(data.field[i]);
	free(data.field);
	return (0);
}
