/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:09 by baskin            #+#    #+#             */
/*   Updated: 2025/11/26 01:43:34 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

static int	sign(double val)
{
	if (val > 0.0)
		return (1);
	if (val < 0.0)
		return (-1);
	return (0);
}

static void	try_move(t_game *game, double dx, double dy)
{
	int		future_x;
	int		future_y;
	double	padding_x;
	double	padding_y;

	padding_x = sign(dx) * 0.2;
	padding_y = sign(dy) * 0.2;
	future_x = (int)(game->player.x + dx + padding_x);
	future_y = (int)(game->player.y);
	if (future_y >= 0 && future_y < game->map_rows && future_x >= 0
		&& future_x < game->map_cols
		&& game->world_map[future_y][future_x] == '0')
		game->player.x += dx;
	future_x = (int)(game->player.x);
	future_y = (int)(game->player.y + dy + padding_y);
	if (future_y >= 0 && future_y < game->map_rows && future_x >= 0
		&& future_x < game->map_cols
		&& game->world_map[future_y][future_x] == '0')
		game->player.y += dy;
}

static void	handle_rotate(t_game *game, double rot_dir)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	rot = ROT_SPEED * rot_dir;
	game->player.dir_x = game->player.dir_x * cos(rot) - game->player.dir_y
		* sin(rot);
	game->player.dir_y = old_dir_x * sin(rot) + game->player.dir_y * cos(rot);
	game->player.plane_x = game->player.plane_x * cos(rot)
		- game->player.plane_y * sin(rot);
	game->player.plane_y = old_plane_x * sin(rot) + game->player.plane_y
		* cos(rot);
}

static void	handle_translation(t_game *game, double total_dx, double total_dy)
{
	if (game->controls.w)
	{
		total_dx += game->player.dir_x;
		total_dy += game->player.dir_y;
	}
	if (game->controls.s)
	{
		total_dx -= game->player.dir_x;
		total_dy -= game->player.dir_y;
	}
	if (game->controls.a)
	{
		total_dx -= game->player.plane_x;
		total_dy -= game->player.plane_y;
	}
	if (game->controls.d)
	{
		total_dx += game->player.plane_x;
		total_dy += game->player.plane_y;
	}
	total_dx *= MOVE_SPEED;
	total_dy *= MOVE_SPEED;
	try_move(game, total_dx, total_dy);
}

void	handle_movement(t_game *game)
{
	if (game->controls.left)
		handle_rotate(game, -1.0);
	if (game->controls.right)
		handle_rotate(game, 1.0);
	handle_translation(game, 0, 0);
}
