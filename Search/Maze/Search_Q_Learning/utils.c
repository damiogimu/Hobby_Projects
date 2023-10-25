#include "my_header.h"

void initQueue(t_queue *queue)
{
	queue->head = 0;
	queue->tail = 0;
	queue->size = -1;
}

void enqueue(char map[][MAP_WIDTH], double Qtable[][MAP_WIDTH], t_queue *queue, t_data *data)
{
	if (queue->size == MAX_QUEUE_SIZE)
	{
		fprintf(stderr, "queue is full\n\n");
		return ;
	}
	map[data->y][data->x] = PATH;
	Qtable[data->y][data->x] = pow(gamma,data->distance) * Reward;
	queue->list[queue->tail] = *data;
	queue->tail = (queue->tail+1) % MAX_QUEUE_SIZE;
	queue->size = queue->tail - queue->head;
	if (queue->tail < queue->head)
		queue->size = MAX_QUEUE_SIZE - (queue->head - queue->tail);
}

t_data *dequeue(t_queue *queue)
{
	t_data *val;
	if (queue->size == 0)
	{
		fprintf(stderr, "queue is empty\n\n");
		return (NULL);
	}
	val = &(queue->list[queue->head]);
	queue->head = (queue->head+1) % MAX_QUEUE_SIZE;
	queue->size = queue->tail - queue->head;
	if (queue->tail < queue->head)
		queue->size = MAX_QUEUE_SIZE - (queue->head - queue->tail);
	return (val);
}

int setup(char map[][MAP_WIDTH], double Qtable[][MAP_WIDTH], t_info *info, t_queue *queue, t_data *data)
{
	srand((unsigned int)time(NULL));
	if (setvbuf(stdout,NULL,_IONBF,0) != 0)	
	{
		fprintf(stderr, "\x1b[31mError : setvbuf\x1b[0m\n");
		return (-1);
	}
	for (int i=0; i<MAP_HEIGHT; i++)
	{
		for (int j=0; j<MAP_WIDTH; j++)
		{
			if (map[i][j] == WALL)
				Qtable[i][j] = -Reward;
			else if (map[i][j] == GOAL)
			{
				info->gx = j;
				info->gy = i;
			}
			else if (map[i][j] == PLAYER)
			{
				info->px = j;
				info->py = i;
				info->init_px = j;
				info->init_py = i;
				Qtable[i][j] = 0.0;
			}
			else
				Qtable[i][j] = 0.0;
		}
	}
	if (info->gy == -1 || info->gx == -1 || info->py == -1 || info->px == -1)
	{
		fprintf(stderr, "\x1b[31mError : Incorrect Map\x1b[0m\n");
		return (-1);
	}
	data->x = info->gx;
	data->y = info->gy;
	enqueue(map, Qtable, queue, data);
	return (0);
}

void reset_map(char map[][MAP_WIDTH], t_info *info)
{
	map[info->gy][info->gx] = GOAL;
	map[info->init_py][info->init_px] = PLAYER;
	info->px = info->init_px;
	info->py = info->init_py;
}

int is_finish(char map[][MAP_WIDTH], t_info *info)
{
	int i;
	char buf[5];
	ssize_t r_size;
	while (1)
	{
		printf("\n\n");
		printf("                               \r");
		printf("finish? (yes or no) -> ");
		r_size = read(STDIN_FILENO, buf, 4);
		for (i=0; i<5; i++)
			if (buf[i] == '\n')
				buf[i] = '\0';
		if (strcmp(buf,"yes") == 0)
			return (1);
		printf("\x1b[3A");
		if (strcmp(buf,"no") == 0)
			return (0);
	}
	return (0);
}

void make_optimal_path(char map[][MAP_WIDTH], double Qtable[][MAP_WIDTH], t_info *info)
{
	int i, j;
	int	maxQ_x, maxQ_y;
	double maxQ;

	while (info->py != info->gy || info->px != info->gx)
	{
		maxQ = -10.0;
		for (i=-1; i<=1; i++)
		{
			for (j=-1; j<=1 ; j++)
			{
				if ((i==0 && j!=0) || (i!=0 && j==0))
				{
					if (map[info->py+i][info->px+j] == GOAL)
					{
						map[info->py][info->px] = OPT;
						return ;
					}
					else if (map[info->py+i][info->px+j] == PATH && maxQ < Qtable[info->py+i][info->px+j])
					{
						maxQ = Qtable[info->py+i][info->px+j];
						maxQ_x = info->px + j;
						maxQ_y = info->py + i;
					}
				}
			}
		}
		info->px = maxQ_x;
		info->py = maxQ_y;
		map[info->py][info->px] = OPT;
	}
}


void disp_map(char map[][MAP_WIDTH])
{
	int i, j;
	printf("\n");
	for (i=0;i<2*MAP_WIDTH+3;i++)
		printf("-");
	printf("\n  ");
	for (i=1; i<=MAP_WIDTH; i++)
		printf("%d ", i);
	printf("\n");
	for (i=0; i<MAP_HEIGHT; i++)
	{
		printf("%d ", i+1);
		for (j=0; j<MAP_WIDTH; j++)
		{
			if (map[i][j] == INIT)
				printf("*");
			else if (map[i][j] == WALL)
				printf("#");
			else if (map[i][j] == PATH)
				printf("\x1b[33mo");
			else if (map[i][j] == PLAYER)
				printf("\x1b[34mP");
			else if (map[i][j] == GOAL)
				printf("\x1b[31mX");
			else if (map[i][j] == OPT)
				printf("\x1b[36m*");
			printf("\x1b[0m ");
		}
		printf("\n");
	}
}

void disp_Qtable(char map[][MAP_WIDTH], double Qtable[][MAP_WIDTH], t_info *info)
{
	int i, j;
	for (i=0; i<8*MAP_WIDTH; i++)
		printf("-");
	printf("\n");
	for (i=0; i<MAP_HEIGHT; i++)
	{
		for (j=0; j<MAP_WIDTH; j++)
		{
			if (map[i][j] == PATH)
				printf("\x1b[33m");
			else if (map[i][j] == PLAYER)
				printf("\x1b[34m");
			else if (map[i][j] == GOAL)
				printf("\x1b[31m");
			else if (map[i][j] == OPT)
				printf("\x1b[36m");
			printf("%7.4f ", Qtable[i][j]);
			printf("\x1b[0m");
		}
		if (i != (MAP_HEIGHT-1))
			printf("\n\n\n\n");
	}
	printf("\n");
	for (i=0; i<8*MAP_WIDTH; i++)
		printf("-");
	printf("\n");
	printf("                               \r");
	printf("phase : %8d  |\n", info->try_c);
	printf("-------------------\n");
	printf("\x1b[2A");
}

double max(double a, double b)
{
	if (a <= b)
		return (b);
	return (a);
}
