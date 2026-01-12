/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:50 by baskin            #+#    #+#             */
/*   Updated: 2025/11/26 02:00:23 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_validator.h"

static void	second_pass(t_game *game, t_parse_state *s, const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_with_error("File could not be opened or does not exist", game);
	process_map_lines(fd, game, s);
	close(fd);
}

static void	check_player_count(t_game *game, t_parse_state *state)
{
	if (state->player_count == 1)
		init_player(game, state->player_dir, state->player_x, state->player_y);
	else
	{
		exit_with_error("Map must contain exactly one player start position",
			game);
	}
}

int	validate_map_file(t_game *game, const char *filename)
{
	t_parse_state	state;

	init_parse_state(&state);
	first_pass(game, &state, filename);
	game->world_map = (char **)malloc(sizeof(char *) * (state.map_rows));
	if (!game->world_map)
		exit_with_error("Memory allocation failed for map.", game);
	ft_memset(game->world_map, 0, sizeof(char *) * (state.map_rows));
	game->map_rows = state.map_rows;
	game->map_cols = state.map_cols;
	second_pass(game, &state, filename);
	check_player_count(game, &state);
	check_map_closure(game);
	return (0);
}
