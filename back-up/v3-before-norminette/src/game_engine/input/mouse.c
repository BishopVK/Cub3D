/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:01:21 by serferna          #+#    #+#             */
/*   Updated: 2025/05/06 18:01:21 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

// TODO: Mejorar hace cosas raras con el raton y el puntero sale en la pantalla
// Tempblando y saltando de un lado a otro
// void	handle_mouse(t_game *game)
// {
// 	int x, y;
// 	mlx_get_mouse_pos(game->mlx, &x, &y);
// 	if (x < SCREEN_WIDTH / 2)
// 		rotate_left(game, game->frameTime * 3000);
// 	else if (x > SCREEN_WIDTH / 2)
// 		rotate_right(game, game->frameTime * 3000);
// 	mlx_set_mouse_pos(game->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
// }
