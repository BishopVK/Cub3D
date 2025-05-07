/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danjimen <danjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:10:36 by danjimen          #+#    #+#             */
/*   Updated: 2025/05/07 12:12:11 by danjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	is_valid_png(const char *path, t_map *m_a)
{
	unsigned char	header[8];
	int				fd;
	ssize_t			bytes_read;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_map_error(m_a, "Error opening file", -1);
	bytes_read = read(fd, header, 8);
	if (bytes_read != 8)
		exit_map_error(m_a, "Error reading file header", fd);
	close(fd);
	if (header[0] != 0x89 || header[1] != 0x50 || header[2] != 0x4E
		|| header[3] != 0x47 || header[4] != 0x0D || header[5] != 0x0A
		|| header[6] != 0x1A || header[7] != 0x0A)
		exit_map_error(m_a, "File is not a valid PNG", -1);
}

static void	check_extension_file(char *path, t_map *m_a)
{
	int	map_len;
	int	map_name_len;

	map_len = ft_strlen(path);
	map_name_len = map_len - 4;
	if (!(ft_strncmp(path + map_name_len, ".png", 4) == 0 && map_len > 4
			&& path[map_len - 5] != '/'))
		exit_map_error(m_a, "Wrong texture file extension", -1);
	is_valid_png(path, m_a);
}

static void	check_element_path(t_map *m_a, char **element, int count, int i)
{
	int	fd;

	i = 0;
	while (element[i])
	{
		if (i == 1)
		{
			check_extension_file(element[i], m_a);
			fd = open(element[i], O_RDONLY);
			if (fd == -1)
			{
				if (errno == ENOENT)
					exit_map_error(m_a, "Texture file does not exist", fd);
				else if (errno == EACCES)
					exit_map_error(m_a, "Texture file is not readable", fd);
				else
					exit_map_error(m_a, "Error opening texture file", fd);
			}
			close(fd);
		}
		count++;
		i++;
	}
	if (count != 2)
		exit_map_error(m_a, "The texture element is incorrect", -1);
}

void	check_elements(t_map *map_s)
{
	check_element_path(map_s, map_s->north, 0, 0);
	check_element_path(map_s, map_s->south, 0, 0);
	check_element_path(map_s, map_s->west, 0, 0);
	check_element_path(map_s, map_s->east, 0, 0);
	check_element_rgb(map_s, map_s->floor, 0);
	check_element_rgb(map_s, map_s->ceiling, 0);
}
