/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:01:21 by serferna          #+#    #+#             */
/*   Updated: 2025/05/06 18:01:21 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_bool	set_directions(t_player *player, char dir)
{
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	if (dir == 'N')
		return (player->dir_x = -1.0, player->plane_y = 0.66, TRUE);
	else if (dir == 'S')
		return (player->dir_x = 1.0, player->plane_y = -0.66, TRUE);
	else if (dir == 'W')
		return (player->dir_y = -1.0, player->plane_x = -0.66, TRUE);
	else
		return (player->dir_y = 1.0, player->plane_x = 0.66, TRUE);
}

t_player	*player_factory(double x, double y, char dir)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	set_directions(player, dir);
	player->pos_x = x;
	player->pos_y = y;
	return (player);
}
