/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:52:36 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/13 21:36:26 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	move(int keycode, t_data *data)
{
	t_vec	new_pos;
	t_vec	move;

	new_pos = init_vec(data->player_pos.x, data->player_pos.y);
	move = init_vec(data->direction.x * MOVE_SPEED,
		data->direction.y * MOVE_SPEED);
	if (keycode == W)
	{
		if (data->map[(int)(new_pos.x + move.x)][(int)new_pos.y] != '1')
			data->player_pos.x += move.x;
		if (data->map[(int)new_pos.x][(int)(new_pos.y + move.y + 0.1)] != '1')
			data->player_pos.y += move.y;
	}
	if (keycode == S)
	{
		if (data->map[(int)(new_pos.x - move.x)][(int)new_pos.y] != '1')
			data->player_pos.x -= move.x;
		if (data->map[(int)new_pos.x][(int)(new_pos.y - move.y - 0.1)] != '1')
			data->player_pos.y -= move.y;
	}
	// if (keycode == W)
	// {
	// 	if (data->map[(int)(new_pos.x + move.x + 0.1)][(int)new_pos.y] != '1')
	// 		data->player_pos.x += move.x;
	// 	if (data->map[(int)new_pos.x][(int)(new_pos.y + move.y + 0.1)] != '1')
	// 		data->player_pos.y += move.y;
	// }
	// if (keycode == W)
	// {
	// 	if (data->map[(int)(new_pos.x + move.x + 0.1)][(int)new_pos.y] != '1')
	// 		data->player_pos.x += move.x;
	// 	if (data->map[(int)new_pos.x][(int)(new_pos.y + move.y + 0.1)] != '1')
	// 		data->player_pos.y += move.y;
	// }
}

/**
 * @brief Key handler
 *
 * This function will choose what to execute based on the pressed key
 *
 * @param	keycode The code of the pressed key
 * @param	param	The t_data * cub3D structure
 * @return	0
 */
int	key_hook(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == ESC)
		exit_cub(data);
	if (keycode == W || keycode == S)
		move(keycode, data);
	return (0);
}
