/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:15:51 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/24 13:50:25 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

int	is_path(char *path)
{
    int fd;

	if (path == NULL)
		return (write(2, "Error. Path texture is missing\n", 32), 0);
	strip_newline(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error. Path texture is not valid: ", 2);
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
    count = 0;
    i = 0;
    strip_newline(color);
    if (color == NULL)
        return (write(2, "Error. Invalid RGB.\n", 21), 1);
    while (color[i])
    {
        if (color[i] == ',' || color[i + 1] == '\0')
        {
            if (color[i + 1] == '\0')
                i++;
            value = ft_atoi(&color[start]);
            if (value < 0 || value > 255)
                return (write(2, "Error. Invalid RGB.\n", 21), 1);
            count++;
            start = i + 1;
        }
        i++;
    }
    if (count > 3)
        return (write(2, "Error. Invalid RGB.\n", 21), 1);
    return (0);    
}

int	parsing_map(t_map_info *map_info)
{
	//fill_spaces(map_info->map2d, map_info->map2_height);
    char **ptr = map_info->map2d;
    while (*ptr != NULL)
    {
        printf("%s", *ptr);
        ptr++;
    }
	if (!is_closed(map_info->map2d, map_info->map2_height))
		return (1);
	if (!is_valid_chars(map_info->map2d, map_info->map2_height))
		return (1);
    if (!has_start_pos(map_info->map2d, map_info->map2_height))
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
    if (parsing_colors(data->colors.f_color) || parsing_colors(data->colors.c_color))
        return (1);
    return (0);
}
