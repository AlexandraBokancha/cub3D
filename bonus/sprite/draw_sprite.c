/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:57:45 by alexandra         #+#    #+#             */
/*   Updated: 2024/09/08 19:55:32 by alexandra        ###   ########.fr       */
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


// calculate the difference between the sprite's and player's position on the map.
// dist euclidean formula = sqrt(dx^2 + dy^2)

void    calculate_sprite_distances(t_data *data)
{
    t_dvec  diff;
    int i;

    i = 0;
    while (i < data->sprites_nb)
    {
        if (data->sprites_arr[i].is_active == false)
            i++;
        diff.x = data->sprites_arr[i].sprite_pos.x - data->player.x;
        diff.y = data->sprites_arr[i].sprite_pos.y - data->player.y;
        data->sprites_arr[i].distance = sqrt(diff.x * diff.x + diff.y * diff.y);
        if (data->sprites_arr[i].distance < 0.8)
        {
            data->sprites_arr[i].is_active = false;
            data->sprites_nb--;
        }
        i++;
    }
}

void    sort_sprites(t_data *data)
{
    int i;
    int j;
    int max;
    t_sprite temp;

    i = 0;
    while (i < data->sprites_nb - 1)
    {
        max = i;
        j = i + 1;
        while (j < data->sprites_nb)
        {
            if (data->sprites_arr[j].distance > data->sprites_arr[max].distance)
                max = j;
            j++;
        }
        if (max != i)
        {
            temp = data->sprites_arr[i];
            data->sprites_arr[i] = data->sprites_arr[max];
            data->sprites_arr[max] = temp;
        }
        i++;
    }
}

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
    // top and bottom 
    data->sprites_arr[i].draw_start.y = data->sprites_arr[i].sprite_size.y / 2 + data->w_height / 2 - (int)(data->sprites_arr[i].perp_dist * data->sprites_arr[i].sprite_size.y);
    if (data->sprites_arr[i].draw_start.y < 0)
        data->sprites_arr[i].draw_start.y = 0;
    data->sprites_arr[i].draw_end.y = data->sprites_arr[i].sprite_size.y / 2 + data->w_height / 2;
    if (data->sprites_arr[i].draw_end.y >= data->w_height)
        data->sprites_arr[i].draw_end.y = data->w_height - 1;
   
    // left and right sides

    data->sprites_arr[i].draw_start.x = data->sprites_arr[i].sprite_size.x / 2 + data->sprites_arr[i].screen_pos.x  - (int)(data->sprites_arr[i].perp_dist * data->sprites_arr[i].sprite_size.x);
    if (data->sprites_arr[i].draw_start.x < 0)
        data->sprites_arr[i].draw_start.x = 0;
    data->sprites_arr[i].draw_end.x = data->sprites_arr[i].sprite_size.x / 2 + data->sprites_arr[i].screen_pos.x;
    if (data->sprites_arr[i].draw_end.x >= data->w_width)
        data->sprites_arr[i].draw_end.x = data->w_width - 1; 
}

int get_pixel_color_from_xpm(int x, int y, t_data *data, int current_slice)
{
    int pixel_offset;
    int color;
    
    pixel_offset = (y * data->sprites[current_slice].line_length) + (x * (data->sprites[current_slice].bits_per_pixel / 8));
    color = *(int *)(data->sprites[current_slice].addr + pixel_offset);
    return (color);
}

void    update_sprite_frame(t_data *data, int i)
{
    data->sprites_arr[i].frame_counter++;
    if (data->sprites_arr[i].frame_counter >= 8)
    {
        data->sprites_arr[i].frame_counter = 0;
        data->sprites_arr[i].current_slice = (data->sprites_arr[i].current_slice + 1) % 8;
    }
}

void    put_sprite_pxl(t_data *data, int i)
{
    int     stripe;
    int     y;
    int     d;
    t_ivec  tex;
    
    stripe = data->sprites_arr[i].draw_start.x;
    while (stripe < data->sprites_arr[i].draw_end.x)
    {
        if (data->sprites_arr[i].perp_dist > 0 && stripe >= 0 
            && stripe < data->w_width && data->sprites_arr[i].perp_dist < data->zbuffer[stripe] + 0.8)
            tex.x = (int)((stripe - (-data->sprites_arr[i].sprite_size.x / 2 + data->sprites_arr[i].screen_pos.x)) * 32 / data->sprites_arr[i].sprite_size.x);     
        y = data->sprites_arr[i].draw_start.y;
        while (y < data->sprites_arr[i].draw_end.y)
        {
           d = (y - data->sprites_arr[i].draw_start.y) * 256 - data->w_height * 128 + data->sprites_arr[i].sprite_size.y * 128;
           tex.y = ((d * 32) / data->sprites_arr[i].sprite_size.y) / 256;
		    if (tex.x >= 0 && tex.x < 32 && tex.y >= 0 && tex.y < 32)
        	{
            	data->sprites_arr[i].color = get_pixel_color_from_xpm(tex.x, tex.y, data, data->sprites_arr[i].current_slice);
                if ((data->sprites_arr[i].color & 0x00FFFFFF) != 0x000000)
                    ft_mlx_pixel_put(&data->img, stripe, y, data->sprites_arr[i].color);
            }
            y++;
        }
        stripe++;
    }
}

int    draw_sprite(t_data *data)
{
    int i;

    i = 0;
    if (data->sprites_nb)
    {
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
    }
    return (0);
}
