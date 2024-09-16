/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 05:47:37 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/16 16:31:19 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief This file contain the primary function to handle doors properly
 *
 * The door code is as follow :
 * c : closed door (bottom of block)
 * o : open   door (right  of block)
 * C : CLOSED door (top    of block)
 * O : OPEN   door (left   of block)
 */

#include "../../includes/cub3d.h"

/**
 * @brief Check if something was hit in the NORTH direction
 * 
 * Check if a door was hit in the NORTH direction
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we're working with
 * @return	An int indicating what type of block was hit
 */
static int	check_north(t_data *data, t_raycast *ray)
{
	printf("ray->h_side (%5f;%5f)\nray->h_pos (%5f;%5f)\n\n", ray->h_side.x, ray->h_side.y, ray->h_pos.x, ray->h_pos.y);
	if (data->map[ray->map.x][ray->map.y] == 'C')
		return (correct_perp_wall_dist(ray, 0.05), 'C');
	if (data->map[(int)ray->h_pos.x][ray->map.y] == 'O'
		&& modf(ray->h_pos.x, &(double){0}) <= 0.05)
		return (correct_perp_wall_dist(ray,
				0.05 - modf(ray->h_pos.x, &(double){0})), 'O');
	if (data->map[(int)ray->h_pos.x][ray->map.y] == 'o'
		&& modf(ray->h_pos.x, &(double){0}) >= 0.95)
		return (correct_perp_wall_dist(ray,
				modf(ray->h_pos.x, &(double){0}) - 0.95), 'o');
	if (data->map[ray->map.x][ray->map.y + 1] == 'c')
		return ('c');
	if (data->map[(int)ray->h_pos.x][ray->map.y + 1] == 'O'
			&& modf(ray->h_pos.x, &(double){0}) <= 0.05)
		return ('O');
	if (data->map[(int)ray->h_pos.x][ray->map.y + 1] == 'o'
			&& modf(ray->h_pos.x, &(double){0}) >= 0.95)
		return ('o');
	return (data->map[ray->map.x][ray->map.y + 1] == '1');
}

/**
 * @brief Check if something was hit in the EAST direction
 * 
 * Check if a door was hit in the EAST direction
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we're working with
 * @return	An int indicating what type of block was hit
 */
static int	check_east(t_data *data, t_raycast *ray)
{
	if (data->map[ray->map.x][ray->map.y] == 'o')
		return (correct_perp_wall_dist(ray, 0.05), 'o');
	if (data->map[ray->map.x][ray->map.y] == 'C'
		&& modf(ray->h_pos.y, &(double){0}) >= 0.95)
		return (correct_perp_wall_dist(ray,
				modf(ray->h_pos.y, &(double){0}) - 0.95), 'C');
	if (data->map[ray->map.x][ray->map.y] == 'c'
		&& modf(ray->h_pos.y, &(double){0}) <= 0.05)
		return (correct_perp_wall_dist(ray,
				0.05 - modf(ray->h_pos.y, &(double){0})), 'c');
	if (data->map[ray->map.x + 1][ray->map.y] == 'O')
		return ('O');
	if (data->map[ray->map.x + 1][(int)ray->h_pos.y] == 'c'
			&& modf(ray->h_pos.y, &(double){0}) <= 0.05)
		return ('c');
	if (data->map[ray->map.x + 1][ray->map.y] == 'C'
			&& modf(ray->h_pos.y, &(double){0}) >= 0.95)
		return ('C');
	return (data->map[ray->map.x + 1][ray->map.y] == '1');
}

/**
 * @brief Check if something was hit in the SOUTH direction
 * 
 * Check if a door was hit in the SOUTH direction
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we're working with
 * @return	An int indicating what type of block was hit
 */
static int	check_south(t_data *data, t_raycast *ray)
{
	if (data->map[ray->map.x][ray->map.y] == 'c')
		return (correct_perp_wall_dist(ray, 0.05), 'c');
	if (data->map[(int)ray->h_pos.x][ray->map.y] == 'O'
		&& modf(ray->h_pos.x, &(double){0}) <= 0.05)
		return (correct_perp_wall_dist(ray,
				0.05 - modf(ray->h_pos.x, &(double){0})), 'O');
	if (data->map[(int)ray->h_pos.x][ray->map.y] == 'o'
		&& modf(ray->h_pos.x, &(double){0}) >= 0.95)
		return (correct_perp_wall_dist(ray,
				modf(ray->h_pos.x, &(double){0}) - 0.95), 'o');
	if (data->map[ray->map.x][ray->map.y - 1] == 'C')
		return ('C');
	if (data->map[(int)ray->h_pos.x][ray->map.y - 1] == 'o'
			&& modf(ray->h_pos.x, &(double){0}) >= 0.95)
		return ('o');
	if (data->map[(int)ray->h_pos.x][ray->map.y - 1] == 'O'
			&& modf(ray->h_pos.x, &(double){0}) <= 0.05)
		return ('O');
	return (data->map[ray->map.x][ray->map.y - 1] == '1');
}

/**
 * @brief Check if something was hit in the WEST direction
 * 
 * Check if a door was hit in the WEST direction
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we're working with
 * @return	An int indicating what type of block was hit
 */
static int	check_west(t_data *data, t_raycast *ray)
{
	if (data->map[ray->map.x][ray->map.y] == 'O')
		return (correct_perp_wall_dist(ray, 0.05), 'O');
	if (data->map[ray->map.x][ray->map.y] == 'c'
		&& modf(ray->h_pos.y, &(double){0}) <= 0.05)
		return (correct_perp_wall_dist(ray,
				0.05 - modf(ray->h_pos.y, &(double){0})), 'c');
	if (data->map[ray->map.x][ray->map.y] == 'C'
		&& modf(ray->h_pos.y, &(double){0}) >= 0.95)
		return (correct_perp_wall_dist(ray,
				modf(ray->h_pos.y, &(double){0}) - 0.95), 'C');
	if (data->map[ray->map.x - 1][ray->map.y] == 'o')
		return ('o');
	if (data->map[ray->map.x - 1][ray->map.y] == 'c'
			&& modf(ray->h_pos.y, &(double){0}) <= 0.05)
		return ('c');
	if (data->map[ray->map.x - 1][ray->map.y] == 'C'
			&& modf(ray->h_pos.y, &(double){0}) >= 0.95)
		return ('C');
	return (data->map[ray->map.x - 1][ray->map.y] == '1');
}

/**
 * @brief Return an integer indicating the type of block the ray hit
 *
 * This funnction check what kind of block was hit, It is needed to properly
 * render door and walls. For norming purpose it is splitted into five function
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we'rte working with
 * @return	An integer indicating what block was hit ('c'/'C'/'o'/'O'/'1'/'0')
 */
int	check_hit(t_data *data, t_raycast *ray)
{
	if (ray->side == 0 && data->player.y == (double)(int)data->player.y)
		data->player.y += 0.0000001;
	if (ray->side == 1 && data->player.x == (double)(int)data->player.x)
		data->player.x += 0.0000001;
	get_hit_pos(data, ray);
	if (ray->side == 1)
	{
		if (ray->dir.x < 0.0)
			return (check_west(data, ray));
		return (check_east(data, ray));
	}
	if (ray->dir.y < 0.0)
		return (check_south(data, ray));
	return (check_north(data, ray));
}
