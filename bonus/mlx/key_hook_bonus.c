/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:49:15 by dbaladro          #+#    #+#             */
/*   Updated: 2024/10/03 22:39:11 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	if (keycode == W || keycode == S || keycode == A || keycode == D
		|| keycode == ALT_W || keycode == ALT_S || keycode == ALT_A
		|| keycode == ALT_D)
		move(data, keycode);
	if (keycode == L)
	{
		if (data->mouse_visibility)
			mlx_mouse_hide(data->mlx, data->window);
		else
			mlx_mouse_show(data->mlx, data->window);
		data->mouse_visibility = (data->mouse_visibility ^ 1);
	}
	if (keycode == F || keycode == ALT_F)
		open_door(data);
	if (keycode == ARROW_LEFT || keycode == ARROW_RIGHT)
		rotate(keycode, data, ROTATION_SPEED);
	return (0);
}
