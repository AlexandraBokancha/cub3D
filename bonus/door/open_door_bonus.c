/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:36:54 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/17 01:52:12 by dbaladro         ###   ########.fr       */
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
static void	change_door_status(char *tile)
{
	if (*tile == 'c' || *tile == 'C')
		*tile += 12;
	else if (*tile == 'o' || *tile == 'O')
		*tile -= 12;
	else
		return ;
}

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

	ray = door_raycast(data);
	if (ray.side_dist.x >= PLAYER_DOOR_REACH
		&& ray.side_dist.y >= PLAYER_DOOR_REACH)
		return ;
	if (!player_can_open_door(data, &ray))
		return ;
	change_door_status(data->door);
}
