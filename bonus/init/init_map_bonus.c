/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:06:49 by alexandra         #+#    #+#             */
/*   Updated: 2024/09/02 14:50:24 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

static  int    map_content(t_data *data, char *map_line, int i)
{
    while (*map_line && ft_isspace(*map_line))
        map_line++;
    if (!ft_strncmp(map_line, "1", 1) || !ft_strncmp(map_line, "0", 1)) 
    {
        data->map_info.start_map = 1;
        data->map_info.map_pos = i;
    }
    else if (!process_info_lines(data, map_line) && !data->map_info.map_pos)
        return (1);
    return (0);
}

static  int    search_map_info(char **map, t_data *data)
{ 
    int i;

    i = 0;
    data->map_info.start_map = 0;
	data->map_info.map_pos = 0;
    data->map_info.map2_height = 0;
    while (i < data->m_height)
    {
        if (!data->map_info.start_map)
        {
            if (map_content(data, map[i], i))
                return (1);
        }
        if (data->map_info.start_map)
            data->map_info.map2_height++;
        i++;
    }
    if (data->map_info.start_map)
        copy_map(data->map_info.map_pos, data->map_info.map2_height, data);
    else
		return (write(2, "Error. Map was not found\n", 26), 1);
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
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
		return (write(2, "Error. File management\n",  24), NULL);
    buf = (char **)malloc(sizeof(char *) * (lines + 1));
    if (!buf)
        return (write(2, "Error. Malloc\n", 15), NULL);
    buf[0] = 0;
    line = get_next_line(fd);
    while (line)
    {
        strip_newline(line);
        buf[i++] = line;
        line = get_next_line(fd);
    }
    buf[i] = '\0';
    close (fd);
    return (buf);
}

static int	check_cub_path(char *path)
{
	if (!ft_strnstr(path, ".cub", ft_strlen(path)))
		return (write(2, "Error. Not a correct map path\n", 31), 1);
	return (0);
}

t_data *init_map_bonus(t_data *data, char  *file_name)
{
if (check_cub_path(file_name))
		exit_cub(data);
    data->m_height = map_h(file_name);
    if (!data->m_height)
        exit_cub(data);
    data->map = open_map(file_name, data->m_height);
    if (!data->map)
        exit_cub(data);
    if (search_map_info(data->map, data))
        exit_cub(data);
    return (data);
}