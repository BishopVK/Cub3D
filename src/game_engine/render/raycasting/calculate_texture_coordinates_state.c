/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_texture_coordinates_state.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:01:21 by serferna          #+#    #+#             */
/*   Updated: 2025/05/06 18:01:21 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

t_bool	calculate_texture_coordinates_state(t_game *game)
{
	t_ray_data	*rd;

	rd = game->ray_data;
	if (rd->side == 0)
		rd->wall_x = game->player->pos_y + rd->perp_wall_dist * rd->ray_dir_y;
	else
		rd->wall_x = game->player->pos_x + rd->perp_wall_dist * rd->ray_dir_x;
	rd->wall_x -= floor(rd->wall_x);
	rd->tex_x = (int)(rd->wall_x * (double)TEXTURE_WIDTH);
	if (rd->side == 0 && rd->ray_dir_x > 0)
		rd->tex_x = TEXTURE_WIDTH - rd->tex_x - 1;
	if (rd->side == 1 && rd->ray_dir_y < 0)
		rd->tex_x = TEXTURE_WIDTH - rd->tex_x - 1;
	rd->step = 1.0 * TEXTURE_HEIGHT / rd->line_height;
	rd->tex_pos = (rd->draw_start - 100 - (double)SCREEN_HEIGHT / 2
			+ (double)rd->line_height / 2) * rd->step;
	game->state = render_walls_floor_ceiling_state;
	return (TRUE);
}
