/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:52:36 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/14 09:59:25 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

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
		if (data->map[(int)new_pos.x][(int)(new_pos.y + move.y + 0.05)] != '1')
			data->player_pos.y += move.y;
	}
	if (keycode == S)
	{
		if (data->map[(int)(new_pos.x - move.x)][(int)new_pos.y] != '1')
			data->player_pos.x -= move.x;
		if (data->map[(int)new_pos.x][(int)(new_pos.y - move.y - 0.05)] != '1')
			data->player_pos.y -= move.y;
	}
	// if (keycode == A)
	// {
	// 	if (data->map[(int)(new_pos.x - move.y - 0.05)][(int)new_pos.y] != '1')
	// 		data->player_pos.x -= move.y;
	// 	if (data->map[(int)new_pos.x][(int)(new_pos.y - move.x - 0.05)] != '1')
	// 		data->player_pos.y -= move.x;
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
 * @brief Rotate camera Left or Right
 *
 * Rotate the camera Left if ARROW_LEFT was pressed
 * Rotate the camera Right if ARROW_RIGHT was pressed
 * CARREFUL you must be sure only ARROW_RIGHT or ARROW_LEFT keycode is used
 *
 * @param keycode	Arrow_LEFT or ARROW_RIGHT
 * @param data		The cub3D global data structure
 */
static void	rotate(int keycode, t_data *data)
{
	double	old_x_dir;
	double	old_camera_x_plane;

	old_x_dir = data->direction.x;
	old_camera_x_plane = data->camera_plane.x;
	if (keycode == ARROW_RIGHT)
	{
		data->direction.x = data->direction.x * cos(-ROTATION_SPEED)
			- data->direction.y * sin(-ROTATION_SPEED);
		data->direction.y = old_x_dir * sin(-ROTATION_SPEED)
			+ data->direction.y * cos(-ROTATION_SPEED);
		data->camera_plane.x = data->camera_plane.x * cos(-ROTATION_SPEED)
			- data->camera_plane.y * sin(-ROTATION_SPEED);
		data->camera_plane.y = old_camera_x_plane * sin(-ROTATION_SPEED)
			+ data->camera_plane.y * cos(-ROTATION_SPEED);
		return ;
	}
	data->direction.x = data->direction.x * cos(ROTATION_SPEED)
		- data->direction.y * sin(ROTATION_SPEED);
	data->direction.y = old_x_dir * sin(ROTATION_SPEED)
		+ data->direction.y * cos(ROTATION_SPEED);
	data->camera_plane.x = data->camera_plane.x * cos(ROTATION_SPEED)
		- data->camera_plane.y * sin(ROTATION_SPEED);
	data->camera_plane.y = old_camera_x_plane * sin(ROTATION_SPEED)
		+ data->camera_plane.y * cos(ROTATION_SPEED);
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
	if (keycode == W || keycode == S || keycode == A)
		move(keycode, data);
	if (keycode == ARROW_LEFT || keycode == ARROW_RIGHT)
		rotate(keycode, data);
	return (0);
}
