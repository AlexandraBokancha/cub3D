/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:36:13 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/21 17:54:23 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// faire une enum;
// stocke les orientations direct;

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (1);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
		{
			return (0);
			break;
		}
		i++;
	}
	return (1);	
}

// mettre a la norme, verifie si on a besoin d'enum

int    process_info_lines(t_data *data, char *line)
{
    if (!ft_strncmp(line, "NO ", 3) && !data->textures.N_path)
    {
		data->textures.identor = nord;
		data->textures.N_path = line + 3;
    }
    else if (!ft_strncmp(line, "SO ", 3) && !data->textures.S_path)
    {
		data->textures.identor = south;
        data->textures.S_path = line + 3;
    }
    else if (!ft_strncmp(line, "WE ", 3) && !data->textures.W_path)
    {
		data->textures.identor = west;
        data->textures.W_path = line + 3;
    }
    else if (!ft_strncmp(line, "EA ", 3) && !data->textures.E_path)
	{
		data->textures.identor = east;
        data->textures.E_path = line + 3;
    }
    else if (!ft_strncmp(line, "F", 1) && !data->colors.f_color)
        data->colors.f_color = line + 1;
    else if (!ft_strncmp(line, "C", 1) && !data->colors.f_color)
        data->colors.c_color = line + 1;
	else
		return (0);
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
        return (write(2, "Error. File management\n", 24));
    line = get_next_line(fd);
    if (line == NULL)
        return (write(2, "Error. Empty map\n", 18));
    while (line)
    {
        height++;
        free(line);
        line = get_next_line(fd);
    }
    close (fd);
    return (height);
}
