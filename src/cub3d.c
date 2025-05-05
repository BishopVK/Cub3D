/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danjimen <danjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:39:00 by danjimen          #+#    #+#             */
/*   Updated: 2025/05/05 12:15:51 by danjimen         ###   ########.fr       */
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
	map_s->chars = map_chars; // Apuntar a la memoria de map_chars
	map_s->floor = floor_rgb;
	map_s->ceiling = ceiling_rgb;
}

int	main(int argc, char *argv[])
{
	t_map		map_s;
	t_map_chars	map_chars;
	t_rgb		floor_rgb;
	t_rgb		ceiling_rgb;
	/* uint64_t	x;
	uint64_t	y; */
	mlx_t		*mlx;
	t_game		*game;

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
	// PLAYER COORDS:
	/* x = 0;
	y = 0;
	char dir;
	while (map_s.map[x])
	{
		y = 0;
		while (map_s.map[x][y])
		{
			if (map_s.map[x][y] == 'N' || map_s.map[x][y] == 'S'
				|| map_s.map[x][y] == 'E' || map_s.map[x][y] == 'W')
			{
				map_s.player_x = x;
				map_s.player_y = y;
				dir = map_s.map[x][y];
				break ;
			}
			y++;
		}
		x++;
	}
	printf("Player x: %d, Player y: %d", map_s.player_x, map_s.player_y); // DB */

	if (!(mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "my_game", true)))
		return (EXIT_FAILURE);
	game = game_factory(mlx, &map_s);
	if (!game)
		return (EXIT_FAILURE);

	game->wall_east = mlx_load_png(game->map_s->east[1]);
	game->wall_west = mlx_load_png(game->map_s->west[1]);
	game->wall_south = mlx_load_png(game->map_s->south[1]);
	game->wall_north = mlx_load_png(game->map_s->north[1]);
	if (!game->wall_east || !game->wall_west || !game->wall_south || !game->wall_north)
	{
		ft_dprintf(2, "Error\n> Failed to load texture\n");
		return (EXIT_FAILURE);
	}
	game->ea_img = mlx_texture_to_image(mlx, game->wall_east);
	game->we_img = mlx_texture_to_image(mlx, game->wall_west);
	game->so_img = mlx_texture_to_image(mlx, game->wall_south);
	game->no_img = mlx_texture_to_image(mlx, game->wall_north);

	// hardcode_map(game);
	mlx_loop_hook(mlx, ft_game_hook, game);
	mlx_loop(mlx);
	mlx_delete_image(mlx, game->screen);
	free(game->ray_data);
	free(game->player);
	free(game);
	mlx_terminate(mlx);
	free_elements(&map_s);
	free_double_pointer(map_s.map);
	/*read_to_create_array(argv[1], &map_array);
	create_copy_map_chars(&map_chars, &copy_chars);
	create_array_copy(&map_array, &copy_array);
	flood_fill(&copy_chars, &copy_array, copy_array.start_y,
		copy_array.start_x);
	free_array(&copy_array);
	verify_flood_fill_result(&copy_chars, &map_array);
	initialize_game(&map_chars, &map_array); */
	return (EXIT_SUCCESS);
}
