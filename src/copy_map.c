/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:38:32 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/03 16:45:39 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static int	get_map_size(char *map[])
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
	if (size.y > size.x)
		return (size.y);
	return (size.x);
}

static char	**alloc_map(int	size)
{
	char	**new_tab;
	int		i;

	new_tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_tab)
		return (print_error("malloc", errno), NULL);
	memset(new_tab, 0, (sizeof(char *) * (size + 1)));
	i = 0;
	while (i < size)
	{
		new_tab[i] = (char *)malloc(size + 1);
		if (!new_tab[i])
			return (print_error("malloc", errno), free_all(&new_tab, i), NULL);
		memset(new_tab[i], 0, size + 1);
		i++;
	}
	return (new_tab);
}

char	**get_map(char *map[])
{
	int		size;
	int		x;
	int		y;
	char	**new_map;

	size = get_map_size(map);
	new_map = alloc_map(size);
	if (!new_map)
		return (NULL);
	x = 0;
	while (x < size && map[x])
	{
		y = 0;
		while (y < size && map[x][y])
		{
			new_map[y][x] = map[x][y];
			y++;
		}
		x++;
	}
	return (new_map);
}
