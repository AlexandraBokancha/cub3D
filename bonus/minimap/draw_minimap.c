/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:10:43 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/16 21:45:14 by dbaladro         ###   ########.fr       */
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
 * @brief Check if if the player has to be drawn on minimap
 *
 * This function check if the part of the map we're drawing is the player
 *
 * @param	data	The cub3D global data structure
 * @param	minimap	The t_minimap object we're working with
 * @param	map_pos	The map_position we're rendering on the minimap
 * @return  1 Draw player, 0 draw floor
 */
static int	is_player(t_data *data, t_minimap *minimap, t_dvec map_pos)
{
	t_dvec	player_delta;

	player_delta = init_dvec(minimap->draw_size.y / 750.0,
			minimap->draw_size.y / 750.0);
	if (fabs(data->player.x - map_pos.x) < player_delta.x
		&& fabs(data->player.y - map_pos.y) < player_delta.y)
		return (1);
	return (0);
}

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
	else if (is_player(data, minimap, map_pos))
		ft_mlx_pixel_put(&data->img, draw_pos.x, draw_pos.y,
			minimap->player_color);
	else if (data->map[(int)map_pos.x][(int)map_pos.y] == '1')
		ft_mlx_pixel_put(&data->img, draw_pos.x, draw_pos.y,
			minimap->block_color);
	else
		ft_mlx_pixel_put(&data->img, draw_pos.x, draw_pos.y,
			minimap->floor_color);
}

void	draw_player_dir(t_data *data)
{
	int		player_size;
	t_dvec	player_direction_start_drawing;
	t_dvec	player_direction_end_drawing;

	t_dvec	texture_pos;
	double	step;

	player_size = data->minimap.draw_size.x / 10.0;
	player_direction_start_drawing = init_dvec(data->minimap.map_screen_pos.x
			- player_size, data->minimap.map_screen_pos.y - player_size);
	player_direction_end_drawing = init_dvec(data->minimap.map_screen_pos.x
			+ player_size, data->minimap.map_screen_pos.y + player_size);

	// step = player_size / 64.0;
	step = 64.0 / (player_size * 2);
	(void) step;
	// texture_pos = init_dvec(-step * player_size,
	// 	-step * player_size);
	// if (texture_pos.x < -32.0)
	// 	texture_pos.x = -32.0;
	// if (texture_pos.y < -32.0)
	// 	texture_pos.y = -32.0;
	//
	texture_pos = init_dvec(-32, -32);



	int	x;
	int	y;
	int	color;
	// double	angle;
	// double	angle_cos;
	// double	angle_sin;
	t_img	player;
	t_dvec	new_tex_pos;

	player = data->texture[4];
	// x = player_direction_start_drawing.x;
	x = player_direction_end_drawing.x;
	// while (x < player_direction_end_drawing.x)
	while (x >= player_direction_start_drawing.x)
	{
		y = player_direction_start_drawing.y;
		// y = player_direction_end_drawing.y;
		texture_pos.y = -32.0;
		while (y < player_direction_end_drawing.y)
		// while (y >= player_direction_start_drawing.y)
		{
			// GET COLOR AFTER ROTATION
			// angle = atan2(-data->direction.y, data->direction.x);
			// angle_cos = cosf(angle);
			// angle_sin = sinf(angle);
			// new_tex_pos = init_dvec(texture_pos.x * angle_cos - (texture_pos.y + 10) * angle_sin,
			// 		texture_pos.x * angle_sin + (texture_pos.y + 10) * angle_cos);
			// new_tex_pos.x = floorf(new_tex_pos.x) + 25.0;
			// if (new_tex_pos.x < 0)
			// 	new_tex_pos.x = 0;
			// new_tex_pos.y = floorf(new_tex_pos.y) + 25.0;
			// if (new_tex_pos.y < 0)
			// 	new_tex_pos.y = 0;
			// printf("new_tex_pos : %f %f\n", new_tex_pos.x, new_tex_pos.y);
			new_tex_pos.x = texture_pos.x + 32.0;
			new_tex_pos.y = texture_pos.y + 32.0;
			color = (unsigned int)*(player.addr + (int)new_tex_pos.x * player.bits_per_pixel / 8
				+ (int)new_tex_pos.y * player.line_length);
			if (color != 0)
				ft_mlx_pixel_put(&data->img, x, y, color);
				
			// texture_pos.y++;
			texture_pos.y += step;
			y++;
			// y--;
		}
		// texture_pos.x++;
		texture_pos.x += step;
		// x++;
		x--;
	}
// DRAW THE PLAYER DIRECTION
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
	draw_player_dir(data);
}
