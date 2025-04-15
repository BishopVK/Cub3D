#include "../../include/cub3d.h"

t_player	*player_factory(double x, double y)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->posX = x;
	player->posY = y;
	player->dirX = -1.0;
	player->dirY = 0.0;
	player->planeX = 0.0;
	player->planeY = 0.7;
	return (player);
}
