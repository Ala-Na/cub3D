/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:21:33 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/13 18:21:01 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_data(t_data *data)
{
	data->mlx = mlx_init(); 
	//TODO if NULL
	data->map_info = malloc(sizeof(t_map));
	data->texture = malloc(sizeof(t_texture));
	data->player = malloc(sizeof(t_player));
	data->map = 0;
	data->map_info->height = 0;
	data->map_info->width = 0;
	data->texture->no_file = 0;
	data->texture->so_file = 0;
	data->texture->we_file = 0;
	data->texture->ea_file = 0;
	data->texture->f_file = 0;
	data->texture->c_file = 0;
	data->texture->temp = 0;
	data->texture->flag_map = 0;
	data->player->dir.x = 0;
	data->player->dir.y = 0;
}

static void	init_img(t_data *data)
{
	data->texture->no.img = mlx_xpm_file_to_image(data->mlx, data->texture->no_file,
			&data->texture->no.width, &data->texture->no.height);
	data->texture->no.addr = mlx_get_data_addr(data->texture->no.img, &data->texture->no.bits_per_pixel,
			&data->texture->no.line_length, &data->texture->no.endian);
	if(!data->texture->no.img)
		ft_error(ERROR_IMG, data);
	data->texture->so.img = mlx_xpm_file_to_image(data->mlx, data->texture->so_file,
			&data->texture->so.width, &data->texture->so.height);
	data->texture->so.addr = mlx_get_data_addr(data->texture->so.img, &data->texture->so.bits_per_pixel,
			&data->texture->so.line_length, &data->texture->so.endian);
	if(!data->texture->so.img)
		ft_error(ERROR_IMG, data);
	data->texture->ea.img = mlx_xpm_file_to_image(data->mlx, data->texture->ea_file,
			&data->texture->ea.width, &data->texture->ea.height);
	data->texture->ea.addr = mlx_get_data_addr(data->texture->ea.img, &data->texture->ea.bits_per_pixel,
			&data->texture->ea.line_length, &data->texture->ea.endian);
	if(!data->texture->ea.img)
		ft_error(ERROR_IMG, data);
	data->texture->we.img = mlx_xpm_file_to_image(data->mlx, data->texture->we_file,
			&data->texture->we.width, &data->texture->we.height);
	data->texture->we.addr = mlx_get_data_addr(data->texture->we.img, &data->texture->we.bits_per_pixel,
			&data->texture->we.line_length, &data->texture->we.endian);
	if(!data->texture->we.img)
		ft_error(ERROR_IMG, data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		init_data(&data);
		get_info_map(argv[1], &data);
		check_file(argv[1], &data);
		check_map(&data);
		init_img(&data);
		launch_engine(&data);
		free_everything(&data);
	}
	else
		ft_putstr(ERROR_NB_ARGUMENT);
	return (0);
}

//TODO Je crois qu'il faut proteger la minilibx car segfault si porgramme lancer avec un env vide (env -i)
