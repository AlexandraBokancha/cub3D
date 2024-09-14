/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 05:47:37 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/14 21:06:49 by dbaladro         ###   ########.fr       */
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
 * @brief Reduce ray->side_dist when door was hit from inside the block
 *
 * This function reduce the ray->side value when a door was hitted from inside
 * It is needed to reduce the perp_wall_dist to render 'realisic' doors
 * It will also correct the side value if needed (diff != 0.05)
 * At this moment a ray hit a side of a side of another block while it should
 * render the previous door
 *
 * @param	ray		The ray we're actually working with
 * @param	diff	The ray side_dist diff we want to apply (door width)
 */
static void	correct_perp_wall_dist(t_raycast *ray, double diff)
{
	double	ratio;
	double	delta;

	if (diff != 0.05)
	{
		if (ray->side == 0)
			ray->side_dist.x = ray->side_dist.y;
		else
			ray->side_dist.y = ray->side_dist.x;
		ray->side = (1 ^ ray->side);
	}
	if (ray->side == 1)
	{
		ratio = fabs(ray->h_side.x) / diff;
		delta = ray->side_dist.x / ratio;
		ray->side_dist.x -= delta;
		return ;
	}
	ratio = fabs(ray->h_side.y) / diff;
	delta = ray->side_dist.y / ratio;
	ray->side_dist.y -= delta;
}

/**
 * @brief Check if something was hit in the North-West direction
 * 
 * Check if a door was hit in the North West direction
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we're working with
 * @return	An int indicating what type of block was hit
 */
static int	check_north_west(t_data *data, t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (data->map[ray->map.x][ray->map.y] == 'C')
			return (correct_perp_wall_dist(ray, 0.05), 'C');
		// NEW
		if (data->map[ray->map.x][ray->map.y] == 'O'
			&& modf(ray->h_pos.x, &(double){0}) <= 0.05)
			return (correct_perp_wall_dist(ray, 0.05 - modf(ray->h_pos.x, &(double){0})), 'O');
			// return (correct_perp_wall_dist(ray, 0.05), 'O');
		//
		if (data->map[ray->map.x][ray->map.y + 1] == 'c')
			return ('c');
		if (data->map[ray->map.x][ray->map.y + 1] == 'O'
				&& modf(ray->h_pos.x, &(double){0}) <= 0.05)
			return ('O');
		if (data->map[ray->map.x][ray->map.y + 1] == 'o'
				&& modf(ray->h_pos.x, &(double){0}) >= 0.95)
			return ('o');
		return (data->map[ray->map.x][ray->map.y + 1] == '1');
	}
	if (data->map[ray->map.x][ray->map.y] == 'O')
		return (correct_perp_wall_dist(ray, 0.05), 'O');
	// NEW
	if (data->map[ray->map.x][ray->map.y] == 'C'
		&& modf(ray->h_pos.y, &(double){0}) >= 0.95)
		return (correct_perp_wall_dist(ray, modf(ray->h_pos.y, &(double){0}) - 0.95), 'C');
		// return (correct_perp_wall_dist(ray, 0.05), 'O');
	//
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
 * @brief Check if something was hit in the North-Est direction
 * 
 * Check if a door was hit in the North Est direction
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we're working with
 * @return	An int indicating what type of block was hit
 */
static int	check_north_est(t_data *data, t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (data->map[ray->map.x][ray->map.y] == 'C')
			return (correct_perp_wall_dist(ray, 0.05), 'C');
		// NEW
		if (data->map[ray->map.x][ray->map.y] == 'o'
			&& modf(ray->h_pos.x, &(double){0}) >= 0.95)
			return (correct_perp_wall_dist(ray, modf(ray->h_pos.x, &(double){0}) - 0.95) , 'o');
			// return (correct_perp_wall_dist(ray, 0.05), 'O');
		//
		if (data->map[ray->map.x][ray->map.y + 1] == 'c')
			return ('c');
		if (data->map[ray->map.x][ray->map.y + 1] == 'o'
				&& modf(ray->h_pos.x, &(double){0}) >= 0.95)
			return ('o');
		if (data->map[(int)ray->h_pos.x][ray->map.y + 1] == 'O'
				&& modf(ray->h_pos.x, &(double){0}) <= 0.05)
			return ('O');
		return (data->map[ray->map.x][ray->map.y + 1] == '1');
	}
	if (data->map[ray->map.x][ray->map.y] == 'o')
		return (correct_perp_wall_dist(ray, 0.05), 'o');
	// NEW
	if (data->map[ray->map.x][ray->map.y] == 'C'
		&& modf(ray->h_pos.y, &(double){0}) >= 0.95)
		return (correct_perp_wall_dist(ray, modf(ray->h_pos.y, &(double){0}) - 0.95), 'C');
		// return (correct_perp_wall_dist(ray, 0.05), 'O');
	//
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
 * @brief Check if something was hit in the South-Est direction
 * 
 * Check if a door was hit in the South Est direction
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we're working with
 * @return	An int indicating what type of block was hit
 */
