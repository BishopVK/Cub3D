/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danjimen <danjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:14:56 by danjimen          #+#    #+#             */
/*   Updated: 2025/05/05 12:41:06 by danjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_map_size(t_map *map_s)
{
	printf("Map Width: %li\n", map_s->map_max_width); // DB
	printf("Map Height: %i\n", map_s->map_height); // DB
	if (map_s->map_max_width < 4)
		exit_map_error(map_s, "The map is too small to be played", -1);
	/* else if (map_s->map_max_width > 256)
		exit_map_error(map_s, "Map wider than 256 not allowed", -1); */
	if (map_s->map_height < 3)
			exit_map_error(map_s, "The map is too small to be played", -1);
	/* else if (map_s->map_height > 256)
		exit_map_error(map_s, "Map taller than 256 not allowed", -1); */
}

static void	chars_and_borders(t_map *map_s, char charac, int i)
{
	char *trimed;

	if (charac == '1' || charac == '0' || charac == 'N'
		|| charac == 'S' || charac == 'W' || charac == 'E')
		map_s->total_map_chars++;
	if ((i == 0 || i == map_s->map_height - 1) && (charac != '1' && charac != ' ' && charac != '\n'))
	{ // DB
		printf("'%c' its not allowed char\n", charac); // DB
		exit_map_error(map_s, "Invalid top or bottom border", -1);
	} // DB
	trimed = ft_strtrim_isspace(map_s->map[i]);
	// printf("first: %c\n", trimed[0]); // DB
	// printf("last: %c\n", trimed[ft_strlen(trimed) - 1]); // DB
	if ((i > 0 || i < map_s->map_height - 1) && (trimed[0] != '1' || trimed[ft_strlen(trimed) - 1] != '1'))
	{ // DB
		printf("'%c' its not allowed char\n", trimed[ft_strlen(trimed) - 1]); // DB
		free (trimed);
		exit_map_error(map_s, "Invalid left or right border", -1);
	} // DB
	free (trimed);
}

void	detect_first_corner(t_map *map_s)
{
	int	j;

	j = 0;
	if (map_s->map[0] == NULL)
		exit_map_error(map_s, "Error: Map not found", -1);
	while (map_s->map[0][j])
	{
		if (map_s->map[0][j] == '1')
		{
			map_s->corner_y = 0;
			map_s->corner_x = j;
			printf("First corner located at ( %i , %i )\n",
				map_s->corner_x, map_s->corner_y); // DB
			break ;
		}
		j++;
	}
}

void	check_map_chars(t_map *map_s, int i, int j)
{
	int	count;

	count = 0;
	detect_first_corner(map_s);
	while (map_s->map[i])
	{
		j = 0;
		while (map_s->map[i][j])
		{
			if (map_s->map[i][j] == 'N' || map_s->map[i][j] == 'S'
				|| map_s->map[i][j] == 'W' || map_s->map[i][j] == 'E')
			{
				map_s->player_x = i;
				map_s->player_y = j;
				map_s->player_dir = map_s->map[i][j];
				count++;
			}
			if (map_s->map[i][j] != 'N' && map_s->map[i][j] != 'S'
					&& map_s->map[i][j] != 'W' && map_s->map[i][j] != 'E'
					&& map_s->map[i][j] != '1' && map_s->map[i][j] != '0'
					&& map_s->map[i][j] != ' ' && map_s->map[i][j] != '\n')
			{ // DB
				printf("\nForbiden char '%c' detected\n", map_s->map[i][j]); // DB
				exit_map_error(map_s, "Error map characters", -1);
			} // DB
			chars_and_borders(map_s, map_s->map[i][j], i);
			j++;
		}
		i++;
	}
	printf("Player cords: ( %i , %i )\n", map_s->player_x, map_s->player_y); // DB
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
		{ // DB
			printf("Se va a guardar en map_s->map[%i]: %s", i, map_s->chars->buffer); // DB
			map_s->map[i++] = ft_strdup(map_s->chars->buffer);
		} // DB
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
	printf("\n"); // DB
	map_s->map[i] = NULL;
}
