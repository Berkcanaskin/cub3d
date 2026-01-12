/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_closure2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:39 by baskin            #+#    #+#             */
/*   Updated: 2025/11/26 02:06:44 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_validator.h"

static int	is_internal_char(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	check_map_walls(char **map, int rows, int cols)
{
	int	y;
	int	x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			if (is_internal_char(map[y][x]) == 1)
			{
				if (x == 0 || x == cols - 1 || y == 0 || y == rows - 1)
					return (0);
				if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ' || map[y
					- 1][x] == ' ' || map[y + 1][x] == ' ')
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

static char	**create_map_copy(t_game *game)
{
	char	**temp_map;
	int		i;

	temp_map = (char **)malloc(sizeof(char *) * game->map_rows);
	if (temp_map == NULL)
		exit_with_error("Memory allocation failed", game);
	i = -1;
	while (++i < game->map_rows)
	{
		temp_map[i] = ft_strdup(game->world_map[i]);
		if (temp_map[i] == NULL)
			exit_with_error("Memory allocation failed", game);
	}
	return (temp_map);
}

void	check_map_closure(t_game *game)
{
	t_map_data	map_data;
	int			is_valid;

	map_data.map = create_map_copy(game);
	map_data.rows = game->map_rows;
	map_data.cols = game->map_cols;
	is_valid = check_map_walls(game->world_map, game->map_rows,
			game->map_cols);
	if (is_valid)
	{
		is_valid = flood_fill(&map_data, (int)game->player.x,
				(int)game->player.y, game);
	}
	while (--map_data.rows >= 0)
		free(map_data.map[map_data.rows]);
	free(map_data.map);
	if (!is_valid)
		exit_with_error("Map is not closed by walls", game);
}
