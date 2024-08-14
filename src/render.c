/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:02:51 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/14 15:01:52 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 *	The render function will render the screen using the raycasting technique
 *
 *	Raycasting work as follow
 * We first have to set some basic variable such as
 * 'player position', 'direction' and 'camera plane'
 *
 * 'player position'
 * The player position in the 2D map. (X pos, Y pos)
 *
 * 'Direction':
 * A vector indicating the direction in which the player is looking
 *
 * 'camera plane':
 * A vector indicating the screen plane.
 * The screen plane define the part we see.
 * It is always perpendicular to 'direction'
 * the size of if define the Field Of View (FOV),
 * based on ration with 'direction' size
 *
 *
 * After everything is set the render work as follow.
 * The program iterate throught every column of the screen in the center of it
 * for each column it will do the following calculation
 *	- Set the ray direction between player and column
 *	- Calculate the distance to the first wall
 *	- Draw a column accordingly to the distance and color
 *
 * Then it draw the image
 */

#include "../includes/cub3d.h"

/**
 * @brief Init a t_raycast variable
 *
 * This function init a t_raycast variable based on the data from data
 * and the screen column we're working with
 *
 * @param data The cub3D global data pointer
 * @param screen_x The screen column we deal with
 *
 * @return A t_raycast object containing all data for further processing
 */
static t_raycast	init_ray(t_data *data, int screen_x)
{
	t_raycast	ray;

	ray.x = screen_x;
	ray.cam_x = (2.0 * (double)screen_x) / (double)data->w_width - 1.0;
	ray.ray_dir = init_vec(data->direction.x + data->camera_plane.x * ray.cam_x,
			data->direction.y + data->camera_plane.y * ray.cam_x);
	ray.imap = init_vec((int)data->player_pos.x, (int)data->player_pos.y);
	ray.delta_dist = init_vec(0x1E30, 0x1E30);
	if (ray.ray_dir.x != 0)
		ray.delta_dist.x = fabs(1.0 / ray.ray_dir.x);
	if (ray.ray_dir.y != 0)
		ray.delta_dist.y = fabs(1.0 / ray.ray_dir.y);
	ray.step = init_vec(-1, -1);
	ray.side_dist = init_vec((data->player_pos.x - ray.imap.x) * ray.delta_dist.x,
		(data->player_pos.y - ray.imap.y) * ray.delta_dist.y);
	if (ray.ray_dir.x >= 0)
		ray.step.x = 1;
	if (ray.ray_dir.x >= 0)
		ray.side_dist.x = (ray.imap.x + 1.0 - data->player_pos.x) * ray.delta_dist.x;
	if (ray.ray_dir.y >= 0)
		ray.step.y = 1.0;
	if (ray.ray_dir.y >= 0)
		ray.side_dist.y = (ray.imap.y + 1.0 - data->player_pos.y) * ray.delta_dist.y;
	return (ray);
}

static int	get_color(int wall_orientation)
{
	if (wall_orientation == NORTH)
		return (0xFFFFFFFF);
	if (wall_orientation == EAST)
		return (0xFFFF0000);
	if (wall_orientation == SOUTH)
		return (0xFF00FF00);
	if (wall_orientation == WEST)
		return (0xFF0000FF);
	return (0xFF000000);
}

/**
 * @brief Return the wall orientation
 *
 * Return an int corresponding to cardinal direction the wall is facing
 *
 * @param ray The t_raycast ray
 *
 * @return 1 NORTH | 2 EAST | 3 SOUTH | 4 WEST
 */
int	get_wall_orientation(t_raycast ray)
{
	if (ray.side == 0)
	{
		if (ray.ray_dir.x < 0)
			return (WEST);
		return (EAST);
	}
	if (ray.ray_dir.y < 0)
		return (SOUTH);
	return (NORTH);
}

/**
 * @brief Draw column to MLX image
 *
 * Draw a wall column in the MLX img based
 *
 * @param data The cub3D global data
 * @param ray The t_raycast we're working with
 */
static void	draw_column(t_data *data, t_raycast ray)
{
	int	wall_orientation;
	int	column_size;
	int	draw_start;
	int	draw_end;
	int	color;
	int	i;

	wall_orientation = get_wall_orientation(ray);
	color = get_color(wall_orientation);
	column_size = (data->w_height / ray.perp_wall_dist);
	draw_start = (-column_size / 2) + data->w_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = column_size / 2 + data->w_height / 2;
	if (draw_end >= data->w_height)
		draw_end = data->w_height - 1;
	i = draw_start;
	while (i < draw_end)
	{
		ft_mlx_pixel_put(&data->img, ray.x, i, color);
		i++;
	}
	return ;
}

/**
 * @brief Return a t_raycast resulting from the raycast to column x
 *
 * This function cast a ray from player to the column x of the screen
 * It create a t_raycast object resulting from the raycasting
 * This object contain every parameter for the raycast
 * plus a flag indicating the type of wall it hit
 */
static t_raycast	raycast(t_data	*data, int x)
{
	t_raycast	ray;
	int			hit;

	ray = init_ray(data, x);
	hit = 0;
	while (hit == 0)
	{
		if (ray.side_dist.x < ray.side_dist.y)
		{
			ray.side_dist.x += ray.delta_dist.x;
			ray.imap.x += ray.step.x;
			ray.side = 0;
		}
		else
		{
			ray.side_dist.y += ray.delta_dist.y;
			ray.imap.y += ray.step.y;
			ray.side = 1;
		}
		hit = (data->map[(int)ray.imap.x][(int)ray.imap.y] == '1');
	}
	ray.perp_wall_dist = ray.side_dist.y - ray.delta_dist.y; 
	if (ray.side == 0)
		ray.perp_wall_dist = ray.side_dist.x - ray.delta_dist.x; 
	return (ray);
}

void draw_black(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->w_width)
	{
		j = 0;
		while (j < data->w_height)
		{
			ft_mlx_pixel_put(&data->img, i, j, 0x00000000);
			j++;
		}
		i++;
	}
}

/**
 * @brief Create a new MLX img and render iterate
 *
 * Render will start the raycasting process.
 * It iterates throught a line of the screen,
 * for each column it first change the pixel position to a camera position
 * convert the pixel value to a value between [-1;1], 0 being the center
 * and store it in @var cam_x
 * The it get the direction of the ray going from player to the column x.
 * And it will launch the Raycast
 * 
 * After all column have been rendered into the image, print the image;
 * @param param The (t_data *) structure
 * @return 0
 */
int	render(void *param)
{
	t_data		*data;
	t_raycast	ray;
	int		x;

	data = (t_data *)param;
	x = 0;
	draw_black(data);
	while (x < data->w_width)
	{
		ray = raycast(data, x);
		draw_column(data, ray);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
	printf("Player (%5f, %5f)\n", data->player_pos.x, data->player_pos.y);
	printf("Direction (%5f :%5f)\n", data->direction.x, data->direction.y);
	printf("Plane (%5f :%5f)\n", data->camera_plane.x, data->camera_plane.y);
	return (0);
}
