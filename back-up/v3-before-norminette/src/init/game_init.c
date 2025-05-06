/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:01:21 by serferna          #+#    #+#             */
/*   Updated: 2025/05/06 18:01:21 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_game	*game_factory(t_map *map_s)
{
	t_game	*game;
	mlx_t	*mlx;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT,
			"😈 serferna & danjimen's f**king Cub3D 😈", true);
	if (!mlx)
		return (NULL);
	game->mlx = mlx;
	game->player = player_factory(map_s->player_x + 0.5, map_s->player_y + 0.5,
			map_s->player_dir);
	game->ray_data = malloc(sizeof(t_ray_data));
	game->screen = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(game->mlx, game->screen, 0, 0);
	game->time = 0;
	game->old_time = 0;
	game->is_done = FALSE;
	game->map_s = map_s;
	return (game);
}
