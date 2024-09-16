/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:02:44 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/16 12:24:21 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Print the text open when player can open a door
 *
 * This function print a msg annoncing if the player can open/close the door
 *
 * @param	data	The cub3D global data structure
 */
static void	print_open_door(t_data *data)
{
	mlx_string_put(data->mlx, data->window, data->w_width / 2,
		data->w_height / 1.8, 0xFFFFFFFF, "OPEN");
}

/**
 * @brief Check if the player is looking at a door he can reach
 *
 * This function return 1 if the player can reach the door he's looking at
 *
 * @param	data	The cub3D global data structure
 * @return	1 if the player can reach the door an open it, else 0
 */
int	is_aiming_at_door(t_data *data, t_raycast *ray)
{
	(void) data;
	if (!(ray->hit == 'c' || ray->hit == 'C' || ray->hit == 'o' || ray->hit == 'O'))
		return (0);
	if (ray->side == 1)
		return (ray->side_dist.x <= 0.35);
	return (ray->side_dist.y <= 0.35);
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

	ray = raycast(data, data->w_width / 2);
	if (is_aiming_at_door(data, &ray))
		print_open_door(data);
}
