/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:27:23 by dbaladro          #+#    #+#             */
/*   Updated: 2024/08/15 16:28:51 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Make a (double) vector from X and Y value
 *
 * @param x X value (double)
 * @param y Y value (double)
 * @return The new vector (x,y)
 */
t_dvec	init_dvec(double x, double y)
{
	t_dvec	res;

	res.x = x;
	res.y = y;
	return (res);
}

/**
 * @brief Make a (int) vector from X and Y value
 *
 * @param x X value (int)
 * @param y Y value (int)
 * @return The new vector (x,y)
 */
t_ivec	init_ivec(int x, int y)
{
	t_ivec	res;

	res.x = x;
	res.y = y;
	return (res);
}
