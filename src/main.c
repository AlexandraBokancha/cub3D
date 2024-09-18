/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:34:23 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/18 14:43:57 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (write(2, "Error.\nProgram needs 2 arguments.\n", 34));
	data = init_cub(av[1]);
	if (!data)
		return (1);
	mlx_loop(data->mlx);
	mlx_do_sync(data->mlx);
	free_cub(data);
	return (0);
}
