# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danjimen <danjimen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 13:35:22 by danjimen          #+#    #+#              #
#    Updated: 2025/05/12 11:02:09 by danjimen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors definition
COLOR_CYAN := "\033[36m"
COLOR_GREEN := "\033[32m"
COLOR_RESET := "\033[0m"

# Macro to print a message in cyan color
define print_cyan
	@echo $(COLOR_CYAN)$1$(COLOR_RESET)
endef

# Macro to print a message in green color
define print_green
	@echo $(COLOR_GREEN)$1$(COLOR_RESET)
endef

NAME			=	cub3D
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -g3

SRC_DIR			=	src
PARSE_DIR		=	src/parse
FLOOD_FILL_DIR	=	src/flood_fill

SRC				=	$(SRC_DIR)/cub3d.c \
					$(PARSE_DIR)/parse.c \
					$(PARSE_DIR)/clean.c \
					$(PARSE_DIR)/debug.c \
					$(PARSE_DIR)/detect_elements.c \
					$(PARSE_DIR)/check_elements.c \
					$(PARSE_DIR)/check_rgb.c \
					$(PARSE_DIR)/map.c \
					$(FLOOD_FILL_DIR)/flood_fill.c \
					$(FLOOD_FILL_DIR)/check_map_chars.c \
					./src/init/game_init.c \
					./src/init/player_init.c \
					./src/game_engine/input/keyboard.c \
					./src/game_engine/input/mouse.c \
					./src/game_engine/render/frame.c \
					./src/game_engine/render/raycasting/calculate_ray_direction_state.c \
					./src/game_engine/render/raycasting/perform_dda_state.c \
					./src/game_engine/render/raycasting/calculate_wall_distance_state.c \
					./src/game_engine/render/raycasting/calculate_line_height_state.c \
					./src/game_engine/render/raycasting/calculate_wall_drawing_bounds_state.c \
					./src/game_engine/render/raycasting/calculate_texture_coordinates_state.c \
					./src/game_engine/render/walls.c \
					./src/game_engine/render/game_states.c \
					./src/game_engine/mlx_interface/get_image_pixel_color.c \
					./src/game_engine/player/movement.c \
					./src/game_engine/player/rotation.c \

OBJ				=	$(SRC:.c=.o)

LIBMLX	= ./lib/MLX42
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

LIBFT_DIR		=	include/libft
LIBFT			=	$(LIBFT_DIR)/libft.a


all: $(NAME)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4


$(NAME): libmlx $(LIBFT) $(OBJ)
	# @$(CC) $(CFLAGS) -I$(LIBFT_DIR)-I$(LIBMLX)/include $(OBJ) $(LIBS) $(LIBFT) -o $(NAME)
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(LIBMLX)/include $(OBJ) $(LIBS) $(LIBFT) -o $(NAME)
	$(call print_cyan,"Compiled cub3D")

%.o: %.c
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@
	# @$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(MINILIBX_DIR) -c $< -o $@

clean:
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@rm -rf $(LIBMLX)/build
	@rm -f $(OBJ)
	$(call print_green,"Cleaned cub3D and MLX42 objects")

fclean: clean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	$(call print_green,"Cleaned the executable cub3D")

re: fclean all

rc: re
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@rm -rf $(LIBMLX)/build
	@rm -f $(OBJ)
	$(call print_green,"Cleaned cub3D and MLX42 objects")

r:	rc
	./$(NAME) $(ARG)

valgrind:
	valgrind --tool=memcheck --leak-check=full --log-file=valgrind_output.txt ./$(NAME) $(ARG)

.PHONY: all clean fclean re
