/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:40:07 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/18 16:31:45 by dbaladro         ###   ########.fr       */
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
#include <stdbool.h>


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
# define DOOR 6

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
# define F 0x0066

/*
 * MINIMAP
 */
# define MINIMAP_FLOOR_COLOR 0x00A4A4A4
# define MINIMAP_BLOCK_COLOR 0x00011D6C
# define MINIMAP_OUTBOUND_COLOR 0x00065B25
# define MINIMAP_PLAYER_COLOR 0x00FF0000

/*
 * DEFAULT CONFIGURATION
 */
# define R_DOOR_TEXTURE "./assets/right_door.xpm"
# define L_DOOR_TEXTURE "./assets/left_door.xpm"
# define PLAYER_TEXTURE "./assets/green_arrow.xpm"
# define TEXTURE_WIDTH 64.0
# define TEXTURE_HEIGHT 64.0
# define MOVE_SPEED 0.05
# define ROTATION_SPEED 0.06
# define TRANSPARENT -16777216
# define DELTA 2.2
# define PLAYER_DOOR_REACH 0.4

/**
 * @struct s_ivec
 * @brief 2D (int) vector structure
 *
 * This structure can represent 2D (int) vector or coordinate
 *
 * @var s_ivec::x
 * X coordinate
 *
 * @var s_ivec::y
 * Y coordinate
 */
typedef struct s_ivec
{
	int	x;
	int	y;
}				t_ivec;
/**
 * @struct s_dvec
 * @brief 2D (double) vector structure
 *
 * This structure can represent 2D (double) vector or coordinate
 *
 * @var s_dvec::x
 * X coordinate
 *
 * @var s_dvec::y
 * Y coordinate
 */
typedef struct s_dvec
{
	double	x;
	double	y;
}				t_dvec;


typedef	struct	s_sprite
{
	t_ivec		sprite_pos; // sprite pos on the map, eq = 'A'
	double		distance; // the distance of sprite to the player
	t_ivec		screen_pos; // position of sprite in camera space
	double		perp_dist;			
	t_ivec		sprite_size; // sprite's height and width on the screen
	t_ivec		draw_start;
	t_ivec		draw_end;
	int			color;
	int			current_slice;
	int			frame_counter;
	int			is_active;
	//int			count;
	//t_dvec		map_pos;
	// int				frames; //  = 8 
	// int				speed;
	// int	time;
	
	
}				t_sprite;

/**
 * @struct s_minimap
 * @brief The structure holding all necessary data for minimap
 *
 * This structure contain all the necessary data for minimap rendering
 * like the size of it, on screen position, color...
 *
 * @var s_minimap::draw_size
 * The vector representing the minimap size on the screen (in pixel)
 *
 * @var s_minimap::map_screen_pos
 * The vector representing the minimap position on the screen
 * CARREFUL vector point in the middle of the minimap
 *
 * @var s_minimap::draw_start
 * Where the minimap drawing should start on screen
 *
 * @var s_minimap::draw_end
 * Where the minimap drawing should end on screen
 *
 * @var s_minimap::block
 * The number of block that are rendered on the minimap
 *
 * @var s_minimap::map_pos
 * The position on the map the minimap is aiming at
 *
 * @var s_minimap::step
 * The step used to parcours the map when rendering the minimap
 *
 * @var s_minimap::outbound_color
 * TRGB outbound color on minimap
 *
 * @var s_minimap::floor_color
 * TRGB floor color on minimap
 *
 * @var s_minimap::block_color
 * TRGB block color on minimap
 *
 * @var s_minimap::player_size
 * The size of the player on the minimap (in pixel)
 *
 * @var s_minimap::player_draw_start
 * The position on the screen the player drawing should start
 *
 * @var s_minimap::player_draw_end
 * The position on the screen the player drawing should end
 *
 * @var s_minimap::player_tex_pos
 * The position of the player texture pixel
 *
 * @var s_minimap::dir_angle
 * The angle of the direction the player is looking to
 *
 * @var s_minimap::player_step
 * The step to parcour the player texture
 */
typedef struct s_minimap
{
	t_ivec	draw_size;
	t_ivec	map_screen_pos;
	t_ivec	draw_start;
	t_ivec	draw_end;
	t_ivec	block;
	t_dvec	map_pos;
	double	step;
	int		outbound_color;
	int		floor_color;
	int		block_color;
	int		player_size;
	t_dvec	player_draw_start;
	t_dvec	player_draw_end;
	t_dvec	player_tex_pos;
	double	dir_angle;
	double	player_step;
}				t_minimap;

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
 *
 * @var s_raycast::hit
 * Take the value of the hitten tile needed to render wall or door
 *
 * @var s_raycast::h_pos
 * A pair of double containing the exact position of the ray hit
 * needed to render door
 *
 * @var s_raycast::h_side
 * Raycast vector, needed for door rendering
 */
