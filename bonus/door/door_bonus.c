/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:02:44 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/16 17:26:41 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Print the text open when player can open a door
 *
 * This function print a msg annoncing if the player can open/close the door
 *
 * @param	data	The cub3D global data structure
 * @param	color	The color in which to print the message (show possibility)
 */
static void	print_open_door(t_data *data, int color)
{
	if (data->door_status == 1)
		mlx_string_put(data->mlx, data->window, data->w_width / 2,
			data->w_height / 1.8, color, "OPEN");
	else
		mlx_string_put(data->mlx, data->window, data->w_width / 2,
			data->w_height / 1.8, color, "CLOSE");
}

/**
 * @brief Check if the player have a door in front of him and can reach it
 *
 * This function check if the player can interact with the door in front of him
 * This is needed to print the 'open' msg on screen when needed
 */
void	check_door(t_data *data)
{
	t_raycast	ray;

	ray = door_raycast(data);
	if (!is_door(ray.hit))
		return ;
	if (ray.side_dist.x >= PLAYER_DOOR_REACH
		&& ray.side_dist.y >= PLAYER_DOOR_REACH)
		return ;
	if (player_can_open_door(data, &ray))
		print_open_door(data, 0xFFFFFFF);
	else
		print_open_door(data, 0xFFFF0000);
}
