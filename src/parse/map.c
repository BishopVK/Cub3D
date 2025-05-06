/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danjimen <danjimen@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:14:56 by danjimen          #+#    #+#             */
/*   Updated: 2025/05/07 00:43:20 by danjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_map_size(t_map *map_s)
{
	if (map_s->map_max_width < 4)
		exit_map_error(map_s, "The map is too small to be played", -1);
	if (map_s->map_height < 3)
		exit_map_error(map_s, "The map is too small to be played", -1);
}

static void	chars_and_borders(t_map *map_s, char charac, int i)
{
	char	*trimed;

	if (charac == '1' || charac == '0' || charac == 'N'
		|| charac == 'S' || charac == 'W' || charac == 'E')
		map_s->total_map_chars++;
	if ((i == 0 || i == map_s->map_height - 1)
		&& (charac != '1' && charac != ' ' && charac != '\n'))
		exit_map_error(map_s, "Invalid top or bottom border", -1);
	trimed = ft_strtrim_isspace(map_s->map[i]);
	if ((i > 0 || i < map_s->map_height - 1)
		&& (trimed[0] != '1' || trimed[ft_strlen(trimed) - 1] != '1'))
	{
		free (trimed);
		exit_map_error(map_s, "Invalid left or right border", -1);
	}
	free (trimed);
}

static void	player_coords_and_dir(t_map *map_s, int *i, int *j, int *count)
{
	if (map_s->map[*i][*j] == 'N' || map_s->map[*i][*j] == 'S'
		|| map_s->map[*i][*j] == 'W' || map_s->map[*i][*j] == 'E')
	{
		map_s->player_x = *i;
		map_s->player_y = *j;
		map_s->player_dir = map_s->map[*i][*j];
		(*count)++;
	}
}

void	check_map_chars(t_map *map_s, int i, int j)
{
	int	count;

	count = 0;
	while (map_s->map[i])
	{
		j = 0;
		while (map_s->map[i][j])
		{
			player_coords_and_dir(map_s, &i, &j, &count);
			if (map_s->map[i][j] != 'N' && map_s->map[i][j] != 'S'
					&& map_s->map[i][j] != 'W' && map_s->map[i][j] != 'E'
					&& map_s->map[i][j] != '1' && map_s->map[i][j] != '0'
					&& map_s->map[i][j] != ' ' && map_s->map[i][j] != '\n')
				exit_map_error(map_s, "Error map characters", -1);
			chars_and_borders(map_s, map_s->map[i][j], i);
			j++;
		}
		i++;
	}
	if (count != 1)
		exit_map_error(map_s, "Error number of players", -1);
}

void	save_map(char *map_file, t_map *map_s, int i, int fd)
{
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		exit_map_error(map_s, "Open error", fd);
	map_s->chars->buffer = get_next_line(fd, false);
	map_s->map = malloc((map_s->map_height + 1) * sizeof(char *));
	while (map_s->chars->buffer != NULL)
	{
		map_s->chars->buffer_trimed = ft_strtrim_isspace(map_s->chars->buffer);
		if (map_s->chars->buffer[0] != '\n'
			&& ft_strlen(map_s->chars->buffer_trimed) > 0
			&& map_s->chars->buffer_trimed[0] == '1')
			map_s->map[i++] = ft_strdup(map_s->chars->buffer);
		free(map_s->chars->buffer);
		map_s->chars->buffer = NULL;
		free(map_s->chars->buffer_trimed);
		map_s->chars->buffer_trimed = NULL;
		if (i > 0 && (ft_strlen(map_s->map[i - 1]) >= 256 || i >= 256))
		{
			map_s->map[i] = NULL;
			exit_map_error(map_s, "Map wider or taller than 256", fd);
		}
		map_s->chars->buffer = get_next_line(fd, false);
	}
	map_s->map[i] = NULL;
}
