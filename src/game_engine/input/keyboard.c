
#include "../../../include/cub3d.h"

t_bool	is_char_walkable(char c)
{
	return (c == '0' || c == 'W' || c == 'N' || c == 'S' || c == 'E');
}

void	move_forward(t_game *game, double move_speed)
{
	if (is_char_walkable(game->map_s->map[(int)(game->player->pos_x
				+ game->player->dir_x * move_speed)][(int)game->player->pos_y]))
		game->player->pos_x += game->player->dir_x * move_speed;
	if (is_char_walkable(game->map_s->map[(int)game->player->pos_x][(int)(game->player->pos_y
				+ game->player->dir_y * move_speed)]))
		game->player->pos_y += game->player->dir_y * move_speed;
}

void	move_backward(t_game *game, double move_speed)
{
	if (is_char_walkable(game->map_s->map[(int)(game->player->pos_x
				- game->player->dir_x * move_speed)][(int)game->player->pos_y]))
		game->player->pos_x -= game->player->dir_x * move_speed;
	if (is_char_walkable(game->map_s->map[(int)game->player->pos_x][(int)(game->player->pos_y
				- game->player->dir_y * move_speed)]))
		game->player->pos_y -= game->player->dir_y * move_speed;
}

void	move_left(t_game *game, double move_speed)
{
	if (is_char_walkable(game->map_s->map[(int)(game->player->pos_x
				- game->player->plane_x
				* move_speed)][(int)game->player->pos_y]))
		game->player->pos_x -= game->player->plane_x * move_speed;
	if (is_char_walkable(game->map_s->map[(int)game->player->pos_x][(int)(game->player->pos_y
				- game->player->plane_y * move_speed)]))
		game->player->pos_y -= game->player->plane_y * move_speed;
}

void	move_right(t_game *game, double move_speed)
{
	if (is_char_walkable(game->map_s->map[(int)(game->player->pos_x
				+ game->player->plane_x
				* move_speed)][(int)game->player->pos_y]))
		game->player->pos_x += game->player->plane_x * move_speed;
	if (is_char_walkable(game->map_s->map[(int)game->player->pos_x][(int)(game->player->pos_y
				+ game->player->plane_y * move_speed)]))
		game->player->pos_y += game->player->plane_y * move_speed;
}

void	rotate_left(t_game *game, double rotation_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(rotation_speed)
		- game->player->dir_y * sin(rotation_speed);
	game->player->dir_y = old_dir_x * sin(rotation_speed) + game->player->dir_y
		* cos(rotation_speed);
	old_plane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(rotation_speed)
		- game->player->plane_y * sin(rotation_speed);
	game->player->plane_y = old_plane_x * sin(rotation_speed) + game->player->plane_y
		* cos(rotation_speed);
}

void	rotate_right(t_game *game, double rotation_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(-rotation_speed)
		- game->player->dir_y * sin(-rotation_speed);
	game->player->dir_y = old_dir_x * sin(-rotation_speed) + game->player->dir_y
		* cos(-rotation_speed);
	old_plane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(-rotation_speed)
		- game->player->plane_y * sin(-rotation_speed);
	game->player->plane_y = old_plane_x * sin(-rotation_speed)
		+ game->player->plane_y * cos(-rotation_speed);
}

void	handle_input(t_game *game)
{
	double	move_speed;
	double	rotation_speed;

	// Calculate movement speed based on frame time
	move_speed = game->frame_time * 1.5;
	rotation_speed = game->frame_time * 2.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT))
		move_speed *= 2;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game, move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game, move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game, move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game, move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game, rotation_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game, rotation_speed);
}
