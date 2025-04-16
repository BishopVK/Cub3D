#include "../../../include/cub3d.h"

t_bool	update_frame_data_state(t_game *game)
{
	game->old_time = game->time;
	game->time = mlx_get_time();
	game->frame_time = (game->time - game->old_time);
	// printf("FPS: %f\n", 1.0 / game->frameTime);
	game->is_done = TRUE;
	return (TRUE);
}

t_bool	render_frame_state(t_game *game)
{
	int			x;
	int			y;
	uint32_t	color;

	x = 0;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			color = game->buffer[y][x];
			game->buffer[y][x] = 0x00000000; // Clear the buffer
			mlx_put_pixel(game->screen, x, y, color);
			x++;
		}
		y++;
	}
	game->state = update_frame_data_state;
	return (TRUE);
}
