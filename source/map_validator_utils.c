/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:47 by baskin            #+#    #+#             */
/*   Updated: 2025/11/26 02:04:40 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_validator.h"

void	exit_with_error(const char *msg, t_game *game)
{
	printf("Error\n%s\n", msg);
	if (game)
	{
		if (game->current_line)
		{
			free(game->current_line);
			game->current_line = NULL;
		}
		free_game(game);
	}
	exit(1);
}

int	my_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s && s[len] != '\0')
		len++;
	return (len);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

char	*skip_whitespace(char *str)
{
	while (*str && my_isspace((unsigned char)*str))
		str++;
	return (str);
}

void	trim_newline(char *s)
{
	int	len;

	len = my_strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		s[len - 1] = '\0';
}
