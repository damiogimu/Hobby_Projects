#include "othello.h"

#define PROCESS 0
#define GUIDE 1

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
	if (0 <= data->x+(dx*(n+1)) && data->x+(dx*(n+1)) < HEIGHT && 0 <= data->y+(dy*(n+1)) && data->y+(dy*(n+1)) < WIDTH && data->tmp[data->x+(dx*(n+1))][data->y+(dy*(n+1))] == data->my_c)
	{
		data->tmp[data->x][data->y] = data->my_c;
		data->flag = 1;
		return ;
	}
	if (0 <= data->x+(dx*(n+1)) && data->x+(dx*(n+1)) < HEIGHT && 0 <= data->y+(dy*(n+1)) && data->y+(dy*(n+1)) < WIDTH && data->tmp[data->x+(dx*(n+1))][data->y+(dy*(n+1))] == data->enemy)
		flood_fill(dx, dy, data, n+1);
	if (data->flag == 0)
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
	int count = 0;
	for (i=0; i<HEIGHT; i++)
	{
		for (j=0; j<WIDTH; j++)
		{
			data->x = i;
			data->y = j;
			if (can_place(data))
			{
				if (GUIDE == 1)
					data->field[i][j] = CAN;
				if (PROCESS == 1)
				{
					usleep(0.7*10e5);
					system("clear");
					disp_field(data, 1);
				}
				for (int k=0;k<HEIGHT; k++)
					strcpy(data->tmp[k], data->field[k]);
				data->tmp[i][j] = NONE;
				count++;
			}
		}
	}
	return (count);
}

int judge_winner(t_data *data)
{
	int i, j;
	int w_num, b_num;
	w_num = b_num = 1;
	for (i=0;i<HEIGHT;i++)
		for(j=0;j<WIDTH;j++)
		{
			if (data->field[i][j] == WHITE)
				w_num++;
			else if (data->field[i][j] == BLACK)
				b_num++;
		}
	disp_field(data, 0);
	printf("BLACK : %d  |  WHITE : %d\n", b_num, w_num);
	if (w_num > b_num)
		printf("\n\nWINNER : WHITE\n");
	else if (w_num < b_num)
		printf("\n\nWINNER : BLACK\n");
	else
		printf("\n\nDRAW\n");

	return (0);
}

int main(void)
{
	char p_name[3][6] = {"BLACK", "WHITE"};
	int i, j;
	int p_c;
	int is_finish = 0;
	t_data data;
	
	setvbuf(stdout, NULL, _IONBF, 0);
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

	srand((unsigned int)time(NULL));
	for (i=0; i<HEIGHT; i++)
		strcpy(data.tmp[i], data.field[i]);
	system("clear");
	printf("select your number of color (0:BLACK  1:WHITE): ");
	scanf("%d", &p_c);
	if (p_c != 0 && p_c != 1)
	{
		printf("Invalid input\n");
		return (0);
	}

	while (is_finish < 2)
	{
		for (i=0; i<HEIGHT; i++)
			strcpy(data.tmp[i], data.field[i]);
		if (check_field(&data) == 0)
		{
			is_finish++;
			continue;
		}
		else
			is_finish = 0;
		disp_field(&data, 0);
		for (i=0; i<HEIGHT; i++)
			for (j=0; j<WIDTH; j++)
				if (data.field[i][j] == CAN)
					data.field[i][j] = NONE;
		for (i=0; i<HEIGHT; i++)
			strcpy(data.tmp[i], data.field[i]);
		printf("%s | select where to place piece: ", p_name[data.my_c-49]);
	
		if ((p_c+49) == data.my_c)
			scanf("%d %d", &data.x, &data.y);
		else
		{
			data.x = rand()%8;
			data.y = rand()%8;
		}

		while (!(can_place(&data)))
		{
			if ((p_c+49) == data.my_c)
				scanf("%d %d", &data.x, &data.y);
			else
			{
				data.x = rand()%8;
				data.y = rand()%8;
			}
			continue;
		}
		if (data.my_c != (p_c+49))
		{
			usleep(3.5*10e5);
			printf("%d ", data.x);
			usleep(1.0*10e5);
			printf("%d\n", data.y);
			usleep(3.0*10e5);
		}
		for (i=0; i<HEIGHT; i++)
			strcpy(data.field[i], data.tmp[i]);
		data.my_c = (data.my_c==WHITE) ? BLACK : WHITE;	
		data.enemy = (data.enemy==WHITE) ? BLACK : WHITE;
		system("clear");
	}

	judge_winner(&data);

	for (i=0; i<HEIGHT; i++)
		free(data.field[i]);
	free(data.field);
	return (0);
}
