/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:44:57 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/18 16:43:42 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Free a tab of height line
 *
 * This function free tab when an error happened in the middle of tab allocation
 *
 * @param	tab		The char tab
 * @param	height	The tab last line to free
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

void	free_map_content(t_data *data)
{
	if (data->map)
		ft_free_tab(data->map, data->m_height);
	if (data->map_info.map2d)
		ft_free_tab(data->map_info.map2d, data->map_info.map2_height);
}

/**
 * @brief free_the cub3D data structure
 *
 * This function properly free the cub3D data program
 *
 * @param	data	The cub3D data structure
 */
void	free_cub(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->mlx)
	{
		i = 0;
		while (i < 4)
		{
			if (data->texture[0].img.img != NULL)
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
