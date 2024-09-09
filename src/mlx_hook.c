/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:52:36 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/06 02:33:18 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"



// NEW
// static 

// static void	move(t_data *data, int key)
// {
// 	t_dvec		dir;
// 	t_dvec		cam_plane;
//
// 	// save original data_value
// 	dir = init_dvec(data->direction.x, data->direction.y);
// 	cam_plane = init_dvec(data->camera_plane.x, data->camera_plane.y);
//
// 	// change the t_data structure
// 	if (key == A)
// 	{
// 		data->direction = init_dvec(-dir.y, dir.x);
// 		data->camera_plane = init_dvec(-cam_plane.y, cam_plane.x);
// 	}
// 	if (key == S)
// 	{
// 		data->direction = init_dvec(-dir.x, -dir.y);
// 		data->camera_plane = init_dvec(-cam_plane.x, -cam_plane.y);
//
// 	}
// 	if (key == D)
// 	{
// 		data->direction = init_dvec(dir.y, -dir.x);
// 		data->camera_plane = init_dvec(cam_plane.y, -cam_plane.x);
// 	}
//
// 	// Check wall distance
// 	// TYHIS IS FALSE AND NEED TYO BE REWORKED
// 	// t_dvec		wall_dist;
// 	//
// 	// wall_dist = init_dvec(data->player.x - (int)data->player.x,
// 	// 		data->player.y - (int)data->player.y);
// 	// if (data->direction.x >= 0)
// 	// 	wall_dist.x = 1 - wall_dist.x;
// 	// if (data->direction.y >= 0)
// 	// 	wall_dist.y = 1 - wall_dist.y;
// 	//
// 	// // move vector
// 	// t_dvec move;
// 	//
// 	// move = init_dvec(data->direction.x * MOVE_SPEED * (wall_dist.x >= 0.1),
// 	// 	data->direction.y * MOVE_SPEED * (wall_dist.y >= 0.1));
//
// 	// Put back data value
// 	data->direction = dir;
// 	data->camera_plane = cam_plane;
//
// 	// MOVE
// 	// data->player.x += move.x;
// 	// data->player.y += move.y;
// 	// return ;
//
// 	//
// 	// shoot ray
// 	// t_raycast	ray;
// 	// ray = raycast(data, data->w_width / 2);
// 	// if (ray.hit == 1)
// 	// 	return (0);
// 	// if (ray.hit != 0 && ray.perp_wall_dist <= 0.1)
// 	// 		return (1);
// 	// return (0);
// }

// int	is_obstacle(char c, t_dvec move)
// {
// 	if (c == '0' || c =='N' || c == 'W' || c == 'S' || c == 'E')
// 		return (0);
// 	if (c == '1')
// 		return (1);
// 	if (move.x < 0 && c == 'O')
// 		return (1);
// 	if (move.x >= 0 && c == 'o')
// 		return (1);
// 	if (move.y < 0 && c == 'C')
// 		return (1);
// 	if (move.y > 0 && c == 'c')
// 		return (1);
// 	return (0);
// }

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

static int	obstacle(t_data *data, t_dvec *move)
{
	// (void)move;
	// return (new_obstacle(data, W));

	t_dvec	pos;

	pos = init_dvec(data->player.x, data->player.y);
	if (move->x == 0)
	{
		if (data->map[(int)(pos.x - 0.001)]
				[(int)(pos.y + move->y * DELTA)] == '1'
				|| data->map[(int)(pos.x + 0.001)]
				[(int)(pos.y + move->y * DELTA)] == '1'
				|| data->map[(int)(pos.x - 0.001)][(int)(pos.y + move->y * DELTA)] == 'o'
				|| data->map[(int)(pos.x + 0.001)][(int)(pos.y + move->y * DELTA)] == 'O')
			return (1);
	}
	if (move->y == 0)
	{
		if (data->map[(int)(pos.x + move->x * DELTA)]
				[(int)(pos.y - 0.001)] == '1'
				|| data->map[(int)(pos.x + move->x * DELTA)]
				[(int)(pos.y + 0.001)] == '1'
				|| data->map[(int)(pos.x + move->x * DELTA)][(int)(pos.y - 0.001)] == 'c'
				|| data->map[(int)(pos.x + move->x * DELTA)][(int)(pos.y - 0.001)] == 'C'
		   )
			return (1);
	}
	// NEW

	if (data->map[(int)(pos.x + move->x * DELTA)][(int)(pos.y)] != '1'
		&& data->map[(int)pos.x][(int)(pos.y + move->y * DELTA)] != '1'
		&& data->map[(int)(pos.x + move->x * DELTA)]
			[(int)(pos.y + move->y * DELTA)] == '1')
		return (1);
	return (0);
}

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
static void	new_move(int key, t_data *data)
{
	t_dvec	pos;
	t_dvec	move;

	if (key != W && key != S && key != A && key != D)
		return ;
	pos = init_dvec(data->player.x, data->player.y);
	move = init_dvec(data->direction.x * MOVE_SPEED,
			data->direction.y * MOVE_SPEED);
	if (key == S)
	{
		move.x = -move.x;
		move.y = -move.y;
	}
	if (key == A)
	{
		move.x = -move.y;
		move.y = move.x;
	}
	if (key == D)
	{
		move.x = move.y;
		move.y = -move.x;
	}
	if (obstacle(data, &move))
		return ;
	if (data->map[(int)(pos.x + move.x * DELTA)][(int)pos.y] != '1')
		data->player.x += move.x;
	if (data->map[(int)pos.x][(int)(pos.y + move.y * DELTA)] != '1')
		data->player.y += move.y;
}

