/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:56:19 by fmonbeig          #+#    #+#             */
/*   Updated: 2022/01/13 21:10:37 by anadege          ###   ########.fr       */
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

void	check_close(int height, t_data *data)
{
	int	width;

	width = -1;
	while(data->map[height][++width])
	{
		if (data->map[height][width] != '1')
		{
			if (data->map[height + 1][width] == '\0' ||
					data->map[height -1][width] == '\0')
				ft_error(ERROR_MAP_NOT_CLOSE, data);
		}
	}
}

static void	get_player_direction(char c, t_data *data)
{
	if (c == 'N')
	{
		data->player->dir.x = 0;
		data->player->dir.y = -1;
	}
		if (c == 'S')
	{
		data->player->dir.x = 0;
		data->player->dir.y = 1;
	}
		if (c == 'E')
	{
		data->player->dir.x = 1;
		data->player->dir.y = 0;
	}
		if (c == 'W')
	{
		data->player->dir.x = -1;
		data->player->dir.y = 0;
	}
}

static void	get_player_camera_plane(char c, t_data *data)
{
	if (c == 'N')
	{
		data->player->cam_plane.x = 0.66;
		data->player->cam_plane.y = 0;
	}
		if (c == 'S')
	{
		data->player->cam_plane.x = -0.66;
		data->player->cam_plane.y = 0;
	}
		if (c == 'E')
	{
		data->player->cam_plane.x = 0;
		data->player->cam_plane.y = 0.66;
	}
		if (c == 'W')
	{
		data->player->cam_plane.x = 0;
		data->player->cam_plane.y = -0.66;
	}
}

void	get_player_position(int height, t_data *data)
{
	static int	flag = 0;
	int			width;

	width = -1;
	while(data->map[height][++width])
	{
		if (data->map[height][width] == 'N' ||
				data->map[height][width] == 'S' ||
				data->map[height][width] == 'E' ||
				data->map[height][width] == 'W' )
		{
			if (flag == 1)
				ft_error(ERROR_TWO_PLAYERS, data);
			data->player->pos.y = height + 0.5;
			data->player->pos.x = width + 0.5;
			get_player_direction(data->map[height][width], data);
			get_player_camera_plane(data->map[height][width], data);
			flag = 1;
		}
	}
}
