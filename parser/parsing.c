/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:15:51 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/18 17:16:10 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

int parsing(t_data *data)
{
    parsing_textures();
    parsing_colors();
    parsing_map();
    return (0);
}