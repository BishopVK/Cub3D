#include "../../../include/cub3d.h"

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
		rd->side_dist_x = (rd->map_x + 1.0 - game->player->pos_x) * rd->delta_dist_x;
	}
	if (rd->ray_dir_y < 0)
	{
		rd->step_y = -1;
		rd->side_dist_y = (game->player->pos_y - rd->map_y) * rd->delta_dist_y;
	}
	else
	{
		rd->step_y = 1;
		rd->side_dist_y = (rd->map_y + 1.0 - game->player->pos_y) * rd->delta_dist_y;
	}
	game->state = perform_dda_state;
	return (TRUE);
}

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
		// Check if we're out of bounds first
		if (rd->map_x < 0 || rd->map_x >= mapWidth || rd->map_y < 0
			|| rd->map_y >= mapHeight)
		{
			rd->hit = 1;
			// Treat as a wall hit
			rd->map_x = fmax(0, fmin(rd->map_x, mapWidth - 1));
			// Clamp to valid indices
			rd->map_y = fmax(0, fmin(rd->map_y, mapHeight - 1));
		}
		// Then check for wall collision
		else if (game->map_s->map[rd->map_x][rd->map_y] == '1')
		{
			rd->hit = 1;
		}
	}
	game->state = calculate_wall_distance_state;
	return (TRUE);
}

t_bool	calculate_wall_distance_state(t_game *game)
{
	t_ray_data	*rd;

	rd = game->ray_data;
	if (rd->side == 0)
		rd->perp_wall_dist = (rd->side_dist_x - rd->delta_dist_x);
	else
		rd->perp_wall_dist = (rd->side_dist_y - rd->delta_dist_y);
	game->state = calculate_wall_drawing_bounds_state;
	return (TRUE);
}

t_bool	calculate_wall_drawing_bounds_state(t_game *game)
{
	t_ray_data	*rd;

	rd = game->ray_data;
	// Calculate height of line to draw on screen
	rd->line_height = (int)(SCREEN_HEIGHT / rd->perp_wall_dist);
	// calculate lowest and highest pixel to fill in current stripe
	rd->draw_start = -rd->line_height / 2 + SCREEN_HEIGHT / 2;
	if (rd->draw_start < 0)
		rd->draw_start = 0;
	rd->draw_end = rd->line_height / 2 + SCREEN_HEIGHT / 2;
	if (rd->draw_end >= SCREEN_HEIGHT)
		rd->draw_end = SCREEN_HEIGHT - 1;
	game->state = calculate_texture_coordinates_state;
	return (TRUE);
}

t_bool	calculate_texture_coordinates_state(t_game *game)
{
	t_ray_data	*rd;

	rd = game->ray_data;
	// calculate value of wallX
	// where exactly the wall was hit
	if (rd->side == 0)
		rd->wall_x = game->player->pos_y + rd->perp_wall_dist * rd->ray_dir_y;
	else
		rd->wall_x = game->player->pos_x + rd->perp_wall_dist * rd->ray_dir_x;
	rd->wall_x -= floor(rd->wall_x);
	// x coordinate on the texture
	rd->tex_x = (int)(rd->wall_x * (double)TEXTURE_WIDTH);
	if (rd->side == 0 && rd->ray_dir_x > 0)
		rd->tex_x = TEXTURE_WIDTH - rd->tex_x - 1;
	if (rd->side == 1 && rd->ray_dir_y < 0)
		rd->tex_x = TEXTURE_WIDTH - rd->tex_x - 1;
	// Calculate step and initial texture position
	rd->step = 1.0 * TEXTURE_HEIGHT / rd->line_height;
	rd->tex_pos = (rd->draw_start - (double)SCREEN_HEIGHT / 2
			+ (double)rd->line_height / 2) * rd->step;
	game->state = render_walls_floor_ceiling_state;
	return (TRUE);
}
