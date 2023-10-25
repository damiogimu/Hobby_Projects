#include "my_header.h"

int main(void)
{
	t_info *info={-1,-1,-1,-1}
	t_data *data={-1,-1};
	t_queue *queue;

	initQueue(queue);
	if (setup(info, data) == -1)
		return (-1);
	if (map_check(map, info) == -1)
		return (-1);
	

	free(info);
	free(data);
	free(queue);
	return (0);
}
