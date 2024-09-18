/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:20:07 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/18 13:51:47 by dbaladro         ###   ########.fr       */
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
	data->texture[0].img = NULL;
	data->map_info.map2d = NULL;
	data->textures.S_path = NULL;
	data->textures.N_path = NULL;
	data->textures.E_path = NULL;
	data->textures.W_path = NULL;
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
 * @brief Load the texture for cub3D
 *
 * This function loads the textures in the cubd3D program
 * IT DO NOT CHECK ERRORS right now
 *
 * @param	data			The cub3D global data structure
 * @param	texture_name	The array_with all textures path
 * @return	0 if no errors happened
 */
static int	load_texture(t_data *data, char **texture_name)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	while (i < 4)
	{
		data->texture[i].img = mlx_xpm_file_to_image(data->mlx,
				texture_name[i], &x, &y);
		data->texture[i].addr = mlx_get_data_addr(data->texture[i].img,
				&data->texture[i].bits_per_pixel, &data->texture[i].line_length,
				&data->texture[i].endian);
		i++;
	}
	return (0);
}

/**
 * @brief Init the data->texture_tab with all texture path
 *
 * 
 * @param	The cub3D global data structure
 */
static void	init_tab_texture(t_data *data)
{
	data->texture_tab[0] = data->textures.N_path;
	data->texture_tab[1] = data->textures.S_path;
	data->texture_tab[2] = data->textures.W_path;
	data->texture_tab[3] = data->textures.E_path;
	data->texture_tab[4] = NULL;
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
	init_tab_texture(data);
	load_texture(data, data->texture_tab);
	mlx_key_hook(data->window, &key_hook, data);
	mlx_hook(data->window, 2, (1L << 0), &key_hook, data);
	mlx_hook(data->window, ON_DESTROY, 0, &exit_cub, data);
	mlx_loop_hook(data->mlx, &render, data);
	return (data);
}
