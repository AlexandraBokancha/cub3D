/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:57:45 by alexandra         #+#    #+#             */
/*   Updated: 2024/09/03 17:42:32 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* comment dessiner un sprite (on le fait apres avoir dessine les murs et le sol)
        
        ETAPES:

1. calculate the distance of sprite to the player 
2. 
*/

void calculate_size_sprite(t_data *data, t_sprite *obj)
{
    // Calculer la position sur l'écran
    obj->screen_pos.x = (int)((data->w_width / 2) * (1 + data->map_size.x / data->map_size.y));

    // Calculer la taille du sprite à l'écran
    obj->sprite_size.y = abs((int)(data->w_height / data->map_size.y));
    obj->sprite_size.x = obj->sprite_size.y;  // Assume a square sprite

    // Calculer les positions de début et de fin du dessin du sprite
    obj->draw_start.y = -obj->sprite_size.y / 2 + data->w_height / 2;
    if (obj->draw_start.y < 0)
        obj->draw_start.y = 0;
    obj->draw_end.y = obj->sprite_size.y / 2 + data->w_height / 2;
    if (obj->draw_end.y >= data->w_height)
        obj->draw_end.y = data->w_height - 1;
    obj->draw_start.x = -obj->sprite_size.x / 2 + obj->screen_pos.x;
    if (obj->draw_start.x < 0)
        obj->draw_start.x = 0;
    obj->draw_end.x = obj->sprite_size.x / 2 + obj->screen_pos.x;
    if (obj->draw_end.x >= data->w_width)
        obj->draw_end.x = data->w_width - 1;
}

void    load_sprite_image(t_data *data, t_sprite *obj)
{
    int x;
    int y;
    
	obj->slices[0] = mlx_xpm_file_to_image(data->mlx, "sprites/coin_1.xpm", &x, &y);
	obj->slices[1] = mlx_xpm_file_to_image(data->mlx, "sprites/coin_2.xpm", &x, &y);
	obj->slices[2] = mlx_xpm_file_to_image(data->mlx, "sprites/coin_3.xpm", &x, &y);
	obj->slices[3] = mlx_xpm_file_to_image(data->mlx, "sprites/coin_4.xpm", &x, &y);
	obj->slices[4] = mlx_xpm_file_to_image(data->mlx, "sprites/coin_5.xpm", &x, &y);
	obj->slices[5] = mlx_xpm_file_to_image(data->mlx, "sprites/coin_6.xpm", &x, &y);
	obj->slices[6] = mlx_xpm_file_to_image(data->mlx, "sprites/coin_7.xpm", &x, &y);
	obj->slices[7] = mlx_xpm_file_to_image(data->mlx, "sprites/coin_8.xpm", &x, &y);
}

void    dist_from_player(t_data *data)
{
    
}

int    draw_sprite(t_data *data)
{  
    dist_from_player(data);
	//calculate_size_sprite(data, &data->sprite);
   // load_sprite_image(data, &data->sprite);
    // render_sprite(data);
    return (0);
}