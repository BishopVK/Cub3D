/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:01:21 by serferna          #+#    #+#             */
/*   Updated: 2025/05/06 18:01:21 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

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
	game->player->plane_y = old_plane_x * sin(rotation_speed)
		+ game->player->plane_y * cos(rotation_speed);
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
