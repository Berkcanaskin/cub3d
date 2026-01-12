/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbicer <vbicer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:37 by baskin            #+#    #+#             */
/*   Updated: 2025/11/26 01:53:23 by vbicer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_file_extension(char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len < 5)
		return (0);
	if (filename[len - 4] == '.' && filename[len - 3] == 'c' && filename[len
			- 2] == 'u' && filename[len - 1] == 'b')
		return (1);
	return (0);
}

int	check_game(t_game *game, int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3D <map.cub>\n");
		return (1);
	}
	if (!check_file_extension(argv[1]))
	{
		printf("Error\nMap file must have .cub extension\n");
		return (1);
	}
	if (init_game(game) == -1)
	{
		printf("Error\nFailed to initialize game\n");
		free_game(game);
		return (1);
	}
	if (init_map(game, argv[1]) == -1)
	{
		free_game(game);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (check_game(&game, argc, argv))
		return (1);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 1L << 17, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
