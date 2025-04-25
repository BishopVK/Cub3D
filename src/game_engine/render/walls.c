#include "../../../include/cub3d.h"
#include <stdint.h>

uint32_t	get_texture_pixel_color(mlx_image_t *img, int x, int y)
{
	uint32_t	offset;
	uint8_t		red;
	uint8_t		green;
	uint8_t		blue;
	uint8_t		alpha;

	// Calculate offset in the pixel array (RGBA format)
	offset = (y * img->width + x) * 4;
	// Extract color components - MLX textures use RGBA format
	red = img->pixels[offset];
	green = img->pixels[offset + 1];
	blue = img->pixels[offset + 2];
	alpha = img->pixels[offset + 3];
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
		game->buffer[y][game->x] = from_rgb(game->map_s->ceiling->r, game->map_s->ceiling->g, game->map_s->ceiling->b); // Sky blue
	// Draw wall - from drawStart to drawEnd
	for (int y = draw_start; y <= draw_end && y < SCREEN_HEIGHT; y++)
	{
		int tex_y = (int)rd->tex_pos & (TEXTURE_HEIGHT - 1);
        rd->tex_pos += rd->step;
		if (rd->side == 0)
		{
			if (rd->step_x > 0)
				color = get_texture_pixel_color(game->wall_north_img, rd->tex_x, tex_y);
			else
				color = get_texture_pixel_color(game->wall_south_img, rd->tex_x, tex_y);
				//color = from_rgb(0, 255, 0);
		}
		else
		{
			if (rd->step_y > 0)
				//color = from_rgb(0, 0, 255);
				color = get_texture_pixel_color(game->wall_west_img, rd->tex_x, tex_y);
			else
				// color = from_rgb(255, 255, 0);
				// Uint32 color = texture[texNum][texHeight * texY + texX];
				color = get_texture_pixel_color(game->wall_east_img, rd->tex_x, tex_y);
		}
		game->buffer[y][game->x] = color;
	}
	// Draw floor - from drawEnd+1 to SCREEN_HEIGHT-1
	for (int y = draw_end + 1; y < SCREEN_HEIGHT; y++)
		game->buffer[y][game->x] = from_rgb(game->map_s->floor->r, game->map_s->floor->g, game->map_s->floor->b); // Brown
	game->state = advance_to_next_ray_state;
	return (TRUE);
}
