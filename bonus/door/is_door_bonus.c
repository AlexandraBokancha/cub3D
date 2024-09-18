/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_door_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:51:00 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/17 01:51:48 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Check if the tile value is a side_door on map
 *
 * This function is usefull for readbility in other functions
 * And also 42 norm purpose
 *
 * @param	tile	A tile of the map
 * @return	1 if this tile is a door ( o | O ), else return 0
 */
int	is_side_door(int tile)
{
	if (tile == 'o')
		return (1);
	if (tile == 'O')
		return (1);
	return (0);
}

/**
 * @brief Check if the tile value is not a side_door on map
 *
 * This function is usefull for readbility in other functions
 * And also 42 norm purpose
 *
 * @param	tile	A tile of the map
 * @return	1 if this tile is a door ( c | C ), else return 0
 */
int	is_not_side_door(int tile)
{
	if (tile == 'c')
		return (1);
	if (tile == 'C')
		return (1);
	return (0);
}

/**
 * @brief Check if the tile value is a door on map
 *
 * This function is usefull for readbility in other functions
 * And also 42 norm purpose
 *
 * @param	tile	A tile of the map
 * @return	1 if this tile is a door (c | C | o | O), else return 0
 */
int	is_door(int tile)
{
	if (is_side_door(tile))
		return (1);
	return (is_not_side_door(tile));
}
