/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:36:13 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/16 20:36:30 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int    check_textures(char **map, t_data *data)
{ 
    int start_map;
    int i;

    start_map = 0;
    i = 0;
    while (i < data->m_height && !start_map)
    {
        // function to skip empty line;
        
        if (!start_map)
        {
            if (!ft_strncmp(map[i], "NO ", 3))
            {
                data->textures[i].direction = ft_strdup("NO");
                data->textures[i].path = ft_strdup(map[i] + 3);
            }
            else if (!ft_strncmp(map[i], "SO ", 3))
            {
                data->textures[i].direction = ft_strdup("SO");
                data->textures[i].path = ft_strdup(map[i] + 3);
            }
            else if (!ft_strncmp(map[i], "WE ", 3))
            {
                data->textures[i].direction = ft_strdup("WE");
                data->textures[i].path = ft_strdup(map[i] + 3);
            }
            else if (!ft_strncmp(map[i], "EA ", 3))
            {
                data->textures[i].direction = ft_strdup("EA");
                data->textures[i].path = ft_strdup(map[i] + 3);
            }
            else if (!ft_strncmp(map[i], "1", 1))
            {
                if (!start_map)
                    start_map = 1;
                printf("%s%d\n", "map was found at line: ", i);
            }
        }
        i++;
    }
    return (0);
}
