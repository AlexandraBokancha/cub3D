/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:46:15 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/18 16:46:05 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Check if an obstacle is in front of the player
 *
 * This check just a bit next to where the player is looking
 * It intend to resolve a bug where you could see throught walls by being
 * perfectly aligned whith them and walking following the border
 * It also give you're player more of a corpulence body feeling when being 
 * near walls
 *
 * @param	data	The cub3D global data structure
 * @param	move	The move the player want to do
 * @return  0 if no obstacle is found, 1 when the move is not possible 
 */
static int	obstacle(t_data *data, t_dvec move)
{
	t_dvec	pos;

	pos = init_dvec(data->player.x, data->player.y);
	if (move.x == 0)
	{
		if (data->map_info.map2d[(int)(pos.x - 0.001)]
				[(int)(pos.y + move.y * DELTA)] == '1'
				|| data->map_info.map2d[(int)(pos.x + 0.001)]
				[(int)(pos.y + move.y * DELTA)] == '1')
			return (1);
	}
	if (move.y == 0)
	{
		if (data->map_info.map2d[(int)(pos.x + move.x * DELTA)]
				[(int)(pos.y - 0.001)] == '1'
				|| data->map_info.map2d[(int)(pos.x + move.x * DELTA)]
				[(int)(pos.y + 0.001)] == '1')
			return (1);
	}
	return (data->map_info.map2d[(int)(pos.x + move.x * DELTA)]
			[(int)(pos.y)] != '1' && data->map_info.map2d[(int)pos.x]
			[(int)(pos.y + move.y * DELTA)] != '1'
			&& data->map_info.map2d[(int)(pos.x + move.x * DELTA)]
			[(int)(pos.y + move.y * DELTA)] == '1');
}

/**
 * @brief Set the move vector
 * 
 * This is needed in order to adjust move vector and direction
 *
 * @param	key			The pressed key
 * @param	direction	The player looking direction
 * @return	A t_dvec vector corresponding to the wanted player movment
 */
t_dvec	set_move(int key, t_dvec direction)
{
	t_dvec	move;
	double	tmp;

	move = init_dvec(direction.x * MOVE_SPEED,
			direction.y * MOVE_SPEED);
	if (key == S)
	{
		move.x = -move.x;
		move.y = -move.y;
	}
	if (key == A)
	{
		tmp = move.x;
		move.x = -move.y;
		move.y = tmp;
	}
	if (key == D)
	{
		tmp = move.x;
		move.x = move.y;
		move.y = -tmp;
	}
	return (move);
}

/**
 * @brief Move the player
 *
 * Make obstacle detection and move accordingly
 *
 * @param	data	The cub3D global data structure
 * @param	key		The key that was pressed
 */
void	move(t_data *data, int key)
{
	t_dvec	pos;
	t_dvec	move;

	pos = init_dvec(data->player.x, data->player.y);
	move = set_move(key, data->direction);
	if (obstacle(data, move))
		return ;
	if (data->map_info.map2d[(int)(pos.x + move.x * DELTA)][(int)pos.y] != '1')
		data->player.x += move.x;
	if (data->map_info.map2d[(int)pos.x][(int)(pos.y + move.y * DELTA)] != '1')
		data->player.y += move.y;
}
