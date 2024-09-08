/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:44:57 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/07 20:42:43 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	free_map_content(t_data *data)
{
	if (data->map)
		ft_free_tab(data->map, data->m_height);
	if (data->map_info.map2d)
		ft_free_tab(data->map_info.map2d, data->map_info.map2_height);
	if (data->texture_tab)
		free(data->texture_tab);
}

void	free_sprite(t_data *data)
{
	int i;

	i = 0;
	if (!data->sprites_nb)
		return ;
	while (i < 8)
	{
		if (data->sprites[0].img != NULL)
			mlx_destroy_image(data->mlx, data->sprites[i].img);
		i++;
	}
}

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
		free_sprite(data);
		while (i < 5)
		{
			if (data->texture[0].img != NULL)
				mlx_destroy_image(data->mlx, data->texture[i].img);
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
	free_map_content(data);
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
