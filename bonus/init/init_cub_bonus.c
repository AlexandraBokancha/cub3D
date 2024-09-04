/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:20:07 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/04 20:06:52 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


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
 * @brief Set the player position, direction and camera plane
 *
 * This function set the Player position, camera direction and camera_plane
 * according to the map information
 *
 * @param	data		The cub3D global data structure
 * @param	x			X position on the map
 * @param	y			Y position on the map
 * @param	orientation	Player orientation
 */
static void	set_player(t_data *data, int x, int y, char orientation)
{
	data->player.x = (double)x + 0.5;
	data->player.y = (double)y + 0.5;
	if (orientation == 'N')
	{
		data->direction.x = 0.0;
		data->direction.y = 1.0;
	}
	if (orientation == 'S')
	{
		data->direction.x = 0.0;
		data->direction.y = -1.0;
	}
	if (orientation == 'E')
	{
		data->direction.x = 1.0;
		data->direction.y = 0.0;
	}
	if (orientation == 'W')
	{
		data->direction.x = -1.0;
		data->direction.y = 0.0;
	}
	data->camera_plane.x = 0.66 * data->direction.y;
	data->camera_plane.y = 0.66 * (-data->direction.x);
}

/**
 * @brief Init the player based on the map information
 *
 * This function first find where the player is on the map
 * when it is found it will set all necessary data in the set_player function
 *
 * @param	data	The cub3D global data structure
 */
void	init_player(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (data->map_info.map2d[x])
	{
		y = 0;
		while (data->map_info.map2d[x][y])
		{
			if (data->map_info.map2d[x][y] == 'N' || data->map_info.map2d[x][y] == 'S'
					|| data->map_info.map2d[x][y] == 'E' || data->map_info.map2d[x][y] == 'W')
			{
				set_player(data, x, y, data->map_info.map2d[x][y]);
				return ;
			}
			y++;
		}
		x++;
	}
	return ;
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
	data->texture_tab = NULL;
	data->w_width = DEFAULT_WIN_WIDTH;
	data->w_height = DEFAULT_WIN_HEIGHT;
	data->texture[0].img = NULL;
	data->sprites[0].img = NULL;
	data->map_info.map2d = NULL;
	data->textures.S_path = NULL;
	data->textures.N_path = NULL;
	data->textures.E_path = NULL;
	data->textures.W_path = NULL;
	data->colors.f_color = NULL;
	data->colors.c_color = NULL;
	data->zbuffer = NULL;
	data = init_screen(data);
	if (!data)
		return (NULL);
	return (data);
}
