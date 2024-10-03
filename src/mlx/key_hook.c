/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:52:36 by dbaladro          #+#    #+#             */
/*   Updated: 2024/10/03 14:56:56 by albokanc         ###   ########.fr       */
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
	if (keycode == W || keycode == S || keycode == A || keycode == D)
		move(data, keycode);
	if (keycode == ARROW_LEFT || keycode == ARROW_RIGHT)
		rotate(keycode, data, ROTATION_SPEED);
	return (0);
}
