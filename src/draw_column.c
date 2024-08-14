/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:01:52 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/14 19:08:16 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * TMP COLOR FOR WALL
 */
static int	get_color(int wall_orientation)
{
	if (wall_orientation == NORTH)
		return (0xFFFFFFFF);
	if (wall_orientation == EAST)
		return (0xFFFF0000);
	if (wall_orientation == SOUTH)
		return (0xFF00FF00);
	if (wall_orientation == WEST)
		return (0xFF0000FF);
	return (0xFF000000);
}

/**
 * @brief Return the wall orientation
 *
 * Return an int corresponding to cardinal direction the wall is facing
 *
 * @param ray The t_raycast ray
 *
 * @return 1 NORTH | 2 EAST | 3 SOUTH | 4 WEST
 */
static int	get_wall_orientation(t_raycast ray)
{
	if (ray.side == 0)
	{
		if (ray.ray_dir.x < 0)
			return (WEST);
		return (EAST);
	}
	if (ray.ray_dir.y < 0)
		return (SOUTH);
	return (NORTH);
}

/**
 * @brief Draw column to MLX image
 *
 * Draw a wall column in the MLX img based
 *
 * @param data The cub3D global data
 * @param ray The t_raycast we're working with
 */
void	draw_column(t_data *data, t_raycast ray)
{
	int	column_size;
	int	draw_start;
	int	draw_end;
	int	color;
	int	i;

	color = get_color(get_wall_orientation(ray));
	column_size = (data->w_height / ray.perp_wall_dist);
	draw_start = (-column_size / 2) + data->w_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = column_size / 2 + data->w_height / 2;
	if (draw_end >= data->w_height)
		draw_end = data->w_height - 1;
	i = draw_start;
	while (i < draw_end)
	{
		ft_mlx_pixel_put(&data->img, ray.x, i, color);
		i++;
	}
	return ;
}
