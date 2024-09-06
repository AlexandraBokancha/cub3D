/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:44:54 by alexandra         #+#    #+#             */
/*   Updated: 2024/09/05 23:23:23 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    load_sprite_image(t_data *data, char **sprites_tab)
{
    int x;
    int y;
	int i;
	
	i = 0;
	while (i < 8)
	{
		data->sprites[i].img = mlx_xpm_file_to_image(data->mlx, sprites_tab[i], &x, &y);
		data->sprites[i].addr = mlx_get_data_addr(data->sprites[i].img, &data->sprites[i].bits_per_pixel, \
			&data->sprites[i].line_length, &data->sprites[i].endian);
		i++;
	}
}

char	**init_tab_sprites(t_data *data)
{
	data->sprites_tab = malloc(sizeof(char *) * 9);
	if (!data->sprites_tab)
		return (NULL);
	data->sprites_tab[0] = "sprites/tile000.xpm";
	data->sprites_tab[1] = "sprites/tile001.xpm";
	data->sprites_tab[2] = "sprites/tile002.xpm";
	data->sprites_tab[3] = "sprites/tile003.xpm";
	data->sprites_tab[4] = "sprites/tile004.xpm";
	data->sprites_tab[5] = "sprites/tile005.xpm";
	data->sprites_tab[6] = "sprites/tile006.xpm";
	data->sprites_tab[7] = "sprites/tile007.xpm";
	data->sprites_tab[8] = NULL;
	return (data->sprites_tab);
}

t_sprite	init_sprite(t_data *data)
{
	t_sprite sprite;
	
	int	x;
	int	y;
	
	x = 0;
	sprite.count = 0;
	while (data->map_info.map2d[x])
	{
		y = 0;
		while (data->map_info.map2d[x][y])
		{
			if (data->map_info.map2d[x][y] == 'A')
			{
				sprite.sprite_pos.x = x + 0.5;
				sprite.sprite_pos.y = y + 0.5;
				sprite.count++;
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
