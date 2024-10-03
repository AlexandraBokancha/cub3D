/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:24:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/10/03 19:30:22 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	mouse_hook(int button, int x, int y, void *param)
{
	t_data	*data;

	(void) x;
	(void) y;
	data = (t_data *)param;
	if (button == 1)
	{
		if (data->mouse_visibility)
			mlx_mouse_hide(data->mlx, data->window);
		else
			mlx_mouse_show(data->mlx, data->window);
		data->mouse_visibility = (data->mouse_visibility ^ 1);
	}
	return (0);
}
