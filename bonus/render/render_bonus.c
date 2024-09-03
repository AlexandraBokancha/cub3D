/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:02:51 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/03 19:38:07 by dbaladro         ###   ########.fr       */
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
static t_raycast	init_ray(t_data *data, int screen_x)
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

// CHECK IF THE RAY HIT A WALL OR DOOR SEPENDING ON MAP SYMBOL
int	ray_hit(t_data *data, t_raycast *ray)
{
	char	tile;

	tile = data->map[(int)ray->map.x][(int)ray->map.y];
	if (ray->side == 0)	// Ray toiuch a side wall EAST / WEST)
	{
		if (ray->dir.x < 0) // Ray is orientated to the left
		{
			if (data->map[(int)ray->map.x + 1][(int)ray->map.y] == 'O')
				return ('O');
			if (tile == 'o')
				return ('o');
		}
		else
		{
			if (tile == 'O')
				return ('O');
			if (data->map[(int)ray->map.x + 1] && data->map[(int)ray->map.x + 1][(int)ray->map.y] == 'O')
				return ('O');
		}
	}
	if (ray->side == 1) // Ray touch NORTH ? SOUTH wall
	{
		if (ray->dir.y < 0) // Ray orientated down
		{
			if (ray->map.y > 1 && data->map[(int)ray->map.x][(int)ray->map.y + 1] == 'c')
				return ('c');
			if (tile == 'C')
				return ('C');
		}
		else
		{
			if (data->map[(int)ray->map.x][(int)ray->map.y - 1] == 'C')
				return ('C');
			if (tile == 'c')
				return ('c');
		}
	}
	if (tile == '1')
		return (1);
	if (tile != 'c' && tile != 'C' && tile != 'o' && tile != 'O')
		return (0);
	//
	//
	//
	// dir = 1;
	// if ((data->direction.x < 0 && (tile == 'o' || tile == 'O'))
	// 		|| (data->direction.y < 0 && (tile == 'c' || tile == 'C')))
	// 	dir = -1;
	// // if (ray->side == 0)
	// // {
	// if (tile == 'c' && ((int)(ray->map.y) == (int)(ray->map.y + dir * 0.05)))
	// 	return ('c');
	// if (tile == 'C' && ((int)(ray->map.y) == (int)(ray->map.y - dir * 0.05)))
	// 	return ('C');
	// // }
	// // if (ray->side == 1)
	// // {
	// if (tile == 'o' && ((int)(ray->map.x) == (int)(ray->map.x + dir * 0.05)))
	// 	return ('o');
	// if (tile == 'O' && ((int)(ray->map.x) == (int)(ray->map.x - dir * 0.05)))
	// 	return ('O');
	// }
	return (0);
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
		// NEW DOOR
		ray.hit = ray_hit(data, &ray);

		// hit = (data->map[(int)ray.map.x][(int)ray.map.y] == '1');
	}
	// NEW DOOR
	// ray.perp_wall_dist = ray.side_dist.y - ray.delta_dist.y;
	

	ray.perp_wall_dist = ray.side_dist.y - (ray.delta_dist.y - ((ray.hit != 1) * 0.025));
	if (ray.side == 0)
		ray.perp_wall_dist = ray.side_dist.x - (ray.delta_dist.x - ((ray.hit != 1) * 0.025));
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
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
	printf("player_pos = %5f ; %5f\n", data->player.x, data->player.y);
	printf("direction = %5f ; %5f\n\n", data->direction.x, data->direction.y);
	return (0);
}
