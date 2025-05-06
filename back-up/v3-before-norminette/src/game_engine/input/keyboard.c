/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:01:21 by serferna          #+#    #+#             */
/*   Updated: 2025/05/06 18:01:21 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	handle_input(t_game *game)
{
	double	move_speed;
	double	rotation_speed;

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
