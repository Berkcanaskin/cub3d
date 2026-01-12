NAME = cub3D

SRCS = source/main.c \
       source/init.c \
       source/init_player.c \
       source/utils.c \
       source/utils2.c \
       source/controls.c \
       source/controls2.c \
       source/game_exit.c \
       source/raycasting.c \
       source/draw.c \
       source/draw2.c \
       source/get_next_line.c \
       source/get_next_line_utils.c \
       source/map_validator.c \
       source/map_validator2.c \
       source/map_validator_utils.c\
       source/map_validator_utils2.c\
       source/parser_elements.c\
       source/parser_main.c\
       source/map_validator_parser.c\
       source/map_validator_grid.c\
       source/map_validator_closure.c\
       source/map_validator_closure2.c\
       source/stack_array.c

OBJS = $(SRCS:.c=.o)

MLX_DIR = minilibx-linux
MLX_A = $(MLX_DIR)/libmlx.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

INCLUDES = -I. -I$(MLX_DIR)

all: $(NAME)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(MLX_A) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re