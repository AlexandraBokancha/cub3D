/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:36:54 by dbaladro          #+#    #+#             */
/*   Updated: 2024/09/16 12:32:45 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	open_door(t_data *data)
{
	t_raycast	ray;
	t_ivec		pos;

	ray = raycast(data, data->w_width / 2);
	pos = init_ivec((int)ray.h_pos.x, (int)ray.h_pos.y);
	if (!is_aiming_at_door(data, &ray))
		return ;
	if (data->map[pos.x][pos.y] == 'c'
		|| data->map[pos.x][pos.y] == 'C')
		data->map[pos.x][pos.y] += 12;
	else if (data->map[pos.x][pos.y] == 'o'
		|| data->map[pos.x][pos.y] == 'O')
		data->map[pos.x][pos.y] -= 12;
	else
		return ;
}
