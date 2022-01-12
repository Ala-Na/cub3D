/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map 2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:56:19 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/12 16:56:27 by fmonbeig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_one(char *line, t_data *data)
{
	int	i;

	i = 0;
	if (line[0] != '1')
		ft_error(ERROR_MAP_NOT_CLOSE, data);
	while(line[i])
		++i;
	if (line[i - 1] != '1')
		ft_error(ERROR_MAP_NOT_CLOSE, data);
}

// void	check_close(int height, t_data *data)
// {
// 	int	width;

// 	width = -1;
// 	while(data->map[height][++width])
// 	{
// 		if (data->map[height][width] != 1)
// 		{

// 		}
// 		ft_error(ERROR_MAP_NOT_CLOSE, data);
// 	}
// }

void	get_player_position(int height, t_data *data)
{
	static int	flag = 0;
	int	width;

	width = -1;
	while(data->map[height][++width])
	{
		if (data->map[height][width] == 'N' ||
				data->map[height][width] == 'S' ||
				data->map[height][width] == 'E' ||
				data->map[height][width] == 'O' )
		{
			if (flag == 1)
				ft_error(ERROR_TWO_PLAYERS, data);
			data->map_info.player_height = height;
			data->map_info.player_width = width;
			data->map_info.player_orientation = data->map[height][width];
			flag = 1;
		}
	}
}
