/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_closure.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:39 by baskin            #+#    #+#             */
/*   Updated: 2025/11/26 02:03:03 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_validator.h"

static void	add_neighbors_to_stack(t_stack *stack, t_point p,
		t_map_data *data, t_game *game)
{
	const int	dx[] = {1, -1, 0, 0};
	const int	dy[] = {0, 0, 1, -1};
	int			i;
	t_point		new_p;

	i = 0;
	while (i < 4)
	{
		new_p.x = p.x + dx[i];
		new_p.y = p.y + dy[i];
		if (new_p.x >= 0 && new_p.x < data->cols && new_p.y >= 0
			&& new_p.y < data->rows && data->map[new_p.y][new_p.x] != '1'
			&& data->map[new_p.y][new_p.x] != 'V')
		{
			stack_push(stack, new_p, game);
		}
		i++;
	}
}

int	flood_fill(t_map_data *data, int x, int y, t_game *game)
{
	t_stack	*stack;
	t_point	p;
	int		is_valid;

	is_valid = 1;
	stack = stack_create(data->rows * data->cols, game);
	p.x = x;
	p.y = y;
	stack_push(stack, p, game);
	while (!stack_is_empty(stack))
	{
		p = stack_pop(stack);
		if (p.x < 0 || p.y < 0 || p.x >= data->cols || p.y >= data->rows
			|| data->map[p.y][p.x] == ' ')
		{
			is_valid = 0;
			break ;
		}
		if (data->map[p.y][p.x] == '1' || data->map[p.y][p.x] == 'V')
			continue ;
		data->map[p.y][p.x] = 'V';
		add_neighbors_to_stack(stack, p, data, game);
	}
	stack_destroy(stack);
	return (is_valid);
}
