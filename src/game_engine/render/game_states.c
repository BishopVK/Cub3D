/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_states.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danjimen <danjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:01:21 by serferna          #+#    #+#             */
/*   Updated: 2025/05/07 08:32:29 by danjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		game->is_done = TRUE;
		mlx_close_window(game->mlx);
		return ;
	}
	game->x = 0;
	game->is_done = FALSE;
	game->state = check_ray_completion_state;
	while (!game->is_done)
		game->state(game);
	handle_input(game);
	handle_mouse(game);
}
