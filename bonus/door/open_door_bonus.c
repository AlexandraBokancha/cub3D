/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:36:54 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/16 16:43:26 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Open a door when it's closed, close it when it was open
 *
 * This function Open or Close door based on previous status
 * 
 * @param	data	The cub3D global data structure
 * @param	pos		The position of the door on the map
 */
static void	change_door_status(t_data *data, t_ivec pos)
{
	if (data->map[pos.x][pos.y] == 'c'
		|| data->map[pos.x][pos.y] == 'C')
		data->map[pos.x][pos.y] += 12;
	else if (data->map[pos.x][pos.y] == 'o'
		|| data->map[pos.x][pos.y] == 'O')
		data->map[pos.x][pos.y] -= 12;
	else
		return ;
}

/**
 * @brief Get door position
 *
 * This function get the position of the door we're trying to open
 * It is needed to open the right door
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The ray containing data abpout the door
 * @return	The position of the door the player is aiming at
 */
// static t_ivec	get_door_pos(t_data *data, t_raycast *ray)
// {
// 	t_ivec	pos;
//
// 	pos = init_ivec((int)ray->h_pos.x, (int)ray->h_pos.y);
// 	if 
// }

/**
 * @brief Open a door when F was pressed
 *
 * This function open on close door on 'F' key press, when possible
 *
 * @param	data	The cub3D global data structure
 */
void	open_door(t_data *data)
{
	t_raycast	ray;
	t_ivec		pos;

	ray = door_raycast(data);
	if (ray.side_dist.x >= PLAYER_DOOR_REACH
		&& ray.side_dist.y >= PLAYER_DOOR_REACH)
		return ;
	if (!player_can_open_door(data, &ray))
		return ;
	// pos = get_door_pos(data, &ray);
	pos = init_ivec((int)ray.h_pos.x, (int)ray.h_pos.y);
	change_door_status(data, pos);
}
