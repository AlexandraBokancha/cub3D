/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:10:43 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/16 09:29:21 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

/**
 * @brief Return the map size
 *
 * This function create a new t_ivec an store the map size
 * max X and Max Y
 *
 * @param	map	The map
 * @return  A vector containing the map size 
 */
t_ivec	get_map_size(const char **map)
{
	t_ivec	map_block;
	int		x;
	int		y;

	map_block = init_ivec(0, 0);
	x = 0;
	while (map[x])
	{
		while (map[x][y])
			y++;
		if (y > map_block.y)
			map_block.y = y;
		x++;
	}
	map_block.x = x;
	return (map_block);
}

/**
 * @brief Init the minimap data structure
 *
 * This function init the minimap data structure
 * It should be called once has most of the value have not to be calcuated
 *
 * @param	data	The cub3D global data structure
 * @return  The t_minimap data structure
 */
t_minimap	init_minimap(t_data *data)
{
	t_minimap	mmap;
	// int			mmap_half_x;
	// int			mmap_half_y;
	int			y;

	mmap.draw_size = init_ivec(data->w_width / 10, data->w_height / 10);
	mmap.map_screen_pos = init_ivec((mmap.draw_size.x / 2.0) * 1.05,
		(mmap.draw_size.y / 2.0) * 1.1);
	mmap.draw_start = init_ivec(mmap.map_screen_pos.x - mmap.draw_size.x / 2,
			mmap.map_screen_pos.y - mmap.draw_size.y / 2); 
	mmap.draw_end = init_ivec(mmap.map_screen_pos.x + mmap.draw_size.x / 2,
			mmap.map_screen_pos.y + mmap.draw_size.y / 2); 
	// GET MAP SIZE
	mmap.map_size = init_ivec(0, 0);
	while (data->map[mmap.map_size.x])
	{
		y = 0;
		while (data->map[mmap.map_size.x][y])
			y++;
		if (y > mmap.map_size.y)
			mmap.map_size.y = y;
		mmap.map_size.x++;
	}
	mmap.block = init_ivec(mmap.map_size.x, mmap.map_size.y);
	if (mmap.block.x > 10)
		mmap.block.x = 10;
	if (mmap.block.y > 10)
		mmap.block.y = 10;
	mmap.step = init_dvec((double)mmap.block.x / mmap.draw_size.x,
			(double)mmap.block.y / mmap.draw_size.y);
	mmap.block_color = MINIMAP_BLOCK_COLOR;
	mmap.floor_color = MINIMAP_FLOOR_COLOR;
	mmap.player_color = MINIMAP_PLAYER_COLOR;
	return (mmap);
}

t_minimap	set_minimap_val(t_data *data, t_minimap minimap)
{

	minimap.map_pos = init_ivec((int)data->player.x, (int)data->player.y);
	if (fabs(minimap.map_size.x - data->player.x) < minimap.block.x / 2.0)
	{
		if (minimap.map_pos.x < minimap.block.x / 2.0)
			minimap.map_pos.x = minimap.block.x / 2.0;
		else
			minimap.map_pos.x = minimap.map_size.x - minimap.block.x / 2.0;
	}
	if (fabs(minimap.map_size.y - data->player.y) < minimap.block.y / 2.0)
	{
		if (minimap.map_pos.y < minimap.block.y / 2.0)
			minimap.map_pos.y = minimap.block.y / 2.0;
		else
			minimap.map_pos.y = minimap.map_size.y - minimap.block.y / 2.0;
	}
	return (minimap);
}

int	is_player(t_data *data, t_minimap *minimap, t_dvec map_pos)
{
	t_dvec	player_delta;

	player_delta = init_dvec(minimap->draw_size.y / 750.0,
			minimap->draw_size.y / 750.0);
	if (fabs(data->player.x - map_pos.x) < player_delta.x
			&& fabs(data->player.y - map_pos.y) < player_delta.y)
		return (1);
	return (0);
}

void	draw_map(t_data *data, t_minimap *minimap)
{
	t_ivec	draw_pos;
	t_dvec	map_pos;
	// t_dvec	map_i;

	draw_pos = init_ivec(minimap->draw_start.x, minimap->draw_start.y);
	// map_i = init_dvec(minimap->map_pos.x - 5.0, minimap->map_pos.y - 5);
	map_pos = init_dvec(minimap->map_pos.x - 5.0, minimap->map_pos.y - 5.0);
	while (draw_pos.x < minimap->draw_end.x)
	{
		draw_pos.y = minimap->draw_start.y;
		map_pos.y = 0;
		while (draw_pos.y < minimap->draw_end.y)
		{
			if (is_player(data, minimap, map_pos))
				ft_mlx_pixel_put(&data->img, draw_pos.x, draw_pos.y,
					minimap->player_color);
			else if (data->map[(int)map_pos.x][(int)map_pos.y] == '1')
				ft_mlx_pixel_put(&data->img, draw_pos.x, draw_pos.y,
					minimap->block_color);
			else
				ft_mlx_pixel_put(&data->img, draw_pos.x, draw_pos.y,
					minimap->floor_color);
			map_pos.y += minimap->step.y;
			draw_pos.y++;
		}
		map_pos.x += minimap->step.x;
		draw_pos.x++;
	}
}

/**
 * @brief Draw he minimap on screen
 *
 * This function draw the minimap on screen, it should be called at every frame
 *
 * @param	data	The cub3D global data stucture
 */
void	draw_minimap(t_data *data)
{
	// FIND minimap aiming pos on map
	data->minimap = set_minimap_val(data, data->minimap);

	// DRAW minimap accordingly
	draw_map(data, &data->minimap);

	// ADD Player on minimap
	// draw_player(data, &data->minimap);

}
