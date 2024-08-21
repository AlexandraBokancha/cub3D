/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:40:07 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/21 16:52:03 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <errno.h>

# include "../libft/includes/libft.h"
//# include "../mlx/mlx.h"

/*
 * WINDOW SIZE
 */
# define DEFAULT_WIN_WIDTH 1920
# define DEFAULT_WIN_HEIGHT 1080

/*
 * WALL ORIENTATION
 */
# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4

/*
 * KEYMAPPING
 */
# define ESC 0xFF1B
# define W 0x0077
# define A 0x0061
# define S 0x0073
# define D 0x0064
# define ARROW_LEFT 0xFF51
# define ARROW_RIGHT 0xFF53

/*
 * DEFAULT CONFIGURATION
 */
# define MOVE_SPEED 0.05
# define ROTATION_SPEED 0.03
# define DELTA 0.25

/**
 * @struct s_vec
 * @brief 2D vector structure
 *
 * This structure can represent 2D vector or coordinate
 *
 * @var s_vec::x
 * X coordinate
 *
 * @var s_vec::y
 * Y coordinate
 */
typedef struct s_vec
{
	double	x;
	double	y;
}				t_vec;

/**
 * @struct s_raycast
 * @brief Structure conatining all necessary variable for raycasting
 *
 * This structure will contain all variable such as player distance to wall,
 * distance between two walls given a certain ray/angle. But also map position
 * of the ray ...
 *
 * @var s_raycast::x
 * The column of the window we're evaluating
 *
 * @var s_raycast::cam_x
 * A raycast compatible conversion of the column to cam_x position,
 * convert value from [1;screen_width] to value in [-1;1], 0 being the center
 *
 * @var s_raycast::ray_dir
 * A vector describing the direction of the casted ray
 *
 * @var s_raycast:side_dist
 * A vector describing the distance between player and the closest wall
 * (given a certain ray)
 *
 * @var s_raycast::delta_dist
 * A vector describing the distance between two walls (given a certain ray)
 *
 * @var s_raycast::imap
 * A pair containing the actual ray position in the map (imap = int player_pos)
 *
 * @var s_raycast::step
 * A pair of int defining in witch direction we should check walls.
 * Depending on were we're looking we would like to check for the 
 * x - 1 wall instead of the x + 1 wall
 *
 * @var s_raycast::perp_wall_dist
 * Distance between wall and camera plane.
 * If we use distance between wall and player we would get fisheye effect
 *
 * @var s_raycast::side
 * 1 if the ray hit a EAST/WEST facing wall
 * 0 if the ray hit a NORTH/SOUTH facing wall
 */
typedef struct s_raycast
{
	int		x;
	double	cam_x;
	t_vec	ray_dir;
	t_vec	side_dist;
	t_vec	delta_dist;
	t_vec	imap;
	t_vec	step;
	double	perp_wall_dist;
	int		side;
}				t_raycast;

/**
 * @struct s_img
 * @brief MLX image data type
 * 
 * This structure contain MLX.image fields to be used in a more efficient way
 *
 * @var s_img::img
 * Pointer to MLX.image
 *
 * @var s_img::addr
 * Information about image
 *
 * @var s_img::bits_per_pixel
 * bits per pixel (impact number of colors that can be rendered)
 *
 * @var s_img::line_length
 * Number of bytes in one line
 * 
 * @var s_img::endian
 * endianess of color
 *
 * */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

/**
 * @struct t_map_info
 * @brief Structure holding map2d data
 * 
 * This structure contains data for a map such as:
 * start position of a player and start orientation (N, S, E or W)
 *
 * @var t_map_info:map2d
 * An array containing map info
 * 
 * @var t_map_info::start_x, start_y
 * Start position of a player
 * 
 * @var t_map_info::start_o;
 * Start orientation of a player
 */
typedef	struct	s_map_info
{
	char **map2d;
	int	map2_height;
	int	start_map;
	int	map_pos;
	int	start_x;
	int	start_y;
	int	start_o;
}				t_map_info;

typedef	enum	s_id
{
	nord,
	south, 
	east,
	west	
}				t_id;

/**
 * @struct t_texture
 * @brief Structure holding texture data
 * 
 * This structure contains data for a texture such as:
 * texture identifier, path to the structure
 *
 * @var t_texture::direction
 * Identifier : NO, SO, WE and EA
 * 
 * @var t_texture::path
 * Path to the texture file
 */
typedef struct s_texture
{
	char	*direction;
	char	*N_path;
	char	*E_path;
	char	*W_path;
	char	*S_path;
	t_id	identor;
}				t_texture;

/**
 * @struct t_colors
 * @brief Structure holding colors data
 * 
 * This structure contains data for a color such as:
 * color of a ceiling and a floor
 *
 * @var t_colors::f_color
 * Floor color
 * 
 * @var t_colors::c_color
 * Ceiling color
 */
typedef	struct	s_colors
{
	char *f_color;
	char *c_color;
}				t_colors;

/**
 * @struct s_data
 * @brief cub3D holding all program data
 * 
 * This structure contain all necessary program data such as:
 * MLX, window instance, window dimensions, the map, player info
 * camera info, textures and colors
 *
 * @var s_data::mlx
 * mlx connection 
 *
 * @var s_data::window
 * mlx window
 *
 * @var s_data::w_height
 * Window height
 *
 * @var s_data::w_width
 * Window width
 *
 * @var s_data::m_height
 * Map height
 *
 * @var s_data::m_width
 * Map width
 * 
 * @var s_data::img
 * mlx window image
 *
 * @var s_data::map
 * Game map
 *
 * @var s_data::player_pos
 * Player position in the map
 *
 * @var s_data::direction
 * Player look direction
 *
 * @var s_data::camera_plane
 * Camera Y plane
 * 
 * @var s_data::textures
 * North, South, West, East texture
 * */

typedef struct s_data
{
	void	*mlx;
	void	*window;
	int		w_height;
	int		w_width;
	int		m_height;
	int		m_width;
	t_img	img;
	char	**map;
	t_vec	player_pos;
	t_vec	direction;
	t_vec	camera_plane;
	t_texture	textures;
	t_map_info	map_info;
	t_colors	colors;
}				t_data;

// ft_mlx_pixel_put.c
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);

// Print error.h
void	print_error(const char *func, int error_nbr);

// free_cub.c
void	free_cub(t_data *data);
void	ft_free_tab(char **tab, int height);
int		exit_cub(t_data *data);

// init_cub.c
t_vec	init_vec(double x, double y);
t_data	*init_cub(void);

// mlx_hook
int		key_hook(int keycode, void *param);
//render.c
int		render(void *param);

// parser.c
t_data	*init_map(t_data *data, char  *file_name);
int		find_map_info(char **map, t_data *data);
int    process_info_lines(t_data *data, char *line);
int		map_h(char *file_name);
int		parsing(t_data *data);
void	strip_newline(char *str);
int		is_closed(char **map, int height);
int		is_valid_chars(char **map, int height);
void	fill_spaces(char **map, int height);
int		is_empty_line(char *line);

#endif // !CUB3D_H
