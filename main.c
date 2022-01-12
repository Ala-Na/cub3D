/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:21:33 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/12 18:12:22 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->map = 0;
	data->map_info.temp_h = 0;
	data->map_info.temp_w = 0;
	data->map_info.player_orientation = 0;
	data->map_info.player_height = 0;
	data->map_info.player_width = 0;
	data->texture.no_file = 0;
	data->texture.so_file = 0;
	data->texture.we_file = 0;
	data->texture.ea_file = 0;
	data->texture.f_file = 0;
	data->texture.c_file = 0;
	data->texture.temp = 0;
	data->texture.flag_map = 0;
}

int	main(int argc, char **argv)
{
	t_data data;

	if (argc == 2)
	{
		init_data(&data);
		get_info_map(argv[1], &data);
		check_file(argv[1], &data);
		check_map(&data);
		free_everything(&data);
	}
	else
		ft_putstr(ERROR_NB_ARGUMENT);
	return (0);
}

//TODO check => optimiser la partie get colour
//	perror("ERROR"); Permet de prnt avec ERROR au debut
//	Est ce qu on utilise calloc au lieu de malloc ?
