/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 22:18:04 by alexandra         #+#    #+#             */
/*   Updated: 2024/10/03 17:41:06 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Calculates the distance between each sprite and the player.
 *
 * This function computes the Euclidean distance between each sprite and
 * the player's position on the map.
 * If a sprite is too close to the player (less than 0.8 units away),
 * it is marked as inactive.
 *
 * J'ai choisi 0.8 mais c'etait un peu aleatoire, j'ai suivi mon feeling
 */
void	calculate_sprite_distances(t_data *data)
{
	t_dvec	diff;
	int		i;

	i = 0;
	while (i < data ->sprites_nb)
	{
		if (!data->sprites_arr[i].is_active)
		{
			i++;
			continue ;
		}
		diff.x = data->sprites_arr[i].sprite_pos.x + 0.5 - data->player.x;
		diff.y = data->sprites_arr[i].sprite_pos.y + 0.5 - data->player.y;
		data->sprites_arr[i].distance = sqrt(diff.x * diff.x + diff.y * diff.y);
		if (data->sprites_arr[i].distance < 0.8)
			data->sprites_arr[i].is_active = 0;
		i++;
	}
}

/**
 * @brief Sorts the sprites based on their distance from the player.
 */
void	sort_sprites(t_data *data)
{
	t_sprite	temp;
	int			i;
	int			j;
	int			max;

	i = 0;
	while (i < data->sprites_nb)
	{
		max = i;
		j = i + 1;
		while (j < data->sprites_nb)
		{
			if (data->sprites_arr[j].distance > data->sprites_arr[max].distance)
				max = j;
			j++;
		}
		if (max != i)
		{
			temp = data->sprites_arr[i];
			data->sprites_arr[i] = data->sprites_arr[max];
			data->sprites_arr[max] = temp;
		}
		i++;
	}
}

/**
 * @brief Updates the sprite's animation frame.
 *
 * This function increments the frame counter for each sprite.
 * When the frame counter reaches a certain
 * threshold (8 frames), the current slice of the sprite
 * (used for animation) is updated.
 * 
 * Je pars du principe qu'on a 8 images de notre
 * sprite (a changer pour d'autres sprite sheet)
 * 
 */
void	update_sprite_frame(t_data *data, int i)
{
	data->sprites_arr[i].frame_counter++;
	if (data->sprites_arr[i].frame_counter >= 8)
	{
		data->sprites_arr[i].frame_counter = 0;
		data->sprites_arr[i].current_slice = \
			(data->sprites_arr[i].current_slice + 1) % 8;
	}
}

/**
 * @brief Retrieves the color of a pixel from an XPM sprite texture.
 *
 * This function fetches the color value of 
 * a specific pixel in the XPM texture for a sprite.
 * The pixel is located by calculating the offset 
 * in the texture data based on its X and Y coordinates.
 *
 * @return The color value of the pixel at (x, y).
 */
int	get_pixel_color_from_xpm(int x, int y, t_data *data, int current_slice)
{
	int	pixel_offset;
	int	color;

	pixel_offset = (y * data->sprites[current_slice].line_length) + (x * \
		(data->sprites[current_slice].bits_per_pixel / 8));
	color = *(int *)(data->sprites[current_slice].addr + pixel_offset);
	return (color);
}

/**
 * @brief Processes the Y axis of the sprite and draws its pixels.
 *
 * This function iterates through the Y-axis pixels of the sprite,
 * calculating the texture's Y coordinate 
 * and fetching the appropriate pixel color. 
 * If the pixel is not transparent, it is drawn to the screen.
 *
 * Sacree norminette
 */
void	process_sprite_y(t_data *data, int i, int stripe)
{
	int	y;
	int	d;

	y = data->sprites_arr[i].draw_start.y;
	while (y < data->sprites_arr[i].draw_end.y)
	{
		// d = (y - data->sprites_arr[i].draw_start.y) * 256 \
		// 	- data->w_height * 128 + \
		// 	data->sprites_arr[i].sprite_size.y * 128;
		d = (y * 256) - (data->w_height * 128) + (data->sprites_arr[i].sprite_size.y * 128);
		data->tex.y = ((d * 32) / data->sprites_arr[i].sprite_size.y) / 256;
		if (data->tex.x >= 0 && data->tex.x < 32 && \
			data->tex.y >= 0 && data->tex.y < 32)
		{
			data->sprites_arr[i].color = get_pixel_color_from_xpm(data->tex.x, \
				data->tex.y, data, data->sprites_arr[i].current_slice);
			if ((data->sprites_arr[i].color & 0x00FFFFFF) != 0x000000)
				ft_mlx_pixel_put(&data->img, stripe, y, \
					data->sprites_arr[i].color);
		}
		y++;
	}
}
