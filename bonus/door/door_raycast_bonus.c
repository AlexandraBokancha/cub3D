/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_raycast_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:28:01 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/16 17:25:06 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Check if the ray hit a door tile, either opened or closed door
 *
 * This function is a modified raycaster for doors
 * Even if the door has not to be rendered in front of the player
 * It can be closed/open maybe
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray used to check for door infront of the player
 * @return	1 if the player is facing the door,
 *			-1 player is facing the side of a door to possibly close the door
 *			Else return 0
 */
static int	face_door(t_data *data, t_raycast *ray)
{
	ray->hit = check_hit(data, ray);
	if (is_door(ray->hit))
			return (1);
	ray->hit = data->map[(int)ray->h_pos.x][(int)ray->h_pos.y];
	if (ray->side == 1)
	{
		if (ray->dir.x >= 0)
			return ((ray->hit == 'C') * -1);
			// return (is_side_door(ray->hit));
			// return (is_door(ray->hit));
		ray->hit = data->map[(int)ray->h_pos.x - 1][(int)ray->h_pos.y];
		// return (is_side_door(ray->hit));
		if (ray->hit != 'c')
			return (0);
		ray->h_pos.x -= 1;
		return (-1);
		// return (is_door(ray->hit));
	}
	if (ray->dir.y >= 0.0)
		// return (is_not_side_door(ray->hit));
		// return (is_door(ray->hit));
		return (-1 * (ray->hit == 'o'));
	ray->hit = data->map[(int)ray->h_pos.x][(int)ray->h_pos.y - 1];
	// return (is_not_side_door(ray->hit));
	if(ray->hit != 'O')
		return (0);
	ray->h_pos.y -= 1;
	return (-1);
	// return (is_door(ray->hit));
}

/**
 * @brief Check if the player can reach the door in front of him
 *
 * This function is a modified raycaster for doors
 * Even if the door has not to be rendered in front of the player
 * It can be closed/open maybe
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray used to check for door infront of the player
 * @return	1 if the player can reach the door in front of himm, else return 0
 */
static int	reach_door(t_data *data, t_raycast *ray)
{
	data->door_status = face_door(data, ray);
	if (data->door_status == 0)
		return (0);
	if (ray->side == 1)
		return (ray->side_dist.x <= PLAYER_DOOR_REACH);
	return (ray->side_dist.y <= PLAYER_DOOR_REACH);
}

/**
 * @brief Create a special ray to make player interact with door
 *
 * This function is a modified raycaster for doors
 * Even if the door has not to be rendered in front of the player
 * It can be closed/open maybe
 *
 * @param	data	The cub3D global data structure
 * @return	The final ray_resulting from the specila door raycast
 */
t_raycast	door_raycast(t_data	*data)
{
	t_raycast	ray;

	ray = init_ray(data, data->w_width / 2);
	ray.hit = 0;
	if (reach_door(data, &ray))
		return (ray);
	while (ray.side_dist.x <= 1.0 || ray.side_dist.y <= 1.0)
	{
		if (ray.side_dist.x < ray.side_dist.y)
		{
			ray.side_dist.x += ray.delta_dist.x;
			ray.map.x += ray.step.x;
		}
		else
		{
			ray.side_dist.y += ray.delta_dist.y;
			ray.map.y += ray.step.y;
		}
		ray.side = (ray.side_dist.y >= ray.side_dist.x);
		if (reach_door(data, &ray))
			break ;
	}
	return (ray);
}
