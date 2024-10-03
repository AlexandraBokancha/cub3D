/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:17:31 by dbaladro          #+#    #+#             */
/*   Updated: 2024/10/03 18:54:53 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Rotate camera using the mouse
 *
 * This function allow to rotate the camera x_axis using the mouse
 *
 * @param	x		The mouse x position
 * @param	y		The mouse y position
 * @param	param	The cub3D global data structure
 */
int	camera_move(int x, int y, void *param)
{
	t_ivec	center;
	t_data	*data;
	double	rotate_speed;
	int		direction;

	(void) y;
	data = (t_data *)param;
	if (data->mouse_visibility == 1)
		return (0);
	center = init_ivec(data->w_width / 2, data->w_height / 2);
	rotate_speed = fabs((double)(x - center.x) / 100.0) * ROTATION_SPEED;
	if (x < center.x)
		direction = ARROW_LEFT;
	else if (x > center.x)
		direction = ARROW_RIGHT;
	else
		direction = 0;
	if (direction != 0)
		rotate(direction, data, rotate_speed);
	if (!data->mouse_visibility)
		mlx_mouse_move(data->mlx, data->window, center.x, center.y);
	return (0);
}
