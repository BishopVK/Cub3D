#include "../../../include/cub3d.h"

t_bool	calculate_ray_direction_state(t_game *game)
{
	t_ray_data	*rd;

	rd = game->ray_data;
	rd->cameraX = 2 * game->x / (double)screenWidth - 1;
	rd->rayDirX = game->player->dirX + game->player->planeX * rd->cameraX;
	rd->rayDirY = game->player->dirY + game->player->planeY * rd->cameraX;
	// which box of the map we're in
	rd->mapX = (int)game->player->posX;
	rd->mapY = (int)game->player->posY;
	// Calculate delta distance
	if (rd->rayDirX == 0)
		rd->deltaDistX = 1e30;
	else
		rd->deltaDistX = fabs(1 / rd->rayDirX);
	if (rd->rayDirY == 0)
		rd->deltaDistY = 1e30;
	else
		rd->deltaDistY = fabs(1 / rd->rayDirY);
	rd->hit = 0;
	// Calculate step and initial sideDist
	if (rd->rayDirX < 0)
	{
		rd->stepX = -1;
		rd->sideDistX = (game->player->posX - rd->mapX) * rd->deltaDistX;
	}
	else
	{
		rd->stepX = 1;
		rd->sideDistX = (rd->mapX + 1.0 - game->player->posX) * rd->deltaDistX;
	}
	if (rd->rayDirY < 0)
	{
		rd->stepY = -1;
		rd->sideDistY = (game->player->posY - rd->mapY) * rd->deltaDistY;
	}
	else
	{
		rd->stepY = 1;
		rd->sideDistY = (rd->mapY + 1.0 - game->player->posY) * rd->deltaDistY;
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
		if (rd->sideDistX < rd->sideDistY)
		{
			rd->sideDistX += rd->deltaDistX;
			rd->mapX += rd->stepX;
			rd->side = 0;
		}
		else
		{
			rd->sideDistY += rd->deltaDistY;
			rd->mapY += rd->stepY;
			rd->side = 1;
		}
		// Check if we're out of bounds first
		if (rd->mapX < 0 || rd->mapX >= mapWidth || rd->mapY < 0
			|| rd->mapY >= mapHeight)
		{
			rd->hit = 1;
			// Treat as a wall hit
			rd->mapX = fmax(0, fmin(rd->mapX, mapWidth - 1));
			// Clamp to valid indices
			rd->mapY = fmax(0, fmin(rd->mapY, mapHeight - 1));
		}
		// Then check for wall collision
		else if (game->map_s->map[rd->mapX][rd->mapY] == '1')
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
		rd->perpWallDist = (rd->sideDistX - rd->deltaDistX);
	else
		rd->perpWallDist = (rd->sideDistY - rd->deltaDistY);
	game->state = calculate_wall_drawing_bounds_state;
	return (TRUE);
}

t_bool	calculate_wall_drawing_bounds_state(t_game *game)
{
	t_ray_data	*rd;

	rd = game->ray_data;
	// Calculate height of line to draw on screen
	rd->lineHeight = (int)(screenHeight / rd->perpWallDist);
	// calculate lowest and highest pixel to fill in current stripe
	rd->drawStart = -rd->lineHeight / 2 + screenHeight / 2;
	if (rd->drawStart < 0)
		rd->drawStart = 0;
	rd->drawEnd = rd->lineHeight / 2 + screenHeight / 2;
	if (rd->drawEnd >= screenHeight)
		rd->drawEnd = screenHeight - 1;
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
		rd->wallX = game->player->posY + rd->perpWallDist * rd->rayDirY;
	else
		rd->wallX = game->player->posX + rd->perpWallDist * rd->rayDirX;
	rd->wallX -= floor(rd->wallX);
	// x coordinate on the texture
	rd->texX = (int)(rd->wallX * (double)texWidth);
	if (rd->side == 0 && rd->rayDirX > 0)
		rd->texX = texWidth - rd->texX - 1;
	if (rd->side == 1 && rd->rayDirY < 0)
		rd->texX = texWidth - rd->texX - 1;
	// Calculate step and initial texture position
	rd->step = 1.0 * texHeight / rd->lineHeight;
	rd->texPos = (rd->drawStart - (double)screenHeight / 2
			+ (double)rd->lineHeight / 2) * rd->step;
	game->state = render_walls_floor_ceiling_state;
	return (TRUE);
}
