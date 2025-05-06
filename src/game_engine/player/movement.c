/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:01:21 by serferna          #+#    #+#             */
/*   Updated: 2025/05/06 18:01:21 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static t_bool	is_char_walkable(char c)
{
	return (c == '0' || c == 'W' || c == 'N' || c == 'S' || c == 'E');
}

void	move_forward(t_game *game, double move_speed)
{
	int	x;
	int	y;

	x = (int)(game->player->pos_x + game->player->dir_x * move_speed);
	y = (int)(game->player->pos_y + game->player->dir_y * move_speed);
	if (is_char_walkable(game->map_s->map[x][(int)game->player->pos_y]))
		game->player->pos_x += game->player->dir_x * move_speed;
	if (is_char_walkable(game->map_s->map[(int)game->player->pos_x][y]))
		game->player->pos_y += game->player->dir_y * move_speed;
}

void	move_backward(t_game *game, double move_speed)
{
	int	x;
	int	y;

	x = (int)(game->player->pos_x - game->player->dir_x * move_speed);
	y = (int)(game->player->pos_y - game->player->dir_y * move_speed);
	if (is_char_walkable(game->map_s->map[x][(int)game->player->pos_y]))
		game->player->pos_x -= game->player->dir_x * move_speed;
	if (is_char_walkable(game->map_s->map[(int)game->player->pos_x][y]))
		game->player->pos_y -= game->player->dir_y * move_speed;
}

void	move_left(t_game *game, double move_speed)
{
	int	x;
	int	y;

	x = (int)(game->player->pos_x - game->player->plane_x * move_speed);
	y = (int)(game->player->pos_y - game->player->plane_y * move_speed);
	if (is_char_walkable(game->map_s->map[x][(int)game->player->pos_y]))
		game->player->pos_x -= game->player->plane_x * move_speed;
	if (is_char_walkable(game->map_s->map[(int)game->player->pos_x][y]))
		game->player->pos_y -= game->player->plane_y * move_speed;
}

void	move_right(t_game *game, double move_speed)
{
	int	x;
	int	y;

	x = (int)(game->player->pos_x + game->player->plane_x * move_speed);
	y = (int)(game->player->pos_y + game->player->plane_y * move_speed);
	if (is_char_walkable(game->map_s->map[x][(int)game->player->pos_y]))
		game->player->pos_x += game->player->plane_x * move_speed;
	if (is_char_walkable(game->map_s->map[(int)game->player->pos_x][y]))
		game->player->pos_y += game->player->plane_y * move_speed;
}
