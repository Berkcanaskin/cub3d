/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:14 by baskin            #+#    #+#             */
/*   Updated: 2025/11/26 01:43:38 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->controls.w = 1;
	else if (keycode == KEY_A)
		game->controls.a = 1;
	else if (keycode == KEY_S)
		game->controls.s = 1;
	else if (keycode == KEY_D)
		game->controls.d = 1;
	else if (keycode == KEY_LEFT)
		game->controls.left = 1;
	else if (keycode == KEY_RIGHT)
		game->controls.right = 1;
	else if (keycode == KEY_ESC)
		close_window(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->controls.w = 0;
	else if (keycode == KEY_A)
		game->controls.a = 0;
	else if (keycode == KEY_S)
		game->controls.s = 0;
	else if (keycode == KEY_D)
		game->controls.d = 0;
	else if (keycode == KEY_LEFT)
		game->controls.left = 0;
	else if (keycode == KEY_RIGHT)
		game->controls.right = 0;
	return (0);
}
