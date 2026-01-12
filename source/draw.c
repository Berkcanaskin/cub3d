/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 23:39:17 by baskin            #+#    #+#             */
/*   Updated: 2025/11/26 01:43:43 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_floor_ceiling(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(game, x, y, game->ceiling_color);
		y++;
	}
	y = ray->draw_end;
	while (y < WIN_HEIGHT)
	{
		put_pixel(game, x, y, game->floor_color);
		y++;
	}
}

static void	draw_vertical_slice(t_game *game, t_ray *ray, t_draw_vars *vars)
{
	int	y;
	int	color;
	int	tex_y;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)vars->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= vars->tex->height)
			tex_y = vars->tex->height - 1;
		vars->tex_pos += vars->step;
		color = get_texture_pixel(vars->tex, vars->tex_x, tex_y);
		if (ray->side == 1)
			color = darken_color(color);
		put_pixel(game, vars->x, y, color);
		y++;
	}
}

static void	calculate_texture_coords(t_game *game, t_ray *ray,
		t_draw_vars *vars, t_texture *tex)
{
	int	flip;

	if (ray->side == 0)
		vars->wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		vars->wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	vars->wall_x -= floor(vars->wall_x);
	vars->tex_x = (int)(vars->wall_x * (double)tex->width);
	flip = 0;
	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			flip = 1;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			flip = 1;
	}
	if (flip == 1)
		vars->tex_x = tex->width - vars->tex_x - 1;
	vars->step = 1.0 * tex->height / ray->line_height;
	vars->tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2)
		* vars->step;
}

static void	draw_wall_texture(t_game *game, t_ray *ray, int x, t_texture *tex)
{
	t_draw_vars	vars;

	calculate_texture_coords(game, ray, &vars, tex);
	vars.x = x;
	vars.tex = tex;
	draw_vertical_slice(game, ray, &vars);
}

void	draw_wall(t_game *game, t_ray *ray, int x)
{
	t_texture	*texture;

	texture = select_texture(game, ray);
	draw_floor_ceiling(game, ray, x);
	draw_wall_texture(game, ray, x, texture);
}
