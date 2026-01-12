/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:45:50 by baskin            #+#    #+#             */
/*   Updated: 2025/11/26 02:07:50 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map_validator.h"

t_stack	*stack_create(int capacity, t_game *game)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (!stack)
		exit_with_error("Memory allocation failed for stack.", game);
	stack->points = (t_point *)malloc(sizeof(t_point) * capacity);
	if (!stack->points)
	{
		free(stack);
		exit_with_error("Memory allocation failed for stack points.", game);
	}
	stack->top = -1;
	stack->capacity = capacity;
	return (stack);
}

void	stack_destroy(t_stack *stack)
{
	if (stack)
	{
		if (stack->points)
			free(stack->points);
		free(stack);
	}
}

void	stack_push(t_stack *stack, t_point point, t_game *game)
{
	if (stack->top >= stack->capacity - 1)
	{
		stack_destroy(stack);
		exit_with_error("Stack overflow.", game);
	}
	stack->top++;
	stack->points[stack->top] = point;
}

t_point	stack_pop(t_stack *stack)
{
	t_point	p;

	if (stack_is_empty(stack))
	{
		p.x = -1;
		p.y = -1;
		return (p);
	}
	p = stack->points[stack->top];
	stack->top--;
	return (p);
}

int	stack_is_empty(t_stack *stack)
{
	return (stack->top == -1);
}
