#include "../../include/cub3d.h"

t_player	*player_factory(double x, double y)
{
	t_player	*player;
	char dir = 'W';

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	if (dir == 'N')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
	else if (dir == 'S')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
	else if (dir == 'W')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (dir == 'E')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}

	player->pos_x = x;
	player->pos_y = y;
	return (player);
}
