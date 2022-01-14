/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:21:33 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/14 18:12:31 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	security_init(t_data *data)
{
	data->mlx = NULL;
	data->screen_width = -1;
	data->screen_height = -1;
	data->win = NULL;
	data->map = NULL;
	data->map_info = NULL;
	data->texture = NULL;
	data->player = NULL;
	data->img = NULL;
}

static void	init_malloc_structure(t_data *data)
{
	data->map_info = malloc(sizeof(t_map));
	if (!data->map_info)
		ft_error(ERROR_MALLOC, data);
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		ft_error(ERROR_MALLOC, data);
	data->texture = malloc(sizeof(t_texture));
	if (!data->texture)
		ft_error(ERROR_MALLOC, data);
	data->texture->no.img = NULL;
	data->texture->so.img = NULL;
	data->texture->ea.img = NULL;
	data->texture->we.img = NULL;
}

static void	init_data(t_data *data)
{
	security_init(data);
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		ft_error(ERROR_MLX, data);
	init_malloc_structure(data);
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
	}
	else
		ft_putstr(ERROR_NB_ARGUMENT);
	return (0);
}
