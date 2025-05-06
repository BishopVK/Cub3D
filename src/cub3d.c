/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danjimen <danjimen@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:39:00 by danjimen          #+#    #+#             */
/*   Updated: 2025/05/06 22:47:57 by danjimen         ###   ########.fr       */
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
	map_s->chars = map_chars; // DB Apuntar a la memoria de map_chars
	map_s->floor = floor_rgb;
	map_s->ceiling = ceiling_rgb;
}

int	init_game_textures(t_game *game, mlx_t *mlx)
{
	game->wall_east = mlx_load_png(game->map_s->east[1]);
	game->wall_west = mlx_load_png(game->map_s->west[1]);
	game->wall_south = mlx_load_png(game->map_s->south[1]);
	game->wall_north = mlx_load_png(game->map_s->north[1]);
	if (!game->wall_east || !game->wall_west || !game->wall_south
		|| !game->wall_north)
	{
		ft_dprintf(2, "Error\n> Failed to load texture\n");
		return (EXIT_FAILURE);
	}
	game->ea_img = mlx_texture_to_image(mlx, game->wall_east);
	game->we_img = mlx_texture_to_image(mlx, game->wall_west);
	game->so_img = mlx_texture_to_image(mlx, game->wall_south);
	game->no_img = mlx_texture_to_image(mlx, game->wall_north);
	return (0);
}

static void	destroy_game(t_game *game)
{
	mlx_delete_image(game->mlx, game->screen);
	mlx_delete_image(game->mlx, game->ea_img);
	mlx_delete_image(game->mlx, game->we_img);
	mlx_delete_image(game->mlx, game->so_img);
	mlx_delete_image(game->mlx, game->no_img);
	mlx_delete_texture(game->wall_east);
	mlx_delete_texture(game->wall_west);
	mlx_delete_texture(game->wall_south);
	mlx_delete_texture(game->wall_north);
	free(game->ray_data);
	free(game->player);
	free(game);
	mlx_terminate(game->mlx);
}

int	main(int argc, char *argv[])
{
	t_map		map_s;
	t_map_chars	map_chars;
	t_rgb		floor_rgb;
	t_rgb		ceiling_rgb;
	mlx_t		*mlx;
	t_game		*game; // DB "Error: Too many variables declarations in a function"

	mlx = NULL; // DB Avoid "error: ‘mlx’ may be used uninitialized"
	initialize_structs(&map_s, &map_chars, &floor_rgb, &ceiling_rgb);
	if (argc != 2)
	{
		ft_dprintf(2, "Error\n> Correct use: %s map.cub\n", argv[0]);
		return (EXIT_FAILURE);
	}
	check_arg_extension(argv[1]);
	read_map(argv[1], &map_s);
	init_flood_fill(&map_s);
	printf("FinalMap\n");
	print_map(map_s.map);
	game = game_factory(&map_s);
	if (!game)
		return (EXIT_FAILURE);
	if (init_game_textures(game, mlx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mlx_loop_hook(mlx, ft_game_hook, game);
	mlx_loop(mlx);
	destroy_game(game);
	free_elements(&map_s);
	free_double_pointer(map_s.map);
	return (EXIT_SUCCESS);
}
