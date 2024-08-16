/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:34:23 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/16 14:14:32 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// char	**copy_map(void)
// {
// 	char **map;
// 	int		i;

// 	map = (char **)malloc(sizeof(char *) * 11);
// 	if (!map)
// 		return (print_error("malloc", errno), NULL);
// 	i = 0;
// 	while (i < 10)
// 	{
// 		map[i] = ft_strndup(test_map[i], 10);
// 		i++;
// 	}
// 	map[10] = NULL;
// 	return (map);
// }

int	main(int ac, char **av)
{
	t_data	*data;

	(void)ac;

	data = init_cub();
	if (!data)
		return (1);
	data = init_map(data, av[1]);
	free_cub(data);
	return (0);
}
