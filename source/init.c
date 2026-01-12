/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:35 by baskin            #+#    #+#             */
/*   Updated: 2025/11/26 01:44:18 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_validator.h"

static void	init_game_variables(t_game *game)
{
	ft_memset(&game->controls, 0, sizeof(game->controls));
	ft_memset(&game->north_texture, 0, sizeof(t_texture));
	ft_memset(&game->south_texture, 0, sizeof(t_texture));
	ft_memset(&game->west_texture, 0, sizeof(t_texture));
	ft_memset(&game->east_texture, 0, sizeof(t_texture));
	game->floor_color = 0;
	game->ceiling_color = 0;
	game->no_path = NULL;
	game->so_path = NULL;
	game->we_path = NULL;
	game->ea_path = NULL;
	game->world_map = NULL;
	game->map_rows = 0;
	game->map_cols = 0;
}

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (-1);
	if (WIN_WIDTH <= 0 || WIN_HEIGHT <= 0)
		exit_with_error("Invalid window dimensions", game);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (game->win == NULL)
		return (-1);
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (game->img == NULL)
		return (-1);
	game->img_data = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	init_game_variables(game);
	return (0);
}

static void	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
		exit_with_error("Failed to load texture file", game);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (!texture->addr)
		exit_with_error("Failed to get texture data address", game);
}

int	init_map(t_game *game, char *filename)
{
	validate_map_file(game, filename);
	load_texture(game, &game->north_texture, game->no_path);
	load_texture(game, &game->south_texture, game->so_path);
	load_texture(game, &game->west_texture, game->we_path);
	load_texture(game, &game->east_texture, game->ea_path);
	return (0);
}
