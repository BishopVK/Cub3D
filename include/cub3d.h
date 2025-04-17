/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danjimen <danjimen@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:33:23 by danjimen          #+#    #+#             */
/*   Updated: 2025/04/05 01:24:23 by danjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCREEN_WIDTH 1280 // 640
# define SCREEN_HEIGHT 960 // 480
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

// libft
# include "libft/libft.h"

// X11
# include <X11/X.h>
# include <X11/keysym.h>

// open
# include <sys/types.h>

// close, read
# include <unistd.h>

// malloc, free, exit
# include <stdlib.h>

// perror
# include <stdio.h>

// strerror
# include <string.h>

// errno
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <errno.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef struct s_player
{
	// x and y start position
	double			pos_x;
	double			pos_y;

	// initial direction vector
	double			dir_x;
	double			dir_y;

	// the 2d raycaster version of camera
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct s_ray_data
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_num;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
}					t_ray_data;

typedef struct s_rgb
{
	char			**element;
	int				r;
	int				g;
	int				b;
}					t_rgb;

// Chars in map
typedef struct s_map_chars
{
	int				empty;
	int				wall;
	/* int	collectible;
	int	exit; */
	int				player;
	char			*buffer;
	char			*buffer_trimed;
}					t_map_chars;

// Array
typedef struct s_map
{
	int				player_x;
	int				player_y;
	char			player_dir;
	char			**north;
	char			**south;
	char			**west;
	char			**east;
	t_rgb			*floor;
	t_rgb			*ceiling;
	int				corner_x;
	int				corner_y;
	unsigned int	moves;
	int				file_lines;
	int				map_height;
	size_t			map_max_width;
	char			**map;
	t_map_chars		*chars;
	int				total_map_chars;
	int				total_1;
	int				total_0;
}					t_map;

// XPM
typedef struct s_img
{
	void			*player;
	char			*player_path;
	void			*collec;
	char			*collec_path;
	void			*wall;
	char			*wall_path;
	void			*wall_border;
	char			*wall_border_path;
	void			*back;
	char			*back_path;
	void			*exit;
	char			*exit_path;
	void			*exit_2;
	char			*exit_path_2;
	void			*enemy;
	char			*enemy_path;
	int				img_px;
}					t_img;

// Game
typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				screen_width;
	int				screen_height;
	t_img			*img;
	t_map			*map_s;
}					t_data;

typedef enum s_key_codes
{
	UP_KEY = 65362,
	LEFT_KEY = 65361,
	DOWN_KEY = 65364,
	RIGHT_KEY = 65363,
	ESC_KEY = 65307,
	W_KEY = 119,
	A_KEY = 97,
	S_KEY = 115,
	D_KEY = 100,
	X_BUTTON = 65293,
	SPACE_KEY = 32
}					t_key_codes;

typedef struct s_game
{
	// MLX
	mlx_t			*mlx;

	// Game variables
	// --------------------
	t_player		*player;

	t_ray_data		*ray_data;

	uint32_t		buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

	t_map			*map_s;

	mlx_image_t		*screen;

	double			time;
	double			old_time;
	double			frame_time;

	int				x;

	// State machine
	t_bool			is_done;
	t_bool			(*state)(struct s_game *game);
}					t_game;

/*_____           _        _
 |  __ \         | |      | |
 | |__) | __ ___ | |_ ___ | |_ _   _ _ __   ___  ___
 |  ___/ '__/ _ \| __/ _ \| __| | | | '_ \ / _ \/ __|
 | |   | | | (_) | || (_) | |_| |_| | |_) |  __/\__ \
 |_|   |_|  \___/ \__\___/ \__|\__, | .__/ \___||___/
								__/ | |
								|___/|_|            */

// ╔═.✵.═════════════════════════════════════════════╗
// 					PARSE FOLDER
// ╚═════════════════════════════════════════════.✵.═╝

//////////////////////////////////////////////////////
//						PARSE.C						//
//////////////////////////////////////////////////////
void				read_map(char *map, t_map *map_s);
void				check_arg_extension(char *map);

//////////////////////////////////////////////////////
//						CLEAN.C						//
//////////////////////////////////////////////////////
void				free_elements(t_map *map_s);
void				exit_map_error(t_map *map_s, char *message, int fd);
void				free_double_pointer(char **pointer);

//////////////////////////////////////////////////////
//						DEBUG.C						//
//////////////////////////////////////////////////////
void				print_rgb_values(t_rgb *element);
void				print_element(char **element);
void				print_elements(t_map *map_s);
void				print_map(char **map);

//////////////////////////////////////////////////////
//					DETECT_ELEMENTS.C				//
//////////////////////////////////////////////////////
void				detect_map_elements(t_map *map_s, int fd);

//////////////////////////////////////////////////////
//					CHECK_ELEMENTS.C				//
//////////////////////////////////////////////////////
void				check_elements(t_map *map_s);

//////////////////////////////////////////////////////
//						MAP.C						//
//////////////////////////////////////////////////////
void				check_map_size(t_map *map_s);
void				check_map_chars(t_map *map_s, int i, int j);
void				save_map(char *map, t_map *m_a, int i);

// ╔═.✵.═════════════════════════════════════════════╗
// 					FLOOD_FILL FOLDER
// ╚═════════════════════════════════════════════.✵.═╝

//////////////////////////////////////////////////////
//					FLOOD_FILL.C					//
//////////////////////////////////////////////////////
void				init_flood_fill(t_map *map_s);

//////////////////////////////////////////////////////////
//					GAME ENGINE FOLDER                  //
//////////////////////////////////////////////////////////
t_bool				calculate_ray_direction_state(t_game *game);
t_bool				perform_dda_state(t_game *game);
t_bool				check_ray_completion_state(t_game *game);
t_bool				advance_to_next_ray_state(t_game *game);
t_bool				render_walls_floor_ceiling_state(t_game *game);
t_bool				calculate_wall_distance_state(t_game *game);
t_bool				calculate_wall_drawing_bounds_state(t_game *game);
t_bool				calculate_texture_coordinates_state(t_game *game);
t_bool				render_frame_state(t_game *game);
t_bool				update_frame_data_state(t_game *game);
t_player			*player_factory(double x, double y, char dir);
t_game				*game_factory(mlx_t *mlx, t_map *map, char dir);
void				handle_input(t_game *game);
void				ft_game_hook(void *param);

#endif
