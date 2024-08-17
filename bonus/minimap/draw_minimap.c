/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:10:43 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/17 19:56:58 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>

/**
 * @brief Set the t_minimap.map_pos vector
 *
 * bin/This function set the map_pos vector that indicate which part of the map
 * we are rendering onj the minimap
 *
 * @param	data	the cub3D global data structure
 * @param	minimap	the t_minimap object we're working on
 * @return  The same t_minimap object with updated map_pos param 
 */
// static t_minimap	set_minimap_val(t_data *data, t_minimap minimap)
// {
// 	minimap.map_pos = init_dvec(data->player.x, data->player.y);
// 	// if (fabs(data->map_size.x - data->player.x) < minimap.block.x / 2.0)
// 	// {
// 	// 	if (minimap.map_pos.x < minimap.block.x / 2.0)
// 	// 		minimap.map_pos.x = minimap.block.x / 2.0;
// 	// 	else
// 	// 		minimap.map_pos.x = data->map_size.x - minimap.block.x / 2.0;
// 	// }
// 	// if (fabs(data->map_size.y - data->player.y) < minimap.block.y / 2.0)
// 	// {
// 	// 	if (minimap.map_pos.y < minimap.block.y / 2.0)
// 	// 		minimap.map_pos.y = minimap.block.y / 2.0;
// 	// 	else
// 	// 		minimap.map_pos.y = data->map_size.y - minimap.block.y / 2.0;
// 	// }
// 	return (minimap);
// }

/**
 * @brief Check if the map_position is inside the map
 *
 * This function check if the position is inside the map
 * Mostly to avoid segfault
 *
 * @param	data	The cub3D global data structure
 * @param	map_pos	The position on the map
 * @return  1 Out of the map, 0 In the map
 */
static int	is_not_int_map(t_data *data, t_dvec map_pos)
{
	int	x;
	int	y;

	if (map_pos.x < 0 || map_pos.y < 0)
		return (1);
	x = 0;
	while (data->map[x] && x < (int)map_pos.x)
		x++;
	if (x != (int)map_pos.x || !data->map[x])
		return (1);
	y = 0;
	while (data->map[x][y] && y < (int)map_pos.y)
		y++;
	if (y != (int)map_pos.y || !data->map[x][y])
		return (1);
	return (0);
}

/**
 * @brief Draw one minimap pixel in data->ing
 *
 * This function draw one pixel of the minimap in the data->img.img MLX image
 * It will put the righjt color depending on what is on the map
 *
 * @param	data		the cub3D global data structure
 * @param	minimap		The t_minimap object
 * @param	map_pos		The position of the map we're going to render
 * @param	draw_pos	The position on the screen we're going to put the pixel
 */
static void	put_minimap_pixel(t_data *data, t_minimap *minimap,
	t_dvec map_pos, t_ivec draw_pos)
{
	if (is_not_int_map(data, map_pos))
		ft_mlx_pixel_put(&data->img, draw_pos.x, draw_pos.y,
			minimap->outbound_color);
	else if (data->map[(int)map_pos.x][(int)map_pos.y] == '1')
		ft_mlx_pixel_put(&data->img, draw_pos.x, draw_pos.y,
			minimap->block_color);
	else
		ft_mlx_pixel_put(&data->img, draw_pos.x, draw_pos.y,
			minimap->floor_color);
}

/**
 * @brief Get the right pixel color when drawing the minimap player
 *
 * This function perform the rotation of player texture
 * and return the right pixel color after rotation
 *
 * @param	data	The cub3D global structure
 * @param	tex_pos	The texture pixel position
 * @param	cos_dir	The direction angle cosinus
 * @param	sin_dir	The direction angle sinus
 * @return  The color TRGB value
 */
static int	get_color(t_data *data, t_dvec tex_pos, double cos_dir,
	double sin_dir)
{
	t_dvec	rotate_tex_pos;
	int		color;

	rotate_tex_pos = init_dvec(tex_pos.x * cos_dir
			- (tex_pos.y - 7) * sin_dir,
			tex_pos.x * sin_dir + (tex_pos.y - 7) * cos_dir);
	rotate_tex_pos.x = floorf(rotate_tex_pos.x) + 32.0;
	if (rotate_tex_pos.x < 0)
		rotate_tex_pos.x = 0;
	rotate_tex_pos.y = floorf(rotate_tex_pos.y) + 28.0;
	if (rotate_tex_pos.y < 0)
		rotate_tex_pos.y = 0;
	color = (unsigned int)*(data->texture[4].addr
			+ (int)rotate_tex_pos.x * data->texture[4].bits_per_pixel / 8
			+ (int)rotate_tex_pos.y * data->texture[4].line_length);
	return (color);
}

/**
 * @brief Draw player on the minimap
 *
 * Draw the player + orientation on the minimap
 *
 * @param	data	The cub3D global data structure
 */
void	draw_player(t_data *data)
{
	t_ivec	pos;
	t_dvec	texture_pos;
	int		color;
	double	angle_cos;
	double	angle_sin;

	pos = init_ivec(data->minimap.player_draw_end.x, 0);
	angle_cos = cosf(-atan2(-data->direction.x, data->direction.y));
	angle_sin = sinf(-atan2(-data->direction.x, data->direction.y));
	texture_pos = init_dvec(-30, -32);
	while (pos.x >= data->minimap.player_draw_start.x)
	{
		pos.y = data->minimap.player_draw_start.y;
		texture_pos.y = -32.0;
		while (pos.y < data->minimap.player_draw_end.y)
		{
			color = get_color(data, texture_pos, angle_cos, angle_sin);
			if (color != 0)
				ft_mlx_pixel_put(&data->img, pos.x, pos.y, 0x0052FF6F);
			texture_pos.y += data->minimap.player_step;
			pos.y++;
		}
		texture_pos.x += data->minimap.player_step;
		pos.x--;
	}
}

/**
 * @brief Draw the minimap on screen
 *
 * Draw the minimap + player position on screen
 *
 * @param	data	The cub3D global data structure
 */
void	draw_minimap(t_data *data)
{
	t_ivec	draw_pos;
	t_dvec	map_pos;

	draw_pos = init_ivec(data->minimap.draw_start.x,
			data->minimap.draw_start.y);
	map_pos = init_dvec(data->player.x - data->minimap.block.x / 2.0 + 0.5,
			data->minimap.map_pos.y + data->minimap.block.y / 2.0);
	while (draw_pos.x < data->minimap.draw_end.x)
	{
		draw_pos.y = data->minimap.draw_end.y - 1;
		map_pos.y = data->player.y - data->minimap.block.y / 2.0 + 0.5;
		while (draw_pos.y >= data->minimap.draw_start.y)
		{
			put_minimap_pixel(data, &data->minimap, map_pos, draw_pos);
			map_pos.y += data->minimap.step;
			draw_pos.y--;
		}
		map_pos.x += data->minimap.step;
		draw_pos.x++;
	}
	draw_player(data);
}
