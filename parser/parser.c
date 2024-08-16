/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:16:18 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/16 20:14:16 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

char    **open_map(char *file_name, int lines)
{
    char **buf;
    char *line;
    int fd;
    int i;

    i = 0;
    line = NULL;
    buf = malloc(sizeof(char *) * (lines + 1));
    if (!buf)
        return (print_error("Error. Malloc.", errno), NULL);
    buf[lines] = NULL;
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return (print_error("Error. File management.", errno), NULL);
    line = get_next_line(fd);
    while (line)
    {
        buf[i++] = line;
        line = get_next_line(fd);
    }
    close (fd);
    return (buf);
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

t_data *init_map(t_data *data, char  *file_name)
{
    t_texture *textures;

    textures = malloc(sizeof(struct s_texture));
    if (!textures)
        return (print_error("Error. Malloc.", errno), NULL);
    data->m_height = map_h(file_name);
    if (!data->m_height)
        return (free(data), NULL);
    data->map = open_map(file_name, data->m_height);
    check_textures(data->map, data);
    // char **ptr = data->map;
    // while (*ptr != NULL)
    // {
    //     printf("%s", *ptr);
    //     ptr++;
    // }
    //data->m_width = map_w(data->map);
    return (data);
}