/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbicer <vbicer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:42:52 by baskin            #+#    #+#             */
/*   Updated: 2025/11/27 01:45:22 by vbicer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_ray
{
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	int			draw_start;
	int			draw_end;
	int			line_height;
}				t_ray;

typedef struct s_controls
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_controls;

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_data;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	char		**world_map;
	int			map_rows;
	int			map_cols;

	t_player	player;

	t_texture	north_texture;
	t_texture	south_texture;
	t_texture	west_texture;
	t_texture	east_texture;

	int			floor_color;
	int			ceiling_color;

	t_controls	controls;

	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;

	char		*current_line;
	char		**flood_fill_map;

}				t_game;

typedef struct s_draw_vars
{
	double		wall_x;
	int			tex_x;
	double		step;
	double		tex_pos;

	int			x;
	t_texture	*tex;

}				t_draw_vars;

int				close_window(t_game *game);
int				init_game(t_game *game);
int				init_map(t_game *game, char *filename);
void			init_player(t_game *game, char dir, int x, int y);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
void			handle_movement(t_game *game);
void			raycasting(t_game *game);
int				game_loop(t_game *game);
void			put_pixel(t_game *game, int x, int y, int color);
int				get_texture_pixel(t_texture *texture, int x, int y);
int				darken_color(int color);
void			exit_with_error(const char *msg, t_game *game);
int				validate_map_file(t_game *game, const char *filename);
void			free_game(t_game *game);

void			calc_wall_dist(t_game *game, t_ray *ray);
t_texture		*select_texture(t_game *game, t_ray *ray);
void			draw_wall(t_game *game, t_ray *ray, int x);
void			init_ray(t_game *game, t_ray *ray, int x);
void			calc_step(t_game *game, t_ray *ray);
void			perform_dda(t_game *game, t_ray *ray);
void			*ft_memset(void *b, int c, size_t len);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);

#endif