typedef struct s_raycast
{
	int		x;
	double	cam_x;
	t_dvec	dir;
	t_dvec	side_dist;
	t_dvec	delta_dist;
	t_ivec	step;
	t_ivec	map;
	double	perp_wall_dist;
	int		side;
	int		hit;
	t_dvec	h_pos;
	t_dvec	h_side;
}				t_raycast;

/**
 * @struct s_draw
 * @brief Wall draw data structure
 *
 * This structure contain all necessary data to render textured wall
 *
 * @var s_draw::column_size
 * Size of the column to be drawn (in pixel)
 *
 * @var s_draw::start
 * The drawing starting height/line
 * 
 * @var s_draw::end
 * The drawing ending height/line
 *
 * @var s_draw::wall_orientation
 * An integer representing the wall orientation Nort/West/East/South
 *
 * @var s_draw::tex_x
 * The wall X hit position converted to texture
 *
 * @var s_draw::wall_x
 * The wall X hit position
 *
 * @var s_draw::step
 * The step from one pixel to another converted to texture size
 *
 * @var s_draw::tex_start
 * The texture Y position start
 */
typedef struct s_draw
{
	int		column_size;
	int		start;
	int		end;
	int		wall_orientation;
	int		tex_x;
	double	wall_x;
	double	step;
	double	tex_start;
}				t_draw;

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
<<<<<<< HEAD
 * @struct t_map_info
 * @brief Structure holding map2d data
 * 
 * This structure contains data for a map such as:
 * start position of a player and start orientation (N, S, E or W)
 *
 * @var t_map_info:map2d
 * An array containing map info
 * 
 * @var t_map_info:map2_height
 * Map2d height
 * 
 * @var t_map_info:start_map
 * A flag for parser to start a map
 * 
 * @var t_map_info:map_pos
 * Map index
 * 
 */
typedef	struct	s_map_info
{
	char 	**map2d;
	int	map2_height;
	int	start_map;
	int	map_pos;
}				t_map_info;

/**
 * @struct t_texture
 * @brief Structure holding texture data
 * 
 * This structure contains data for a texture such as:
 * path to the structure
 * 
 * @var t_texture::@_path
 * Path to the texture file
 */
// typedef struct s_texture
// {
// 	char	*N_path;
// 	char	*E_path;
// 	char	*W_path;
// 	char	*S_path;
// }				t_texture;

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
=======
 * @struct s_texture
 * @brief Structure to store texture path and image data
 *
 * This structure store the structure path and necessary data like
 * size of it and MLX img
 *
 * @var s_texture::path
 * Path to texture file
 *
 * @var s_texture::size
 * Texture size in pixel, needed for rendering
 *
 * @var s_texture::img
 * Texture MLX image
 */
typedef struct s_texture
{
	char	*path;
	t_ivec	size;
	t_img	img;
}				t_texture;

/**
>>>>>>> door
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
 * @var s_data::m_height
 * Map height
 * 
 * @var s_data::m_width
 * Map width
 * 
 * @var s_data::img
 * mlx window image
 *
 * @var s_data::texture
 * The buffer containing pointer to the different textures
 *	*	texture[0] = NORTH texture
 *	*	texture[1] = EAST texture
 *	*	texture[2] = SOUTH texture
 *	*	texture[3] = WEST texture
 *	*	texture[4] = PLAYER texture
 *	*	texture[5] =  texture
 *	*	texture[6] =  texture
 *	*	texture[7] =  texture
 *	*	texture[8] =  texture
 *
 * @var s_data::floor_color
 * TRGB floor color
 *
 * @var s_data::ceiling_color
 * TRGB ceiling color
 *
 * @var s_data::map
 * Game map
 * 
 * @var s_data::texture_tab
 * An array of strings representing the file paths to the textures used in the game.
 *
 * @var s_data::map_size
 * The vector represent the map size (in block)
 *
 * @var s_data::player
 * Player position in the map
 *
 * @var s_data::direction
 * Player look direction
 *
 * @var s_data::camera_plane
 * Camera Y plane
<<<<<<< HEAD
 * 
 * @var s_data::textures
 * A structure holding the paths for the textures used in the game.
 *
 * @var s_data::map_info
 * A structure containing additional information about the map, such as its starting position
 * and validation status.
 *
 * @var s_data::colors
 * A structure holding the color information for various elements in the game, including the
 * floor and ceiling.
=======
 *
 * @var s_data::minimap
 * minimap data structure for minimap rendering
 *
 * @var s_data::mouse_visibility
 * Boolean indicating if the value mouse is visible or not
 * Needed for mouse rotation bonus
 *
 * @var s_data::door
 * pointer on door player is aiming at, easier for door opening
 *
 * @var s_data::door_status
 * Int indicating if the door can be opened or closed
>>>>>>> door
 * */
