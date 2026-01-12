/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_grid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbicer <vbicer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:42 by baskin            #+#    #+#             */
/*   Updated: 2025/11/27 04:51:14 by vbicer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_validator.h"

void	calculate_map_dimensions(t_game *game, t_parse_state *s)
{
	int	i;
	int	current_len;

	i = s->first_map_line;
	game->map_rows = 0;
	game->map_cols = 0;
	while (i < s->line_count)
	{
		if (*skip_whitespace(s->lines[i]) != '\0')
		{
			game->map_rows++;
			current_len = my_strlen(s->lines[i]);
			if (current_len > game->map_cols)
				game->map_cols = current_len;
		}
		i++;
	}
	if (game->map_rows == 0)
		exit_with_error("Map is empty", game);
	game->world_map = (char **)malloc(sizeof(char *) * (game->map_rows + 1));
	if (!game->world_map)
		exit_with_error("Memory allocation failed", game);
	game->world_map[game->map_rows] = NULL;
}
