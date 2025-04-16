#include "../../include/cub3d.h"

t_player	*player_factory(double x, double y)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos_x = x;
	player->pos_y = y;
	player->dir_x = -1.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.7;
	return (player);
}
