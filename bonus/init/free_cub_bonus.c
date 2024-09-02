/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:44:57 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/18 15:12:09 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Free the cub3d data structure and its associated resources.
 *
 * This function is responsible for freeing the resources associated with
 * the cub3d data structure.
 * It frees the MLX instance, the window instance, the image, and the map.
 * If any of these resources are NULL, they are not freed.
 *
 * @param data A pointer to the cub3d data structure.
 */
void	free_cub(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->mlx)
	{
		i = 0;
		while (data->texture[i].img.img != NULL && i < 5)
		{
			mlx_destroy_image(data->mlx, data->texture[i].img.img);
			i++;
		}
		if (data->img.img)
			mlx_destroy_image(data->mlx, data->img.img);
		if (data->window)
			mlx_destroy_window(data->mlx, data->window);
		if (data->mlx)
			mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->map)
		ft_free_char_tab(&data->map);
	free(data);
	return ;
}

/**
 * @brief Free cub3D ressources and exit
 *
 * Free the cub3d ressources and exit with status code 0
 *
 * @param	data The cub3D data structure
 * @return	0
 */
int	exit_cub(t_data *data)
{
	free_cub(data);
	exit(0);
	return (0);
}
