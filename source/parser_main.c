/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbicer <vbicer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:55 by baskin            #+#    #+#             */
/*   Updated: 2025/11/27 04:00:32 by vbicer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_validator.h"
#include <stdlib.h>

void	init_parse_state(t_parse_state *s)
{
	s->line_count = 0;
	s->first_map_line = -1;
	s->map_started = 0;
	s->element_count = 0;
	s->identifiers[0] = "NO";
	s->identifiers[1] = "SO";
	s->identifiers[2] = "WE";
	s->identifiers[3] = "EA";
	s->identifiers[4] = "F";
	s->identifiers[5] = "C";
	s->player_count = 0;
	s->player_x = -1;
	s->player_y = -1;
	s->player_dir = 0;
	s->lines = NULL;
	s->map_rows = 0;
	s->map_cols = 0;
	ft_memset(s->found_elements, 0, sizeof(int) * 6);
}

void	free_lines(t_parse_state *s)
{
	int	i;

	if (!s->lines)
		return ;
	i = 0;
	while (s->lines[i])
	{
		free(s->lines[i]);
		i++;
	}
	free(s->lines);
	s->lines = NULL;
}
