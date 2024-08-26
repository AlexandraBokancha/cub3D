/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:15:51 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/26 14:40:58 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

static int	is_path(char *path)
{
    int fd;

	if (path == NULL)
		return (write(2, "Error. Path texture is missing\n", 32), 0);
	strip_newline(path);
    while (*path && ft_isspace(*path))
       path++;
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

static int parsing_textures(t_texture textures)
{
	if (!is_path(textures.N_path) || !is_path(textures.E_path) \
		|| !is_path(textures.S_path) || !is_path(textures.W_path))
			return (1);
    return (0);
}

static int parsing_colors(char *color)
{
    int start;
    int count;
    int i;

    if (color == NULL)
        return (1);
    start = 0;
    count = 0;
    i = 0;
    strip_newline(color);
    while (color[i])
    {
        if (color[i] == ',' || color[i + 1] == '\0')
        {
            if (color[i + 1] == '\0')
                i++;
            if (validate_value(color, start, i))
                return (0);
            start = i + 1;
            count++;
        }
        i++;
    }
    return (count);    
}

static int	parsing_map(t_map_info *map_info)
{
	if (!is_closed(map_info->map2d, map_info->map2_height))
		return (1);
	if (!is_valid_chars(map_info->map2d, map_info->map2_height))
		return (1);
    if (!has_start_pos(map_info->map2d, map_info->map2_height))
		return (1);
	return (0);	
};
int    rgb_to_hex(char *color)
{
    int i;
    int r;
    int g;
    int b;

    i = 0;
    r = ft_atoi(&color[i]);
    while (ft_isdigit(color[i]))
        i++;
    if (color[i] == ',')
        i++;
    g = ft_atoi(&color[i]);
     while
      (ft_isdigit(color[i]))
        i++;
    if (color[i] == ',')
        i++;
    b = ft_atoi(&color[i]);
    return (0 << 24 | r << 16 | g << 8 | b);    
}

int parsing(t_data *data)
{
	if (parsing_textures(data->textures))
        return (1);
    if (parsing_map(&data->map_info))
		return (1);
    if (parsing_colors(data->colors.f_color) != 3 || parsing_colors(data->colors.c_color) != 3)
        return (write(2, "Error. Invalid RGB.\n", 21), 1);
    return (0);
}