typedef struct s_data
{
	void		*mlx;
	void		*window;
	double		*zbuffer; // to store the perpendicular distance of each stripe
	int			w_height;
	int			w_width;
	int			m_height;
	int			m_width;
	int			sprites_nb;
	t_img		img;
	t_texture	texture[8];
	t_img		sprites[8];
	int			floor_color;
	int			ceiling_color;
	char		**map;
	char		*texture_tab[5];
	char		*sprites_tab[8];
	t_ivec		tex;
	t_dvec		player;
	t_dvec		direction;
	t_dvec		camera_plane;
	t_minimap	minimap;
	// t_texture	textures;
	t_map_info	map_info;
	t_colors	colors;
	t_sprite	*sprites_arr;
	int			mouse_visibility;
	char		*door;
	int			door_status;
}				t_data;

/*  ______ _____  _____   ____  _____   */
/* |  ____|  __ \|  __ \ / __ \|  __ \  */
/* | |__  | |__) | |__) | |  | | |__) | */
/* |  __| |  _  /|  _  /| |  | |  _  /  */
/* | |____| | \ \| | \ \| |__| | | \ \  */
/* |______|_|  \_\_|  \_\\____/|_|  \_\ */
/*                                      */
// Print error.c
void		print_error(const char *func, int error_nbr);

/*  _____ _   _ _____ _______  */
/* |_   _| \ | |_   _|__   __| */
/*   | | |  \| | | |    | |    */
/*   | | | . ` | | |    | |    */
/*  _| |_| |\  |_| |_   | |    */
/* |_____|_| \_|_____|  |_|    */
/*                             */
// init_vec.c
t_ivec		init_ivec(int x, int y);
t_dvec		init_dvec(double x, double y);
// init_player.c
void		init_player(t_data *data);
// init_cub.c
t_data		*init_cub(char *param);
// free_cub.c
void		free_cub(t_data *data);
int			exit_cub(t_data *data);
// load_texure.c
int			load_texture(t_data *data, t_texture *texture);

/*  _____  ______ _   _ _____  ______ _____   */
/* |  __ \|  ____| \ | |  __ \|  ____|  __ \  */
/* | |__) | |__  |  \| | |  | | |__  | |__) | */
/* |  _  /|  __| | . ` | |  | |  __| |  _  /  */
/* | | \ \| |____| |\  | |__| | |____| | \ \  */
/* |_|  \_\______|_| \_|_____/|______|_|  \_\ */
/*                                            */
// draw_floor_and_ceiling
void		draw_floor_and_ceiling(t_data *data);
// draw_column.c
void		draw_column(t_data *data, t_raycast ray);
//render.c
t_raycast	init_ray(t_data *data, int screen_x);
t_raycast	raycast(t_data	*data, int x);
int			render(void *param);


/*  __  __ _     __   __ */
/* |  \/  | |    \ \ / / */
/* | \  / | |     \ V /  */
/* | |\/| | |      > <   */
/* | |  | | |____ / . \  */
/* |_|  |_|______/_/ \_\ */
/*                       */
// ft_mlx_pixel_put.c
void		ft_mlx_pixel_put(t_img *img, int x, int y, int color);
// mlx_hook
void		rotate(int keycode, t_data *data, double rotation_speed);
int			key_hook(int keycode, void *param);
// move.c
void		move(t_data *data, int key);

