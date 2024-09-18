/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:53:38 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/18 21:07:12 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief This function load the necessary texture in the game
 *
 * Load the texture from the texture_name tab into the game
 *
 * @param	data			The cub3D global data structure
 * @param	texture_name	The texure name tab
 * @return  0 on sucess, 1 on error
 */
int	load_texture(t_data *data, t_texture *texture)
{
	int	i;

	i = 0;
	while (i < TEXTURE_NBR && texture[i].path)
	{
		data->texture[i].img.img = mlx_xpm_file_to_image(data->mlx,
				texture[i].path, &data->texture[i].size.x,
				&data->texture[i].size.y);
		if (!data->texture[i].img.img)
			return (print_error("mlx_xpm_file_to_image", errno), free_cub(data),
				1);
		data->texture[i].img.addr = mlx_get_data_addr(data->texture[i].img.img,
				&data->texture[i].img.bits_per_pixel,
				&data->texture[i].img.line_length,
				&data->texture[i].img.endian);
		if (!data->texture[i].img.addr)
			return (print_error("mlx_get_data_addr", errno), free_cub(data),
				1);
		i++;
	}
	return (0);
}
