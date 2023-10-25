#include "my_header.h"

void initQueue(t_queue *queue)
{
	queue->head = 0;
	queue->tail = 0;
	queue->size = 0;
}

void enqueue(t_queue *queue, t_data *data)
{
	if (queue->size == MAX_QUEUE_SIZE)	
	{
		fprintf(stderr, "queue is full\n");
		return ;
	}
	queue->list[queue->head] = *data;
	queue->tail = (queue->tail + 1) % MAX_QUEUE_SIZE;
	queue->size = queue->tail - queue->head;
	if (queue->tail < queue->head)
		queue->size = MAX_QUEUE_SIZE - (queue->head - queue->tail);
}

t_pos *dequeue(t_queue *queue)
{
	t_pos *tmp_data;
	if (queue->size == 0)
	{
		fprintf(stderr, "queue is empty\n");
		return (NULL);
	}
	tmp_data = &(queue->list[queue->head]);
	queue->head = (queue->head + 1) % MAX_QUEUE_SIZE;
	queue->size = queue->tail - queue->head;
	if (queue->tail < queue->head)
		queue->size = MAX_QUEUE_SIZE - (queue->head - queue->tail);
}

int setup(t_info *info, t_data *data, t_queue *queue)
{
	info = malloc(sizeof(t_info)) == NULL;
	data = malloc(sizeof(t_data)) == NULL;
	queue = malloc(sizeof(t_queue)) == NULL;
	if (info == NULL || data == NULL || queue == NULL)
	{
		fprintf(stderr, "malloc Error\n");
		free(info);
		free(data);
		free(queue);
		return (-1);
	}
	return (0);
}

int map_check(char map[][MAP_WIDTH], t_info *info)
{
	for (int i=0; i<MAP_HEIGHT; i++)
	{
		for (int j=0; j<MAP_WIDTH; j++)
		{
			if (map[i][j] == PLAYER)
			{
				info->px = j;
				info->py = i;
			}
			else if (map[i][j] == GOAL)
			{
				info->px = j;
				info->py = i;
			}
		}
	}
}
