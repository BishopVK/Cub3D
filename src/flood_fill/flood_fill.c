/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danjimen <danjimen@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:00:33 by danjimen          #+#    #+#             */
/*   Updated: 2025/05/07 00:37:09 by danjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	flood_fill_open(t_map *map_s, char **copy, int x, int y)
{
	if (x < 0 || x > map_s->map_height + 1
		|| y < 0 || (size_t)y >= map_s->map_max_width + 2
		|| copy[x][y] == '1' || copy[x][y] == '\n'
		|| copy[x][y] == 'X' || copy[x][y] == ' ')
		return ;
	copy[x][y] = 'X';
	flood_fill_open(map_s, copy, x + 1, y);
	flood_fill_open(map_s, copy, x - 1, y);
	flood_fill_open(map_s, copy, x, y + 1);
	flood_fill_open(map_s, copy, x, y - 1);
}

static void	init_copy_array(char ***copy, t_map *map_s, char c)
{
	*copy = (char **)malloc((map_s->map_height + 3) * sizeof(char *));
	(*copy)[0] = (char *)malloc(map_s->map_max_width + 3);
	ft_memset((*copy)[0], c, map_s->map_max_width + 1);
	(*copy)[0][map_s->map_max_width + 1] = '\n';
	(*copy)[0][map_s->map_max_width + 2] = '\0';
	(*copy)[map_s->map_height + 1] = (char *)malloc(map_s->map_max_width + 3);
	ft_memset((*copy)[map_s->map_height + 1], c, map_s->map_max_width + 1);
	(*copy)[map_s->map_height + 1][map_s->map_max_width + 1] = '\n';
	(*copy)[map_s->map_height + 1][map_s->map_max_width + 2] = '\0';
}

static void	allocate_copy_line(char ***copy, t_map *map_s, int i)
{
	(*copy)[i + 1] = (char *)malloc(map_s->map_max_width + 3);
	if (!(*copy)[i + 1])
	{
		free_double_pointer(*copy);
		exit_map_error(map_s, "Error allocating memory for copy", -1);
		exit (EXIT_FAILURE);
	}
}

char	**dupe_and_upscale_array(t_map *map_s, char c)
{
	char	**copy;
	int		i;
	int		j;

	i = 0;
	init_copy_array(&copy, map_s, c);
	while (i < map_s->map_height)
	{
		allocate_copy_line(&copy, map_s, i);
		j = 0;
		copy[i + 1][0] = c;
		ft_memset(copy[i + 1], c, map_s->map_max_width + 1);
		while (map_s->map[i][j])
		{
			if (map_s->map[i][j] != '\n' && map_s->map[i][j] != ' ')
				copy[i + 1][j + 1] = map_s->map[i][j];
			j++;
		}
		copy[i + 1][map_s->map_max_width + 1] = '\n';
		copy[i + 1][map_s->map_max_width + 2] = '\0';
		i++;
	}
	copy[map_s->map_height + 2] = NULL;
	return (copy);
}

void	init_flood_fill(t_map *map_s)
{
	char	**copy_upscale;

	copy_upscale = dupe_and_upscale_array(map_s, '2');
	flood_fill_open(map_s, copy_upscale, 0, 0);
	count_chars(map_s, copy_upscale);
	free_double_pointer(copy_upscale);
}
