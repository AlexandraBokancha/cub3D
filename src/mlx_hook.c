/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:52:36 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/15 12:27:49 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

/**
 * @brief Move player position forward or backward based on pressed key
 *
 * This function move the player position based on the pressed key
 * W : Forward | S : Backward
 * THe function if messy to be 42nrorm compliant
 *
 * @param	key		Keycode of the pressed key
 * @param	data	The cub3D global data structure
 */
static void	move_forward_backward(int key, t_data *data)
{
	t_vec	pos;
	t_vec	move;

	pos = init_vec(data->player.x, data->player.y);
	move = init_vec(data->direction.x * MOVE_SPEED,
			data->direction.y * MOVE_SPEED);
	if (key == W)
	{
		if (data->map[(int)(pos.x + move.x * DELTA)]
				[(int)(pos.y + move.y * DELTA)] == '1')
			return ;
		if (data->map[(int)(pos.x + move.x * DELTA)][(int)pos.y] != '1')
			data->player.x += move.x;
		if (data->map[(int)pos.x][(int)(pos.y + move.y * DELTA)] != '1')
			data->player.y += move.y;
	}
	if (key != S)
		return ;
	if (data->map[(int)(pos.x - move.x * DELTA)]
			[(int)(pos.y - move.y * DELTA)] == '1')
		return ;
	if (data->map[(int)(pos.x - move.x * DELTA)][(int)pos.y] != '1')
		data->player.x -= move.x;
	if (data->map[(int)pos.x][(int)(pos.y - move.y * DELTA)] != '1')
		data->player.y -= move.y;
}

/**
 * @brief Move player position to the left or right based on pressed key
 *
 * This function move the player position based on the pressed key
 * A : Left | D : Right
 * THe function if messy to be 42nrorm compliant
 *
 * @param	key		Keycode of the pressed key
 * @param	data	The cub3D global data structure
 */
static void	move_sideway(int key, t_data *data)
{
	t_vec	pos;
	t_vec	move;

	pos = init_vec(data->player.x, data->player.y);
	move = init_vec(data->direction.x * MOVE_SPEED,
			data->direction.y * MOVE_SPEED);
	if (key == A)
	{
		if (data->map[(int)(pos.x - move.y * DELTA)]
			[(int)(pos.y + move.x * DELTA)] == '1')
			return ;
		if (data->map[(int)(pos.x - move.y * DELTA)][(int)pos.y] != '1')
			data->player.x -= move.y;
		if (data->map[(int)pos.x][(int)(pos.y + move.x * DELTA)] != '1')
			data->player.y += move.x;
	}
	if (key != D)
		return ;
	if (data->map[(int)(pos.x + move.y * DELTA)]
		[(int)(pos.y - move.x * DELTA)] == '1')
		return ;
	if (data->map[(int)(pos.x + move.y * DELTA)][(int)pos.y] != '1')
		data->player.x += move.y;
	if (data->map[(int)pos.x][(int)(pos.y - move.x * DELTA)] != '1')
		data->player.y -= move.x;
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
 * It will either move or rotate the camera
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
		move_forward_backward(keycode, data);
	if (keycode == A || keycode == D)
		move_sideway(keycode, data);
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
