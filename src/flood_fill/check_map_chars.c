/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danjimen <danjimen@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:00:33 by danjimen          #+#    #+#             */
/*   Updated: 2025/05/07 00:26:31 by danjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	manage_errors(int count_chars, int count_2, char **copy, t_map *map_s)
{
	if (count_2 != 0)
	{
		free_double_pointer(copy);
		exit_map_error(map_s, "Maps whith holes not allowed", -1);
		exit (EXIT_FAILURE);
	}
	if (count_chars != map_s->total_map_chars)
	{
		free_double_pointer(copy);
		exit_map_error(map_s, "Unclosed map not allowed", -1);
		exit (EXIT_FAILURE);
	}
}

void	count_chars(t_map *map_s, char **copy)
{
	int	i;
	int	j;
	int	count_chars;
	int	count_2;

	i = 0;
	count_chars = 0;
	count_2 = 0;
	while (copy[i])
	{
		j = 0;
		while (copy[i][j])
		{
			if (copy[i][j] == '1' || copy[i][j] == '0' || copy[i][j] == 'N'
				|| copy[i][j] == 'S' || copy[i][j] == 'W' || copy[i][j] == 'E')
				count_chars++;
			if (copy[i][j] == '2')
				count_2++;
			j++;
		}
		i++;
	}
	manage_errors(count_chars, count_2, copy, map_s);
}
