/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:44:57 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/23 20:16:17 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	ft_free_tab(char **tab, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_cub(t_data *data)
{
	if (!data)
		return ;
	// if (data->mlx)
	// {
	// 	if (data->img.img)
	// 		mlx_destroy_image(data->mlx, data->img.img);
	// 	if (data->window)
	// 		mlx_destroy_window(data->mlx, data->window);
	// 	if (data->mlx)
	// 		mlx_destroy_display(data->mlx);
	// 	free(data->mlx);
	// }
	if (data->map)
		ft_free_tab(data->map, data->m_height);
	if (data->map_info.map2d)
		ft_free_tab(data->map_info.map2d, data->map_info.map2_height);
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