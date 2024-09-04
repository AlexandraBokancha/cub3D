/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:44:54 by alexandra         #+#    #+#             */
/*   Updated: 2024/09/04 20:14:41 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int get_current_time() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void    load_sprite_image(t_data *data)
{
    int x;
    int y;
	int i;

	data->sprites[0].img = mlx_xpm_file_to_image(data->mlx, "sprites/coin_1.xpm", &x, &y);
	data->sprites[1].img = mlx_xpm_file_to_image(data->mlx, "sprites/coin_2.xpm", &x, &y);
	data->sprites[2].img = mlx_xpm_file_to_image(data->mlx, "sprites/coin_3.xpm", &x, &y);
	data->sprites[3].img = mlx_xpm_file_to_image(data->mlx, "sprites/coin_4.xpm", &x, &y);
	data->sprites[4].img = mlx_xpm_file_to_image(data->mlx, "sprites/coin_5.xpm", &x, &y);
	data->sprites[5].img = mlx_xpm_file_to_image(data->mlx, "sprites/coin_6.xpm", &x, &y);
	data->sprites[6].img = mlx_xpm_file_to_image(data->mlx, "sprites/coin_7.xpm", &x, &y);
	data->sprites[7].img = mlx_xpm_file_to_image(data->mlx, "sprites/coin_8.xpm", &x, &y);
	i = 0;
	while (i < 8)
	{
		data->sprites[i].addr = mlx_get_data_addr(data->sprites[i].img, &data->sprites[i].bits_per_pixel, \
			&data->sprites[i].line_length, &data->sprites[i].endian);
		i++;
	}
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
	sprite.current_slice = 0;
	sprite.frame_counter = 0;
	return (sprite);
}
