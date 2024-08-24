/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:20:07 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/24 18:09:03 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Make a vector from X and Y value
 *
 * @param x X value
 * @param y Y value
 * @return The new vector (x,y)
 */

t_vec	init_vec(double x, double y)
{
	t_vec	res;

	res.x = x;
	res.y = y;
	return (res);
}

/**
 * @brief Initializes the cub3d data structure.
 *
 * This function allocates and initializes a new cub3d data structure.
 * It sets the MLX instance, the MLX window, the image, and the map to NULL,
 * then it sets the window dimensions to the default values.
 * It then calls init_screen to initialize the screen.
 * If any of these operations fail, it returns NULL.
 *
 * @return A pointer to the initialized cub3d data structure, or NULL on error
 */

t_data	*init_cub(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(struct s_data));
	if (!data)
		return (write(2, "Error. Malloc\n", 15), NULL);
	data->mlx = NULL;
	data->window = NULL;
	data->img.img = NULL;
	data->map = NULL;
	data->w_width = DEFAULT_WIN_WIDTH;
	data->w_height = DEFAULT_WIN_HEIGHT;
	data->map_info.map2d = NULL;
	data->map_info.map2_height = 0; 
	data->map_info.start_map = 0;
	data->map_info.map_pos = 0;
	data->textures.S_path = NULL;
	data->textures.N_path = NULL;
	data->textures.E_path = NULL;
	data->textures.W_path = NULL;
	data->colors.f_color = NULL;
	data->colors.c_color = NULL;
	data->colors.start = 0;
	// data = init_screen(data);
	// if (!data)
	// 	return (NULL);
	return (data);
}
