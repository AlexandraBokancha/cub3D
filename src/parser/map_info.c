/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:16:18 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/26 18:24:07 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

/**
 * @brief Processes a line of the map and updates map-related data.
 *
 * This function checks whether a line in the map corresponds to the beginning of the map 
 * content (i.e., contains a '1' or '0'). If so, it marks the map's start position 
 * and updates relevant data in the `t_data` structure. If the line does not start the 
 * map and does not contain necessary information, it returns an error.
 *
 * @param data A pointer to the `t_data` structure containing map-related data.
 * @param map_line A pointer to the current line of the map being processed.
 * @param i The current line index in the map.
 * 
 * @return Returns 0 if successful, 1 if an error occurs.
 */
static  int    map_content(t_data *data, char *map_line, int i)
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
 * @brief Searches and processes the map information within the map file.
 *
 * This function iterates through the lines of the map to locate and process 
 * the map content. It updates the map's start position and height, and if the map 
 * is found, it copies the map data for further processing. If no map content is found, 
 * it returns an error.
 *
 * @param map A pointer to an array of strings representing the map lines.
 * @param data A pointer to the `t_data` structure where map information is stored.
 * 
 * @return Returns 0 if successful, 1 if an error occurs (e.g., if the map is not found).
 */
static  int    search_map_info(char **map, t_data *data)
{ 
    int i;

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
    return (0);
}

/**
 * @brief Opens and reads the content of a .cub map file into memory.
 *
 * This function reads the lines of a given .cub file into an array of strings. 
 * It allocates memory for the array, opens the file, reads each line, 
 * and stores it in the array. If the file cannot be opened or read, 
 * or if memory allocation fails, it returns an error.
 *
 * @param file_name The path to the .cub file to be opened.
 * @param lines The number of lines expected in the map file.
 * 
 * @return A pointer to an array of strings representing the map lines, or NULL on error.
 */
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
    while (i < lines && line)
    {
        buf[i++] = line;
        line = get_next_line(fd);
    }
    close (fd);
    return (buf);
}

/**
 * @brief Checks if the provided file path points to a valid .cub file.
 *
 * This function verifies that the file path provided ends with the ".cub" extension, 
 * indicating that it is a valid map file for the cub3d project. If the path is not valid, 
 * it returns an error.
 *
 * @param path The file path to be checked.
 * 
 * @return Returns 0 if the path is valid, 1 if the path is invalid.
 */
static int	check_cub_path(char *path)
{
	if (!ft_strnstr(path, ".cub", ft_strlen(path)))
		return (write(2, "Error. Not a correct map path\n", 31), 1);
	return (0);
}

/**
 * @brief Initializes and processes the map data from a .cub file.
 *
 * This function initializes the `t_data` structure with map information from
 * the provided `.cub` file. It verifies the file path, reads the file content,
 * and processes the map data. If any errors occur during these steps,
 * the program exits gracefully using the `exit_cub` function.
 *
 * @param data A pointer to the `t_data` structure to be initialized.
 * @param file_name The path to the `.cub` map file to be processed.
 * 
 * @return A pointer to the initialized `t_data` structure containing map information.
 */
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
