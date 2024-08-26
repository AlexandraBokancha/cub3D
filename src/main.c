/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:34:23 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/26 15:59:30 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_texture(t_data *data, char **texture_name)
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
char	**init_tab_texture(t_data *data)
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
	(void) ac;
	t_data	*data;

	data = init_cub();
	if (!data)
		return (1);
	data = init_map(data, av[1]);
	if (!data)
		return (1);
	data->floor_color = rgb_to_hex(data->colors.f_color);
    data->ceiling_color = rgb_to_hex(data->colors.c_color);
	init_player(data);
	data->texture_tab = init_tab_texture(data);
	load_texture(data, data->texture_tab);
	// HOOK EVERYTHING
	mlx_key_hook(data->window, &key_hook, data);
	mlx_hook(data->window, 2, (1L << 0), &key_hook, data);
	mlx_hook(data->window, ON_DESTROY, 0, &exit_cub, data);
	//mlx_hook(data->window, ON_MOUSEMOVE, (1L<<6), &camera_move, data); // Mouse movment detection
	mlx_loop_hook(data->mlx, &render, data);
	mlx_loop(data->mlx);
	mlx_do_sync(data->mlx);

	// EXIT
	free_cub(data);
	return (0);
}