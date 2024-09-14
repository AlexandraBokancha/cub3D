/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:46:15 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/14 14:21:46 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief This function return the distance from the wall on X/Y axis
 *
 * Return the distance between the player and the walls when player try to move
 *
 * @param	data	The cub3d data structure copy
 * @return	The vector containing (x_axis distance, y_axis distamce)
 */
static	t_dvec	get_wall_dist(t_data data)
{
	t_dvec		wall_dist;
	t_dvec		old_dir;
	t_raycast	ray;

	old_dir = data.direction;
	// GET SIDE DIST
	data.direction.y = 0;
	data.direction.x = 1;
	if (old_dir.x < 0)
		data.direction.x = -1;
	ray = raycast(&data, 960);
	wall_dist.x = fabs(ray.h_side.x);
	
	// GET NOT_SIDE DIST
	data.direction.x = 0;
	data.direction.y = 1;
	if (old_dir.y < 0)
		data.direction.y = -1;
	ray = raycast(&data, 960);
	wall_dist.y = ray.side_dist.y;
	return (wall_dist);
}

void	new_move(t_data *data, int key)
{
	t_dvec		dir;
	t_dvec		cam_plane;

	// save original data_value
	dir = init_dvec(data->direction.x, data->direction.y);
	cam_plane = init_dvec(data->camera_plane.x, data->camera_plane.y);

	// change the t_data structure
	if (key == A)
	{
		data->direction = init_dvec(-dir.y, dir.x);
		data->camera_plane = init_dvec(-cam_plane.y, cam_plane.x);
	}
	if (key == S)
	{
		data->direction = init_dvec(-dir.x, -dir.y);
		data->camera_plane = init_dvec(-cam_plane.x, -cam_plane.y);

	}
	if (key == D)
	{
		data->direction = init_dvec(dir.y, -dir.x);
		data->camera_plane = init_dvec(cam_plane.y, -cam_plane.x);
	}

	// move vector
	t_dvec move;
	move = init_dvec(data->direction.x * MOVE_SPEED, data->direction.y * MOVE_SPEED);

	// raycast
	// t_raycast	ray;
	// ray = raycast(data, 960);
	// if (ray.side_dist.x < MOVE_SPEED || ray.side_dist.y < MOVE_SPEED)
	// 	return ;

	// Get wall_distance
	t_dvec	wall_dist;
	wall_dist = get_wall_dist(*data);
	if (wall_dist.x > fabs(move.x * DELTA))
		data->player.x += move.x;
	if (wall_dist.y > fabs(move.y * DELTA))
		data->player.y += move.y;

	// Put back data value
	data->direction = dir;
	data->camera_plane = cam_plane;
	return ;
}
