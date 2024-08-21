/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:15:51 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/21 17:56:53 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

int	is_path(char *path)
{
    int fd;

	if (path == NULL)
		return (write(2, "Error. Path is missing\n", 24), 0);
	strip_newline(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error. Path is not valid: ", 2);
		ft_putstr_fd(path, 2);
		return (ft_putstr_fd("\n", 2), 0);
	}
	close(fd);
	return (1);
}

int parsing_textures(t_texture textures)
{
	if (!is_path(textures.N_path) || !is_path(textures.E_path) \
		|| !is_path(textures.S_path) || !is_path(textures.W_path))
			return (1);
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

int	parsing_map(t_map_info *map_info)
{
	fill_spaces(map_info->map2d, map_info->map2_height);
	if (!is_closed(map_info->map2d, map_info->map2_height))
		return (1);
	if (!is_valid_chars(map_info->map2d, map_info->map2_height))
		return (1);
	return (0);	
};

//save colors in rgb ??

int parsing(t_data *data)
{
	if (parsing_textures(data->textures))
        return (1);
    if (parsing_map(&data->map_info))
		return (1);
    if (!parsing_colors(data->colors.f_color))
        return (1);
    return (0);
}
