/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:44:54 by alexandra         #+#    #+#             */
/*   Updated: 2024/09/01 21:00:46 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_sprite(t_data *data)
{
	int x = 4;
	int y = 3;
	data->sprite.img = mlx_xpm_file_to_image(data->mlx, "spirit/637f63c86c424d2aee601e54179c89abdJjS7DsokeOlzfn4-0.xpm", &x, &y);
	data->sprite.addr = mlx_get_data_addr(data->sprite.img, &data->sprite.bits_per_pixel, &data->sprite.line_length, 
		&data->sprite.endian);
}
