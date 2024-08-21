/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:16:18 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/21 18:10:00 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

int	has_player(char *line)
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
	//printf("%d\n", player_in);
	if (player_in != 1)
		return (0);
	return (1);
}
static  int    copy_map(int map_pos, int height,  t_data *data)
{
    int i;

    i = 0;
    while (i < height)
    {   
        data->map_info.map2d[i] = data->map[map_pos];
        map_pos++;
        i++;
    }
    data->map_info.map2d[i] = NULL;
	return (1);
}

// mettre a la norme 

static  int    search_map_info(char **map, t_data *data)
{ 
    int i;

    i = 0;
    while (i < data->m_height)
    {
        if (!data->map_info.start_map)
        {
            if (!ft_strncmp(map[i], "1", 1) || !ft_strncmp(map[i], "0", 1)) 
            {
                data->map_info.start_map = 1;
                data->map_info.map_pos = i;
            }
        	else if (!process_info_lines(data, map[i]))
			{
				if (!is_empty_line(map[i]))
				{
					write(2, "Error. Invalid line in the map: ", 32);
					return (ft_putstr_fd(map[i], 2), 1);
				}
			}
        }
        if (data->map_info.start_map)
		{
			printf("%s", data->map[i]);
			if (!has_player(data->map[i]))
			{
				return(write(2, "Error. Player start position is absent, or there is more then one position\n", 76), 1);
				break;
			}
            data->map_info.map2_height++;
		}
        i++;
    }
    if (data->map_info.start_map)
	{
        if (!copy_map(data->map_info.map_pos, data->map_info.map2_height, data))
			return (0);
	}
    else
		return (write(2, "Error. Map was not found\n", 36), 1);
    return (0);
}


char    **open_map(char *file_name, int lines)
{
    char **buf;
    char *line;
    int fd;
    int i;

    i = 0;
    line = NULL;
    buf = (char **)malloc(sizeof(char *) * (lines + 1));
    if (!buf)
        return (write(2, "Error. Malloc\n", 15), NULL);
    buf[lines] = NULL;
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
    {
        free(buf);
		return (write(2, "Error. File management\n",  24), NULL);
    }
    line = get_next_line(fd);
    while (line)
    {
        buf[i++] = line;
        line = get_next_line(fd);
    }
    close (fd);
    return (buf);
}

int	check_cub_path(char *path)
{
	if (!ft_strnstr(path, ".cub", ft_strlen(path)))
		return (write(2, "Error. Not a correct map path\n", 31), 1);
	return (0);
}

t_data *init_map(t_data *data, char  *file_name)
{
    if (check_cub_path(file_name))
		exit_cub(data);
    data->m_height = map_h(file_name);
    if (!data->m_height)
        exit_cub(data);
    data->map = open_map(file_name, data->m_height);
    if (!data->map)
        exit_cub(data);
    if (search_map_info(data->map, data))
        exit_cub(data);
    if (parsing(data))
        exit_cub(data);
    return (data);
}
