/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danjimen <danjimen@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:00:33 by danjimen          #+#    #+#             */
/*   Updated: 2025/04/17 23:14:30 by danjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// DB (REMOVE FUNCTION)
void	count_pieces(t_map *map_s, char **copy)
{
	int	i;
	int	j;
	int	count_v;

	i = 0;
	count_v = 0;
	while (copy[i])
	{
		j = 0;
		while (copy[i][j])
		{
			if (copy[i][j] == 'V')
				count_v++;
			j++;
		}
		i++;
	}
	(void)map_s;
	/* if (count_v != map_s->total_map_chars)
	{
		free_double_pointer(copy);
		exit_map_error(map_s, "Maps with more than one piece are not allowed", -1);
		exit (EXIT_FAILURE);
	}
	else // DB
		printf("MAPA DE UNA SÓLA PIEZA!! PUEDES CONTINUAR\n"); // DB */
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
	printf("Huecos en el mapa = %i\n", count_2); // DB
	printf("Chars mapa original = %i\n", map_s->total_map_chars); // DB
	printf("Chars mapa comprobado = %i\n", count_chars); // DB
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
	else // DB
		printf("MAPA CERRADO!! PUEDES CONTINUAR\n"); // DB */
}

// DB (REMOVE FUNCTION)
void	flood_fill_pieces(t_map *map_s, char **copy, int x, int y)
{
	if (x < map_s->corner_y || x > map_s->map_height
		|| y < 0 || y >= (int)ft_strlen(map_s->map[x])
		|| copy[x][y] == ' ' || copy[x][y] == '\n' || copy[x][y] == 'V')
		return ;
	copy[x][y] = 'V';
	flood_fill_pieces(map_s, copy, x + 1, y);
	flood_fill_pieces(map_s, copy, x - 1, y);
	flood_fill_pieces(map_s, copy, x, y + 1);
	flood_fill_pieces(map_s, copy, x, y - 1);
}

void	flood_fill_open(t_map *map_s, char **copy, int x, int y)
{
	if (x < 0 || x > map_s->map_height + 1
		|| y < 0 || (size_t)y >= map_s->map_max_width + 2
		|| copy[x][y] == '1' || copy[x][y] == '\n' || copy[x][y] == 'X' || copy[x][y] == ' ')
		return ;
	copy[x][y] = 'X';
	flood_fill_open(map_s, copy, x + 1, y);
	flood_fill_open(map_s, copy, x - 1, y);
	flood_fill_open(map_s, copy, x, y + 1);
	flood_fill_open(map_s, copy, x, y - 1);
}

char	**duplicate_array(t_map *map_s)
{
	char	**copy;
	int		i;

	i = 0;
	copy = (char **)malloc((map_s->map_height + 1) * sizeof(char *));
	while (i < map_s->map_height)
	{
		copy[i] = (char *)malloc(ft_strlen(map_s->map[i]) + 1);
		if (!copy[i])
		{
			free_double_pointer(copy);
			exit_map_error(map_s, "Error allocating memory for copy", -1);
			exit (EXIT_FAILURE);
		}
		ft_strcpy(copy[i], map_s->map[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	**dupe_and_upscale_array(t_map *map_s, char c)
{
	char	**copy;
	int		i;
	int		j;

	i = 0;
	copy = (char **)malloc((map_s->map_height + 3) * sizeof(char *));
	copy[0] = (char *)malloc(map_s->map_max_width + 3);
	ft_memset(copy[0], c, map_s->map_max_width + 1);
	copy[0][map_s->map_max_width + 1] = '\n';
	copy[0][map_s->map_max_width + 2] = '\0';
	copy[map_s->map_height + 1] = (char *)malloc(map_s->map_max_width + 3);
	ft_memset(copy[map_s->map_height + 1], c, map_s->map_max_width + 1);
	copy[map_s->map_height + 1][map_s->map_max_width + 1] = '\n';
	copy[map_s->map_height + 1][map_s->map_max_width + 2] = '\0';
	while (i < map_s->map_height)
	{
		copy[i + 1] = (char *)malloc(map_s->map_max_width + 3);
		if (!copy[i + 1])
		{
			free_double_pointer(copy);
			exit_map_error(map_s, "Error allocating memory for copy", -1);
			exit (EXIT_FAILURE);
		}
		j = 0;
		copy[i + 1][0] = c;
		ft_memset(copy[i + 1], c, map_s->map_max_width + 1);
		while(map_s->map[i][j])
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
	//char	**copy;
	char	**copy_upscale;

	/* copy = duplicate_array(map_s);
	printf("\n-- MAP COPY --\n"); // DB
	print_map(copy); // DB */
	/* flood_fill_pieces(map_s, copy, map_s->corner_y, map_s->corner_x);
	printf("\n-- AFTER FLOOD FILL --\n"); // DB
	print_map(copy); // DB
	count_pieces(map_s, copy);
	free_double_pointer(copy); */
	copy_upscale = dupe_and_upscale_array(map_s, '2');
	printf("\n-- COPY UPSCALE --\n"); // DB
	print_map(copy_upscale); // DB
	flood_fill_open(map_s, copy_upscale, 0, 0);
	printf("\n-- AFTER FLOOD FILL --\n"); // DB
	print_map(copy_upscale); // DB
	count_chars(map_s, copy_upscale);
	free_double_pointer(copy_upscale);
	/* map_s->game_map = dupe_and_upscale_array(map_s, '1');
	printf("\n-- GAME MAP for SERGIO --\n"); // DB
	print_map(map_s->game_map); // DB */
}

/* void	flood_fill(t_map_chars *copy_chars, t_map *copy_array,
	int x, int y)
{
	if (x < 1 || x >= copy_array->height || y < 1 || y >= copy_array->width
	|| copy_array->map[x][y] == '1' || copy_array->map[x][y] == 'V')
	return ;
	if (copy_array->map[x][y] == 'P')
	copy_chars->player--;
	else if (copy_array->map[x][y] == 'E')
	copy_chars->exit--;
	else if (copy_array->map[x][y] == 'C')
	copy_chars->collectible--;
	copy_array->map[x][y] = 'V';
	flood_fill(copy_chars, copy_array, x + 1, y);
	flood_fill(copy_chars, copy_array, x - 1, y);
	flood_fill(copy_chars, copy_array, x, y + 1);
	flood_fill(copy_chars, copy_array, x, y - 1);
} */