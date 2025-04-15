// #include "../include/cube.h"

// void	hardcode_map(t_game *game)
// {
// 	game->world_map[0][0] = ' ';
// 	game->world_map[0][1] = '1';
// 	game->world_map[0][2] = '1';
// 	game->world_map[0][3] = '1';
// 	game->world_map[0][4] = '1';
// 	game->world_map[0][5] = '1';
// 	game->world_map[0][6] = '1';
// 	game->world_map[0][7] = '1';
// 	game->world_map[0][8] = '1';
// 	game->world_map[0][9] = '1';
// 	game->world_map[1][0] = '1';
// 	game->world_map[1][1] = '0';
// 	game->world_map[1][2] = '0';
// 	game->world_map[1][3] = '0';
// 	game->world_map[1][4] = '0';
// 	game->world_map[1][5] = '0';
// 	game->world_map[1][6] = '0';
// 	game->world_map[1][7] = '0';
// 	game->world_map[1][8] = '0';
// 	game->world_map[1][9] = '1';
// 	game->world_map[2][0] = '1';
// 	game->world_map[2][1] = '0';
// 	game->world_map[2][2] = '1';
// 	game->world_map[2][3] = '1';
// 	game->world_map[2][4] = '1';
// 	game->world_map[2][5] = '1';
// 	game->world_map[2][6] = '1';
// 	game->world_map[2][7] = '0';
// 	game->world_map[2][8] = '0';
// 	game->world_map[2][9] = '1';
// 	game->world_map[3][0] = '1';
// 	game->world_map[3][1] = '0';
// 	game->world_map[3][2] = '0';
// 	game->world_map[3][3] = '0';
// 	game->world_map[3][4] = '0';
// 	game->world_map[3][5] = '0';
// 	game->world_map[3][6] = '1';
// 	game->world_map[3][7] = '0';
// 	game->world_map[3][8] = '0';
// 	game->world_map[3][9] = '1';
// 	game->world_map[4][0] = '1';
// 	game->world_map[4][1] = '0';
// 	game->world_map[4][2] = '1';
// 	game->world_map[4][3] = '1';
// 	game->world_map[4][4] = '1';
// 	game->world_map[4][5] = '0';
// 	game->world_map[4][6] = '1';
// 	game->world_map[4][7] = '0';
// 	game->world_map[4][8] = '0';
// 	game->world_map[4][9] = '1';
// 	game->world_map[5][0] = '1';
// 	game->world_map[5][1] = '0';
// 	game->world_map[5][2] = '0';
// 	game->world_map[5][3] = '0';
// 	game->world_map[5][4] = '0';
// 	game->world_map[5][5] = '0';
// 	game->world_map[5][6] = '1';
// 	game->world_map[5][7] = '0';
// 	game->world_map[5][8] = '0';
// 	game->world_map[5][9] = '1';
// 	game->world_map[6][0] = '1';
// 	game->world_map[6][1] = '0';
// 	game->world_map[6][2] = '0';
// 	game->world_map[6][3] = '0';
// 	game->world_map[6][4] = '0';
// 	game->world_map[6][5] = '0';
// 	game->world_map[6][6] = '0';
// 	game->world_map[6][7] = '0';
// 	game->world_map[6][8] = '0';
// 	game->world_map[6][9] = '1';
// 	game->world_map[7][0] = '1';
// 	game->world_map[7][1] = '0';
// 	game->world_map[7][2] = '0';
// 	game->world_map[7][3] = '0';
// 	game->world_map[7][4] = '0';
// 	game->world_map[7][5] = '0';
// 	game->world_map[7][6] = '0';
// 	game->world_map[7][7] = '0';
// 	game->world_map[7][8] = '0';
// 	game->world_map[7][9] = '1';
// 	game->world_map[8][0] = '1';
// 	game->world_map[8][1] = '0';
// 	game->world_map[8][2] = '0';
// 	game->world_map[8][3] = '0';
// 	game->world_map[8][4] = '0';
// 	game->world_map[8][5] = '0';
// 	game->world_map[8][6] = '0';
// 	game->world_map[8][7] = '0';
// 	game->world_map[8][8] = '0';
// 	game->world_map[8][9] = '1';
// 	game->world_map[9][0] = '1';
// 	game->world_map[9][1] = '1';
// 	game->world_map[9][2] = '1';
// 	game->world_map[9][3] = '1';
// 	game->world_map[9][4] = '1';
// 	game->world_map[9][5] = '1';
// 	game->world_map[9][6] = '1';
// 	game->world_map[9][7] = '1';
// 	game->world_map[9][8] = '1';
// 	game->world_map[9][9] = '1';
// }

// int	main(void)
// {
// 	mlx_t	*mlx;
// 	t_game	*game;

// 	if (!(mlx = mlx_init(screenWidth, screenHeight, "my_game", true)))
// 		return (EXIT_FAILURE);
// 	game = game_factory(mlx);
// 	if (!game)
// 		return (EXIT_FAILURE);
// 	hardcode_map(game);
// 	mlx_loop_hook(mlx, ft_game_hook, game);
// 	mlx_loop(mlx);
// 	mlx_delete_image(mlx, game->screen);
// 	free(game->ray_data);
// 	free(game->player);
// 	free(game);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }
