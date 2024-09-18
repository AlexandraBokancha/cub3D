/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:36:13 by alexandra         #+#    #+#             */
/*   Updated: 2024/09/19 00:40:44 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	strip_newline(char *str)
{
	char	*pos;

	pos = ft_strchr(str, '\n');
	if (pos != NULL)
		*pos = '\0';
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	process_info_lines(t_data *data, char *line)
{
	if (!ft_strncmp(line, "NO ", 3) && !data->texture[0].path)
		data->texture[0].path = line + 3;
	else if (!ft_strncmp(line, "SO ", 3) && !data->texture[2].path)
		data->texture[2].path = line + 3;
	else if (!ft_strncmp(line, "WE ", 3) && !data->texture[1].path)
		data->texture[1].path = line + 3;
	else if (!ft_strncmp(line, "EA ", 3) && !data->texture[3].path)
		data->texture[3].path = line + 3;
	else if (!ft_strncmp(line, "F ", 2) && !data->colors.f_color)
		data->colors.f_color = line + 2;
	else if (!ft_strncmp(line, "C ", 2) && !data->colors.c_color)
		data->colors.c_color = line + 2;
	else
	{
		if (is_empty_line(line))
			return (1);
		else
		{
			write(2, "Error. Invalid line in the map: ", 32);
			return (ft_putstr_fd(line, 2), 0);
		}
	}
	return (1);
}

void	copy_map(int map_pos, int height, t_data *data)
{
	int		i;
	char	**tmp_map;

	i = 0;
	tmp_map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!tmp_map)
		return ((void)write(2, "Error. Malloc\n", 15));
	while (i < height)
	{
		tmp_map[i] = ft_strdup(data->map[map_pos]);
		if (!tmp_map[i])
			return ((void)write(2, "Error. Malloc\n", 15));
		i++;
		map_pos++;
	}
	tmp_map[i] = NULL;
	data->map_info.map2d = rotate_map(tmp_map);
	ft_free_char_tab(&tmp_map);
	data->map_info.map2_height = ft_tab_size(data->map_info.map2d);
	if (!data->map_info.map2d)
		return ((void)write(2, "Error. Malloc\n", 15));
}

int	map_h(char *file_name)
{
	char	*line;
	int		height;
	int		fd;

	line = NULL;
	height = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error. File management\n", 24), 0);
	line = get_next_line(fd);
	if (line == NULL)
		return (write(2, "Error. Empty map\n", 18), 0);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	return (height);
}
