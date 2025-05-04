/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image_pixel_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:01:21 by serferna          #+#    #+#             */
/*   Updated: 2025/05/04 18:01:21 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

uint32_t	from_rgb(int r, int g, int b, int alpha)
{
	return ((r << 24) | (g << 16) | (b << 8) | alpha);
}

uint32_t	get_image_pixel_color(mlx_image_t *img, int x, int y)
{
	uint32_t	offset;
	uint8_t		red;
	uint8_t		green;
	uint8_t		blue;
	uint8_t		alpha;

	offset = (y * img->width + x) * 4;
	red = img->pixels[offset];
	green = img->pixels[offset + 1];
	blue = img->pixels[offset + 2];
	alpha = img->pixels[offset + 3];
	return (from_rgb(red, green, blue, alpha));
}
