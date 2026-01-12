/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_parser.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbicer <vbicer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:44 by baskin            #+#    #+#             */
/*   Updated: 2025/11/27 04:40:17 by vbicer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_validator.h"
#include <stdlib.h>

char	*extract_path(char *line, t_game *game)
{
	char	*start;
	char	*end;
	char	*result;
	int		len;
	int		i;

	start = skip_whitespace(line);
	if (*start == '\0')
		return (NULL);
	end = start + my_strlen(start);
	while (end > start && my_isspace((unsigned char)*(end - 1)))
		end--;
	len = end - start;
	if (len == 0)
		return (NULL);
	result = (char *)malloc(len + 1);
	if (!result)
		exit_with_error("Memory allocation failed", game);
	i = -1;
	while (++i < len)
		result[i] = start[i];
	result[len] = '\0';
	return (result);
}

static int	parse_rgb_value(const char **ptr_to_s, int *component)
{
	int			val;
	const char	*ptr;

	val = 0;
	ptr = skip_whitespace((char *)*ptr_to_s);
	if (*ptr == '-' || *ptr == '+')
		return (-1);
	if (*ptr < '0' || *ptr > '9')
		return (-1);
	while (*ptr >= '0' && *ptr <= '9')
	{
		val = val * 10 + (*ptr - '0');
		ptr++;
	}
	if (val < 0 || val > 255)
		return (-1);
	*component = val;
	*ptr_to_s = ptr;
	return (0);
}

int	parse_rgb(const char *s)
{
	int			color_comps[3];
	const char	*ptr;
	int			j;

	ptr = s;
	j = 0;
	while (j < 3)
	{
		if (parse_rgb_value(&ptr, &color_comps[j]) == -1)
			return (-1);
		ptr = skip_whitespace((char *)ptr);
		if (j < 2)
		{
			if (*ptr != ',')
				return (-1);
			ptr++;
		}
		j++;
	}
	ptr = skip_whitespace((char *)ptr);
	if (*ptr != '\0')
		return (-1);
	return ((color_comps[0] << 16) | (color_comps[1] << 8) | color_comps[2]);
}

int	identify_element(char *line, char **identifiers)
{
	char	*ptr;
	int		i;
	int		id_len;
	char	next;

	ptr = skip_whitespace(line);
	i = 0;
	while (i < 6)
	{
		id_len = my_strlen(identifiers[i]);
		if (my_strncmp(ptr, identifiers[i], id_len) == 0)
		{
			next = ptr[id_len];
			if (next == '\0' || my_isspace((unsigned char)next))
				return (i);
		}
		i++;
	}
	return (-1);
}
