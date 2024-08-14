/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:40:07 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/14 23:13:54 by dbaladro         ###   ########.fr       */
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
# include "../mlx/mlx.h"

/*
 * WINDOW SIZE
 */
# define DEFAULT_WIN_WIDTH 1920
# define DEFAULT_WIN_HEIGHT 1080

/*
 * MLX EVENTS
 */
# define ON_MOUSEMOVE 6
# define ON_DESTROY 17

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
# define TEXTURE_WIDTH 64.0
# define TEXTURE_HEIGHT 64.0
# define MOVE_SPEED 0.05
# define ROTATION_SPEED 0.03
# define DELTA 1.1

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
 * @var s_raycast::dir
 * A vector describing the direction of the casted ray
 *
 * @var s_raycast:side_dist
 * A vector describing the distance between player and the closest wall
 * (given a certain ray)
 *
 * @var s_raycast::delta_dist
 * A vector describing the distance between two walls (given a certain ray)
 *
 * @var s_raycast::map
 * A pair containing the actual ray position in the map (map = int player_pos)
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
	t_vec	dir;
	t_vec	side_dist;
	t_vec	delta_dist;
	t_vec	map;
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
 * @struct s_data
 * @brief cub3D holding all program data
 * 
 * This structure contain all necessary program data such as:
 * MLX, window instance, window dimensions, the map, player info
 * camera info ...
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
 * @var s_data::img
 * mlx window image
 *
 * @var s_data::texture
 * The buffer containing pointer to the different textures
 *
 * @var s_data::map
 * Game map
 *
 * @var s_data::player
 * Player position in the map
 *
 * @var s_data::direction
 * Player look direction
 *
 * @var s_data::camera_plane
 * Camera Y plane
 * */
typedef struct s_data
{
	void	*mlx;
	void	*window;
	int		w_height;
	int		w_width;
	t_img	img;
	t_img	texture[4];
	char	**map;
	t_vec	player;
	t_vec	direction;
	t_vec	camera_plane;
}				t_data;

// ft_mlx_pixel_put.c
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);

// Print error.h
void	print_error(const char *func, int error_nbr);

// free_cub.c
void	free_cub(t_data *data);
int		exit_cub(t_data *data);

// init_cub.c
t_vec	init_vec(double x, double y);
t_data	*init_cub(void);

// mlx_hook
int		key_hook(int keycode, void *param);
int		camera_move(int x, int y, void *param);

// draw_column.c
void	draw_column(t_data *data, t_raycast ray);

//render.c
int		render(void *param);

#endif // !CUB3D_H
