/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:32:58 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/26 16:36:51 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

void    strip_newline(char *str)
{
    char *pos;

    pos = ft_strchr(str, '\n');
    if (pos != NULL)
        *pos = '\0';
}

int	find_pos(char *line)
{
	int player_in;
	int i;
	
	i = 0;
	player_in = 0;
	while (line[i] && line[i] != '\n')
	{
		if ((line[i] == 'N' || line[i] == 'W' \
			|| line[i] == 'E' || line[i] == 'S'))
			player_in++;
		i++;
	}
	return (player_in);
}

int	has_start_pos(char **map, int height)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (i < height)
	{
		count += find_pos(map[i]);
		if (count > 1)
			return (write(2, "Error. More then one start position found\n", 43), 0);
		i++;
	}
	if (!count)
		return (write(2, "Error. No start position found\n", 32), 0);
	return (1);
}

int validate_value(char *color, int start, int end)
{
    int value;
    
    if (end == start)
        return (1);
    value = ft_atoi(&color[start]);
    if (value < 0 || value > 255)
        return (1);
    return (0);
}

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
