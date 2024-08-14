/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:52:36 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/14 19:14:04 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

/**
 * @brief Move player position based on pressed key
 *
 * This function move the player position based on the pressed key
 * W : Forward | S : Backward | A : Left | D : Right
 * THe function if messy to be 42nrorm compliant
 *
 * @param	key		Keycode of the pressed key
 * @param	data	The cub3D global data structure
 */
static void	move(int key, t_data *data)
{
	t_vec	pos;
	t_vec	move;

	pos = init_vec(data->player.x, data->player.y);
	move = init_vec(data->direction.x * MOVE_SPEED,
			data->direction.y * MOVE_SPEED);
	if (key == S && data->map[(int)(pos.x - move.x * 1.1)][(int)pos.y] != '1')
		move.x = -move.x;
	if (key == S && data->map[(int)pos.x][(int)(pos.y - move.y * 1.1)] != '1')
		move.y = -move.y;
	if (key == A && data->map[(int)(pos.x - move.y * 1.1)][(int)pos.y] != '1')
		move.x = -(data->direction.y * MOVE_SPEED);
	if (key == A && data->map[(int)pos.x][(int)(pos.y + move.x * 1.1)] != '1')
		move.y = data->direction.x * MOVE_SPEED;
	if (key == D && data->map[(int)(pos.x + move.y * 1.1)][(int)pos.y] != '1')
		move.x = data->direction.y * MOVE_SPEED;
	if (key == D && data->map[(int)pos.x][(int)(pos.y - move.x * 1.1)] != '1')
		move.y = -(data->direction.x * MOVE_SPEED);
	data->player.x += move.x;
	data->player.y += move.y;
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
	if (keycode == W || keycode == S || keycode == A || keycode == D)
		move(keycode, data);
	if (keycode == ARROW_LEFT || keycode == ARROW_RIGHT)
		rotate(keycode, data);
	return (0);
}

// int	camera_move(int x, int y, void *param)
// {
// 	// int		mouse_x;
// 	// int		mouse_y;
// 	t_data	*data;
//
// 	data = (t_data *)param;
// 	(void)data;
// 	// mlx_mouse_get_pos(data->mlx, data->window, &mouse_x, &mouse_y);
// 	printf("mouse_pos = (%5d, %5d)\n", x, y);
// 	// printf("mouse_pos = (%5d, %5d)\n", mouse_x, mouse_y);
// 	return (0);
// }
