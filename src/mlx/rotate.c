/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:36:06 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/16 12:36:15 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
