/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_line_height_state.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:01:21 by serferna          #+#    #+#             */
/*   Updated: 2025/05/06 18:01:21 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

// Calculate height of line to draw on screen
t_bool	calculate_line_height_state(t_game *game)
{
	t_ray_data	*rd;

	rd = game->ray_data;
	rd->line_height = (int)(SCREEN_HEIGHT / rd->perp_wall_dist);
	game->state = calculate_wall_drawing_bounds_state;
	return (TRUE);
}