/* ************************************************************************** */
/*                      ____   ____  _   _ _    _  _____                      */
/*                     |  _ \ / __ \| \ | | |  | |/ ____|                     */
/*                     | |_) | |  | |  \| | |  | | (___                       */
/*                     |  _ <| |  | | . ` | |  | |\___ \                      */
/*                     | |_) | |__| | |\  | |__| |____) |                     */
/*                     |____/ \____/|_| \_|\____/|_____/                      */
/*                                                                            */
/* ************************************************************************** */
t_data *init_map_bonus(t_data *data, char  *file_name);
// init_sprite_bonus.c
t_sprite	*init_sprites(t_data *data);
/*  _____  ______ _   _ _____  ______ _____   */
/* |  __ \|  ____| \ | |  __ \|  ____|  __ \  */
/* | |__) | |__  |  \| | |  | | |__  | |__) | */
/* |  _  /|  __| | . ` | |  | |  __| |  _  /  */
/* | | \ \| |____| |\  | |__| | |____| | \ \  */
/* |_|  \_\______|_| \_|_____/|______|_|  \_\ */
/*                                            */
// get_hit_pos_bonus.c
void		get_hit_pos(t_data *data, t_raycast *ray);
// check_hit_bonus.c
int			check_hit(t_data *data, t_raycast *ray);
// correct_perp_wall_dist_bonus.c
void		correct_perp_wall_dist(t_raycast *ray, double diff);

/*  __  __ _____ _   _ _____ __  __          _____   */
/* |  \/  |_   _| \ | |_   _|  \/  |   /\   |  __ \  */
/* | \  / | | | |  \| | | | | \  / |  /  \  | |__) | */
/* | |\/| | | | | . ` | | | | |\/| | / /\ \ |  ___/  */
/* | |  | |_| |_| |\  |_| |_| |  | |/ ____ \| |      */
/* |_|  |_|_____|_| \_|_____|_|  |_/_/    \_\_|      */
/*                                                   */
// init_minimap.c
t_minimap	init_minimap(t_data *data);
// draw_minimap.c
void		draw_minimap(t_data *data);

// init_map.c
t_data	*init_map(t_data *data, char  *file_name);
int		find_map_info(char **map, t_data *data);
int		process_info_lines(t_data *data, char *line);
void	copy_map(int map_pos, int height,  t_data *data);
int		is_empty_line(char *line);
int		map_h(char *file_name);


// parsing.c
int		parsing(t_data *data);
void	strip_newline(char *str);
int		is_closed(char **map, int height);
int		is_valid_chars(char **map, int height);
int		check_inside(char **map, int height);
int		is_closed_inside(int x_dep, int y_dep, char **map, int height);
int		check_borders(char *line);
int		check_first_last(char *line);
int		has_start_pos(char **map, int height);
int		validate_value(char *color, int start, int end);
int		rgb_to_hex(char *color);
int		parsing_bonus(t_data *data);
int		parsing_textures(const t_texture *textures);
int		parsing_colors(char *color);


// sprite
void	init_tab_sprites(t_data *data);
void    load_sprite_image(t_data *data, char **sprites_tab);
int		count_sprites_nb(t_data *data);
void    calculate_sprite_distances(t_data *data);
void    sort_sprites(t_data *data);
void    update_sprite_frame(t_data *data, int i);
int		get_pixel_color_from_xpm(int x, int y, t_data *data, int current_slice);
void    process_sprite_y(t_data *data, int i, int stripe);
void	draw_sprite(t_data *data);
void	free_sprite(t_data *data);


/*  _____   ____ _______    _______ ______  */
/* |  __ \ / __ \__   __|/\|__   __|  ____| */
/* | |__) | |  | | | |  /  \  | |  | |__    */
/* |  _  /| |  | | | | / /\ \ | |  |  __|   */
/* | | \ \| |__| | | |/ ____ \| |  | |____  */
/* |_|  \_\\____/  |_/_/    \_\_|  |______| */
/*                                          */
// rotate_bonus.c
int			camera_move(int x, int y, void *param);

/*  _____   ____   ____  _____   _____  */
/* |  __ \ / __ \ / __ \|  __ \ / ____| */
/* | |  | | |  | | |  | | |__) | (___   */
/* | |  | | |  | | |  | |  _  / \___ \  */
/* | |__| | |__| | |__| | | \ \ ____) | */
/* |_____/ \____/ \____/|_|  \_\_____/  */
/*                                      */
// is_door_bonus.c
int			is_side_door(int tile);
int			is_not_side_door(int tile);
int			is_door(int tile);
// door_raycast_bonus.c
t_raycast	door_raycast(t_data	*data);
// player_can_open_door_bonus.c
int			player_can_open_door(t_data *data, t_raycast *ray);
// int			is_aiming_at_door(t_data *data, t_raycast *ray);
void		check_door(t_data *data);
// open_door_bonus.c
void		open_door(t_data *data);

// TESTING ????
// COPY_MAP
char		**get_map(char *map[]);

#endif // !CUB3D_H
