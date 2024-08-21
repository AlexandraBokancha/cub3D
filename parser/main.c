/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:34:23 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/21 16:16:54 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_all_info(t_data *data)
{
	printf("%s\n", "**** my map ***");
	printf("\n");
	char **ptr = data->map_info.map2d;
    while (*ptr != NULL)
    {
        printf("%s", *ptr);
        ptr++;
    }
	printf("\n");
	printf("\n");
	printf("%s\n", "**** my info ****");
	printf("\n");
	printf("\n");
	printf("my F color : %s\n", data->colors.f_color);
	printf("my C color : %s\n", data->colors.c_color);

}

int	main(int ac, char **av)
{
	t_data	*data;

	(void)ac;

	data = init_cub();
	if (!data)
		return (1);
	data = init_map(data, av[1]);
	if (!data)
		exit_cub(data);
	free_cub(data);
	return (0);
}
