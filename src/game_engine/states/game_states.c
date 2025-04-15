#include "../../../include/cub3d.h"

t_bool	check_x_axis_state(t_game *game)
{
	if (game->x >= screenWidth)
	{
		game->state = render_frame_state;
		return (TRUE);
	}
	game->state = calculate_ray_direction_state;
	return (TRUE);
}

t_bool	update_x_axis_state(t_game *game)
{
	game->x++;
	game->state = check_x_axis_state;
	return (TRUE);
}

void	ft_game_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->x = 0;
	game->is_done = FALSE;
	game->state = check_x_axis_state;
	while (!game->is_done)
		game->state(game);
	handle_input(game);
	// handle_mouse(game);
}
