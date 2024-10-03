/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albokanc <albokanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:57:45 by alexandra         #+#    #+#             */
/*   Updated: 2024/10/03 17:36:13 by albokanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* comment dessiner un sprite 
        
        ETAPES:

1. calculate the distance of sprite to the player 
2. calculate sprite screen position
3. calculate size of the sprite
4. initialiser le debut et la fin de draw
5. put pxl

*/

/**
 * @brief Projects a sprite onto the 2D camera plane.
 *
 * This function calculates the position of the sprite
 * relative to the player's position and projects it 
 * onto the camera plane using the inverse of the 2x2 camera matrix.
 * The sprite's screen position and its 
 * perpendicular distance from the player are stored for later use.
 * 
 */
void	sprite_to_camera(t_data *data, int i)
{
	t_dvec	relative_pos;
	t_dvec	transform;
	double	inv;

	relative_pos.x = data->sprites_arr[i].sprite_pos.x + 0.5 - data->player.x;
	relative_pos.y = data->sprites_arr[i].sprite_pos.y + 0.5 - data->player.y;
	inv = 1.0 / (data->camera_plane.x * data->direction.y - \
		data->direction.x * data->camera_plane.y);
	transform.x = inv * (data->direction.y * relative_pos.x - \
		data->direction.x * relative_pos.y);
	transform.y = inv * (-data->camera_plane.y * relative_pos.x \
		+ data->camera_plane.x * relative_pos.y);
	data->sprites_arr[i].screen_pos.x = (int)((data->w_width / 2) \
		* (1 + transform.x / transform.y));
	data->sprites_arr[i].perp_dist = transform.y;
}

/**
 * @brief Calculates the size of the sprite on the screen.
 *
 * This function computes the height and width of the sprite based
 * on its distance from the player.
 * The sprite is assumed to be square (32x32pxl);
 *
 */
void	sprite_size(t_data *data, int i)
{
	data->sprites_arr[i].sprite_size.y = abs((int)(data->w_height \
		/ data->sprites_arr[i].perp_dist));
	data->sprites_arr[i].sprite_size.x = abs((int)(data->w_height \
		/ data->sprites_arr[i].perp_dist));
}

/**
 * @brief Initializes the coordinates for drawing the sprite.
 *
 * This function calculates the top, bottom, left, 
 * and right positions of the sprite on the screen.
 *
 */
void	init_draw(t_data *data, int i)
{
	data->sprites_arr[i].draw_start.y = data->sprites_arr[i].sprite_size.y \
		/ 2 + data->w_height / 2 - (int)(data->sprites_arr[i].perp_dist * \
		data->sprites_arr[i].sprite_size.y);
	if (data->sprites_arr[i].draw_start.y < 0)
		data->sprites_arr[i].draw_start.y = 0;
	data->sprites_arr[i].draw_end.y = data->sprites_arr[i].sprite_size.y \
		/ 2 + data->w_height / 2 ;
	data->sprites_arr[i].draw_start.x = data->sprites_arr[i].sprite_size.x \
		/ 2 + data->sprites_arr[i].screen_pos.x \
		- (int)(data->sprites_arr[i].perp_dist \
		* data->sprites_arr[i].sprite_size.x);
	if (data->sprites_arr[i].draw_start.x < 0)
		data->sprites_arr[i].draw_start.x = 0;
	data->sprites_arr[i].draw_end.x = data->sprites_arr[i].sprite_size.x \
		/ 2 + data->sprites_arr[i].screen_pos.x;
	if (data->sprites_arr[i].draw_end.x >= data->w_width)
		data->sprites_arr[i].draw_end.x = data->w_width - 1;
}

/**
 * @brief Draws the pixels of the sprite onto the screen.
 *
 * This function iterates over the horizontal stripes of the sprite and
 * draws the sprite's pixels onto the screen.
 * It checks the sprite's perpendicular distance from
 * the player to determine whether it 
 * should be drawn in front of the background (walls and floor).
 * The texture's X coordinate is calculated
 * for each stripe.
 *
 */
void	put_sprite_pxl(t_data *data, int i)
{
	int	stripe;

	stripe = data->sprites_arr[i].draw_start.x;
	while (stripe < data->sprites_arr[i].draw_end.x)
	{
		data->tex.x = (int)( 256 * (stripe - \
			(-data->sprites_arr[i].sprite_size.x / \
			2 + data->sprites_arr[i].screen_pos.x)) * 32 \
			/ data->sprites_arr[i].sprite_size.x) / 256;
		if (data->sprites_arr[i].perp_dist > 0 && stripe > 0 \
			&& stripe < data->w_width && \
			data->sprites_arr[i].perp_dist < data->zbuffer[stripe])
		{
			process_sprite_y(data, i, stripe);
		}
		stripe++;
	}
}

/**
 * @brief Draws all active sprites in the game.
 *
 * This function loops through all sprites, 
 * sorting them by distance from the player to ensure that 
 * closer sprites are drawn in front of farther ones.
 * It projects each sprite onto the camera plane, 
 * calculates its size, initializes its draw positions,
 * and renders it on the screen.
 *
 */
void	draw_sprite(t_data *data)
{
	int	i;

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
}
