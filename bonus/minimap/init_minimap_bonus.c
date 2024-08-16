/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:27:47 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/16 12:32:07 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

	mmap.draw_size = init_ivec(data->w_width / 8, data->w_height / 8);
	mmap.map_screen_pos = init_ivec((mmap.draw_size.x / 2.0) * 1.05,
			(mmap.draw_size.y / 2.0) * 1.1);
	mmap.draw_start = init_ivec(mmap.map_screen_pos.x - mmap.draw_size.x / 2,
			mmap.map_screen_pos.y - mmap.draw_size.y / 2);
	mmap.draw_end = init_ivec(mmap.map_screen_pos.x + mmap.draw_size.x / 2,
			mmap.map_screen_pos.y + mmap.draw_size.y / 2);
	mmap.block = init_ivec(data->map_size.x, data->map_size.y);
	if (mmap.block.x > data->w_width / 100)
		mmap.block.x = data->w_width / 100;
	if (mmap.block.y > data->w_height / 100)
		mmap.block.y = data->w_height / 100;
	mmap.step = (double)mmap.block.x / mmap.draw_size.x;
	if ((double)mmap.block.y / mmap.draw_size.y)
		mmap.step = (double)mmap.block.y / mmap.draw_size.y;
	mmap.block_color = MINIMAP_BLOCK_COLOR;
	mmap.floor_color = MINIMAP_FLOOR_COLOR;
	mmap.player_color = MINIMAP_PLAYER_COLOR;
	mmap.outbound_color = MINIMAP_OUTBOUND_COLOR;
	return (mmap);
}
