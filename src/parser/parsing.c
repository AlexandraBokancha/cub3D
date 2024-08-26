/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:15:51 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/26 16:39:43 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

/**
 * @brief Checks if a texture path is valid.
 *
 * This function checks if the given texture path is non-null, strips any newline characters,
 * skips leading whitespace, and attempts to open the file. If the path is invalid or the file
 * cannot be opened, it returns 0 and prints an appropriate error message.
 *
 * @param path The file path to check.
 * @return 1 if the path is valid and the file can be opened, 0 otherwise.
 */
static int	is_path(char *path)
{
    int fd;

	if (path == NULL)
		return (write(2, "Error. Path texture is missing\n", 32), 0);
	strip_newline(path);
    while (*path && ft_isspace(*path))
       path++;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error. Path texture is not valid: ", 2);
		ft_putstr_fd(path, 2);
		return (ft_putstr_fd("\n", 2), 0);
	}
	close(fd);
	return (1);
}

static int parsing_textures(t_texture textures)
{
	if (!is_path(textures.N_path) || !is_path(textures.E_path) \
		|| !is_path(textures.S_path) || !is_path(textures.W_path))
			return (1);
    return (0);
}

/**
 * @brief Parses and validates a color string.
 *
 * This function checks the format of the given color string, ensuring it contains exactly
 * three comma-separated values. It strips any newline characters and validates each value.
 *
 * @param color The color string to validate.
 * @return The number of valid comma-separated values (should be 3), or 0 if invalid.
 */
static int parsing_colors(char *color)
{
    int start;
    int count;
    int i;

    if (color == NULL)
        return (0);
    start = 0;
    count = 0;
    i = 0;
    strip_newline(color);
    while (color[i])
    {
        if (color[i] == ',' || color[i + 1] == '\0')
        {
            if (color[i + 1] == '\0')
                i++;
            if (validate_value(color, start, i))
                return (0);
            start = i + 1;
            count++;
        }
        i++;
    }
    return (count);    
}

/**
 * @brief Validates the map structure.
 *
 * This function validates the map structure by checking if the map is closed, contains valid
 * characters, and has a valid starting position. It returns 1 if any of these checks fail.
 *
 * @param map_info The map_info structure containing the map to validate.
 * @return 0 if the map is valid, 1 if any validation step fails.
 */
static int	parsing_map(t_map_info *map_info)
{
	if (!is_closed(map_info->map2d, map_info->map2_height))
		return (1);
	if (!is_valid_chars(map_info->map2d, map_info->map2_height))
		return (1);
    if (!has_start_pos(map_info->map2d, map_info->map2_height))
		return (1);
	return (0);	
};

/**
 * @brief Main parsing function for cub3d data.
 *
 * This function orchestrates the parsing of textures, map, and colors. It validates the texture
 * paths, the map structure, and the RGB color strings. If any of these validations fail, it
 * returns 1 to indicate an error.
 *
 * @param data The main cub3d data structure containing textures, map, and color information.
 * @return 0 if all parsing is successful, 1 if any parsing step fails.
 */
int parsing(t_data *data)
{
	if (parsing_textures(data->textures))
        return (1);
    if (parsing_map(&data->map_info))
		return (1);
    if (parsing_colors(data->colors.f_color) != 3 || parsing_colors(data->colors.c_color) != 3)
        return (write(2, "Error. Invalid RGB.\n", 21), 1);
    return (0);
}
