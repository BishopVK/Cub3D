/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danjimen <danjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:10:36 by danjimen          #+#    #+#             */
/*   Updated: 2025/05/07 11:08:54 by danjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	save_rgb_values(t_rgb *element, char **splited)
{
	element->r = ft_atoi(splited[0]);
	element->g = ft_atoi(splited[1]);
	element->b = ft_atoi(splited[2]);
}

static void	check_rgb_values(t_map *map_s, char **splited, int *count_colors)
{
	int	j;
	int	k;

	j = 0;
	while (splited[j])
	{
		k = 0;
		while (splited[j][k])
		{
			if (!ft_isdigit(splited[j][k]) || k > 2)
			{
				free_double_pointer(splited);
				exit_map_error(map_s, "Invalid RGB value", -1);
			}
			k++;
		}
		if (ft_atoi(splited[j]) < 0 || ft_atoi(splited[j]) > 255)
		{
			free_double_pointer(splited);
			exit_map_error(map_s, "Invalid RGB range color", -1);
		}
		(*count_colors)++;
		j++;
	}
}

void	check_element_rgb(t_map *map_s, t_rgb *element, int i)
{
	int		count_elements;
	char	**splited;
	int		count_colors;

	count_elements = 0;
	while (element->element[i])
	{
		if (i == 1)
		{
			splited = ft_split(element->element[i], ',');
			count_colors = 0;
			check_rgb_values(map_s, splited, &count_colors);
			if (count_colors != 3)
			{
				free_double_pointer(splited);
				exit_map_error(map_s, "Invalid RGB color", -1);
			}
			save_rgb_values(element, splited);
			free_double_pointer(splited);
		}
		count_elements++;
		i++;
	}
	if (count_elements != 2)
		exit_map_error(map_s, "The RGB element is incorrect", -1);
}
