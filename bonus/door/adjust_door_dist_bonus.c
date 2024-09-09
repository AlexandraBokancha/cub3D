/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_door_dist_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:02:44 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/09 22:06:53 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Adjust the ray->side_dist when hitting a door to give it some 3D
 *
 * Adjust the ray->side_dist changinf to change the perp_wall_dist
 * Give the door some 'fat' and realistic aspect
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray we're working with
 */
void	adjust_door_dist(t_data *data, t_raycast *ray)
{

}
