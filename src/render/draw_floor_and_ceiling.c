/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_and_ceiling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 00:48:43 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/30 19:57:53 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Draw a unicolor floor and ceiling
 * Draw th ceiling in the right color then draw the floor
 * @param	data	the cub3d global data structure
 */
void	draw_floor_and_ceiling(t_data *data)
{
	int	x;
	int	y;
	int	middle_line;

	y = -1;
	middle_line = data->w_height / 2;
	while (++y < middle_line)
	{
		x = 0;
		while (x < data->w_width)
		{
			ft_mlx_pixel_put(&data->img, x, y, data->ceiling_color);
			x++;
		}
	}
	while (y < data->w_height)
	{
		x = 0;
		while (x < data->w_width)
		{
			ft_mlx_pixel_put(&data->img, x, y, data->floor_color);
			x++;
		}
		y++;
	}
}
