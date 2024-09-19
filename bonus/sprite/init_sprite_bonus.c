/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:44:54 by alexandra         #+#    #+#             */
/*   Updated: 2024/09/19 20:14:59 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Loads sprite images from XPM files into memory.
 *
 * This function loads sprite images from the file paths specified
 * in the `sprites_tab` array.
 * It uses the MLX function `mlx_xpm_file_to_image` to load each image
 * and stores the image's address and additional data required for rendering.
 *
 */
void	load_sprite_image(t_data *data, char **sprites_tab)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	while (i < 8)
	{
		data->sprites[i].img = mlx_xpm_file_to_image(data->mlx, \
			sprites_tab[i], &x, &y);
		data->sprites[i].addr = mlx_get_data_addr(data->sprites[i].img, \
			&data->sprites[i].bits_per_pixel, \
			&data->sprites[i].line_length, &data->sprites[i].endian);
		i++;
	}
}

/**
 * @brief Initializes the array of sprite file paths.
 *
 * This function sets up the paths to the sprite
 * textures in the `sprites_tab` array.
 *
 */
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
}

/**
 * @brief Counts the number of sprites on the map.
 *
 * This function scans the 2D map for sprite indicators ('A') and counts
 * how many sprites are present on the map.
 * This count is later used to allocate memory for sprite structures.
 *
 */
int	count_sprites_nb(t_data *data)
{
	int	x;
	int	y;
	int	count;

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

/**
 * @brief Initializes individual sprite data.
 *
 * This function sets the initial position, animation frame,
 * and other properties for a specific sprite based
 * on its position on the map.
 * 
 * Sacree norminette 
 *
 */
void	init_data_sprites(t_sprite *sprites, int i, int x, int y)
{
	sprites[i].sprite_pos.x = x + 0.5;
	sprites[i].sprite_pos.y = y + 0.5;
	sprites[i].current_slice = 0;
	sprites[i].frame_counter = 0;
	sprites[i].is_active = 1;
}

/**
 * @brief Allocates and initializes all sprites on the map.
 * @return A pointer to the initialized sprite array,
 * or NULL if memory allocation fails.
 */
t_sprite	*init_sprites(t_data *data)
{
	t_sprite	*sprites;
	int			x;
	int			y;
	int			i;

	x = 0;
	i = 0;
	sprites = (t_sprite *)malloc(sizeof(struct s_sprite) * (data->sprites_nb));
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
