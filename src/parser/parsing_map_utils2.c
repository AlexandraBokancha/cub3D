/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:31:10 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/28 18:01:53 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

int	check_first_last(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{	
		if (line[i] != '1' && line[i] != ' ')
			return (write(2, "Error. Map is not closed\n", 26), 0);
		i++;
	}
	return (1);
}

int	find_last_one(char *line)
{
	int i;
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
		if (line[i] != 32  && line[i] != '\t')
		{
			printf("%d\n", line[i]);
			return (0);
		}
		i++;
	}
	return (1);
}


int	check_borders(char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	if (!is_empty_line(line) && *line != '1')
	{
		printf("%c\n", line[0]);
		return (write(2, "Error.1 Map is not closed\n", 26), 0);
	}
	if (!find_last_one(line))
		return (write(2, "Error. 2Map is not closed\n", 26), 0);
	return (1);
}
