/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:44:54 by alexandra         #+#    #+#             */
/*   Updated: 2024/09/03 17:37:19 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int get_current_time() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}


t_sprite	init_sprite(t_data *data)
{
	t_sprite sprite;
	
	int	x;
	int	y;
	
	x = 0;
	while (data->map_info.map2d[x])
	{
		y = 0;
		while (data->map_info.map2d[x][y])
		{
			if (data->map_info.map2d[x][y] == 'A')
			{
				sprite.sprite_pos.x = x + 0.5;
				sprite.sprite_pos.y = y + 0.5;
				break;
			}
			y++;
		}
		if (data->map_info.map2d[x][y] == 'A')
			break;
		x++;
	}
	return (sprite);
}
