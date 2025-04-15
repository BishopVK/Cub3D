# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danjimen <danjimen@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 13:35:22 by danjimen          #+#    #+#              #
#    Updated: 2025/04/05 00:35:52 by danjimen         ###   ########.fr        #
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
					$(PARSE_DIR)/map.c \
					$(FLOOD_FILL_DIR)/flood_fill.c \
					./src/init/game_init.c \
					./src/init/player_init.c \
					./src/game_engine/input/keyboard.c \
					./src/game_engine/input/mouse.c \
					./src/game_engine/render/frame.c \
					./src/game_engine/render/raycasting.c \
					./src/game_engine/render/walls.c \
					./src/game_engine/states/game_states.c \

OBJ				=	$(SRC:.c=.o)

LIBMLX	= ./lib/MLX42
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

LIBFT_DIR		=	include/libft
LIBFT			=	$(LIBFT_DIR)/libft.a

MINILIBX_DIR	=	include/minilibx-linux
MINILIBX		=	$(MINILIBX_DIR)/libmlx_Linux.a

all: $(NAME)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(MINILIBX):
	@$(MAKE) -C $(MINILIBX_DIR)

$(NAME): libmlx $(LIBFT) $(MINILIBX) $(OBJ)
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(MINILIBX_DIR) -I$(LIBMLX)/include $(OBJ) $(LIBS) $(LIBFT) $(MINILIBX) -L$(MINILIBX_DIR) -lX11 -lXext -lbsd -o $(NAME)
	$(call print_cyan,"Compiled cub3D")

%.o: %.c
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(MINILIBX_DIR) -c $< -o $@

clean:
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(MINILIBX_DIR) clean
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(MAKE) -s -C $(MINILIBX_DIR) clean
	@rm -f $(NAME)
	$(call print_green,"Cleaned the executable cub3D")

re: fclean all

rc: re
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(MINILIBX_DIR) clean
	@rm -f $(OBJ)

r:	rc
	./$(NAME) $(ARG)

valgrind:	rc
	valgrind --leak-check=full ./$(NAME) $(ARG)

.PHONY: all clean fclean re
