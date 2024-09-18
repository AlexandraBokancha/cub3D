/* ************************************************************************** */
/*                                                                            */ /*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:02:51 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/03 12:28:00 by dbaladro         ###   ########.fr       */
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

#include "../../includes/cub3d.h"

/**
 * @brief Init a t_raycast variable
 *
 * This function init a t_raycast variable based on the data from data
 * and the screen column we're working with
 * @param data The cub3D global data pointer
 * @param screen_x The screen column we deal with
 *
 * @return A t_raycast object containing all data for further processing
 */
t_raycast	init_ray(t_data *data, int screen_x)
{
	t_raycast	ray;

	ray.x = screen_x;
	ray.cam_x = (2.0 * (double)screen_x) / (double)data->w_width - 1.0;
	ray.dir = init_dvec(data->direction.x + data->camera_plane.x * ray.cam_x,
			data->direction.y + data->camera_plane.y * ray.cam_x);
	ray.map = init_ivec((int)data->player.x, (int)data->player.y);
	ray.delta_dist = init_dvec(0x1E30, 0x1E30);
	if (ray.dir.x != 0)
		ray.delta_dist.x = fabs(1.0 / ray.dir.x);
	if (ray.dir.y != 0)
		ray.delta_dist.y = fabs(1.0 / ray.dir.y);
	ray.step = init_ivec(-1, -1);
	ray.side_dist = init_dvec((data->player.x - ray.map.x) * ray.delta_dist.x,
			(data->player.y - ray.map.y) * ray.delta_dist.y);
	if (ray.dir.x >= 0)
		ray.step.x = 1;
	if (ray.dir.x >= 0)
		ray.side_dist.x = (ray.map.x + 1.0 - data->player.x) * ray.delta_dist.x;
	if (ray.dir.y >= 0)
		ray.step.y = 1.0;
	if (ray.dir.y >= 0)
		ray.side_dist.y = (ray.map.y + 1.0 - data->player.y) * ray.delta_dist.y;
	return (ray);
}

/**
 * @brief Return a t_raycast resulting from the raycast to column x
 *
 * This function cast a ray from player to the column x of the screen
 * It create a t_raycast object resulting from the raycasting
 * This object contain every parameter for the raycast
 * plus a flag indicating the type of wall it hit
 */
t_raycast	raycast(t_data	*data, int x)
{
	t_raycast	ray;

	ray = init_ray(data, x);
	ray.hit = 0;
	while (ray.hit == 0)
	{
		if (ray.side_dist.x < ray.side_dist.y)
		{
			ray.side_dist.x += ray.delta_dist.x;
			ray.map.x += ray.step.x;
			ray.side = 0;
		}
		else
		{
			ray.side_dist.y += ray.delta_dist.y;
			ray.map.y += ray.step.y;
			ray.side = 1;
		}
		ray.hit = (data->map[(int)ray.map.x][(int)ray.map.y] == '1');
	}
	ray.perp_wall_dist = ray.side_dist.y - ray.delta_dist.y;
	if (ray.side == 0)
		ray.perp_wall_dist = ray.side_dist.x - ray.delta_dist.x;
	return (ray);
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
	int			x;

	data = (t_data *)param;
	x = 0;
	draw_floor_and_ceiling(data);
	while (x < data->w_width)
	{
		ray = raycast(data, x);
		draw_column(data, ray);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
	return (0);
}
