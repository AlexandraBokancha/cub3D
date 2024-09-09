/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 05:47:37 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/09 22:06:59 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief This file contain the primary function to handle doors properly
 *
 * The door code is as follow :
 * c : closed door (bottom of block)
 * o : open   door (right  of block)
 * C : CLOSED door (top    of block)
 * O : OPEN   door (left   of block)
 */

#include "../../includes/cub3d.h"

static int	check_door_side(t_data *data, t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (data->map[ray->map.x][ray->map.y] == 'o'
				&& ray->h_pos.x - (int)ray->map.x <= 0.05)
			return ('o');
		if (data->map[ray->map.x][ray->map.y] == 'O'
				&& ray->h_pos.x - (int)ray->map.x >= 0.95)
			return ('O');
		return (0);
	}
	if (data->map[ray->map.x][ray->map.y] == 'c'
			&& ray->h_pos.y - (int)ray->map.y <= 0.05)
		return ('c');
	if (data->map[ray->map.x][ray->map.y] == 'C'
			&& ray->h_pos.y - (int)ray->map.y >= 0.95)
		return ('C');
	return (0);
}

static int	check_south_west(t_data *data, t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (data->map[ray->map.x][ray->map.y - 1] == 'c')
		{
			// PERP WALL DIST ADJUSTMENT
			return ('c');
		}
		if (data->map[ray->map.x][ray->map.y] == 'C')
			return ('C');
		if (data->map[ray->map.x][ray->map.y] == 'o'
				&& ray->h_pos.x - (int)ray->map.x <= 0.05)
			return ('o');
		if (data->map[ray->map.x][ray->map.y] == 'O'
				&& ray->h_pos.x - (int)ray->map.x >= 0.95)
			return ('O');
		return (data->map[ray->map.x][ray->map.y]);
	}
	if (data->map[ray->map.x + 1][ray->map.y] == 'O')
	{
		// PERP WALL DIST ADJUSTMENT
		return ('O');
	}
	if (data->map[ray->map.x][ray->map.y] == 'o')
		return ('C');
	if (data->map[ray->map.x][ray->map.y] == 'c'
			&& ray->h_pos.y - (int)ray->map.y <= 0.05)
		return ('c');
	if (data->map[ray->map.x][ray->map.y] == 'C'
			&& ray->h_pos.y - (int)ray->map.y >= 0.95)
		return ('C');
	return (data->map[ray->map.x][ray->map.y]);
}

int	check_hit(t_data *data, t_raycast *ray)
{
	ray_hit_pos(data, ray);
	if (ray->dir.x < 0.0 && ray->dir.y < 0.0)
		return (check_south_west(data, ray));
	if (ray->dir.x < 0.0 && ray->dir.y >= 0.0)
		return (check_north_west(data, ray));
	if (ray->dir.x >= 0.0 && ray->dir.y < 0.0)
		return (check_south_est(data, ray));
	return (check_north_est(data, ray));
}
