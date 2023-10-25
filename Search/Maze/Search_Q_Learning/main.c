#include "my_header.h"

char map[MAP_HEIGHT][MAP_WIDTH]={\
	{"111111111"},\
	{"1000001G1"},\
	{"101110001"},\
	{"101010111"},\
	{"101010101"},\
	{"1P0000001"},\
	{"111111111"}};

int check(int x, int y)
{
	if (x < 0 || MAP_WIDTH <= x || y < 0 || MAP_HEIGHT <= y)
		return (0);
	if (map[y][x] != INIT && map[y][x] != PLAYER)
		return (0);
	return (1);
}

int create_Qtable(double Qtable[][MAP_WIDTH], t_info *info, t_queue *queue, t_data *data)
{
	t_data tmp_data;
	while (queue->size != 0 && queue->size != MAX_QUEUE_SIZE)
	{
		if ((data = dequeue(queue)) == NULL)
			return (0);
		data->distance += 1.0;
		tmp_data.distance = data->distance;
		
		if (check(data->x, data->y-1) == 1)
		{
			tmp_data.x = data->x;
			tmp_data.y = data->y - 1;
			enqueue(map, Qtable, queue, &tmp_data);
		}
		if (check(data->x, data->y+1) == 1)
		{
			tmp_data.x = data->x;
			tmp_data.y = data->y + 1;
			enqueue(map, Qtable, queue, &tmp_data);
		}
		if (check(data->x-1, data->y) == 1)
		{
			tmp_data.x = data->x - 1;
			tmp_data.y = data->y;
			enqueue(map, Qtable, queue, &tmp_data);
		}
		if (check(data->x+1, data->y) == 1)
		{
			tmp_data.x = data->x + 1;
			tmp_data.y = data->y;
			enqueue(map, Qtable, queue, &tmp_data);
		}
	}
	map[info->gy][info->gx] = GOAL;
	map[info->py][info->px] = PLAYER;
	return (1);
}

void move(char map[][MAP_WIDTH], double Qtable[][MAP_WIDTH], t_info *info)
{
	double total;
	double up, right, left, down;
	double dir;
	
	total = exp(Qtable[info->py-1][info->px]/T) \
			+ exp(Qtable[info->py+1][info->px]/T) \
			+ exp(Qtable[info->py][info->px-1]/T) \
			+ exp(Qtable[info->py][info->px+1]/T);
	dir = (rand()%1000)/1000.0;
	up = exp(Qtable[info->py - 1][info->px]/T)/total;
	right = exp(Qtable[info->py][info->px + 1]/T)/total;
	left = exp(Qtable[info->py][info->px - 1]/T)/total;
	down = exp(Qtable[info->py + 1][info->px]/T)/total;

	if (0.0 <= dir && dir < up)
	{
		info->next_px = info->px;
		info->next_py = info->py - 1;
	}
	else if (up <= dir && dir < (up+right))
	{
		info->next_px = info->px + 1;
		info->next_py = info->py;
	}
	else if ((up+right) <= dir && dir < (up+right+left))
	{
		info->next_px = info->px - 1;
		info->next_py = info->py;
	}
	else
	{
		info->next_px = info->px;
		info->next_py = info->py + 1;
	}
	if (0 <= info->next_py && info->next_py < MAP_HEIGHT && 0 <= info->next_px && info->next_px < MAP_WIDTH)
	{
		update_Qtable(Qtable, info);
		if (map[info->next_py][info->next_px] != WALL)
		{
			map[info->py][info->px] = PATH;
			info->px = info->next_px;
			info->py = info->next_py;
			map[info->py][info->px] = PLAYER;
		}
	}
}

void update_Qtable(double Qtable[][MAP_WIDTH], t_info *info)
{
	double next_maxQ;
	double reward = 0.0;

	next_maxQ = max(max(Qtable[info->next_py-1][info->next_px],Qtable[info->next_py+1][info->next_px]),\
					max(Qtable[info->next_py][info->next_px-1],Qtable[info->next_py][info->next_px+1]));
	if (map[info->next_py][info->next_px] == WALL)
		reward = -1.0;
	else if (map[info->next_py][info->next_px] == GOAL)
		reward = 1.0;	
	Qtable[info->py][info->px] = (1.0-alpha)*Qtable[info->py][info->px] + alpha*(reward + gamma*next_maxQ);
}

int main(void)
{
	int finish_f = 0;
	double Qtable[MAP_HEIGHT][MAP_WIDTH];
	t_info info={-1,-1,0,0,-1,-1,-1,-1,1};
	t_data data={-1,-1,0.0};
	t_queue queue;

	initQueue(&queue);
	if (setup(map, Qtable, &info, &queue, &data) == -1)
		return (-1);
	create_Qtable(Qtable, &info, &queue, &data);

	disp_map(map);
	disp_Qtable(map, Qtable, &info);
	usleep(DELAY);
	while (finish_f != 1)
	{
		if (info.py == info.gy && info.px == info.gx)
		{
			reset_map(map, &info);
			if (info.try_c++ % TRIAL == 0 && (finish_f = is_finish(map, &info)) == 1)
				make_optimal_path(map, Qtable, &info);
		}
		else
			move(map, Qtable, &info);
		if (finish_f != 1)
			printf("\x1b[%dF", (5*MAP_HEIGHT+2));
		disp_map(map);
		disp_Qtable(map, Qtable, &info);
		usleep(DELAY);
	}
	return (0);
}
