/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hit_pos_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:25:29 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/17 02:40:14 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Get the exact position of the ray when a side was hit
 *
 * This functiion return the exact hit position when a side was hit
 * Just here because of the 42 norm limiting function to 25 lines
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we're actually working with
 */
static void	side_hit(t_data *data, t_raycast *ray)
{
	int		delta;
	double	real_delta_dist;
	double	real_side_dist;

	if (ray->dir.x == 0)
		real_delta_dist = 1;
	else
		real_delta_dist = sqrtf(1.0 + (ray->dir.y * ray->dir.y)
				/ (ray->dir.x * ray->dir.x));
	real_side_dist = (ray->map.x + 1.0 - data->player.x) * real_delta_dist;
	if (ray->dir.x < 0.0)
		real_side_dist = (data->player.x - ray->map.x) * real_delta_dist;
	// delta = ray->side_dist.x / ray->delta_dist.x;
	delta = real_side_dist / (real_delta_dist + 0.000000001);
	ray->h_side.x = -(data->player.x - (int)data->player.x) - delta;
	if (ray->dir.x >= 0)
		ray->h_side.x = 1.0 + (int)data->player.x - data->player.x + delta;
	ray->h_side.y = sqrtf(real_side_dist * real_side_dist
			- (ray->h_side.x * ray->h_side.x));
	ray->h_pos.x = (int)data->player.x - delta;
	if (ray->dir.x >= 0)
		ray->h_pos.x = (int)data->player.x + 1 + delta;
	ray->h_pos.y = data->player.y - ray->h_side.y;
	if (ray->dir.y >= 0)
		ray->h_pos.y = data->player.y + ray->h_side.y;
}

/**
 * @brief Get the exact position of the ray when a top/bottom side was hit
 *
 * This functiion return the exact hit position when a top/bottom side was hit
 * Just here because of the 42 norm limiting function to 25 lines
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we're actually working with
 */
static void	not_side_hit(t_data *data, t_raycast *ray)
{
	int		delta;
	double	real_delta_dist;
	double	real_side_dist;

	if (ray->dir.y == 0)
		real_delta_dist = 1;
	else
		real_delta_dist = sqrtf(1.0 + (ray->dir.x * ray->dir.x)
				/ (ray->dir.y * ray->dir.y));
	real_side_dist = (ray->map.y + 1.0 - data->player.y) * real_delta_dist;
	if (ray->dir.y < 0.0)
		real_side_dist = (data->player.y - ray->map.y) * real_delta_dist;
	delta = real_side_dist / (real_delta_dist + 0.000000001);
	ray->h_side.y = -(data->player.y - (int)data->player.y) - delta;
	if (ray->dir.y >= 0)
		ray->h_side.y = 1.0 + (int)data->player.y - data->player.y + delta;
	ray->h_side.x = sqrtf(real_side_dist * real_side_dist
			- (ray->h_side.y * ray->h_side.y));
	ray->h_pos.y = (int)data->player.y - delta;
	if (ray->dir.y >= 0)
		ray->h_pos.y = (int)data->player.y + 1 + delta;
	ray->h_pos.x = data->player.x - ray->h_side.x;
	if (ray->dir.x >= 0)
		ray->h_pos.x = data->player.x + ray->h_side.x;
}

/**
 * @brief Get the exact position of the ray hit
 *
 * This function get the exact ray hit positon
 * Updating the ray.h_pos and ray.h_side value
 * It is needed to render door and especially door side
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we're actually working with
 */
void	get_hit_pos(t_data *data, t_raycast *ray)
{
	if (ray->side == 1)
		side_hit(data, ray);
	else
		not_side_hit(data, ray);
}
