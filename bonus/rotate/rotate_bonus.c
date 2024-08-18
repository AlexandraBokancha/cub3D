/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:17:31 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/18 11:18:35 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	camera_move(int x, int y, void *param)
{
	// int		mouse_x;
	// int		mouse_y;
	t_data	*data;

	data = (t_data *)param;
	(void)data;
	// mlx_mouse_get_pos(data->mlx, data->window, &mouse_x, &mouse_y);
	printf("mouse_pos = (%5d, %5d)\n", x, y);
	// printf("mouse_pos = (%5d, %5d)\n", mouse_x, mouse_y);
	return (0);
}
