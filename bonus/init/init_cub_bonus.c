/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:20:07 by dbaladro          #+#    #+#             */
/*   Updated: 2024/10/03 19:23:35 by dbaladro         ###   ########.fr       */
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
	int	i;

	i = -1;
	data->mlx = NULL;
	data->window = NULL;
	data->img.img = NULL;
	data->map = NULL;
	data->w_width = DEFAULT_WIN_WIDTH;
	data->w_height = DEFAULT_WIN_HEIGHT;
	data->texture[0].img.img = NULL;
	data->map_info.map2d = NULL;
	while (++i < TEXTURE_NBR)
		data->texture[i].path = NULL;
	data->sprites[0].img = NULL;
	data->colors.f_color = NULL;
	data->colors.c_color = NULL;
	data->map_info.map2d = NULL;
	data->colors.f_color = NULL;
	data->colors.c_color = NULL;
	data->zbuffer = NULL;
	data->mouse_visibility = 0;
	data->sprites_nb = 0;
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
 * @brief Set the necessary texture
 *
 * Set the correct path foor player and door sprite
 * Then load all texture
 *
 * @param	data	The cub3D global data structure
 * @return	1 on error, 0 on success
 */
static int	set_texture(t_data *data)
{
	data->texture[4].path = PLAYER_TEXTURE;
	data->texture[5].path = R_DOOR_TEXTURE;
	data->texture[6].path = L_DOOR_TEXTURE;
	return (load_texture(data, data->texture));
}

/**
 * @brief Set the mlx hook
 *
 * Set the the mouse to th center and hide it 
 * Then set the key_hook / mouse_hook / ON_DESTROY hook
 *
 * @param	data	The cub3D global data structure
 */
static void	set_hook(t_data *data)
{
	mlx_mouse_hide(data->mlx, data->window);
	mlx_mouse_move(data->mlx, data->window, data->w_width / 2,
		data->w_height / 2);
	mlx_hook(data->window, ON_MOUSEMOVE, (1L << 6), &camera_move, data);
	mlx_hook(data->window, 2, (1L << 0), &key_hook, data);
	mlx_hook(data->window, 4, (1L << 2), &mouse_hook, data);
	mlx_hook(data->window, ON_DESTROY, 0, &exit_cub, data);
	mlx_loop_hook(data->mlx, &render, data);
	return ;
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
	data = init_map_bonus(data, param);
	if (!data)
		return (NULL);
	init_player(data);
	data->minimap = init_minimap(data);
	data->sprites_nb = count_sprites_nb(data);
	if (data->sprites_nb)
	{
		data->sprites_arr = init_sprites(data);
		init_tab_sprites(data);
		load_sprite_image(data, data->sprites_tab);
	}
	if (set_texture(data) != 0)
		return (free_cub(data), NULL);
	set_hook(data);
	return (data);
}
