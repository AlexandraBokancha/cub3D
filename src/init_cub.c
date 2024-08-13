/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:20:07 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/13 20:08:54 by dbaladro         ###   ########.fr       */
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
 * @brief Initializes the screen for the cub3d program.
 *
 * Initializes the MLX connetion, the MLX window and the MLX image.
 * If any of these initializations fail, it frees the cub3d data structure
 * and returns NULL.
 *
 * @param data A pointer to the cub3d data structure.
 * @return A pointer to the initialized cub3d data structure, or NULL on error.
 */
static t_data	*init_screen(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (print_error("malloc", errno), free_cub(data), NULL);
	data->window = mlx_new_window(data->mlx, data->w_width, data->w_height,
			"cub3D");
	if (!data->window)
		return (print_error("malloc", errno), free_cub(data), NULL);
	data->img.img = mlx_new_image(data->mlx, data->w_width, data->w_height);
	if (!data->img.img)
		return (print_error("malloc", errno), free_cub(data), NULL);
	data->img.addr = mlx_get_data_addr(data->img.img,
		&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	return (data);
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
		return (print_error("malloc", errno), NULL);
	data->mlx = NULL;
	data->window = NULL;
	data->img.img = NULL;
	data->map = NULL;
	data->w_width = DEFAULT_WIN_WIDTH;
	data->w_height = DEFAULT_WIN_HEIGHT;
	data = init_screen(data);
	if (!data)
		return (NULL);
	return (data);
}

