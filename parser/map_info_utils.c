/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:36:13 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/18 17:19:52 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void    process_info_lines(t_data *data, char *line, int i)
{
    if (!ft_strncmp(line, "NO ", 3))
    {
        data->textures[i].direction = ft_strdup("NO");
        data->textures[i].path = ft_strdup(line + 3);
    }
    else if (!ft_strncmp(line, "SO ", 3))
    {
        data->textures[i].direction = ft_strdup("SO");
        data->textures[i].path = ft_strdup(line + 3);
    }
    else if (!ft_strncmp(line, "WE ", 3))
    {
        data->textures[i].direction = ft_strdup("WE");
        data->textures[i].path = ft_strdup(line + 3);
    }
    else if (!ft_strncmp(line, "EA ", 3))
    {
        data->textures[i].direction = ft_strdup("EA");
        data->textures[i].path = ft_strdup(line + 3);
    }
    else if (!ft_strncmp(line, "F", 1))
        data->colors.f_color = ft_strdup(line + 1);
    else if (!ft_strncmp(line, "C", 1))
        data->colors.c_color = ft_strdup(line + 1);
}

int map_h(char *file_name)
{
    char    *line;
    int     height;
    int     fd;

    line = NULL;
    height = 0;
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return (print_error("Error. File management.", errno), 0);
    line = get_next_line(fd);
    if (line == NULL)
        return (print_error("Error. Empty map.", 5), 0);
    while (line)
    {
        height++;
        free(line);
        line = get_next_line(fd);
    }
    close (fd);
    return (height);
}
