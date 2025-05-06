/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_wall_drawing_bounds_state.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:01:21 by serferna          #+#    #+#             */
/*   Updated: 2025/05/06 18:01:21 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

// calculate lowest and highest pixel to fill in current stripe
t_bool	calculate_wall_drawing_bounds_state(t_game *game)
{
	t_ray_data	*rd;

	rd = game->ray_data;
	rd->draw_start = -rd->line_height / 2 + SCREEN_HEIGHT / 2 + 100;
	if (rd->draw_start < 0)
		rd->draw_start = 0;
	rd->draw_end = rd->line_height / 2 + SCREEN_HEIGHT / 2 + 100;
	if (rd->draw_end >= SCREEN_HEIGHT)
		rd->draw_end = SCREEN_HEIGHT - 1;
	game->state = calculate_texture_coordinates_state;
	return (TRUE);
}
