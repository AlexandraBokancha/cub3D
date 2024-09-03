/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:57:45 by alexandra         #+#    #+#             */
/*   Updated: 2024/09/03 21:23:51 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* comment dessiner un sprite (on le fait apres avoir dessine les murs et le sol)
        
        ETAPES:

1. calculate the distance of sprite to the player 
2. calculate sprite screen position
3. calculate size of the sprite
*/

void    load_sprite_image(t_data *data)
{
    int x;
    int y;
    
	data->sprite.slices[0] = mlx_xpm_file_to_image(data->mlx, "sprites/coin_1.xpm", &x, &y);
	data->sprite.slices[1] = mlx_xpm_file_to_image(data->mlx, "sprites/coin_2.xpm", &x, &y);
	data->sprite.slices[2] = mlx_xpm_file_to_image(data->mlx, "sprites/coin_3.xpm", &x, &y);
	data->sprite.slices[3] = mlx_xpm_file_to_image(data->mlx, "sprites/coin_4.xpm", &x, &y);
	data->sprite.slices[4] = mlx_xpm_file_to_image(data->mlx, "sprites/coin_5.xpm", &x, &y);
	data->sprite.slices[5] = mlx_xpm_file_to_image(data->mlx, "sprites/coin_6.xpm", &x, &y);
	data->sprite.slices[6] = mlx_xpm_file_to_image(data->mlx, "sprites/coin_7.xpm", &x, &y);
	data->sprite.slices[7] = mlx_xpm_file_to_image(data->mlx, "sprites/coin_8.xpm", &x, &y);
}

// calculate the difference between the sprite's and player's position on the map.
// dist euclidean formula = sqrt(dx^2 + dy^2)

void    dist_from_player(t_data *data)
{
    t_dvec  diff;

    diff.x = data->sprite.sprite_pos.x - data->player.x;
    diff.y = data->sprite.sprite_pos.y - data->player.y;
    data->sprite.distance = sqrt(diff.x * diff.x + diff.y * diff.y);
}
// project the sprite on the camera plane (in 2D):
// substract the player position from the sprite positin
// multiply the result with the inverse of the 2x2 camera matrix
// player direction vector: data->direction;
// camera plane vector: data->camera_plane;
// inverse matrix formula:
// 1 / (dir.x * plane - dir.y * plane.x) X (plane.y - dir.y, -plane.x dir.x)

void    sprite_to_camera(t_data *data)
{
    t_dvec  relative_pos;
    t_dvec  transform;
    double  inv;
    
    relative_pos.x = data->sprite.sprite_pos.x - data->player.x;
    relative_pos.y = data->sprite.sprite_pos.y - data->player.y;
    inv = 1.0 / (data->camera_plane.x * data->direction.y - data->direction.x * data->camera_plane.y);
    transform.x = inv * (data->direction.y * relative_pos.x- data->direction.x * relative_pos.y);
    transform.y = inv * (-data->camera_plane.y * relative_pos.x+ data->camera_plane.x * relative_pos.y);
    data->sprite.screen_pos.x = (int)((data->w_width / 2) * (1 + transform.x / transform.y)); 
    data->sprite.perp_dist = transform.y;
}
// calculate the height of the sprite on the screen (in our case
// the sprite is square (32 x 32 pix))

void    sprite_size(t_data *data)
{
    data->sprite.sprite_size.y = abs((int)(data->w_height / data->sprite.perp_dist) / 1);
    data->sprite.sprite_size.x = abs((int)(data->w_height / data->sprite.perp_dist) / 1);
}

// calculate the top and bottom of the sprite 
// calculate the left and right sides of the sprite 

void    init_draw(t_data *data)
{
    // top and bottom 
    
    data->sprite.draw_start.y = -data->sprite.sprite_size.y / 2 + data->w_height / 2;
    if (data->sprite.draw_start.y < 0)
        data->sprite.draw_start.y = 0;
    data->sprite.draw_end.y = data->sprite.sprite_size.y / 2 + data->w_height / 2;
    if (data->sprite.draw_end.y >= data->w_height)
        data->sprite.draw_end.y = data->w_height - 1;
    
    // left and right sides

    data->sprite.draw_start.x = -data->sprite.sprite_size.x / 2 + data->sprite.screen_pos.x;
    if (data->sprite.draw_start.x < 0)
        data->sprite.draw_start.x = 0;
    data->sprite.draw_end.x = data->sprite.sprite_size.x / 2 + data->sprite.screen_pos.x;
    if (data->sprite.draw_end.x >= data->w_width)
        data->sprite.draw_end.x = data->w_width - 1;    
}

int get_pixel_color_from_xpm(int x, int y, void *img)
{
   t_img img_sprite;
   int pixel_offset;
   int color;
   
    
    img_sprite.addr = mlx_get_data_addr(img, &img_sprite.bits_per_pixel, &img_sprite.line_length, &img_sprite.endian);
    pixel_offset = (y * img_sprite.line_length) + (x * (img_sprite.bits_per_pixel / 8));
    color = *(int *)(img_sprite.addr + pixel_offset);
    return (color);
}

void    update_sprite_frame(t_data *data)
{
    int frame_counter;
    int tmp_current;

    frame_counter = 0;
    tmp_current = 0;
    frame_counter++;
    if (frame_counter >= 8)
    {
        frame_counter = 0;
        tmp_current = (tmp_current + 1) % 8;
    }
    data->sprite.current_slice = tmp_current;
}

void    put_sprite_pxl(t_data *data)
{
    int     stripe;
    int     y;
    int     d;
    t_ivec  tex;
    
    stripe = data->sprite.draw_start.x;
    while (stripe < data->sprite.draw_end.x)
    {
        if (data->sprite.perp_dist > 0 && stripe >= 0 
            && stripe < data->w_width && data->sprite.perp_dist < data->zbuffer[stripe])
            tex.x = (int)((stripe - (-data->sprite.sprite_size.x / 2 + data->sprite.screen_pos.x)) * 32 / data->sprite.sprite_size.x);
        y = data->sprite.draw_start.y;
        while (y < data->sprite.draw_end.y)
        {
           d = (y - data->sprite.draw_start.y) * 256 - data->w_height * 128 + data->sprite.sprite_size.y * 128;
           tex.y = ((d * 32) / data->sprite.sprite_size.y) / 256;  
            data->sprite.color = get_pixel_color_from_xpm(tex.x, tex.y, data->sprite.slices[data->sprite.current_slice]);
            if (data->sprite.color != TRANSPARENT)
                ft_mlx_pixel_put(&data->img, stripe, y, data->sprite.color);
            y++;
        }
        stripe++;
    }
}

int    draw_sprite(t_data *data)
{  
    dist_from_player(data);
    sprite_to_camera(data);
    sprite_size(data);
    init_draw(data);
    load_sprite_image(data);
    update_sprite_frame(data);
    put_sprite_pxl(data);
    return (0);
}