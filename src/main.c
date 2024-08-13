/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:34:23 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/13 20:00:42 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	test_map[10][10] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '1', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '1', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
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

int	main()
{
	t_data	*data;

	data = init_cub();
	if (!data)
		return (1);
	data->player_pos.x = 1.5;
	data->player_pos.y = 1.5;
	data->direction.x = -1;
	data->direction.y = 0;
	data->camera_plane.x = 0;
	data->camera_plane.y = 0.66;
	data->map = copy_map();
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
	free_cub(data);
	return (0);
}
