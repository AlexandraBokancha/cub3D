/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:34:23 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/02 14:52:39 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_texture_bonus(t_data *data, char **texture_name)
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
	data->texture[i].img = mlx_xpm_file_to_image(data->mlx,
		PLAYER_TEXTURE, &x, &y);
	data->texture[i].addr = mlx_get_data_addr(data->texture[i].img,
		&data->texture[i].bits_per_pixel, &data->texture[i].line_length,
		&data->texture[i].endian);
	return (0);
}

/**
 * @brief Return the map size
 *
 * This function create a new t_ivec an store the map size
 * max X and Max Y
 *
 * @param	map	The map
 * @return  A vector containing the map size 
 */
t_ivec	get_map_size(char *map[])
{
	t_ivec	map_block;
	int		x;
	int		y;

	map_block = init_ivec(0, 0);
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
			y++;
		if (y > map_block.y)
			map_block.y = y;
		x++;
	}
	map_block.x = x;
	return (map_block);
}

char	**init_tab_texture_bonus(t_data *data)
{
	data->texture_tab = malloc(sizeof(char *) * 5);
	if (!data->texture_tab)
		return (NULL);
	data->texture_tab[0] = data->textures.N_path;
	data->texture_tab[1] = data->textures.S_path;
	data->texture_tab[2] = data->textures.W_path;
	data->texture_tab[3] = data->textures.E_path;
	data->texture_tab[4] = NULL;
	return (data->texture_tab);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (1);
	data = init_cub();
	if (!data)
		return (1);
	data = init_map_bonus(data, av[1]);
	if (!data)
		return (1);
	data->map_size = get_map_size(data->map);
	data->ceiling_color = rgb_to_hex(data->colors.c_color);
	data->floor_color = rgb_to_hex(data->colors.f_color);
	init_player(data);
	data->minimap = init_minimap(data);
	data->texture_tab = init_tab_texture_bonus(data);
	load_texture_bonus(data, data->texture_tab);
	//init_sprite(data);
	mlx_key_hook(data->window, &key_hook, data);
	mlx_hook(data->window, 2, (1L << 0), &key_hook, data);
	mlx_hook(data->window, ON_DESTROY, 0, &exit_cub, data);
	// mlx_hook(data->window, ON_MOUSEMOVE, (1L<<6), &camera_move, data); // Mouse movment detection
	mlx_loop_hook(data->mlx, &render, data);
	mlx_loop(data->mlx);
	mlx_do_sync(data->mlx);
	free_cub(data);
	return (0);
}
