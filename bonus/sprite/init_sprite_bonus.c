/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:44:54 by alexandra         #+#    #+#             */
/*   Updated: 2024/09/09 21:52:25 by alexandra        ###   ########.fr       */
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
		data->sprites[i].addr = mlx_get_data_addr(data->sprites[i].img, \
			&data->sprites[i].bits_per_pixel, \
			&data->sprites[i].line_length, &data->sprites[i].endian);
		i++;
	}
}

void	init_tab_sprites(t_data *data)
{
	data->sprites_tab[0] = "sprites/tile000.xpm";
	data->sprites_tab[1] = "sprites/tile001.xpm";
	data->sprites_tab[2] = "sprites/tile002.xpm";
	data->sprites_tab[3] = "sprites/tile003.xpm";
	data->sprites_tab[4] = "sprites/tile004.xpm";
	data->sprites_tab[5] = "sprites/tile005.xpm";
	data->sprites_tab[6] = "sprites/tile006.xpm";
	data->sprites_tab[7] = "sprites/tile007.xpm";
	data->sprites_tab[8] = NULL;
}

int	count_sprites_nb(t_data *data)
{
	int	x;
	int	y;
	int count;
	
	x = 0;
	count = 0;
	while (data->map_info.map2d[x])
	{
		y = 0;
		while (data->map_info.map2d[x][y])
		{
			if (data->map_info.map2d[x][y] == 'A')
				count++;
			y++;
		}
		x++;
	}
	return (count);
}

void	init_data_sprites(t_sprite *sprites, int i, int x, int y)
{
	sprites[i].sprite_pos.x = x + 0.5;
	sprites[i].sprite_pos.y = y + 0.5;
	sprites[i].current_slice = 0;
	sprites[i].frame_counter = 0;
	sprites[i].is_active = 1;
}

t_sprite	*init_sprites(t_data *data)
{
	t_sprite *sprites;
	int x;
	int y;
	int i;
	
	x = 0;
	i = 0;
	sprites = (t_sprite *)malloc(sizeof(t_sprite) * (data->sprites_nb));
	if (!sprites)
		return (write(2, "Error. Malloc\n", 15), NULL);
	while (data->map_info.map2d[x])
	{
		y = 0;
		while (data->map_info.map2d[x][y] && i < data->sprites_nb)
		{
			if (data->map_info.map2d[x][y] == 'A')
			{
				init_data_sprites(sprites, i, x, y);
				i++;
			}
			y++;
		}
		x++;
	}
	return (sprites);
}
