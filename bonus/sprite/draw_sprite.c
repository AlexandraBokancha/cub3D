/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:57:45 by alexandra         #+#    #+#             */
/*   Updated: 2024/09/09 22:22:30 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* comment dessiner un sprite (on le fait apres avoir dessine les murs et le sol)
        
        ETAPES:

1. calculate the distance of sprite to the player 
2. calculate sprite screen position
3. calculate size of the sprite
4. initialiser le debut et la fin de draw

*/


// project the sprite on the camera plane (in 2D):
// substract the player position from the sprite positin
// multiply the result with the inverse of the 2x2 camera matrix
// player direction vector: data->direction;
// camera plane vector: data->camera_plane;
// inverse matrix formula:
// 1 / (dir.x * plane - dir.y * plane.x) X (plane.y - dir.y, -plane.x dir.x)

void    sprite_to_camera(t_data *data, int i)
{
    t_dvec  relative_pos;
    t_dvec  transform;
    double  inv;
    
    relative_pos.x = data->sprites_arr[i].sprite_pos.x - data->player.x;
    relative_pos.y = data->sprites_arr[i].sprite_pos.y - data->player.y;
    inv = 1.0 / (data->camera_plane.x * data->direction.y - data->direction.x * data->camera_plane.y);
    transform.x = inv * (data->direction.y * relative_pos.x - data->direction.x * relative_pos.y);
    transform.y = inv * (-data->camera_plane.y * relative_pos.x + data->camera_plane.x * relative_pos.y);
    data->sprites_arr[i].screen_pos.x = (int)((data->w_width / 2) * (1 + transform.x / transform.y)); 
    data->sprites_arr[i].perp_dist = transform.y;
}
// calculate the height of the sprite on the screen (in our case
// the sprite is square (32 x 32 pix)

void    sprite_size(t_data *data, int i)
{
    data->sprites_arr[i].sprite_size.y = abs((int)(data->w_height / data->sprites_arr[i].perp_dist));
    data->sprites_arr[i].sprite_size.x = abs((int)(data->w_height / data->sprites_arr[i].perp_dist));
}

// calculate the top and bottom of the sprite 
// calculate the left and right sides of the sprite 

void    init_draw(t_data *data, int i)
{
    data->sprites_arr[i].draw_start.y = data->sprites_arr[i].sprite_size.y / 2 + data->w_height / 2 \
        - (int)(data->sprites_arr[i].perp_dist * data->sprites_arr[i].sprite_size.y);
    if (data->sprites_arr[i].draw_start.y < 0)
        data->sprites_arr[i].draw_start.y = 0;
    data->sprites_arr[i].draw_end.y = data->sprites_arr[i].sprite_size.y / 2 + data->w_height / 2;
    if (data->sprites_arr[i].draw_end.y >= data->w_height)
        data->sprites_arr[i].draw_end.y = data->w_height - 1;
    data->sprites_arr[i].draw_start.x = data->sprites_arr[i].sprite_size.x / 2 + data->sprites_arr[i].screen_pos.x \
        - (int)(data->sprites_arr[i].perp_dist * data->sprites_arr[i].sprite_size.x);
    if (data->sprites_arr[i].draw_start.x < 0)
        data->sprites_arr[i].draw_start.x = 0;
    data->sprites_arr[i].draw_end.x = data->sprites_arr[i].sprite_size.x / 2 + data->sprites_arr[i].screen_pos.x;
    if (data->sprites_arr[i].draw_end.x >= data->w_width)
        data->sprites_arr[i].draw_end.x = data->w_width - 1; 
}
        
void    put_sprite_pxl(t_data *data, int i)
{
    int     stripe;
  
    stripe = data->sprites_arr[i].draw_start.x;
    while (stripe < data->sprites_arr[i].draw_end.x)
    {
        if (data->sprites_arr[i].perp_dist > 0 && stripe >= 0 
            && stripe < data->w_width && data->sprites_arr[i].perp_dist <= data->zbuffer[stripe] + 0.8)
        {
            data->tex.x = (int)((stripe - (-data->sprites_arr[i].sprite_size.x / \
                2 + data->sprites_arr[i].screen_pos.x)) * 32 / data->sprites_arr[i].sprite_size.x);
            process_sprite_y(data, i, stripe);
        }     
        stripe++;
    }
}

int    draw_sprite(t_data *data)
{
    int i;

    i = 0;
    calculate_sprite_distances(data);
    sort_sprites(data);
    while (i < data->sprites_nb)
    {
        if (data->sprites_arr[i].is_active)
        {
            sprite_to_camera(data, i);
            sprite_size(data, i);
            init_draw(data, i);
            update_sprite_frame(data, i);
            put_sprite_pxl(data, i);
        }
        i++;
    }
    return (0);
}
