/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:50 by baskin            #+#    #+#             */
/*   Updated: 2025/11/26 02:01:18 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_validator.h"

static void	first_pass_process_line(t_game *game, t_parse_state *s, char *line)
{
	char	*ptr;

	ptr = skip_whitespace(line);
	if (*ptr == '\0')
	{
		if (s->map_started == 1)
			s->map_started = 2;
		return ;
	}
	if (s->map_started == 2)
		exit_with_error("Map must be the last element in the file", game);
	if (*ptr == '1' || *ptr == ' ' || *ptr == '0')
	{
		if (s->element_count != 6)
			exit_with_error("Map started before all 6 elements were defined",
				game);
		measure_map_dimensions(s, line);
	}
	else
		handle_element_line(game, s, ptr);
}

void	first_pass(t_game *game, t_parse_state *s, const char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_with_error("File could not be opened or does not exist", game);
	s->line_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		s->line_count++;
		trim_newline(line);
		game->current_line = line;
		first_pass_process_line(game, s, line);
		game->current_line = NULL;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (s->element_count != 6)
		exit_with_error("Missing one or more required elements", game);
	if (s->first_map_line == -1)
		exit_with_error("Map not found in file", game);
}

void	process_map_lines(int fd, t_game *game, t_parse_state *s)
{
	char	*line;
	int		curr;
	int		idx;

	curr = 0;
	idx = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		curr++;
		if (curr >= s->first_map_line && idx < s->map_rows)
		{
			trim_newline(line);
			game->current_line = line;
			parse_map_line(game, s, line, idx++);
			game->current_line = NULL;
		}
		free(line);
		line = get_next_line(fd);
	}
}
