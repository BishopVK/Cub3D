
#include "../../../include/cub3d.h"

t_bool	is_char_walkable(char c)
{
	return (c == '0' || c == 'W' || c == 'N' || c == 'S' || c == 'E');
}

void	move_forward(t_game *game, double moveSpeed)
{
	// if (game->map_s->map[(int)(game->player->posX + game->player->dirX
	// 		* moveSpeed)][(int)game->player->posY] == '0')
	// 	game->player->posX += game->player->dirX * moveSpeed;
	// if (game->map_s->map[(int)game->player->posX][(int)(game->player->posY
	// 		+ game->player->dirY * moveSpeed)] == '0')
	// 	game->player->posY += game->player->dirY * moveSpeed;
	if (is_char_walkable(game->map_s->map[(int)(game->player->posX + game->player->dirX * moveSpeed)][(int)game->player->posY]))
		game->player->posX += game->player->dirX * moveSpeed;
	if (is_char_walkable(game->map_s->map[(int)game->player->posX][(int)(game->player->posY + game->player->dirY * moveSpeed)]))
		game->player->posY += game->player->dirY * moveSpeed;
}

void	move_backward(t_game *game, double moveSpeed)
{
	// if (game->map_s->map[(int)(game->player->posX - game->player->dirX
	// 		* moveSpeed)][(int)game->player->posY] == '0')
	// 	game->player->posX -= game->player->dirX * moveSpeed;
	// if (game->map_s->map[(int)game->player->posX][(int)(game->player->posY
	// 		- game->player->dirY * moveSpeed)] == '0')
	// 	game->player->posY -= game->player->dirY * moveSpeed;
	if (is_char_walkable(game->map_s->map[(int)(game->player->posX - game->player->dirX * moveSpeed)][(int)game->player->posY]))
		game->player->posX -= game->player->dirX * moveSpeed;
	if (is_char_walkable(game->map_s->map[(int)game->player->posX][(int)(game->player->posY - game->player->dirY * moveSpeed)]))
		game->player->posY -= game->player->dirY * moveSpeed;
}

void	move_left(t_game *game, double moveSpeed)
{
	// if (game->map_s->map[(int)(game->player->posX - game->player->planeX
	// 		* moveSpeed)][(int)game->player->posY] == '0')
	// 	game->player->posX -= game->player->planeX * moveSpeed;
	// if (game->map_s->map[(int)game->player->posX][(int)(game->player->posY
	// 		- game->player->planeY * moveSpeed)] == '0')
	// 	game->player->posY -= game->player->planeY * moveSpeed;
	if (is_char_walkable(game->map_s->map[(int)(game->player->posX - game->player->planeX * moveSpeed)][(int)game->player->posY]))
		game->player->posX -= game->player->planeX * moveSpeed;
	if (is_char_walkable(game->map_s->map[(int)game->player->posX][(int)(game->player->posY - game->player->planeY * moveSpeed)]))
		game->player->posY -= game->player->planeY * moveSpeed;
}

void	move_right(t_game *game, double moveSpeed)
{
	// if (game->map_s->map[(int)(game->player->posX + game->player->planeX
	// 		* moveSpeed)][(int)game->player->posY] == '0')
	// 	game->player->posX += game->player->planeX * moveSpeed;
	// if (game->map_s->map[(int)game->player->posX][(int)(game->player->posY
	// 		+ game->player->planeY * moveSpeed)] == '0')
	// 	game->player->posY += game->player->planeY * moveSpeed;
	if (is_char_walkable(game->map_s->map[(int)(game->player->posX + game->player->planeX * moveSpeed)][(int)game->player->posY]))
		game->player->posX += game->player->planeX * moveSpeed;
	if (is_char_walkable(game->map_s->map[(int)game->player->posX][(int)(game->player->posY + game->player->planeY * moveSpeed)]))
		game->player->posY += game->player->planeY * moveSpeed;
}

void	rotate_left(t_game *game, double rotSpeed)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = game->player->dirX;
	game->player->dirX = game->player->dirX * cos(rotSpeed) - game->player->dirY
		* sin(rotSpeed);
	game->player->dirY = oldDirX * sin(rotSpeed) + game->player->dirY
		* cos(rotSpeed);
	oldPlaneX = game->player->planeX;
	game->player->planeX = game->player->planeX * cos(rotSpeed)
		- game->player->planeY * sin(rotSpeed);
	game->player->planeY = oldPlaneX * sin(rotSpeed) + game->player->planeY
		* cos(rotSpeed);
}

void	rotate_right(t_game *game, double rotSpeed)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = game->player->dirX;
	game->player->dirX = game->player->dirX * cos(-rotSpeed)
		- game->player->dirY * sin(-rotSpeed);
	game->player->dirY = oldDirX * sin(-rotSpeed) + game->player->dirY
		* cos(-rotSpeed);
	oldPlaneX = game->player->planeX;
	game->player->planeX = game->player->planeX * cos(-rotSpeed)
		- game->player->planeY * sin(-rotSpeed);
	game->player->planeY = oldPlaneX * sin(-rotSpeed) + game->player->planeY
		* cos(-rotSpeed);
}

void	handle_input(t_game *game)
{
	double	moveSpeed;
	double	rotSpeed;

	// Calculate movement speed based on frame time
	moveSpeed = game->frameTime * 1.5;
	rotSpeed = game->frameTime * 2.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game, moveSpeed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game, moveSpeed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game, moveSpeed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game, moveSpeed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game, rotSpeed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game, rotSpeed);
}
