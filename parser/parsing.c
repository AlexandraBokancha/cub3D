/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:15:51 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/19 20:28:20 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

int parsing_textures(char *path)
{
    int fd;
    
    //printf("Before strip: [%s]\n", path);
    strip_newline(path);
    //printf("After strip: [%s]\n", path);

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (print_error("Error: path is not valid", errno), 1);
    close(fd);
    return (0);
}

int parsing_colors(char *color)
{
    int value;
    int start;
    int count;
    int i;

    start = 0;
    i = 0;
    count = 0;
    while (color[i])
    {
        if (color[i] == ',' || color[i + 1] == '\0')
        {
            if (color[i + 1] == '\0')
                i++;
            value = ft_atoi(&color[start]);
            if (value < 0 || value > 255)
                return (write(2, "Error. Invalid RGB.\n", 21), 0);
            count++;
            start = i + 1;
        }
        i++;
    }
    if (count > 3)
        return (write(2, "Error. Invalid RGB.\n", 21), 0);
    return (1);    
}

int parsing(t_data *data)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (parsing_textures(data->textures[i].path))
        {
            break;
            return (1);
        }
        i++;
    }
    if (!parsing_colors(data->colors.f_color))
        return (1);
    //parsing_map();
    return (0);
}