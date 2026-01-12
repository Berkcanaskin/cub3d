/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbicer <vbicer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 01:43:05 by baskin            #+#    #+#             */
/*   Updated: 2025/11/27 04:00:19 by vbicer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_VALIDATOR_H
# define MAP_VALIDATOR_H

# include "cub3d.h"
# include "get_next_line.h"

typedef struct s_parse_state
{
	int					line_count;
	int					first_map_line;
	int					map_started;
	int					element_count;
	int					found_elements[6];
	char				*identifiers[6];
	char				**lines;
	int					player_count;
	int					player_x;
	int					player_y;
	char				player_dir;
	int					map_rows;
	int					map_cols;
}						t_parse_state;

typedef struct s_map_data
{
	char				**map;
	int					rows;
	int					cols;
}						t_map_data;

int						validate_map_file(t_game *game, const char *filename);

void					init_parse_state(t_parse_state *s);
void					free_lines(t_parse_state *s);

void					calculate_map_dimensions(t_game *game,
							t_parse_state *s);

char					*extract_path(char *line, t_game *game);
int						parse_rgb(const char *s);
int						identify_element(char *line, char **identifiers);

void					check_map_closure(t_game *game);

void					exit_with_error(const char *msg, t_game *game);
int						my_strlen(const char *s);
int						is_valid_map_char(char c);
char					*skip_whitespace(char *str);
void					trim_newline(char *s);
int						my_isspace(int c);
int						my_strncmp(const char *s1, const char *s2, size_t n);

void					handle_element_line(t_game *g, t_parse_state *s,
							char *ptr);
int						handle_player_char(t_parse_state *s, char c, int row,
							int x);
void					measure_map_dimensions(t_parse_state *s, char *line);
void					parse_map_line(t_game *game, t_parse_state *s,
							char *line, int row_idx);
void					first_pass(t_game *game, t_parse_state *s,
							const char *filename);
void					process_map_lines(int fd, t_game *game,
							t_parse_state *s);
int						flood_fill(t_map_data *data, int x, int y,
							t_game *game);
typedef struct s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct s_stack
{
	t_point				*points;
	int					top;
	int					capacity;
}						t_stack;

t_stack					*stack_create(int capacity, t_game *game);
void					stack_destroy(t_stack *stack);
void					stack_push(t_stack *stack, t_point point, t_game *game);
t_point					stack_pop(t_stack *stack);
int						stack_is_empty(t_stack *stack);

#endif