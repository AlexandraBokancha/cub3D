/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:01:31 by albokanc          #+#    #+#             */
/*   Updated: 2024/08/21 15:55:54 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

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

int	check_char_in_line(char *line)
{
	int i;
	
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' \
			&& line[i] != 'S' && line[i] != 'S' && line[i] != 'E') 
		{
			write(2, "Error. Values are not valid\n", 29);
			return (0);
			break;
		}
		i++;
	}
	return (1);
}

int is_valid_chars(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (!check_char_in_line(map[i]))
			return (0);
		i++;
	}
	return (1);
}
