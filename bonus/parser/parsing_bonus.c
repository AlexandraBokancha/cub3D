/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:46:31 by alexandra         #+#    #+#             */
/*   Updated: 2024/09/18 22:32:45 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_char_bonus(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'A' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'W' && line[i] != 'E'
			&& line[i] != ' ' && !is_door(line[i]))
			return (write(2, "Error. Values are not valid\n", 29), 0);
		i++;
	}
	return (1);
}

int	is_valid_chars_bonus(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (!check_char_bonus(map[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parsing_map_bonus(t_map_info *map_info)
{
	if (!is_closed(map_info->map2d, map_info->map2_height))
		return (1);
	if (!is_valid_chars_bonus(map_info->map2d, map_info->map2_height))
		return (1);
	if (!has_start_pos(map_info->map2d, map_info->map2_height))
		return (1);
	if (!check_inside(map_info->map2d, map_info->map2_height))
		return (1);
	return (0);
}

int	parsing_bonus(t_data *data)
{
	if (parsing_textures(data->texture))
		return (1);
	if (parsing_map_bonus(&data->map_info))
		return (1);
	if (parsing_colors(data->colors.f_color) != 3
		|| parsing_colors(data->colors.c_color) != 3)
		return (1);
	return (0);
}
