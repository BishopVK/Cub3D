/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danjimen <danjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:39:00 by danjimen          #+#    #+#             */
/*   Updated: 2025/05/07 12:10:54 by danjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	initialize_structs(t_map *map_s, t_map_chars *map_chars,
		t_rgb *floor_rgb, t_rgb *ceiling_rgb)
{
	ft_memset(map_s, 0, sizeof(t_map));
	ft_memset(map_chars, 0, sizeof(t_map_chars));
	ft_memset(floor_rgb, 0, sizeof(t_rgb));
	ft_memset(ceiling_rgb, 0, sizeof(t_rgb));
	map_s->chars = map_chars;
	map_s->floor = floor_rgb;
	map_s->ceiling = ceiling_rgb;
}

static void	destroy_images_and_textures(t_game *game)
{
	if (game->mlx && game->screen)
		mlx_delete_image(game->mlx, game->screen);
	if (game->mlx && game->ea_img)
		mlx_delete_image(game->mlx, game->ea_img);
	if (game->mlx && game->we_img)
		mlx_delete_image(game->mlx, game->we_img);
	if (game->mlx && game->so_img)
		mlx_delete_image(game->mlx, game->so_img);
	if (game->mlx && game->no_img)
		mlx_delete_image(game->mlx, game->no_img);
	if (game->wall_east)
		mlx_delete_texture(game->wall_east);
	if (game->wall_west)
		mlx_delete_texture(game->wall_west);
	if (game->wall_south)
		mlx_delete_texture(game->wall_south);
	if (game->wall_north)
		mlx_delete_texture(game->wall_north);
}

static void	destroy_game(t_game *game, t_map *map_s)
{
	destroy_images_and_textures(game);
	if (game->ray_data)
		free(game->ray_data);
	if (game->player)
		free(game->player);
	if (game->mlx)
		mlx_terminate(game->mlx);
	if (game)
		free(game);
	exit_map_error(map_s, "", -1);
}

int	init_game_textures(t_game *game, mlx_t *mlx, t_map *map_s)
{
	game->ea_img = NULL;
	game->we_img = NULL;
	game->so_img = NULL;
	game->no_img = NULL;
	game->wall_east = mlx_load_png(game->map_s->east[1]);
	game->wall_west = mlx_load_png(game->map_s->west[1]);
	game->wall_south = mlx_load_png(game->map_s->south[1]);
	game->wall_north = mlx_load_png(game->map_s->north[1]);
	if (!game->wall_east || !game->wall_west || !game->wall_south
		|| !game->wall_north)
	{
		ft_dprintf(2, "Error\n> Failed to load texture\n");
		destroy_game(game, map_s);
		return (EXIT_FAILURE);
	}
	game->ea_img = mlx_texture_to_image(mlx, game->wall_east);
	game->we_img = mlx_texture_to_image(mlx, game->wall_west);
	game->so_img = mlx_texture_to_image(mlx, game->wall_south);
	game->no_img = mlx_texture_to_image(mlx, game->wall_north);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_map		map_s;
	t_map_chars	map_chars;
	t_rgb		floor_rgb;
	t_rgb		ceiling_rgb;
	t_game		*game;

	if (argc != 2)
		return (ft_dprintf(2, "Error\n> Correct use: %s map.cub\n", argv[0]),
			EXIT_FAILURE);
	initialize_structs(&map_s, &map_chars, &floor_rgb, &ceiling_rgb);
	check_arg_extension(argv[1]);
	read_map(argv[1], &map_s);
	init_flood_fill(&map_s);
	game = game_factory(&map_s);
	if (!game)
		return (EXIT_FAILURE);
	if (init_game_textures(game, game->mlx, &map_s) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mlx_loop_hook(game->mlx, ft_game_hook, game);
	mlx_loop(game->mlx);
	destroy_game(game, &map_s);
	free_elements(&map_s);
	free_double_pointer(map_s.map);
	return (EXIT_SUCCESS);
}
