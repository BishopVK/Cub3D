#include "../../../include/cub3d.h"

t_bool	check_ray_completion_state(t_game *game)
{
	if (game->x >= SCREEN_WIDTH)
	{
		game->state = render_frame_state;
		return (TRUE);
	}
	game->state = calculate_ray_direction_state;
	return (TRUE);
}

t_bool	advance_to_next_ray_state(t_game *game)
{
	game->x++;
	game->state = check_ray_completion_state;
	return (TRUE);
}

void	ft_game_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->x = 0;
	game->is_done = FALSE;
	game->state = check_ray_completion_state;
	while (!game->is_done)
		game->state(game);
	handle_input(game);
	// handle_mouse(game);
}