// /**
//  * @brief Move player position to the left or right based on pressed key
//  *
//  * This function move the player position based on the pressed key
//  * A : Left | D : Right
//  * THe function if messy to be 42nrorm compliant
//  *
//  * @param	key		Keycode of the pressed key
//  * @param	data	The cub3D global data structure
//  */
// static void	move_sideway(int key, t_data *data)
// {
// 	t_dvec	pos;
// 	t_dvec	move;
//
// 	pos = init_dvec(data->player.x, data->player.y);
// 	move = init_dvec(-data->direction.y * MOVE_SPEED,
// 			data->direction.x * MOVE_SPEED);
// 	if (key == A)
// 	{
// 		if (obstacle(data, move))
// 			return ;
// 		// if (new_obstacle(data, key))
// 		// 	return ;
// 		if (data->map[(int)(pos.x + move.x * DELTA)][(int)pos.y] != '1')
// 			data->player.x += move.x;
// 		if (data->map[(int)pos.x][(int)(pos.y + move.y * DELTA)] != '1')
// 			data->player.y += move.y;
// 	}
// 	if (key != D)
// 		return ;
// 	move.x = -move.x;
// 	move.y = -move.y;
// 	if (obstacle(data, move))
// 		return ;
// 	// if (new_obstacle(data, key))
// 	// 	return ;
// 	if (data->map[(int)(pos.x + move.x * DELTA)][(int)pos.y] != '1')
// 		data->player.x += move.x;
// 	if (data->map[(int)pos.x][(int)(pos.y + move.y * DELTA)] != '1')
// 		data->player.y += move.y;
// }

/**
 * @brief Rotate camera Left or Right
 *
 * Rotate the camera Left if ARROW_LEFT was pressed
 * Rotate the camera Right if ARROW_RIGHT was pressed
 * CARREFUL you must be sure only ARROW_RIGHT or ARROW_LEFT keycode is used
 *
 * @param	keycode			Arrow_LEFT or ARROW_RIGHT
 * @param	data			The cub3D global data structure
 * @param	rotation_speed	The rotation speed
 */
void	rotate(int keycode, t_data *data, double rotation_speed)
{
	double	old_x_dir;
	double	old_camera_x_plane;

	old_x_dir = data->direction.x;
	old_camera_x_plane = data->camera_plane.x;
	if (keycode == ARROW_RIGHT)
	{
		data->direction.x = data->direction.x * cos(-rotation_speed)
			- data->direction.y * sin(-rotation_speed);
		data->direction.y = old_x_dir * sin(-rotation_speed)
			+ data->direction.y * cos(-rotation_speed);
		data->camera_plane.x = data->camera_plane.x * cos(-rotation_speed)
			- data->camera_plane.y * sin(-rotation_speed);
		data->camera_plane.y = old_camera_x_plane * sin(-rotation_speed)
			+ data->camera_plane.y * cos(-rotation_speed);
		return ;
	}
	data->direction.x = data->direction.x * cos(rotation_speed)
		- data->direction.y * sin(rotation_speed);
	data->direction.y = old_x_dir * sin(rotation_speed)
		+ data->direction.y * cos(rotation_speed);
	data->camera_plane.x = data->camera_plane.x * cos(rotation_speed)
		- data->camera_plane.y * sin(rotation_speed);
	data->camera_plane.y = old_camera_x_plane * sin(rotation_speed)
		+ data->camera_plane.y * cos(rotation_speed);
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
	if (keycode == W || keycode == S || keycode == A || keycode == D)
		new_move(keycode, data);
	// if (keycode == W || keycode == S)
	// 	move_forward_backward(keycode, data);
	// if (keycode == A || keycode == D)
	// 	move_sideway(keycode, data);
	if (keycode == ARROW_LEFT || keycode == ARROW_RIGHT)
		rotate(keycode, data, ROTATION_SPEED);
	return (0);
}
