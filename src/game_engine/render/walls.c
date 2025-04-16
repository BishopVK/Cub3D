#include "../../../include/cub3d.h"

uint32_t	from_rgb(int r, int g, int b)
{
	const int alpha = 255; // Fully opaque
	return ((r << 24) | (g << 16) | (b << 8) | alpha);
}

t_bool	render_walls_floor_ceiling_state(t_game *game)
{
	t_ray_data	*rd;
	int			drawStart;
	int			drawEnd;
		uint32_t color;

	rd = game->ray_data;
	drawStart = rd->draw_start;
	drawEnd = rd->draw_end;
	if (drawStart < 0)
		drawStart = 0;
	if (drawStart >= SCREEN_HEIGHT)
		drawStart = SCREEN_HEIGHT - 1;
	if (drawEnd < 0)
		drawEnd = 0;
	if (drawEnd >= SCREEN_HEIGHT)
		drawEnd = SCREEN_HEIGHT - 1;
	for (int y = 0; y < drawStart; y++)
		game->buffer[y][game->x] = from_rgb(51, 255, 255); // Sky blue
	// Draw wall - from drawStart to drawEnd
	for (int y = drawStart; y <= drawEnd && y < SCREEN_HEIGHT; y++)
	{
		if (rd->side == 0)
		{                                    // X-axis wall hit (east/west)
			if (rd->step_x > 0)               // East-facing wall (to the right)
				color = from_rgb(255, 0, 0); // Red
			else                             // West-facing wall (to the left)
				color = from_rgb(0, 255, 0); // Green
		}
		else
		{                                      // Y-axis wall hit (north/south)
			if (rd->step_y > 0)
				// South-facing wall (behind at start)
				color = from_rgb(0, 0, 255);   // Blue
			else
				// North-facing wall (in front at start)
				color = from_rgb(255, 255, 0); // Yellow
		}
		game->buffer[y][game->x] = color;
	}
	// Draw floor - from drawEnd+1 to SCREEN_HEIGHT-1
	for (int y = drawEnd + 1; y < SCREEN_HEIGHT; y++)
		game->buffer[y][game->x] = from_rgb(112, 83, 25); // Brown
	game->state = update_x_axis_state;
	return (TRUE);
}
