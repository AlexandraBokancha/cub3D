/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_perp_wall_dist_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 21:50:26 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/14 21:51:00 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	correct_perp_wall_dist(t_raycast *ray, double diff)
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
