/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:06:49 by alexandra         #+#    #+#             */
/*   Updated: 2024/10/08 16:49:07 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief	Processes a single line of the map file
 *			and determine if it contains map data.
 *
 * This function checks if the line contains valid map contents
 * (starts with '1' or '0') 
 * or if it contains other configuration
 * lines like texture paths or color definitions.
 * If it finds the start of the map, it sets the appropriate flags in the data
 * structure. If a configuration line is processed before the map starts,
 * the function delegates processing to `process_info_lines`.
 *
 * @return	0 if successful,
 *			1 if there is an error in processing the configuration lines.
 */

static int	map_content(t_data *data, char *map_line, int i)
{
	while (*map_line && ft_isspace(*map_line))
		map_line++;
	if (!ft_strncmp(map_line, "1", 1) || !ft_strncmp(map_line, "0", 1))
	{
		data->map_info.start_map = 1;
		data->map_info.map_pos = i;
	}
	else if (!process_info_lines(data, map_line) && !data->map_info.map_pos)
		return (1);
	return (0);
}

/**
 * @brief Scans the map file to locate and process the map data,
 * counting its dimensions.
 *
 * This function iterates through each line of the map file,
 * looking for the start of the map.
 * If found, it tracks the starting
 * position and counts the height of the map. After locating the map, 
 * it calls `copy_map` to extract the map data from the file.
 * If no map is found, an error is printed.
 *
 * @return 0 if successful, 1 if no map was found or if there is an error.
 */
static int	search_map_info(char **map, t_data *data)
{
	int	i;

	i = 0;
	data->map_info.start_map = 0;
	data->map_info.map_pos = 0;
	data->map_info.map2_height = 0;
	while (i < data->m_height)
	{
		if (!data->map_info.start_map)
		{
			if (map_content(data, map[i], i))
				return (1);
		}
		if (data->map_info.start_map)
			data->map_info.map2_height++;
		i++;
	}
	if (data->map_info.start_map)
		copy_map(data->map_info.map_pos, data->map_info.map2_height, data);
	else
		return (write(2, "Error. Map was not found\n", 26), 1);
	if (!data->map_info.map2d)
		return (1);
	return (0);
}

/**
 * @brief Opens the map file and reads its contents line by line into a buffer.
 *
 * This function opens the specified map file and reads
 * each line, removing newlines and storing the lines in a buffer.
 * 
 * @return A pointer to the buffer containing the map lines, or NULL on error.
 */
char	**open_map(char *file_name, int lines)
{
	char	**buf;
	char	*line;
	int		fd;
	int		i;

	i = 0;
	line = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error. File management\n", 24), NULL);
	buf = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!buf)
		return (write(2, "Error. Malloc\n", 15), NULL);
	buf[0] = 0;
	line = get_next_line(fd);
	while (line)
	{
		strip_newline(line);
		buf[i] = line;
		line = get_next_line(fd);
		i++;
	}
	buf[i] = NULL;
	close (fd);
	return (buf);
}

/**
 * @brief Checks if the given file path has the correct .cub extension.
 * @return 0 if the path is valid, 1 if the path does not end with `.cub`.
 */
int	check_cub_path(char *path)
{
	if (((ft_strncmp(".cub", path + (ft_strlen(path) - 4), 4))))
		return (write(2, "Error. Not a correct map path\n", 31), 1);
	return (0);
}

/**
 * @brief Initializes the map by loading and parsing the .cub file
 * for the bonus version of cub3D.
 *
 * This function verifies the file path, opens and reads the map file, processes
 * the map and configuration data, and
 * parses textures and colors. If any step fails, it frees the cub3D
 * data structure and exits the program.
 * Function also sets the ceiling and floor colors based on parsed RGB values.

 * @return A pointer to the initialized cub3D data structure, or exits on error.
 */
t_data	*init_map_bonus(t_data *data, char *file_name)
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
	if (parsing_bonus(data))
		exit_cub(data);
	data->ceiling_color = rgb_to_hex(data->colors.c_color);
	data->floor_color = rgb_to_hex(data->colors.f_color);
	return (data);
}
