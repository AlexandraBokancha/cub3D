/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:34:23 by dbaladro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/10 12:43:16 by alexandra        ###   ########.fr       */
=======
/*   Updated: 2024/09/17 02:35:16 by dbaladro         ###   ########.fr       */
>>>>>>> door
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

<<<<<<< HEAD
int	load_texture_bonus(t_data *data, char **texture_name)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	while (i < 4)
	{
		data->texture[i].img = mlx_xpm_file_to_image(data->mlx,
			texture_name[i], &x, &y);
		data->texture[i].addr = mlx_get_data_addr(data->texture[i].img,
			&data->texture[i].bits_per_pixel, &data->texture[i].line_length,
			&data->texture[i].endian);
		i++;
	}
	data->texture[i].img = mlx_xpm_file_to_image(data->mlx,
		PLAYER_TEXTURE, &x, &y);
	data->texture[i].addr = mlx_get_data_addr(data->texture[i].img,
		&data->texture[i].bits_per_pixel, &data->texture[i].line_length,
		&data->texture[i].endian);
	return (0);
}
=======
/* ************************************************************************** */
/*                          FOR TESTING PURPOSE ONLY                          */
/* ************************************************************************** */


char	*test_map_001[4] =
{
	"111",
	"1N1",
	"111",
	NULL
};

char	*test_map_002[11] =
{
	"1111111111",
	"1000000001",
	"1000000001",
	"1010000101",
	"1001011001",
	"1000N00001",
	"1001010001",
	"1010000101",
	"1000000001",
	"1111111111",
	NULL
};

char	*test_map_003[11] =
{
	"111111111111111111111",
	"100000000000000000o01",
	"100000000E0O00000O0c1",
	"101000010000000000c01",
	"1001c110000000000c1O1",
	"1000000000000c0oo0o01",
	"1001C1000000Oocccco11",
	"101000000000OOOOcccO1",
	"100000000000000000001",
	"111111111111111111111",
	NULL
};

char	*test_map_004[14] =
{
	"111111111111111",
	"100000000000001",
	"100000000000001",
	"100O0000000C001",
	"100000000000001",
	"100000000000001",
	"100000000000001",
	"100000000000001",
	"100000000000001",
	"1W0o0000000o001",
	"100000000000001",
	"100000000000001",
	"111111111111111",
	NULL
};

char	*test_map_005[8] =
{
	"11111111",
	"100S0001",
	"10c00O01",
	"10000001",
	"10o00C01",
	"10000001",
	"11111111",
	NULL
};

char	*texture[5] = 
{
	"./assets/tile110.xpm",
	"./assets/tile068.xpm",
	"./assets/tile073.xpm",
	"./assets/tile085.xpm",
	NULL
};

char	**copy_map(char *test_map[])
{
	char	**map;
	int		i;
	int		tab_size;

	tab_size = ft_tab_size((char **)test_map);
	map = (char **)malloc(sizeof(char *) * (tab_size + 1));
	if (!map)
		return (print_error("malloc", errno), NULL);
	i = 0;
	while (i < tab_size)
	{
		map[i] = ft_strndup(test_map[i], ft_strlen(test_map[i]));
		i++;
	}
	map[tab_size] = NULL;
	return (map);
}
/* ************************************************************************** */
/*                           END OF TESTING FUNCTION                          */
/* ************************************************************************** */
>>>>>>> door

/**
 * @brief Return the map size
 *
 * This function create a new t_ivec an store the map size
 * max X and Max Y
 *
 * @param	map	The map
 * @return  A vector containing the map size 
 */
t_ivec	get_map_size(char *map[])
{
	t_ivec	map_block;
	int		x;
	int		y;

	map_block = init_ivec(0, 0);
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
			y++;
		if (y > map_block.y)
			map_block.y = y;
		x++;
	}
	map_block.x = x;
	return (map_block);
}

<<<<<<< HEAD
void	init_tab_texture_bonus(t_data *data)
{
	data->texture_tab[0] = data->textures.N_path;
	data->texture_tab[1] = data->textures.S_path;
	data->texture_tab[2] = data->textures.W_path;
	data->texture_tab[3] = data->textures.E_path;
	data->texture_tab[4] = NULL;
}
void	load_mlx(t_data *data)
{
	mlx_key_hook(data->window, &key_hook, data);
=======
void	init_mouse(t_data *data)
{
	mlx_mouse_hide(data->mlx, data->window);
	mlx_mouse_move(data->mlx, data->window, data->w_width / 2,
		data->w_height / 2);
}


int	main()
{
	t_data	*data;

	data = init_cub();
	if (!data)
		return (1);
	// PLAYER, COLOR AND CAMERA SETUP HAVE TO BE DONE IN THE INIT AFTER PARSING
	data->map = get_map(test_map_003);
	data->map_size = get_map_size(data->map);
	data->ceiling_color = 0x00645832;
	data->floor_color = 0x00474747;
	// MINIMAP
	init_player(data);
	data->player.x = 2;
	data->player.y = 7;
	data->minimap = init_minimap(data);

	// ROTATE_BONUS
	init_mouse(data);

	// HOOK EVERYTHING
	// mlx_key_hook(data->window, &key_hook, data);
>>>>>>> door
	mlx_hook(data->window, 2, (1L << 0), &key_hook, data);
	mlx_hook(data->window, ON_DESTROY, 0, &exit_cub, data);
	mlx_hook(data->window, ON_MOUSEMOVE, (1L<<6), &camera_move, data); // Mouse movment detection
	mlx_loop_hook(data->mlx, &render, data);
	mlx_loop(data->mlx);
	mlx_do_sync(data->mlx);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (write(2, "Error. Wrong number of arguments\n", 34), 1);
	data = init_cub();
	if (!data)
		return (1);
	data = init_map_bonus(data, av[1]);
	if (!data)
		return (1);
	init_player(data);
	init_tab_texture_bonus(data);
	load_texture_bonus(data, data->texture_tab);
	data->minimap = init_minimap(data);
	data->sprites_nb = count_sprites_nb(data);
	if (data->sprites_nb)
	{
		data->sprites_arr = init_sprites(data);
		init_tab_sprites(data);
		load_sprite_image(data, data->sprites_tab);	
	}
	load_mlx(data);
	free_cub(data);
	return (0);
}
