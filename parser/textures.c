/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:36:13 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/16 20:54:29 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


static  void    copy_map(int map_pos, int map_height, t_data *data)
{
    (void) (map_pos);
    (void) (data);
    (void) (map_height);
}
// maybe need to add exitcode for some specific error while parsing

int    parse_map(char **map, t_data *data)
{ 
    int start_map;
    int map_height;
    int map_pos;
    int i;

    start_map = 0;
    i = 0;
    map_height = 0;
    map_pos = 0;
    while (i < data->m_height)
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
            // add color F C + struct colors
            else if (!ft_strncmp(map[i], "1", 1))
            {
                if (!start_map)
                    start_map = 1;
                map_pos = i;
            }
            map_height++;
        }
        i++;
    }
    if (start_map)
        copy_map(map_pos, map_height, data);
    else
        return (print_error("Error: map was not found in a file", errno), 2);
    return (0);
}
