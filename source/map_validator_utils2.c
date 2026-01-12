/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbicer <vbicer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:47 by baskin            #+#    #+#             */
/*   Updated: 2025/11/27 04:51:01 by vbicer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_validator.h"

int	handle_player_char(t_parse_state *s, char c, int row, int x)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		s->player_count++;
		s->player_x = x;
		s->player_y = row;
		s->player_dir = c;
		return (1);
	}
	return (0);
}

void	measure_map_dimensions(t_parse_state *s, char *line)
{
	int	len;

	if (s->first_map_line == -1)
		s->first_map_line = s->line_count;
	s->map_started = 1;
	len = my_strlen(line);
	if (len > s->map_cols)
		s->map_cols = len;
	s->map_rows++;
}

void	parse_map_line(t_game *g, t_parse_state *s, char *line, int row_idx)
{
	int		x;
	char	c;
	int		line_len;

	g->world_map[row_idx] = (char *)malloc(sizeof(char) * (g->map_cols + 1));
	if (!g->world_map[row_idx])
		exit_with_error("Memory allocation failed for map row.", g);
	x = 0;
	line_len = my_strlen(line);
	while (x < g->map_cols)
	{
		if (x < line_len)
			c = line[x];
		else
			c = ' ';
		if (is_valid_map_char(c) == 0)
			exit_with_error("Map contains invalid character", g);
		if (handle_player_char(s, c, row_idx, x) == 1)
			g->world_map[row_idx][x] = '0';
		else
			g->world_map[row_idx][x] = c;
		x++;
	}
	g->world_map[row_idx][g->map_cols] = '\0';
}

int	my_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	my_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
