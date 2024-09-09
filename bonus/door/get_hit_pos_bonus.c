/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hit_pos_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:25:29 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/09 21:47:11 by dbaladro         ###   ########.fr       */
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
	double	delta;

	delta = ray->side_dist.x / ray->delta_dist.x;
	ray->h_side.x = 1.0 + data->player.x - (int)data->player.x - delta;
	if (data->direction.x >= 0)
		ray->h_side.x = data->player.x - (int)data->player.x + delta;
	ray->h_side.y = sqrtf(ray->side_dist.x * ray->side_dist.x
		- (ray->h_side.x * ray->h_side.x));
	ray->h_pos.x = (int)data->player.x - delta;
	if (data->direction.x >= 0)
		ray->h_pos.x = (int)data->player.x + 1 + delta;
	ray->h_pos.y = data->player.y - ray->h_side.y;
	if (data->direction.y >= 0)
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
	double	delta;

	delta = ray->side_dist.y / ray->delta_dist.y;
	ray->h_side.y = 1.0 + data->player.y - (int)data->player.y - delta;
	if (data->direction.y >= 0)
		ray->h_side.y = data->player.y - (int)data->player.y + delta;
	ray->h_side.y = sqrtf(ray->side_dist.y * ray->side_dist.y
		- (ray->h_side.y * ray->h_side.y));
	ray->h_pos.y = (int)data->player.y - delta;
	if (data->direction.y >= 0)
		ray->h_pos.y = (int)data->player.y + 1 + delta;
	ray->h_pos.x = data->player.x - ray->h_side.x;
	if (data->direction.x >= 0)
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
