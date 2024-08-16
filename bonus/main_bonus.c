/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:34:23 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/16 12:29:23 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* ************************************************************************** */
/*                          FOR TESTING PURPOSE ONLY                          */
/* ************************************************************************** */

char	test_map[10][10] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '1', '0', '1', '1', '0', '0', '1'},
	{'1', '0', '0', '0', 'N', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '1', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
};

char	*texture[5] = 
{
	"./assets/tile110.xpm",
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
/* ************************************************************************** */
/*                           END OF TESTING FUNCTION                          */
/* ************************************************************************** */

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

/**
 * @brief Return the map size
 *
 * This function create a new t_ivec an store the map size
 * max X and Max Y
 *
 * @param	map	The map
 * @return  A vector containing the map size 
 */
t_ivec	get_map_size(const char **map)
{
	t_ivec	map_block;
	int		x;
	int		y;

	map_block = init_ivec(0, 0);
	x = 0;
	while (map[x])
	{
		while (map[x][y])
			y++;
		if (y > map_block.y)
			map_block.y = y;
		x++;
	}
	map_block.x = x;
	return (map_block);
}

int	main()
{
	t_data	*data;

	data = init_cub();
	if (!data)
		return (1);
	// PLAYER, COLOR AND CAMERA SETUP HAVE TO BE DONE IN THE INIT AFTER PARSING
	data->map = copy_map();
	data->map_size = get_map_size((const char **)data->map);
	data->ceiling_color = 0x00645832;
	data->floor_color = 0x00474747;
	init_player(data);
	data->minimap = init_minimap(data);

	// LOAD TEXTURE
	load_texture(data, texture);

	// HOOK EVERYTHING
	// mlx_key_hook(data->window, &key_hook, data);
	mlx_hook(data->window, 2, (1L << 0), &key_hook, data);
	mlx_hook(data->window, ON_DESTROY, 0, &exit_cub, data);
	// mlx_hook(data->window, ON_MOUSEMOVE, (1L<<6), &camera_move, data); // Mouse movment detection
	mlx_loop_hook(data->mlx, &render, data);
	mlx_loop(data->mlx);
	mlx_do_sync(data->mlx);

	// EXIT
	free_cub(data);
	return (0);
}
