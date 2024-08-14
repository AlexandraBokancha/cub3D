/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:01:52 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/15 00:56:19 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

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
		if (ray.dir.x < 0)
			return (WEST);
		return (EAST);
	}
	if (ray.dir.y < 0)
		return (SOUTH);
	return (NORTH);
}

/**
 * @brief Create a new t_draw object based on data and ray
 *
 * Create a new t_draw object with all necessary information for wall drawing
 *
 * @param	data	The cub3D global data structure
 * @param	ray		The t_raycast we're actualy working with
 * @return  A new T_draw object  
 */
static t_draw	init_draw(t_data *data, const t_raycast *ray)
{
	t_draw	draw;

	draw.column_size = (data->w_height / ray->perp_wall_dist);
	draw.start = (-draw.column_size / 2) + data->w_height / 2;
	if (draw.start < 0)
		draw.start = 0;
	draw.end = draw.column_size / 2 + data->w_height / 2;
	if (draw.end >= data->w_height)
		draw.end = data->w_height - 1;
	draw.wall_orientation = get_wall_orientation(*ray) - 1;
	if (ray->side == 0)
		draw.wall_x = data->player.y + ray->perp_wall_dist * ray->dir.y;
	else
		draw.wall_x = data->player.x + ray->perp_wall_dist * ray->dir.x;
	draw.wall_x -= floorf(draw.wall_x);
	draw.tex_x = (int)(draw.wall_x * TEXTURE_WIDTH);
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		draw.tex_x = TEXTURE_WIDTH - draw.tex_x - 1;
	draw.step = 1.0 * TEXTURE_HEIGHT / draw.column_size;
	draw.tex_start = (draw.start - (double)data->w_height / 2
			+ (double)draw.column_size / 2) * draw.step;
	return (draw);
}

/**
 * @brief Get texture color on position x, y
 *
 * Get texture color on position x, y
 * CARREFUL the function is not protected against invalid x and y
 *
 * @param	texture	The t_img texture
 * @param	x		X position
 * @param	y		Y position
 * @return  An unsigned int color
 */
static int	get_texture_color(t_img texture, int x, int y)
{
	char	*c;

	c = texture.addr + (x * (texture.bits_per_pixel / 8)
			+ y * texture.line_length);
	return ((int)*c);
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
	t_draw	draw;
	int		color;
	int		i;
	int		tex_y;

	draw = init_draw(data, &ray);
	i = draw.start;
	while (i < draw.end)
	{
		tex_y = (int)draw.tex_start & ((int)TEXTURE_HEIGHT - 1);
		draw.tex_start += draw.step;
		color = get_texture_color(data->texture[draw.wall_orientation],
				draw.tex_x, tex_y);
		ft_mlx_pixel_put(&data->img, ray.x, i, color);
		i++;
	}
	return ;
}
