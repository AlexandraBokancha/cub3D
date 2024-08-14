/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:34:23 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/15 00:54:52 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	test_map[10][10] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '1', '0', '1', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '1', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
};

char	*texture[5] = 
{
	"./assets/tile065.xpm",
	"./assets/tile068.xpm",
	"./assets/tile073.xpm",
	"./assets/tile085.xpm",
	NULL
};

char	**copy_map(void)
{
	char **map;
	int		i;

	map = (char **)malloc(sizeof(char *) * 11);
	if (!map)
		return (print_error("malloc", errno), NULL);
	i = 0;
	while (i < 10)
	{
		map[i] = ft_strndup(test_map[i], 10);
		i++;
	}
	map[10] = NULL;
	return (map);
}

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

int	main()
{
	t_data	*data;

	data = init_cub();
	if (!data)
		return (1);
	// PLAYER AND CAMERA SETUP HAVE TO BE DONE IN THE INIT AFTER PARSING
	data->ceiling_color = 0x00645832;
	data->floor_color = 0x00474747;
	data->player.x = 1.9;
	data->player.y = 1.9;
	data->direction.x = 0.5;
	data->direction.y = 0.5;
	data->camera_plane.x = 0.66 * data->direction.y;
	data->camera_plane.y = 0.66 * (-data->direction.x);
	data->map = copy_map();

	// LOAD TEXTURE
	load_texture(data, texture);
	// int *a = (int *)malloc(sizeof(int));
	// int *b = (int *)malloc(sizeof(int));
	// data->texture[0].img = mlx_new_image(data->mlx, 64, 64);
	// data->texture[0].img = mlx_xpm_file_to_image(data->mlx, "./assets/tile065.xpm", a, b);

	// HOOK EVERYTHING
	// mlx_key_hook(data->window, &key_hook, data);
	mlx_hook(data->window, 2, (1L << 0), &key_hook, data);
	mlx_hook(data->window, ON_DESTROY, 0, &exit_cub, data);
	// mlx_hook(data->window, ON_MOUSEMOVE, (1L<<6), &camera_move, data); // Mouse movment detection
	mlx_loop_hook(data->mlx, &render, data);
	mlx_loop(data->mlx);

	// EXIT
	free_cub(data);
	return (0);
}
