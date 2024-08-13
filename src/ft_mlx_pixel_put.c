/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:19:41 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/13 20:10:45 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Put set the pixel in (x,y) to color in the image img
 *
 * @param img The t_img structure
 * @param x X position in the window
 * @param y Y position in the window
 * @param color New pixel color
 */
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr +
		(y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}
