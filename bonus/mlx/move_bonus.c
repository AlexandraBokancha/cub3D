/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:46:15 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/18 23:10:59 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Set necessary parameter and save the original one in dir && cam_plane
 *
 * This function is needed to be 42 norm compliant
 * It changes the t_data->direction AND t_data->camera_plane
 * And save the original value in dir and cam_plane for further backup
 *
 * @param	data		The cub3D global data structure
 * @param	key			The actual key that was pressed
 * @param	dir			A t_dvec to save the original t_data->direction
 * @param	cam_plane	A t_dvec to sace the original t_data->camera_plane
 */
static void	set_param(t_data *data, int key, t_dvec *dir, t_dvec *cam_plane)
{
	*dir = init_dvec(data->direction.x, data->direction.y);
	*cam_plane = init_dvec(data->camera_plane.x, data->camera_plane.y);
	if (key == A)
	{
		data->direction = init_dvec(-dir->y, dir->x);
		data->camera_plane = init_dvec(-cam_plane->y, cam_plane->x);
	}
	if (key == S)
	{
		data->direction = init_dvec(-dir->x, -dir->y);
		data->camera_plane = init_dvec(-cam_plane->x, -cam_plane->y);
	}
	if (key == D)
	{
		data->direction = init_dvec(dir->y, -dir->x);
		data->camera_plane = init_dvec(cam_plane->y, -cam_plane->x);
	}
	return ;
}

/**
 * @brief Return 1 if an obstacle is present else 0
 *
 * This function is required for proper movment as it give the player
 * a bit of 'fat'
 *
 * @param	data	The cub3D global data structure
 * @return	1 if an obstacle is present else 0 
 */
static int	obstacle(t_data *data, t_dvec *move)
{
	t_raycast	ray;
	int			i;
	int			step;
	int			pos;

	i = 0;
	step = (int)(0.15 * data->w_width);
	pos = data->w_width / 2 - step;
	while (i < 3)
	{
		ray = raycast(data, pos);
		if (ray.side == 1 && ray.side_dist.x < MOVE_SPEED * DELTA)
			move->x = 0;
		if (ray.side == 0 && ray.side_dist.y < MOVE_SPEED * DELTA)
			move->y = 0;
		i++;
	}
	return (move->x == 0 && move->y == 0);
}

/**
 * @brief This function return the distance from the wall on X/Y axis
 *
 * Return the distance between the player and the walls when player try to move
 *
 * @param	data	The cub3d data structure copy
 * @return	The vector containing (x_axis distance, y_axis distamce)
 */
static	t_dvec	get_wall_dist(t_data *data)
{
	t_dvec		wall_dist;
	t_dvec		old_dir;
	t_raycast	ray;

	old_dir = init_dvec(data->direction.x, data->direction.y);
	data->direction.y = 0;
	data->direction.x = 1;
	if (old_dir.x < 0)
		data->direction.x = -1;
	ray = raycast(data, 960);
	wall_dist.x = fabs(ray.h_side.x);
	if (wall_dist.x > 0.05 && ray.hit != 1)
		wall_dist.x -= 0.04;
	data->direction.x = 0;
	data->direction.y = 1;
	if (old_dir.y < 0)
		data->direction.y = -1;
	ray = raycast(data, 960);
	wall_dist.y = fabs(ray.h_side.y);
	if (wall_dist.y > 0.05 && ray.hit != 1)
		wall_dist.y -= 0.04;
	data->direction = old_dir;
	return (wall_dist);
}

/**
 * @brief Adjust value of player position
 *
 * This function is here to avoid rounded value which cause various issue
 * during raycasting
 *
 * @param	data	The cub3D global data structure
 */
static void	adjust_player_pos(t_data *data)
{
	if (modf(data->player.x, &(double){0}) <= 0.01)
		data->player.x += 0.01;
	if (modf(data->player.x, &(double){0}) >= 0.99)
		data->player.x -= 0.01;
	if (modf(data->player.y, &(double){0}) <= 0.01)
		data->player.y += 0.01;
	if (modf(data->player.y, &(double){0}) >= 0.99)
		data->player.y -= 0.01;
	return ;
}

/**
 * @brief Perform move
 *
 * This function perform the movment checkup and action based on pressed key
 *
 * @param	data	The cub3D global data structure
 * @param	key		The pressed key
 */
void	move(t_data *data, int key)
{
	t_dvec	dir;
	t_dvec	cam_plane;
	t_dvec	move;
	t_dvec	wall_dist;

	set_param(data, key, &dir, &cam_plane);
	move = init_dvec(data->direction.x * MOVE_SPEED,
			data->direction.y * MOVE_SPEED);
	if (obstacle(data, &move))
	{
		data->direction = dir;
		data->camera_plane = cam_plane;
		return ;
	}
	wall_dist = get_wall_dist(data);
	if (wall_dist.x > fabs(move.x * DELTA))
		data->player.x += move.x;
	if (wall_dist.y > fabs(move.y * DELTA))
		data->player.y += move.y;
	adjust_player_pos(data);
	data->direction = dir;
	data->camera_plane = cam_plane;
	return ;
}
