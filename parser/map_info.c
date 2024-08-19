/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:16:18 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/19 18:28:27 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

static  void    copy_map(int map_pos, t_data *data)
{
    int i;

    i = 0;
    data->map_info.map2d = (char **)malloc(sizeof(char *) * (data->map_info.map2_height + 1));
    if (!data->map_info.map2d)
        return ((void)print_error("Error. Malloc.", errno));
    while (i < data->map_info.map2_height)
    {   
        data->map_info.map2d[i] = ft_strdup(data->map[map_pos]);
        map_pos++;
        i++;
    }
    data->map_info.map2d[i] = NULL;
}

static  int    search_map_info(char **map, t_data *data)
{ 
    int i;

    i = 0;
    while (i < data->m_height)
    {
        if (!data->map_info.start_map)
        {
            process_info_lines(data, map[i], i);
            if (!ft_strncmp(map[i], "1", 1) || !ft_strncmp(map[i], "0", 1)) 
            {
                if (!data->map_info.start_map)
                    data->map_info.start_map = 1;
                data->map_info.map_pos = i;
            }
        }
        if (data->map_info.start_map)
            data->map_info.map2_height++;
        i++;
    }
    if (data->map_info.start_map)
        copy_map(data->map_info.map_pos, data);
    else
        return (print_error("Error: map was not found in a file", errno), 2);
    return (0);
}

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
    {
        free(buf);
        return (print_error("Error. File management.", errno), NULL);
    }
    line = get_next_line(fd);
    while (line)
    {
        buf[i++] = line;
        line = get_next_line(fd);
    }
    close (fd);
    return (buf);
}

t_data *init_map(t_data *data, char  *file_name)
{
    // check extension of map
    data->m_height = map_h(file_name);
    if (!data->m_height)
        exit_cub(data);
    data->map = open_map(file_name, data->m_height);
    if (!data->map)
        exit_cub(data);
    if (search_map_info(data->map, data))
        exit_cub(data);
    if (parsing(data))
        exit_cub(data);
    return (data);
}