static int	check_south_est(t_data *data, t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (data->map[ray->map.x][ray->map.y] == 'c')
			return (correct_perp_wall_dist(ray, 0.05), 'c');
		// NEW
		if (data->map[ray->map.x][ray->map.y] == 'o'
			&& modf(ray->h_pos.x, &(double){0}) >= 0.95)
			return (correct_perp_wall_dist(ray, modf(ray->h_pos.x, &(double){0}) - 0.95), 'o');
			// return (correct_perp_wall_dist(ray, 0.05), 'O');
		//
		if (data->map[ray->map.x][ray->map.y - 1] == 'C')
			return ('C');
		if (data->map[ray->map.x][ray->map.y - 1] == 'o'
				&& modf(ray->h_pos.x, &(double){0}) >= 0.95)
			return ('o');
		if (data->map[ray->map.x][ray->map.y - 1] == 'O'
				&& modf(ray->h_pos.x, &(double){0}) <= 0.05)
			return ('O');
		return (data->map[ray->map.x][ray->map.y - 1] == '1');
	}
	if (data->map[ray->map.x][ray->map.y] == 'o')
		return (correct_perp_wall_dist(ray, 0.05), 'o');
	// NEW
	if (data->map[ray->map.x][ray->map.y] == 'c'
		&& modf(ray->h_pos.y, &(double){0}) <= 0.05)
		return (correct_perp_wall_dist(ray, 0.05 - modf(ray->h_pos.y, &(double){0})), 'c');
		// return (correct_perp_wall_dist(ray, 0.05), 'O');
	//
	if (data->map[ray->map.x + 1][ray->map.y] == 'O')
		return ('O');
	if (data->map[ray->map.x + 1][ray->map.y] == 'c'
			&& modf(ray->h_pos.y, &(double){0}) <= 0.05)
		return ('c');
	if (data->map[ray->map.x + 1][(int)ray->h_pos.y] == 'C'
			&& modf(ray->h_pos.y, &(double){0}) >= 0.95)
		return ('C');
	return (data->map[ray->map.x + 1][ray->map.y] == '1');
}

/**
 * @brief Check if something was hit in the South-West direction
 * 
 * Check if a door was hit in the South West direction
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we're working with
 * @return	An int indicating what type of block was hit
 */
static int	check_south_west(t_data *data, t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (data->map[ray->map.x][ray->map.y] == 'c')
			return (correct_perp_wall_dist(ray, 0.05), 'c');
		// NEW
		if (data->map[ray->map.x][ray->map.y] == 'O'
			&& modf(ray->h_pos.x, &(double){0}) <= 0.05)
			return (correct_perp_wall_dist(ray, 0.05 - modf(ray->h_pos.x, &(double){0})), 'O');
			// return (correct_perp_wall_dist(ray, 0.05), 'O');
		//
		if (data->map[ray->map.x][ray->map.y - 1] == 'C')
			return ('C');
		if (data->map[ray->map.x][ray->map.y - 1] == 'o'
				&& modf(ray->h_pos.x, &(double){0}) >= 0.95)
			return ('o');
		if (data->map[ray->map.x][ray->map.y - 1] == 'O'
				&& modf(ray->h_pos.x, &(double){0}) <= 0.05)
			return ('O');
		return (data->map[ray->map.x][ray->map.y - 1] == '1');
	}
	if (data->map[ray->map.x][ray->map.y] == 'O')
		return (correct_perp_wall_dist(ray, 0.05), 'O');
	// NEW
	if (data->map[ray->map.x][ray->map.y] == 'c'
		&& modf(ray->h_pos.y, &(double){0}) <= 0.05)
		return (correct_perp_wall_dist(ray, 0.05 - modf(ray->h_pos.y, &(double){0})), 'c');
		// return (correct_perp_wall_dist(ray, 0.05), 'O');
	//
	if (data->map[ray->map.x - 1][ray->map.y] == 'o')
		return ('C');
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
	get_hit_pos(data, ray);
	if (ray->dir.x < 0.0 && ray->dir.y < 0.0)
		return (check_south_west(data, ray));
	if (ray->dir.x < 0.0 && ray->dir.y >= 0.0)
		return (check_north_west(data, ray));
	if (ray->dir.x >= 0.0 && ray->dir.y < 0.0)
		return (check_south_est(data, ray));
	return (check_north_est(data, ray));
}
