
#include "../../include/cub3d.h"

t_game	*game_factory(mlx_t *mlx, t_map *map_s)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = mlx;
	game->player = player_factory(map_s->player_y + 0.5,
			map_s->player_x + 0.5);
	game->ray_data = malloc(sizeof(t_ray_data));
	game->screen = mlx_new_image(mlx, screenWidth, screenHeight);
	mlx_image_to_window(game->mlx, game->screen, 0, 0);
	game->time = 0;
	game->oldTime = 0;
	game->is_done = FALSE;
	game->map_s = map_s;
	return (game);
}
