/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:40:38 by baskin            #+#    #+#             */
/*   Updated: 2025/11/26 02:06:08 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	int	pixel_index;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		pixel_index = y * game->line_length + x * (game->bits_per_pixel / 8);
		*(int *)(game->img_data + pixel_index) = color;
	}
}

int	get_texture_pixel(t_texture *texture, int x, int y)
{
	int	pixel_index;

	if (!texture || !texture->addr)
		return (0xFF0000);
	if (x < 0)
		x = 0;
	if (x >= texture->width)
		x = texture->width - 1;
	if (y < 0)
		y = 0;
	if (y >= texture->height)
		y = texture->height - 1;
	pixel_index = y * texture->line_length + x * (texture->bits_per_pixel / 8);
	return (*(int *)(texture->addr + pixel_index));
}

int	darken_color(int color)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) / 2;
	g = ((color >> 8) & 0xFF) / 2;
	b = (color & 0xFF) / 2;
	return ((r << 16) | (g << 8) | b);
}
