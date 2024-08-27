/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:31:10 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/27 16:12:00 by alexandra        ###   ########.fr       */
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

int	check_borders(char *line)
{
	while (*line && ft_isspace(*line))
        line++;
	if (*line != '1' || line[ft_strlen(line) - 1] != '1')
		return (write(2, "Error. Map is not closed\n", 26), 0);
	return (1);
}
