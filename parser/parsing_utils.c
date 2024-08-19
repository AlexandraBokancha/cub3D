/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:32:58 by alexandra         #+#    #+#             */
/*   Updated: 2024/08/19 18:26:33 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

void    strip_newline(char *str)
{
    char *pos;

    pos = ft_strchr(str, '\n');
    if (pos != NULL)
        *pos = '\0';
}

