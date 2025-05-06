/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_wall_distance_state.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:01:21 by serferna          #+#    #+#             */
/*   Updated: 2025/05/06 18:01:21 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

t_bool	calculate_wall_distance_state(t_game *game)
{
	t_ray_data	*rd;

	rd = game->ray_data;
	if (rd->side == 0)
		rd->perp_wall_dist = (rd->side_dist_x - rd->delta_dist_x);
	else
		rd->perp_wall_dist = (rd->side_dist_y - rd->delta_dist_y);
	game->state = calculate_line_height_state;
	return (TRUE);
}
