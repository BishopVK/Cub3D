#include "../../../include/cub3d.h"
#include <stdint.h>

uint32_t get_texture_pixel_color(mlx_image_t *img, int x, int y)
{
	uint8_t	*pixel;
		uint8_t	alpha;
		uint8_t	red;
		uint8_t	green;
		uint8_t	blue;

		pixel = &img->pixels[((y * img->width) + x) * 4];
		red = pixel[0];
		green = pixel[1];
		blue = pixel[2];
		alpha = pixel[3];
		return (red << 24 | green << 16 | blue << 8 | alpha);
}

uint32_t	from_rgb(int r, int g, int b)
{
	const int	alpha = 255;

	return ((r << 24) | (g << 16) | (b << 8) | alpha);
}

t_bool	render_walls_floor_ceiling_state(t_game *game)
{
	t_ray_data	*rd;
	int			draw_start;
	int			draw_end;
	uint32_t	color;
	int tex_y;

	rd = game->ray_data;
	draw_start = rd->draw_start;
	draw_end = rd->draw_end;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_start >= SCREEN_HEIGHT)
		draw_start = SCREEN_HEIGHT - 1;
	if (draw_end < 0)
		draw_end = 0;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	for (int y = 0; y < draw_start; y++)
		game->buffer[y][game->x] = from_rgb(51, 255, 255); // Sky blue
	// Draw wall - from drawStart to drawEnd
	for (int y = draw_start; y <= draw_end && y < SCREEN_HEIGHT; y++)
	{
		if (rd->side == 0)
		{
			if (rd->step_x > 0)
				color = from_rgb(255, 0, 0);
			else
				color = from_rgb(0, 255, 0);
		}
		else
		{
			if (rd->step_y > 0)
				color = from_rgb(0, 0, 255);
			else
				color = from_rgb(255, 255, 0);
				// Uint32 color = texture[texNum][texHeight * texY + texX];
				// color = get_texture_pixel_color(game->wall_east_img, rd->tex_num, (TEXTURE_HEIGHT * tex_y + rd->tex_x));
		}
		game->buffer[y][game->x] = color;
	}
	// Draw floor - from drawEnd+1 to SCREEN_HEIGHT-1
	for (int y = draw_end + 1; y < SCREEN_HEIGHT; y++)
		game->buffer[y][game->x] = from_rgb(112, 83, 25); // Brown
	game->state = advance_to_next_ray_state;
	return (TRUE);
}
