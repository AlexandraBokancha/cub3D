/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:38:32 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/19 00:43:52 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_all(char ***tab, int pos)
{
	int	i;

	if (!tab | ! *tab)
		return ;
	i = 0;
	while (i < pos)
	{
		if ((*tab)[i])
		{
			free((*tab)[i]);
			(*tab)[i] = NULL;
		}
		i++;
	}
	free(*tab);
	*tab = NULL;
}

static t_ivec	get_map_size(char *map[])
{
	t_ivec	size;
	int		col;

	size = init_ivec(0, 0);
	while (map[size.x])
	{
		col = 0;
		while (map[size.x][col])
			col++;
		if (col > size.y)
			size.y = col;
		size.x++;
	}
	return (size);
}

static char	**alloc_map(t_ivec size)
{
	char	**new_tab;
	int		i;

	new_tab = (char **)malloc(sizeof(char *) * (size.y + 1));
	if (!new_tab)
		return (print_error("malloc", errno), NULL);
	memset(new_tab, ' ', (sizeof(char *) * (size.y + 1)));
	i = 0;
	while (i < size.y)
	{
		new_tab[i] = (char *)malloc(size.x + 1);
		if (!new_tab[i])
			return (print_error("malloc", errno), free_all(&new_tab, i), NULL);
		memset(new_tab[i], (int)' ', size.x + 1);
		new_tab[i][size.x] = '\0';
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

/**
 * @brief Rotate the map passed as a parameter returning a new_allocated map
 *
 * This function is needed after the get_next_line to have
 * a correct display of the map
 *
 * @param	map	The map that was read after get_net_line
 * @return	The rotated_map NEWLY ALOCATED
 */
char	**rotate_map(char *map[])
{
	t_ivec	size;
	int		x;
	int		y;
	char	**new_map;

	size = get_map_size(map);
	new_map = alloc_map(size);
	if (!new_map)
		return (NULL);
	x = 0;
	while (x < size.x && map[x])
	{
		y = size.y;
		while (y-- > 0)
			new_map[size.y - 1 - y][x] = map[ft_tab_size(map) - 1 - x]
			[ft_strlen(map[x]) - 1 - y];
		x++;
	}
	return (new_map);
}
