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
