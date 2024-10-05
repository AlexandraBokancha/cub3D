/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:20:07 by dbaladro          #+#    #+#             */
/*   Updated: 2024/10/05 19:22:16 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Set all value of the cube3D data structure to default calues
 *
 * This function set all data value to NULL/0.
 * It is needed for error && memory managment
 * And for 42 Norm
 *
 * @param	data	The cub3D global data structure
 */
static void	set_default_value(t_data *data)
{
	data->mlx = NULL;
	data->window = NULL;
	data->img.img = NULL;
	data->map = NULL;
	data->w_width = DEFAULT_WIN_WIDTH;
	data->w_height = DEFAULT_WIN_HEIGHT;
	data->texture[0].img.img = NULL;
	data->map_info.map2d = NULL;
	data->texture[0].path = NULL;
	data->texture[1].path = NULL;
	data->texture[2].path = NULL;
	data->texture[3].path = NULL;
	data->texture[4].path = NULL;
	data->colors.f_color = NULL;
	data->colors.c_color = NULL;
	return ;
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
			&data->img.bits_per_pixel, &data->img.line_length,
			&data->img.endian);
	return (data);
}

/**
 * @brief Initializes the cub3d data structure.
 *
 * This function allocates and initializes a new cub3d data structure.
 * It sets the MLX windows and all the program data
 *
 * @param	param	The cub3D argument (av[1])
 * @return A pointer to the initialized cub3d data structure, or NULL on error
 */
t_data	*init_cub(char *param)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(struct s_data));
	if (!data)
		return (print_error("malloc", errno), NULL);
	if (check_cub_path(param))
		return (free(data), NULL);
	set_default_value(data);
	data = init_screen(data);
	if (!data)
		return (NULL);
	data = init_map(data, param);
	if (!data)
		return (NULL);
	data->floor_color = rgb_to_hex(data->colors.f_color);
	data->ceiling_color = rgb_to_hex(data->colors.c_color);
	init_player(data);
	load_texture(data, data->texture);
	mlx_key_hook(data->window, &key_hook, data);
	mlx_hook(data->window, 2, (1L << 0), &key_hook, data);
	mlx_hook(data->window, ON_DESTROY, 0, &exit_cub, data);
	mlx_loop_hook(data->mlx, &render, data);
	return (data);
}
