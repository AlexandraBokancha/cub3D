/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:15:51 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/18 18:27:27 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

void strip_newline(char *str)
{
    char *pos;

    pos = ft_strchr(str, '\n');
    if (pos != NULL)
        *pos = '\0';
}

int parsing_textures(char *path)
{
    int fd;
    
    strip_newline(path);
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (print_error("Error: path is not valid", errno), 1);
    close(fd);
    return (0);
}

int parsing(t_data *data)
{
    int i;

    i = 0;
    while (i < 4)
    {
        parsing_textures(data->textures[i].path);
        i++;
    }
    //parsing_colors();
    //parsing_map();
    return (0);
}