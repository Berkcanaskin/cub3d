/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:52 by baskin            #+#    #+#             */
/*   Updated: 2025/11/26 01:45:25 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_validator.h"

static void	set_color_value(t_game *g, int elem_idx, char *value_start)
{
	int	color;

	color = parse_rgb(value_start);
	if (color == -1)
		exit_with_error("Invalid color format or value", g);
	if (elem_idx == 4)
		g->floor_color = color;
	else if (elem_idx == 5)
		g->ceiling_color = color;
}

static void	set_texture_path(t_game *g, int elem_idx, char *value_start)
{
	char	*path;

	path = extract_path(value_start, g);
	if (path == NULL)
		exit_with_error("Invalid texture path format", g);
	if (elem_idx == 0)
		g->no_path = path;
	else if (elem_idx == 1)
		g->so_path = path;
	else if (elem_idx == 2)
		g->we_path = path;
	else if (elem_idx == 3)
		g->ea_path = path;
}

static void	handle_element(t_game *g, t_parse_state *s, int elem_idx,
		char *line)
{
	char	*value_start;

	if (s->found_elements[elem_idx] == 1)
		exit_with_error("Duplicate element definition", g);
	s->found_elements[elem_idx] = 1;
	s->element_count++;
	value_start = skip_whitespace(line + my_strlen(s->identifiers[elem_idx]));
	if (*value_start == '\0')
		exit_with_error("Missing path/color value for element", g);
	if (elem_idx < 4)
		set_texture_path(g, elem_idx, value_start);
	else
		set_color_value(g, elem_idx, value_start);
}

void	handle_element_line(t_game *game, t_parse_state *s, char *ptr)
{
	int	elem_idx;

	elem_idx = identify_element(ptr, s->identifiers);
	if (elem_idx != -1)
		handle_element(game, s, elem_idx, ptr);
	else
		exit_with_error("Invalid identifier or map sequence", game);
}
