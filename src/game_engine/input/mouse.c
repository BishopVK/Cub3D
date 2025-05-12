/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danjimen <danjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:01:21 by serferna          #+#    #+#             */
/*   Updated: 2025/05/12 10:50:23 by danjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"
#include <math.h>

void	handle_mouse(t_game *game)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(game->mlx, &x, &y);
	if (x < ((SCREEN_WIDTH / 2) - 10))
		rotate_left(game, game->frame_time * 3);
	else if (x > ((SCREEN_WIDTH / 2) + 10))
		rotate_right(game, game->frame_time * 3);
	mlx_set_mouse_pos(game->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}
