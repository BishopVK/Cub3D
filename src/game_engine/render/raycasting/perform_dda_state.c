#include "../../../../include/cub3d.h"

t_bool	perform_dda_state(t_game *game)
{
	t_ray_data	*rd;

	rd = game->ray_data;
	// perform DDA
	while (rd->hit == 0)
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (rd->side_dist_x < rd->side_dist_y)
		{
			rd->side_dist_x += rd->delta_dist_x;
			rd->map_x += rd->step_x;
			rd->side = 0;
		}
		else
		{
			rd->side_dist_y += rd->delta_dist_y;
			rd->map_y += rd->step_y;
			rd->side = 1;
		}
		if (game->map_s->map[rd->map_x][rd->map_y] == '1')
			rd->hit = 1;
	}
	game->state = calculate_wall_distance_state;
	return (TRUE);
}
