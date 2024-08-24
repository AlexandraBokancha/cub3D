/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:36:13 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/24 18:29:13 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (1);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);	
}

int    process_info_lines(t_data *data, char *line)
{
    if (!ft_strncmp(line, "NO ", 3) && !data->textures.N_path)
		data->textures.N_path = line + 3;
    else if (!ft_strncmp(line, "SO ", 3) && !data->textures.S_path)
        data->textures.S_path = line + 3;
    else if (!ft_strncmp(line, "WE ", 3) && !data->textures.W_path)
        data->textures.W_path = line + 3;
    else if (!ft_strncmp(line, "EA ", 3) && !data->textures.E_path)
        data->textures.E_path = line + 3;
    else if (!ft_strncmp(line, "F ", 2) && !data->colors.f_color)
        data->colors.f_color = line + 2;
    else if (!ft_strncmp(line, "C ", 2) && !data->colors.c_color)
        data->colors.c_color = line + 2;
	else
    {
    	if (is_empty_line(line))
	       return (1);
        else
		{
		    write(2, "Error. Invalid line in the map: ", 32);
			return (ft_putstr_fd(line, 2), 0);
		}
    }
	return (1);
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
        return (write(2, "Error. File management\n", 24), 0);
    line = get_next_line(fd);
    if (line == NULL)
        return (write(2, "Error. Empty map\n", 18), 0);
    while (line)
    {
        height++;
        free(line);
        line = get_next_line(fd);
    }
    close (fd);
    return (height);
}

void    copy_map(int map_pos, int height,  t_data *data)
{
    int i;

    i = 0;
    data->map_info.map2d = (char **)malloc(sizeof(char *) * (height + 1));
    if (!data->map_info.map2d)
        return ((void)write(2, "Error. Malloc\n", 15));
    while (i < height)
    {   
        data->map_info.map2d[i] = ft_strdup(data->map[map_pos]);
        map_pos++;
        i++;
    }
    data->map_info.map2d[i] = NULL;
}
int ft_isspace(char c)
{
    if (c == ' ')
        return (1);
    return (0);
}
