/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:27:36 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/18 13:47:22 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Set the player position, direction and camera plane
 *
 * This function set the Player position, camera direction and camera_plane
 * according to the map information
 *
 * @param	data		The cub3D global data structure
 * @param	x			X position on the map
 * @param	y			Y position on the map
 * @param	orientation	Player orientation
 */
static void	set_player(t_data *data, int x, int y, char orientation)
{
	data->player.x = (double)x + 0.5;
	data->player.y = (double)y + 0.5;
	if (orientation == 'N')
	{
		data->direction.x = 0.0;
		data->direction.y = 1.0;
	}
	if (orientation == 'S')
	{
		data->direction.x = 0.0;
		data->direction.y = -1.0;
	}
	if (orientation == 'E')
	{
		data->direction.x = 1.0;
		data->direction.y = 0.0;
	}
	if (orientation == 'W')
	{
		data->direction.x = -1.0;
		data->direction.y = 0.0;
	}
	data->camera_plane.x = 0.66 * data->direction.y;
	data->camera_plane.y = 0.66 * (-data->direction.x);
}

/**
 * @brief Init the player based on the map information
 *
 * This function first find where the player is on the map
 * when it is found it will set all necessary data in the set_player function
 *
 * @param	data	The cub3D global data structure
 */
void	init_player(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (data->map_info.map2d[x])
	{
		y = 0;
		while (data->map_info.map2d[x][y])
		{
			if (data->map_info.map2d[x][y] == 'N'
					|| data->map_info.map2d[x][y] == 'S'
					|| data->map_info.map2d[x][y] == 'E'
					|| data->map_info.map2d[x][y] == 'W')
			{
				set_player(data, x, y, data->map_info.map2d[x][y]);
				return ;
			}
			y++;
		}
		x++;
	}
	return ;
}
