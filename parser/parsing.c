/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:15:51 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/20 17:31:29 by albokanc         ###   ########.fr       */
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

int	check_first_last(char *line)
{
	int i;

	i = 0;
	while(line[i] && line[i] != '\n')
	{	
		if (line[i] != '1')
		{	
			write(2, "Error. Map is not closed\n", 26);
			return (0);
			break;
		}
		i++;
	}
	return (1);
}

int	check_borders(char *line)
{
	//printf("%zu\n", ft_strlen(line));
	if (line[0] != '1')
	{
		write(2, "Error. Map is not closed\n", 26);
			return (0);
	}
	if (line[ft_strlen(line) - 2] != '1')
	{
		write(2, "Error. Map is not closed\n", 26);
			return (0);
	}
	return (1);
}

int	is_wall(char *line, int last, int i)
{
	if (i == 0 || i == last - 1)
	{
		if (!check_first_last(line))
			return (0);
	}
	else
	{
		if (!check_borders(line))
			return (0);
	}
	return (1);
}

int	is_closed(char **map, int height)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (!is_wall(map[i], height, i))
			return (0);
		i++;
	}
	return (1);
}

void	fill_spaces(char **map, int height)
{
	int i;
	int j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int is_valid_chars(char **map, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' || map[i][j] != '0' \
				|| map[i][j] != 'N' || map[i][j] != 'S' \
				|| map[i][j] != 'E' || map[i][j] != 'W')
			{
				write(2, "Error. Map is not closed\n", 26);
				return (0);
				break ;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	parsing_map(t_map_info *map_info)
{
	fill_spaces(map_info->map2d, map_info->map2_height);
	if (!is_valid_chars(map_info->map2d, map_info->map2_height))
		return (1);
	if (!is_closed(map_info->map2d, map_info->map2_height))
		return (1);
	return (0);	
};

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
	//save colors in rgb ??
    if (parsing_map(&data->map_info))
		return (1);
    return (0);
}