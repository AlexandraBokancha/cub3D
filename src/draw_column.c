/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:01:52 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/14 23:01:35 by dbaladro         ###   ########.fr       */
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
 * @struct s_draw
 * @brief Wall draw data structure
 *
 * This structure contain all necessary data to render textured wall
 *
 * @var s_draw::column_size
 * Size of the column to be drawn (in pixel)
 *
 * @var s_draw::start
 * The drawing starting height/line
 * 
 * @var s_draw::end
 * The drawing ending height/line
 *
 * @var s_draw::wall_orientation
 * An integer representing the wall orientation Nort/West/East/South
 *
 * @var s_draw::tex_x
 * The wall X hit position converted to texture
 *
 * @var s_draw::wall_x
 * The wall X hit position
 *
 * @var s_draw::step
 * The step from one pixel to another converted to texture size
 *
 * @var s_draw::tex_start
 * The texture Y position start
 */
typedef struct s_draw
{
	int		column_size;
	int		start;
	int		end;
	int		wall_orientation;
	int		tex_x;
	double	wall_x;
	double	step;
	double	tex_start;
}				t_draw;

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

static int	get_texture_color(t_img texture, int x, int y)
{
	char	*c;

	c = texture.addr + (x * (texture.bits_per_pixel / 8)
		+ y * texture.line_length);
	return ((int)*c);
}

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

/**
 * @brief Draw column to MLX image
 *
 * Draw a wall column in the MLX img based
 *
 * @param data The cub3D global data
 * @param ray The t_raycast we're working with
 */
// void	draw_column(t_data *data, t_raycast ray)
// {
// 	int	column_size;
// 	int	draw_start;
// 	int	draw_end;
// 	int	color;
// 	int	i;
//
// 	color = get_color(get_wall_orientation(ray));
// 	column_size = (data->w_height / ray.perp_wall_dist);
// 	draw_start = (-column_size / 2) + data->w_height / 2;
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	draw_end = column_size / 2 + data->w_height / 2;
// 	if (draw_end >= data->w_height)
// 		draw_end = data->w_height - 1;
// 	i = draw_start;
// 	while (i < draw_end)
// 	{
// 		ft_mlx_pixel_put(&data->img, ray.x, i, color);
// 		i++;
// 	}
// 	return ;
// }
