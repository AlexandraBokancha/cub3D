/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:31:10 by alexandra         #+#    #+#             */
/*   Updated: 2024/09/18 14:06:21 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_first_last(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (write(2, "Error. Map is not closed\n", 26), 0);
		i++;
	}
	return (1);
}

int	find_last_one(char *line)
{
	int	i;
	int	last_one;

	i = 0;
	last_one = -1;
	while (line[i])
	{
		if (line[i] == '1')
			last_one = i;
		i++;
	}
	i = last_one + 1;
	while (line[i])
	{
		if (line[i] != 32 && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	check_borders(char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	if (!is_empty_line(line) && *line != '1')
		return (write(2, "Error. Map is not closed\n", 26), 0);
	if (!find_last_one(line))
		return (write(2, "Error. Map is not closed\n", 26), 0);
	return (1);
}

int	is_closed_inside(int x_dep, int y_dep, char **map, int height)
{
	if (x_dep > 0 && (map[x_dep -1][y_dep] == '\0' \
		|| ft_isspace(map[x_dep - 1][y_dep])))
		return (0);
	if (x_dep < height - 1 && (map[x_dep + 1][y_dep] == '\0' \
		|| ft_isspace(map[x_dep + 1][y_dep])))
		return (0);
	if (y_dep > 0 && (map[x_dep][y_dep - 1] == '\0' \
		|| ft_isspace(map[x_dep - 1][y_dep - 1])))
		return (0);
	if (y_dep < (int)ft_strlen(map[x_dep]) - 1 && map[x_dep][y_dep + 1] == '\0')
		return (0);
	return (1);
}
