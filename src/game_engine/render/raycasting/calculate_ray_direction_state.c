#include "../../../../include/cub3d.h"

t_bool	calculate_ray_direction_state(t_game *game)
{
	t_ray_data	*rd;

	rd = game->ray_data;
	rd->camera_x = 2 * game->x / (double)SCREEN_WIDTH - 1;
	rd->ray_dir_x = game->player->dir_x + game->player->plane_x * rd->camera_x;
	rd->ray_dir_y = game->player->dir_y + game->player->plane_y * rd->camera_x;
	// which box of the map we're in
	rd->map_x = (int)game->player->pos_x;
	rd->map_y = (int)game->player->pos_y;
	// Calculate delta distance
	if (rd->ray_dir_x == 0)
		rd->delta_dist_x = 1e30;
	else
		rd->delta_dist_x = fabs(1 / rd->ray_dir_x);
	if (rd->ray_dir_y == 0)
		rd->delta_dist_y = 1e30;
	else
		rd->delta_dist_y = fabs(1 / rd->ray_dir_y);
	rd->hit = 0;
	// Calculate step and initial sideDist
	if (rd->ray_dir_x < 0)
	{
		rd->step_x = -1;
		rd->side_dist_x = (game->player->pos_x - rd->map_x) * rd->delta_dist_x;
	}
	else
	{
		rd->step_x = 1;
		rd->side_dist_x = (rd->map_x + 1.0 - game->player->pos_x)
			* rd->delta_dist_x;
	}
	if (rd->ray_dir_y < 0)
	{
		rd->step_y = -1;
		rd->side_dist_y = (game->player->pos_y - rd->map_y) * rd->delta_dist_y;
	}
	else
	{
		rd->step_y = 1;
		rd->side_dist_y = (rd->map_y + 1.0 - game->player->pos_y)
			* rd->delta_dist_y;
	}
	game->state = perform_dda_state;
	return (TRUE);
}