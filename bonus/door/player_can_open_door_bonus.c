/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_can_open_door_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:25:11 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/16 17:36:11 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Check if the player can open a 'c' door
 *
 * This function check if the player can open a 'c' door
 * It ishere for 42 norm purpose
 *
 * @param	data	The cub3D global data structure
 * @param	player	The player converted to (int) coordinated
 * @param	h_pos	The ray->h_pos converted to (int)
 * @return	1 if the door can be opened, else 0
 */
static int	check_down_door(t_data *data, t_ivec player, t_ivec h_pos)
{
	if (player.y != h_pos.y)
		return (1);
	if (player.x == h_pos.x && data->player.x - player.x >= 0.85)
		return (0);
	if (player.x == h_pos.x + 1 && data->player.x - player.x <= 0.15)
		return (0);
	return (1);
}

/**
 * @brief Check if the player can open a 'C' door
 *
 * This function check if the player can open a 'C' door
 * It ishere for 42 norm purpose
 *
 * @param	data	The cub3D global data structure
 * @param	player	The player converted to (int) coordinated
 * @param	h_pos	The ray->h_pos converted to (int)
 * @return	1 if the door can be opened, else 0
 */
static int	check_up_door(t_data *data, t_ivec player, t_ivec h_pos)
{
	if (player.y != h_pos.y - 1)
		return (1);
	if (player.x == h_pos.x && data->player.x - player.x >= 0.85)
		return (0);
	if (player.x == h_pos.x - 1 && data->player.x - player.x <= 0.15)
		return (0);
	return (1);
}

/**
 * @brief Check if the player can open a 'o' door
 *
 * This function check if the player can open a 'o' door
 * It ishere for 42 norm purpose
 *
 * @param	data	The cub3D global data structure
 * @param	player	The player converted to (int) coordinated
 * @param	h_pos	The ray->h_pos converted to (int)
 * @return	1 if the door can be opened, else 0
 */
static int	check_right_door(t_data *data, t_ivec player, t_ivec h_pos)
{
	if (player.x != h_pos.x - 1)
		return (1);
	if (player.y == h_pos.y + 1 && data->player.y - player.y >= 0.80)
		return (0);
	if (player.y == h_pos.y && data->player.y - player.y <= 0.10)
		return (0);
	return (1);
}

/**
 * @brief Check if the player can open a 'O' door
 *
 * This function check if the player can open a 'O' door
 * It ishere for 42 norm purpose
 *
 * @param	data	The cub3D global data structure
 * @param	player	The player converted to (int) coordinated
 * @param	h_pos	The ray->h_pos converted to (int)
 * @return	1 if the door can be opened, else 0
 */
static int	check_left_door(t_data *data, t_ivec player, t_ivec h_pos)
{
	if (player.x != h_pos.x)
		return (1);
	if (player.y == h_pos.y && data->player.y - player.y >= 0.80)
		return (0);
	if (player.y == h_pos.y + 1 && data->player.y - player.y <= 0.10)
		return (0);
	return (1);
}

/**
 * @brief Return 1 if the player can open the door
 *
 * This function check if the player can open the door
 * It does it by checking if the player will not get stuck in it after opening
 * It is needed to print the write 'open' msg and to open doors
 */
int	player_can_open_door(t_data *data, t_raycast *ray)
{
	t_ivec	player;
	t_ivec	h_pos;

	player = init_ivec((int)data->player.x, (int)data->player.y);
	h_pos = init_ivec((int)ray->h_pos.x, (int)ray->h_pos.y);
	if (ray->hit == 'c')
		return (check_down_door(data, player, h_pos));
	if (ray->hit == 'C')
		return (check_up_door(data, player, h_pos));
	if (ray->hit == 'o')
		return (check_right_door(data, player, h_pos));
	if (ray->hit == 'O')
		return (check_left_door(data, player, h_pos));
	return (0);
}
