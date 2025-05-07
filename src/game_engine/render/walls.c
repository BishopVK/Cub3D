/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danjimen <danjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:01:21 by serferna          #+#    #+#             */
/*   Updated: 2025/05/07 09:19:08 by danjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	check_bounds(t_ray_data *rd)
{
	int	draw_start;
	int	draw_end;

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
}

static void	set_sky_earth_colors(t_game *game)
{
	int	draw_start;
	int	draw_end;
	int	y;

	draw_start = game->ray_data->draw_start;
	draw_end = game->ray_data->draw_end;
	y = 0;
	while (y < draw_start)
	{
		game->buffer[y][game->x] = from_rgb(game->map_s->ceiling->r,
				game->map_s->ceiling->g, game->map_s->ceiling->b, 255);
		y++;
	}
	y = draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		game->buffer[y][game->x] = from_rgb(game->map_s->floor->r,
				game->map_s->floor->g, game->map_s->floor->b, 255);
		y++;
	}
}

static void	set_wall_line_texture(t_game *game)
{
	t_ray_data	*rd;

	rd = game->ray_data;
	if (rd->side == 0 && rd->step_x > 0)
		rd->tex_num = 0;
	else if (rd->side == 0 && rd->step_x < 0)
		rd->tex_num = 1;
	else if (rd->side == 1 && rd->step_y > 0)
		rd->tex_num = 2;
	else
		rd->tex_num = 3;
}

static void	set_texture_color(t_game *game)
{
	int			y;
	uint32_t	color;
	int			tex_y;
	t_ray_data	*rd;

	rd = game->ray_data;
	y = game->ray_data->draw_start;
	set_wall_line_texture(game);
	while (y < game->ray_data->draw_end)
	{
		tex_y = (int)game->ray_data->tex_pos & (TEXTURE_HEIGHT - 1);
		game->ray_data->tex_pos += game->ray_data->step;
		if (game->ray_data->tex_num == 0)
			color = get_image_pixel_color(game->so_img, rd->tex_x, tex_y);
		else if (game->ray_data->tex_num == 1)
			color = get_image_pixel_color(game->no_img, rd->tex_x, tex_y);
		else if (game->ray_data->tex_num == 2)
			color = get_image_pixel_color(game->ea_img, rd->tex_x, tex_y);
		else
			color = get_image_pixel_color(game->we_img, rd->tex_x, tex_y);
		game->buffer[y][game->x] = color;
		y++;
	}
}

t_bool	render_walls_floor_ceiling_state(t_game *game)
{
	t_ray_data	*rd;

	rd = game->ray_data;
	check_bounds(rd);
	set_sky_earth_colors(game);
	set_texture_color(game);
	game->state = advance_to_next_ray_state;
	return (TRUE);
}
