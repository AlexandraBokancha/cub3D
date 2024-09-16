/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:02:44 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/16 15:20:38 by dbaladro         ###   ########.fr       */
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
	mlx_string_put(data->mlx, data->window, data->w_width / 2,
		data->w_height / 1.8, color, "OPEN");
}

/**
 * @brief Check if the player is looking at a door he can reach
 *
 * This function return 1 if the player can reach the door he's looking at
 *
 * @param	data	The cub3D global data structure
 * @return	1 if the player can reach the door an open it, else 0
 */
// int	is_aiming_at_door(t_data *data, t_raycast *ray)
// {
// 	(void) data;
// 	if (!(ray->hit == 'c' || ray->hit == 'C' || ray->hit == 'o' || ray->hit == 'O'))
// 		return (0);
// 	if (ray->side == 1)
// 		return (ray->side_dist.x <= 0.35);
// 	return (ray->side_dist.y <= 0.35);
// }

int	player_can_open_door(t_data *data, t_raycast *ray)
{
	t_ivec	player;
	t_ivec	h_pos;

	player = init_ivec((int)data->player.x, (int)data->player.y);
	h_pos = init_ivec((int)ray->h_pos.x, (int)ray->h_pos.y);
	if (ray->hit == 'c')
	{
		if (player.y != h_pos.y)
			return (1);
		if (player.x == h_pos.x && data->player.x - player.x >= 0.85)
			return (0);
		if (player.x == h_pos.x + 1 && data->player.x - player.x <= 0.15)
			return (0);
		return (1);
	}
	if (ray->hit == 'C')
	{
		if (player.y != h_pos.y - 1)
			return (1);
		if (player.x == h_pos.x && data->player.x - player.x >= 0.85)
			return (0);
		if (player.x == h_pos.x - 1 && data->player.x - player.x <= 0.15)
			return (0);
		return (1);
	}
	if (ray->hit == 'o')
	{
		if (player.x != h_pos.x - 1)
			return (1);
		if (player.y == h_pos.y + 1 && data->player.y - player.y >= 0.85)
			return (0);
		if (player.y == h_pos.y && data->player.y - player.y <= 0.15)
			return (0);
		return (1);
	}
	if (ray->hit == 'O')
	{
		if (player.x != h_pos.x)
			return (1);
		if (player.y == h_pos.y && data->player.y - player.y >= 0.85)
			return (0);
		if (player.y == h_pos.y + 1 && data->player.y - player.y <= 0.15)
			return (0);
		return (1);
	}
	return (0);
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
